/*
    SPDX-FileCopyrightText: 2024 Rahul Vadhyar vadhyarrahul@gmail.com>
    SPDX-License-Identifier: AGPL-3.0-or-later
*/
// Qt
#include <QQmlEngine>
#include <QQmlExtensionPlugin>
#include "airpodsHandler.hpp"

class KDEAirpodsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri) override {
        qmlRegisterType<AirpodsHandler>(uri, 1, 0, "AirpodsHandler");
    }
};

#include "KDEAirPods.moc"