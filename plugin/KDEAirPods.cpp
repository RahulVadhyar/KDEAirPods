/*
    SPDX-FileCopyrightText: 2024 Rahul Vadhyar vadhyarrahul@gmail.com>
    SPDX-License-Identifier: AGPL-3.0-or-later
*/

#include "KDEAirPods.hpp"

// KF
#include <KLocalizedString>
// Qt
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlContext>

static QJSValue singletonTypeExampleProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)

    QJSValue helloWorld = scriptEngine->newObject();
    helloWorld.setProperty("text", i18n("Hello world!"));
    return helloWorld;
}


void KDEAirpodsPlugin::registerTypes(const char* uri)
{
    Q_ASSERT(uri == QLatin1String("com.github.rahulvadhyar.private.KDEAirPods"));

    qmlRegisterSingletonType(uri, 1, 0, "HelloWorld", singletonTypeExampleProvider);
}

