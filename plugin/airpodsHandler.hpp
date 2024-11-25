/*
    SPDX-FileCopyrightText: 2024 Rahul Vadhyar vadhyarrahul@gmail.com>
    SPDX-License-Identifier: AGPL-3.0-or-later
*/
#pragma once

#include <QObject>
#include "DevicesInfoFetcher.h"

class AirpodsHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceName READ getDeviceName WRITE setDeviceName NOTIFY deviceNameChanged)
    Q_PROPERTY(QString deviceAddress READ getDeviceAddress WRITE setDeviceAddress NOTIFY deviceAddressChanged)
    Q_PROPERTY(bool connected READ getConnected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(int ancStatus READ getAncStatus WRITE setAncStatus NOTIFY ancStatusChanged)
    Q_PROPERTY(int leftBattery READ getLeftBattery NOTIFY leftBatteryChanged)
    Q_PROPERTY(int rightBattery READ getRightBattery NOTIFY rightBatteryChanged)
    Q_PROPERTY(int caseBattery READ getCaseBattery NOTIFY caseBatteryChanged)
    Q_PROPERTY(bool leftCharging READ getLeftCharging NOTIFY leftChargingChanged)
    Q_PROPERTY(bool rightCharging READ getRightCharging NOTIFY rightChargingChanged)
    Q_PROPERTY(bool caseCharging READ getCaseCharging NOTIFY caseChargingChanged)

public:
    explicit AirpodsHandler(QObject *parent = nullptr);
    QString getDeviceName() const;
    QString getDeviceAddress() const;
    bool getConnected() const;
    int getAncStatus() const;
    int getLeftBattery() const;
    int getRightBattery() const;
    int getCaseBattery() const;
    bool getLeftCharging() const;
    bool getRightCharging() const;
    bool getCaseCharging() const;

public Q_SLOTS:
    void setDeviceName(const QString &name);
    void setDeviceAddress(const QString &address);
    void setAncStatus(int status);
    void setConnected(bool status);
    void connectDevice();
    void disconnectDevice();
    void updateBatteryStatuses();

Q_SIGNALS:
    void connectedChanged();
    void ancStatusChanged();
    void deviceNameChanged();
    void deviceAddressChanged();
    void leftBatteryChanged();
    void rightBatteryChanged();
    void caseBatteryChanged();
    void leftChargingChanged();
    void rightChargingChanged();
    void caseChargingChanged();
    
private:
    QString deviceName = "Not Connected";
    QString deviceAddress  = "Not Connected";
    bool connected = false;
    int ancStatus = 0;
    std::shared_ptr<DevicesInfoFetcher> devicesInfoFetcher;
    std::shared_ptr<Device> device = nullptr;
    int leftBattery = 0;
    int rightBattery = 0;
    int caseBattery = 0;
    bool leftCharging = false;
    bool rightCharging = false;
    bool caseCharging = false; 

    void handleBatteryEvent(size_t id, std::map<DeviceBatteryType, DeviceBatteryData> batteryStatus);
    void handleActiveDeviceEvent(std::shared_ptr<Device> device);

};