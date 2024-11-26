/*
    SPDX-FileCopyrightText: 2024 Rahul Vadhyar vadhyarrahul@gmail.com>
    SPDX-License-Identifier: AGPL-3.0-or-later
*/

#include "airpodsHandler.hpp"
#include "DevicesInfoFetcher.h"
#include <QQmlEngine>
#include <iostream>
#include <regex>
AirpodsHandler::AirpodsHandler(QObject *parent)
    : QObject(parent)
{
    this->devicesInfoFetcher = std::make_shared<DevicesInfoFetcher>();
    this->devicesInfoFetcher->GetOnActiveDeviceChangedEvent().Subscribe([this](size_t listenerId, const std::shared_ptr<Device>& newDevice) {
        this->handleActiveDeviceEvent(newDevice);
    });
    auto devices = this->devicesInfoFetcher->GetDevices();
    if (devices.size() == 0){
        return;
    }
    for(auto device : devices){
        if (device->GetConnected()){
            this->handleActiveDeviceEvent(device);
            break;
        }
    }
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
    if (ancStatus != status && this->connected) {
            this->device->SetAnc(DeviceAncMode(status));
            ancStatus = status; 
            Q_EMIT ancStatusChanged(); 
    }
}


void AirpodsHandler::connectDevice() {
    if(!this->device){
        return;
    }
    this->devicesInfoFetcher->Connect(this->device->GetAddress());
}

void AirpodsHandler::disconnectDevice() {
    if(this->connected && this->device){
        this->device->Disconnect();
    }
}

int AirpodsHandler::getLeftBattery() const { 
    return leftBattery; 
}

int AirpodsHandler::getRightBattery() const { 
    return rightBattery; 
}

int AirpodsHandler::getCaseBattery() const { 
    return caseBattery; 
}

bool AirpodsHandler::getLeftCharging() const { 
    return leftCharging; 
}

bool AirpodsHandler::getRightCharging() const { 
    return rightCharging; 
}

bool AirpodsHandler::getCaseCharging() const { 
    return caseCharging; 
}

bool AirpodsHandler::getIsInEar() const { 
    return isInEar; 
}

void AirpodsHandler::updateBatteryStatuses() {
    if(!this->connected && this->device){
        return;
    }
    auto batteryStatus = this->device->GetBatteryStatus();
    this->leftBattery = batteryStatus[DeviceBatteryType::Left].Battery;
    this->rightBattery = batteryStatus[DeviceBatteryType::Right].Battery;
    this->caseBattery = batteryStatus[DeviceBatteryType::Case].Battery;
    this->leftCharging = batteryStatus[DeviceBatteryType::Left].isCharging;
    this->rightCharging = batteryStatus[DeviceBatteryType::Right].isCharging;
    this->caseCharging = batteryStatus[DeviceBatteryType::Case].isCharging;
    Q_EMIT leftBatteryChanged();
    Q_EMIT rightBatteryChanged();
    Q_EMIT caseBatteryChanged();
    Q_EMIT leftChargingChanged();
    Q_EMIT rightChargingChanged();
    Q_EMIT caseChargingChanged();
}

void AirpodsHandler::handleBatteryEvent(size_t id, std::map<DeviceBatteryType, DeviceBatteryData> batteryStatus){
    this->leftBattery = batteryStatus[DeviceBatteryType::Left].Battery;
    this->rightBattery = batteryStatus[DeviceBatteryType::Right].Battery;
    this->caseBattery = batteryStatus[DeviceBatteryType::Case].Battery;
    this->leftCharging = batteryStatus[DeviceBatteryType::Left].isCharging;
    this->rightCharging = batteryStatus[DeviceBatteryType::Right].isCharging;
    this->caseCharging = batteryStatus[DeviceBatteryType::Case].isCharging;
    Q_EMIT leftBatteryChanged();
    Q_EMIT rightBatteryChanged();
    Q_EMIT caseBatteryChanged();
    Q_EMIT leftChargingChanged();
    Q_EMIT rightChargingChanged();
    Q_EMIT caseChargingChanged();
}

void AirpodsHandler::handleActiveDeviceEvent(std::shared_ptr<Device> newDevice){
    if(this->connected){
        this->setConnected(false);
        this->isInEar = false;
        Q_EMIT isInEarChanged();
        return;
    }
    this->device = newDevice;
    this->setConnected(newDevice->GetConnected());
    this->setDeviceAddress(QString::fromStdString(this->device->GetAddress()));
    this->setDeviceName(QString::fromStdString(this->device->GetName()));
    this->setAncStatus((int)this->device->GetAncMode());
    this->device->GetBattery().GetBatteryChangedEvent().Subscribe([this](size_t listenerId, const std::map<DeviceBatteryType, DeviceBatteryData>& data) {
        this->handleBatteryEvent(listenerId, data);
    });
    this->device->GetAnc().GetAncChangedEvent().Subscribe([this](size_t listenerId, const DeviceAncMode& data) {
        this->ancStatus = (int)data;
        Q_EMIT ancStatusChanged();
    });

    this->device->GetConnectedPropertyChangedEvent().Subscribe([this](size_t listenerId, const bool& data) {
        if(!data){
            std::cout << "Device Disconnected" << std::endl;
            this->setConnected(false);
            this->isInEar = false;
            Q_EMIT isInEarChanged();
        }
    });
    this->device->GetIsInEarChangedEvent().Subscribe([this](size_t listenerId, const bool& data) {
        this->isInEar = data;
        Q_EMIT isInEarChanged();
    });
    this->updateBatteryStatuses();
}
