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
                     bool reset,
                     QObject *parent)
    : QObject(parent)
    , m_settings(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) % QDir::separator() % "settings.ini", QSettings::IniFormat, this)
{
    if (!m_settings.allKeys().count() || reset)
        setDefaultValues();
    set(settings);
}

QString AppEngine::settingsPath()
{
    return m_settings.fileName();
}

QString AppEngine::startUrl() const
{
   const QString url =  m_startUrl.isEmpty() ? fromUserInput(getQString(browserHomePage)) : m_startUrl;
   return url;
}

void AppEngine::setStartUrl(const QString &url)
{
    m_startUrl = fromUserInput(url);
}

void AppEngine::set(const QSettings &settings)
{
    const QStringList keyList = settings.allKeys();
    QString key;
    foreach (key, keyList) {
        QVariant variant = settings.value(key);
        if (key == QString(browserHomePage) || key == QString(organizationDomain)) {
            variant = fromUserInput(settings.value(key).toString());
        }
        if (key == QString(videoPlaylist)) {
            const QStringList playlist = settings.value(key).toStringList();
            QString file;
            QStringList normalizedPlayList;
            foreach (file, playlist) {
                normalizedPlayList << fromUserInput(file);
            }
        }
        m_settings.setValue(key, variant);
    }
}

QString AppEngine::fromUserInput(const QString& userInput) const
{
    QFileInfo fileInfo(userInput);
    QString url = QUrl::fromUserInput(userInput).toString();
    if (fileInfo.exists())
        url = QUrl::fromLocalFile(fileInfo.absoluteFilePath()).toString();
    return url;
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

void AppEngine::setDefaultValues()
{
    m_settings.setValue(organization, defaultOrganization);
    m_settings.setValue(organizationDomain, defaultOrganizationDomain);
    m_settings.setValue(applicationName, defaultApplicationName);
    m_settings.setValue(applicationVersion, defaultApplicationVersion);
    m_settings.setValue(applicationIcon, defaultApplicationIcon);

    m_settings.setValue(proxyEnable, false);
    m_settings.setValue(proxySystem, true);
    m_settings.setValue(proxyHost, QStringLiteral("proxy.example.com"));
    m_settings.setValue(proxyPort, 3128);
    m_settings.setValue(proxyAuth, false);
    m_settings.setValue(proxyUsername, QStringLiteral("username"));
    m_settings.setValue(proxyPassword, QStringLiteral("password"));

    m_settings.setValue(viewFullScreen, true);
    m_settings.setValue(viewMaximized, false);
    m_settings.setValue(viewFixedSize, false);
    m_settings.setValue(viewFixedWidth, 1024);
    m_settings.setValue(viewFixedHeight, 600);
    m_settings.setValue(viewMinimalWidth, 320);
    m_settings.setValue(viewMinimalHeight, 200);
    m_settings.setValue(viewKeyboard, true);

    m_settings.setValue(browserHomePage, defaultOrganizationDomain);
    m_settings.setValue(javascript, true);
    m_settings.setValue(javascriptCanOpenWindows, false);
    m_settings.setValue(webgl, false);
    m_settings.setValue(plugins, true);
    m_settings.setValue(ignoreSslErrors, true);

    m_settings.setValue(localStorageEnable, false);
    m_settings.setValue(videoPlaylist, QStringList() << defaultVideoUrl);
    m_settings.setValue(videoTimeout, defaultVideoTimeout);
}
