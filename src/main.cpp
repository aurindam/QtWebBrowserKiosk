/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt WebBrowser KioskMode application.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "appengine.h"
#include "constant.h"

#include <QGuiApplication>
#include <QCommandLineParser>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QNetworkProxyFactory>
#include <QtWebEngine/qtwebengineglobal.h>

int main(int argc, char **argv)
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    //do not use any plugins installed on the device
    qputenv("QML2_IMPORT_PATH", QByteArray());

    QGuiApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("This is a modified Qt Web Browser working in kiosk mode");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("startUrl", QCoreApplication::translate("main", "Open this URL, optionally (else the homepage in config file will be used)"), "[startUrl]");

    QCommandLineOption configOption(QStringList() << "c" << "config",
             QCoreApplication::translate("main", "Configuration INI-file"),
             QCoreApplication::translate("main", "filepath"));
    parser.addOption(configOption);
    // Process the actual command line arguments given by the user
    parser.process(app);
    const QStringList args = parser.positionalArguments();

    QSettings settings(parser.value(configOption), QSettings::IniFormat);
    const QString orgName = settings.value(QString(organization)).toString();
    const QString orgDomain = settings.value(QString(organizationDomain)).toString();
    const QString appName = settings.value(QString(applicationName)).toString();
    const QString appVersion = settings.value(QString(applicationVersion)).toString();

    app.setOrganizationName(orgName.isEmpty() ? QString(defaultOrganization) : orgName);
    app.setOrganizationDomain(orgDomain.isEmpty() ? QString(defaultOrganizationDomain) : orgDomain);
    app.setApplicationName(appName.isEmpty() ? QString(defaultApplicationName) : appName);
    app.setApplicationVersion(appVersion.isEmpty() ? QString(defaultApplicationVersion) : appVersion);


    AppEngine appEngine(settings);
    if (args.count())
        appEngine.setStartUrl(args.at(0));
    // --- Network --- //
    if (appEngine.getBool(proxyEnable)) {
        bool system = appEngine.getBool(proxySystem);
        if (system) {
            QNetworkProxyFactory::setUseSystemConfiguration(system);
        } else {
            QNetworkProxy proxy;
            proxy.setType(QNetworkProxy::HttpProxy);
            proxy.setHostName(
                appEngine.getQString(proxyHost)
            );
            proxy.setPort(appEngine.getUInt(proxyPort));
            if (appEngine.getBool(proxyAuth)) {
                proxy.setUser(appEngine.getQString(proxyUsername));
                proxy.setPassword(appEngine.getQString(proxyPassword));
            }
            QNetworkProxy::setApplicationProxy(proxy);
        }
    }

    QtWebEngine::initialize();
    QQmlApplicationEngine engine;
    QQmlContext *rootContext = engine.rootContext();
    rootContext->setContextProperty("AppEngine", &appEngine);
    engine.load(QUrl("qrc:///qml/Main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;
    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));

    app.exec();
}
