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

#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QStringBuilder>
#include <QCoreApplication>
#include <QDebug>

AppEngine::AppEngine(const QSettings &settings,
                     QObject *parent)
    : QObject(parent)
    , m_settings(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) % QDir::separator() % "settings.ini", QSettings::IniFormat, this)
{
    set(settings);
}

QString AppEngine::settingsPath()
{
    return m_settings.fileName();
}

QString AppEngine::homeUrl() const
{
    return fromUserInput(getQString(browserHomePage)).toString();
}

void AppEngine::setHomeUrl(const QString &url)
{
    if(isUrl(url))
        m_settings.setValue(browserHomePage, url);
}

void AppEngine::set(const QSettings &settings)
{
    settings.contains(organization) ?
                m_settings.setValue(organization, settings.value(organization)) :
                m_settings.setValue(organization, defaultOrganization);
    settings.contains(organizationDomain) ?
                m_settings.setValue(organizationDomain, settings.value(organizationDomain)) :
                m_settings.setValue(organizationDomain, defaultOrganizationDomain);
    settings.contains(applicationName) ?
                m_settings.setValue(applicationName, settings.value(applicationName)) :
                m_settings.setValue(applicationName, defaultApplicationName);
    settings.contains(applicationVersion) ?
                m_settings.setValue(applicationVersion, settings.value(applicationVersion)) :
                m_settings.setValue(applicationVersion, defaultApplicationVersion);
    settings.contains(applicationIcon) ?
                m_settings.setValue(applicationIcon, settings.value(applicationIcon)) :
                m_settings.setValue(applicationIcon, defaultApplicationIcon);

    settings.contains(proxyEnable) ?
                m_settings.setValue(proxyEnable, settings.value(proxyEnable)) :
                m_settings.setValue(proxyEnable, false);
    settings.contains(proxySystem) ?
                m_settings.setValue(proxySystem, settings.value(proxySystem)) :
                m_settings.setValue(proxySystem, true);
    settings.contains(proxyHost) ?
                m_settings.setValue(proxyHost, settings.value(proxyHost)) :
                m_settings.setValue(proxyHost, QStringLiteral("proxy.example.com"));
    settings.contains(proxyPort) ?
                m_settings.setValue(proxyPort, settings.value(proxyPort)) :
                m_settings.setValue(proxyPort, 3128);
    settings.contains(proxyAuth) ?
                m_settings.setValue(proxyAuth, settings.value(proxyAuth)) :
                m_settings.setValue(proxyAuth, false);
    settings.contains(proxyUsername) ?
                m_settings.setValue(proxyUsername, settings.value(proxyUsername)) :
                m_settings.setValue(proxyUsername, QStringLiteral("username"));
    settings.contains(proxyPassword) ?
                m_settings.setValue(proxyPassword, settings.value(proxyPassword)) :
                m_settings.setValue(proxyPassword, QStringLiteral("password"));

    settings.contains(viewFullScreen) ?
                m_settings.setValue(viewFullScreen, settings.value(viewFullScreen)) :
                m_settings.setValue(viewFullScreen, true);
    settings.contains(viewMaximized) ?
                m_settings.setValue(viewMaximized, settings.value(viewMaximized)) :
                m_settings.setValue(viewMaximized, false);
    settings.contains(viewFixedSize) ?
                m_settings.setValue(viewFixedSize, settings.value(viewFixedSize)) :
                m_settings.setValue(viewFixedSize, false);
    settings.contains(viewFixedWidth) ?
                m_settings.setValue(viewFixedWidth, settings.value(viewFixedWidth)) :
                m_settings.setValue(viewFixedWidth, 1024);
    settings.contains(viewFixedHeight) ?
                m_settings.setValue(viewFixedHeight, settings.value(viewFixedHeight)) :
                m_settings.setValue(viewFixedHeight, 600);
    settings.contains(viewMinimalWidth) ?
                m_settings.setValue(viewMinimalWidth, settings.value(viewMinimalWidth)) :
                m_settings.setValue(viewMinimalWidth, 320);
    settings.contains(viewMinimalHeight) ?
                m_settings.setValue(viewMinimalHeight, settings.value(viewMinimalHeight)) :
                m_settings.setValue(viewMinimalHeight, 200);

    settings.contains(browserHomePage) ?
                m_settings.setValue(browserHomePage, settings.value(browserHomePage)) :
                m_settings.setValue(browserHomePage, defaultOrganizationDomain);
    settings.contains(javascript) ?
                m_settings.setValue(javascript, settings.value(javascript)) :
                m_settings.setValue(javascript, true);
    settings.contains(javascriptCanOpenWindows) ?
                m_settings.setValue(javascriptCanOpenWindows, settings.value(javascriptCanOpenWindows)) :
                m_settings.setValue(javascriptCanOpenWindows, false);
    settings.contains(webgl) ?
                m_settings.setValue(webgl, settings.value(webgl)) :
                m_settings.setValue(webgl, false);
    settings.contains(plugins) ?
                m_settings.setValue(plugins, settings.value(plugins)) :
                m_settings.setValue(plugins, true);
    settings.contains(ignoreSslErrors) ?
                m_settings.setValue(ignoreSslErrors, settings.value(ignoreSslErrors)) :
                m_settings.setValue(ignoreSslErrors, true);

    settings.contains(localStorageEnable) ?
                m_settings.setValue(localStorageEnable, settings.value(localStorageEnable)) :
                m_settings.setValue(localStorageEnable, false);
}

QUrl AppEngine::fromUserInput(const QString& userInput) const
{
    QFileInfo fileInfo(userInput);
    if (fileInfo.exists())
        return QUrl::fromLocalFile(fileInfo.absoluteFilePath());
    return QUrl::fromUserInput(userInput);
}

bool AppEngine::isUrl(const QString& userInput)
{
    if (userInput.startsWith(QStringLiteral("www."))
            || userInput.startsWith(QStringLiteral("http"))
            || userInput.startsWith(QStringLiteral("ftp"))
            || userInput.contains(QStringLiteral("://"))
            || userInput.endsWith(QStringLiteral(".com")))
        return true;
    return false;
}

QString AppEngine::domainFromString(const QString& urlString)
{
    return QUrl::fromUserInput(urlString).host();
}

QString AppEngine::fallbackColor()
{
    static QList<QString> colors = QList<QString>() << QStringLiteral("#46a2da")
                                                    << QStringLiteral("#18394c")
                                                    << QStringLiteral("#ff8c0a")
                                                    << QStringLiteral("#5caa15");
    static int index = -1;
    if (++index == colors.count())
        index = 0;
    return colors[index];
}

QString AppEngine::restoreSetting(const QString &name, const QString &defaultValue)
{
    return m_settings.value(name, defaultValue).toString();
}

void AppEngine::saveSetting(const QString &name, const QString &value)
{
    m_settings.setValue(name, value);
}

bool AppEngine::getBool(const QString &name, const bool defaultValue) const
{
    if (m_settings.contains(name)) {
        return m_settings.value(name).toBool();
    }
    return defaultValue;
}

int AppEngine::getInt(const QString &name, const int defaultValue) const
{
    if (m_settings.contains(name)) {
        return m_settings.value(name).toInt();
    }
    return defaultValue;
}

quint16 AppEngine::getUInt(const QString &name, const quint16 defaultValue) const
{
    if (m_settings.contains(name)) {
        return m_settings.value(name).toUInt();
    }
    return defaultValue;
}

qreal AppEngine::getReal(const QString &name, const qreal defaultValue) const
{
    if (m_settings.contains(name)) {
        return m_settings.value(name).toReal();
    }
    return defaultValue;
}

QString AppEngine::getQString(const QString &name, const QString &defaultValue) const
{
    if (m_settings.contains(name)) {
        return m_settings.value(name).toString();
    }
    return defaultValue;
}

QStringList AppEngine::getQStringList(const QString &name, const QStringList &defaultValue) const
{
    if (m_settings.contains(name)) {
        return m_settings.value(name).toStringList();
    }
    return defaultValue;
}
