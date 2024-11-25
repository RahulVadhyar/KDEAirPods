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

public:

    explicit AirpodsHandler(QObject *parent = nullptr);
    QString getDeviceName() const;
    QString getDeviceAddress() const;
    bool getConnected() const;
    int getAncStatus() const;

public Q_SLOTS:
    void setDeviceName(const QString &name);
    void setDeviceAddress(const QString &address);
    void setAncStatus(int status);
    void setConnected(bool status);
    void connectDevice();
    void disconnectDevice();

Q_SIGNALS:
    void connectedChanged();
    void ancStatusChanged();
    void deviceNameChanged();
    void deviceAddressChanged();

    
private:
    QString deviceName;
    QString deviceAddress;
    bool connected;
    int ancStatus;
    std::shared_ptr<DevicesInfoFetcher> devicesInfoFetcher;
    std::shared_ptr<Device> device;
};