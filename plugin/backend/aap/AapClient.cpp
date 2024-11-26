//
// MagicPodsCore
// https://github.com/steam3d/MagicPodsCore
//
// Copyright: 2020-2024 Aleksandr Maslov <https://magicpods.app> & Andrei Litvintsev <a.a.litvintsev@gmail.com>
// License: AGPL-3.O 
//

#include "AapClient.h"

#include "Logger.h"

#include <thread>
#include <sys/ioctl.h>
#include <fcntl.h>

AapClient::AapClient(const std::string& address) : _address{address} {
}

void AapClient::Start() {
    std::lock_guard lockGuard{_startStopMutex};

    if (_isStarted)
        return;
    _isStarted = true;

    struct sockaddr_l2 addr = { 0 };

    LOG_RELEASE("Start Bluetooth client, server addr %s", _address.c_str());

    /* allocate a socket */
    _socket = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);

    /* set the outgoing connection parameters, server's address and port number */
    addr.l2_family = AF_BLUETOOTH;								/* Addressing family, always AF_BLUETOOTH */
    addr.l2_psm = htobs(0x1001);					/* server's port number */
    str2ba(_address.c_str(), &addr.l2_bdaddr);		/* server's Bluetooth Address */

    /* connect to server */
    if(connect(_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("failed to connect");
        exit(1);
    }
    LOG_RELEASE("connected...");

    std::thread thread([this]() {           
        unsigned char buffer[1024];
        std::vector<unsigned char> vectorBuffer(1024); // optimize
        while(_isStarted) {
            memset(buffer, 0, sizeof(buffer));
            ssize_t receivedBytesLength = recv(_socket, buffer, sizeof(buffer), 0);
            if (receivedBytesLength >= 0) {
                // std::cout << "Packet: " << bytesToHexString(buffer, receivedBytesLength) << std::endl;
                // std::cout << "Length: " << receivedBytesLength << std::endl;
                /*
                In ear detection:
                for airpods pro 2 only:
                get 2 packets, one is:
                040004000600000{0 or 1} -> 0 is in ear, 1 is out ear, len 8
                the next packet is for ANC
                or this one(means that the airpods switch sides or smthg)
                0400040006000100
                */

                LOG_DEBUG("o(%zu):%s", receivedBytesLength, bytesToHexString(buffer, receivedBytesLength).c_str());
                vectorBuffer.assign(buffer, buffer + receivedBytesLength);
                InEarWatcher->ProcessBytes(vectorBuffer);
                BatteryWatcher->ProcessBytes(vectorBuffer);
                AncWatcher->ProcessBytes(vectorBuffer);
            }
            else if (receivedBytesLength < 0) {
                break;
            }
            else {
                LOG_DEBUG("then");
            }
        }

        LOG_DEBUG("Thread stopped");
    });
    thread.detach();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    SendRequest(AapInit{});
    std::this_thread::sleep_for(std::chrono::seconds(1));
    SendRequest(AapEnableNotifications{NotificationsMode::Unknown1});
}

void AapClient::Stop() {
    std::lock_guard lockGuard{_startStopMutex};

    if (!_isStarted)
        return;
    _isStarted = false;

    close(_socket);

    LOG_RELEASE("Stop Bluetooth client, server addr %s", _address.c_str());
}

void AapClient::SendRequest(const AapRequest& aapRequest) {
    auto requestData = aapRequest.Request();
    ssize_t sendedBytesLength = send(_socket, requestData.data(), requestData.size(), 0);
    LOG_DEBUG("i(%zu):%s", requestData.size(), bytesToHexString(requestData.data(), requestData.size()).c_str());
}
