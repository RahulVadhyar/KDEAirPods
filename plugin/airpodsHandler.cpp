/*
    SPDX-FileCopyrightText: 2024 Rahul Vadhyar vadhyarrahul@gmail.com>
    SPDX-License-Identifier: AGPL-3.0-or-later
*/

#include "airpodsHandler.hpp"
#include "DevicesInfoFetcher.h"
#include <QQmlEngine>

AirpodsHandler::AirpodsHandler(QObject *parent)
    : QObject(parent)
{
    this->devicesInfoFetcher = std::make_shared<DevicesInfoFetcher>();
    auto devices = this->devicesInfoFetcher->GetDevices();
    if(devices.size() == 0){
        this->connected = false;
    } else {
        this->connected = true;
    }

    this->device = this->devicesInfoFetcher->GetActiveDevice();
    this->deviceName = QString::fromStdString(this->device->GetName());
    this->deviceAddress = QString::fromStdString(this->device->GetAddress());
    this->ancStatus = (int)this->device->GetAncMode();
    this->updateBatteryStatuses();
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
        this->device->SetAnc(DeviceAncMode(status));
        Q_EMIT ancStatusChanged(); 
        this->updateBatteryStatuses();
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

void AirpodsHandler::updateBatteryStatuses() {
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