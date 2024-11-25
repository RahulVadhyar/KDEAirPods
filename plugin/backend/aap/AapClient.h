//
// MagicPodsCore
// https://github.com/steam3d/MagicPodsCore
//
// Copyright: 2020-2024 Aleksandr Maslov <https://magicpods.app> & Andrei Litvintsev <a.a.litvintsev@gmail.com>
// License: AGPL-3.O 
//

#pragma once

#include "Aap.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <thread>
#include <array>
#include <memory>

class AapClient {
private:
    std::unique_ptr<AapBatteryWatcher> BatteryWatcher {std::make_unique<AapBatteryWatcher>()};
    std::unique_ptr<AapAncWatcher> AncWatcher {std::make_unique<AapAncWatcher>()};
    std::unique_ptr<AapInEarWatcher> InEarWatcher {std::make_unique<AapInEarWatcher>()};

    std::string _address{};
    int _socket{};
    bool _isStarted{false};
    
    std::mutex _startStopMutex{};

public:
    explicit AapClient(const std::string& address);

    void Start();
    void Stop();

    bool IsStarted() const {
        return _isStarted;
    }

    Event<std::map<BatteryType, BatteryWatcherData>>& GetBatteryEvent() {
        return BatteryWatcher->GetEvent();
    }

    Event<AncWatcherData>& GetAncEvent() {
        return AncWatcher->GetEvent();
    }

    Event<bool>& GetInEarEvent() {
        return InEarWatcher->GetEvent();
    }

    void SendRequest(const AapRequest& aapRequest);

private:
    std::vector<char> hexStringToBytes(const std::string& hex) {
        std::vector<char> bytes;

        for (unsigned int i = 0; i < hex.length(); i += 2) {
            std::string byteString = hex.substr(i, 2);
            char byte = (char) strtol(byteString.c_str(), NULL, 16);
            bytes.push_back(byte);
        }

        return bytes;
    }

    inline static const char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                            '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    std::string bytesToHexString(unsigned char *data, int len)
    {
        std::string s(len * 2, ' ');
        for (int i = 0; i < len; ++i) {
            s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
            s[2 * i + 1] = hexmap[data[i] & 0x0F];
        }
        return s;
    }
};