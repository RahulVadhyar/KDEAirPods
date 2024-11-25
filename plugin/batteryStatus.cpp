/*
    SPDX-FileCopyrightText: 2024 Rahul Vadhyar vadhyarrahul@gmail.com>
    SPDX-License-Identifier: AGPL-3.0-or-later
*/

#include "batteryStatus.hpp"

BatteryStatusModel::BatteryStatusModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int BatteryStatusModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_batteryStatus.count();
}

QVariant BatteryStatusModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_batteryStatus.size())
        return QVariant();

    const BatteryStatus &batteryStatus = m_batteryStatus[index.row()];

    switch (role) {
    case TypeRole:
        return QVariant::fromValue(batteryStatus.type);
    case StatusRole:
        return QVariant::fromValue(batteryStatus.status);
    case IsChargingRole:
        return batteryStatus.isCharging;
    case BatteryRole:
        return batteryStatus.battery;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> BatteryStatusModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[StatusRole] = "status";
    roles[IsChargingRole] = "isCharging";
    roles[BatteryRole] = "battery";
    return roles;
}

int BatteryStatusModel::count() const
{
    return m_batteryStatus.count();
}

void BatteryStatusModel::updateBatteryStatus(const QVector<BatteryStatus> &batteryStatus)
{
    beginResetModel();
    m_batteryStatus = batteryStatus;
    endResetModel();
    Q_EMIT countChanged();
}

void BatteryStatusModel::updateBatteryStatusAtIndex(int index, const BatteryStatus &batteryStatus)
{
    if (index < 0 || index >= m_batteryStatus.size())
        return;

    m_batteryStatus[index] = batteryStatus;
    QModelIndex modelIndex = createIndex(index, 0);
    Q_EMIT dataChanged(modelIndex, modelIndex);
}