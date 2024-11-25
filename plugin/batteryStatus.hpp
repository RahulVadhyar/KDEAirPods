/*
    SPDX-FileCopyrightText: 2024 Rahul Vadhyar vadhyarrahul@gmail.com>
    SPDX-License-Identifier: AGPL-3.0-or-later
*/
#pragma once

#include <QAbstractListModel>
#include <QVector>
#include "DeviceBattery.h"

struct BatteryStatus {
    DeviceBatteryType type;
    DeviceBatteryStatus status;
    bool isCharging;
    int battery;
};

class BatteryStatusModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum BatteryRoles {
        TypeRole = Qt::UserRole + 1,
        StatusRole,
        IsChargingRole,
        BatteryRole
    };
    BatteryStatusModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    int count() const;

    Q_SIGNAL void countChanged();

    Q_SLOT void updateBatteryStatus(const QVector<BatteryStatus> &batteryStatus);
    Q_SLOT void updateBatteryStatusAtIndex(int index, const BatteryStatus &batteryStatus);

private:
    QVector<BatteryStatus> m_batteryStatus;
};