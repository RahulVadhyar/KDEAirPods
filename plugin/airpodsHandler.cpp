/*
    SPDX-FileCopyrightText: 2024 Rahul Vadhyar vadhyarrahul@gmail.com>
    SPDX-License-Identifier: AGPL-3.0-or-later
*/

#include "airpodsHandler.hpp"

AirpodsHandler::AirpodsHandler(QObject *parent)
    : QObject(parent)
{
    // auto devices = this->devicesInfoFetcher.GetDevices();
    // if(devices.size() == 0){
    //     this->connected = false;
    // } else {
    //     this->connected = true;
    // }

    // this->device = this->devicesInfoFetcher.GetActiveDevice();
    // this->deviceName = QString::fromStdString(this->device->GetName());
    // this->deviceAddress = QString::fromStdString(this->device->GetAddress());
    // this->ancStatus = (int)this->device->GetAncMode();
}

QString AirpodsHandler::getDeviceName() const { 
    return deviceName; 
}

void AirpodsHandler::setDeviceName(const QString &name) { 
    if (deviceName != name) {
        deviceName = name; 
        Q_EMIT deviceNameChanged(); 
    }
}

QString AirpodsHandler::getDeviceAddress() const { 
    return deviceAddress; 
}

void AirpodsHandler::setDeviceAddress(const QString &address) { 
    if (deviceAddress != address) {
        deviceAddress = address; 
        Q_EMIT deviceAddressChanged(); 
    }
}

bool AirpodsHandler::getConnected() const { 
    return connected; 
}
void AirpodsHandler::setConnected(bool status) { 
    if (connected != status) {
        connected = status; 
        Q_EMIT connectedChanged(); 
    }
}

int AirpodsHandler::getAncStatus() const { 
    return ancStatus; 
}
void AirpodsHandler::setAncStatus(int status) { 
    if (ancStatus != status) {
        ancStatus = status; 
        Q_EMIT ancStatusChanged(); 
    }
}

void AirpodsHandler::connectDevice() {
    // this->device->Connect();
    // this->connected = true;
    // Q_EMIT connectedChanged();
}

void AirpodsHandler::disconnectDevice() {
    // this->device->Disconnect();
    // this->connected = false;
    // Q_EMIT connectedChanged();
}