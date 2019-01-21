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

#ifndef APPENGINE_H
#define APPENGINE_H

#include <QtCore/QEvent>
#include <QtCore/QFileInfo>
#include <QtCore/QSettings>
#include <QtCore/QUrl>
#include <QtGui/QColor>

class AppEngine : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString settingsPath READ settingsPath FINAL CONSTANT)
    Q_PROPERTY(QString startUrl READ startUrl WRITE setStartUrl)

public:
    AppEngine(const QSettings &settings, QObject *parent = 0);

    QString settingsPath();
    QString startUrl() const;
    void setStartUrl(const QString &url);

    Q_INVOKABLE bool isUrl(const QString& userInput);
    Q_INVOKABLE QUrl fromUserInput(const QString& userInput) const;
    Q_INVOKABLE QString domainFromString(const QString& urlString);
    Q_INVOKABLE QString fallbackColor();
    Q_INVOKABLE QString restoreSetting(const QString &name, const QString &defaultValue = QString());
    Q_INVOKABLE void saveSetting(const QString &name, const QString &value);

    Q_INVOKABLE bool getBool(const QString &name, const bool defval = false) const;
    Q_INVOKABLE int getInt(const QString &name, const int defval = 0) const;
    Q_INVOKABLE quint16 getUInt(const QString &name, const quint16 defval = 0) const;
    Q_INVOKABLE qreal getReal(const QString &name, const qreal defval = 0) const;
    Q_INVOKABLE QString getQString(const QString &name, const QString &defaultValue = QString()) const;
    Q_INVOKABLE QStringList getQStringList(const QString &name, const QStringList &defaultValue = QStringList()) const;

private:
    void set(const QSettings &settings);

private:
    QSettings m_settings;
    QUrl m_startUrl;
};

#endif // APPENGINE_H
