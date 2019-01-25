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

#ifndef CONSTANT_H
#define CONSTANT_H

const char* const organization = "application/organization";
const char* const organizationDomain = "application/organization-domain";
const char* const applicationName = "application/name";
const char* const applicationVersion = "application/version";
const char* const applicationIcon = "application/icon";

const char* const proxyEnable = "proxy/enable";
const char* const proxySystem = "proxy/system";
const char* const proxyHost = "proxy/host";
const char* const proxyPort = "proxy/port";
const char* const proxyAuth = "proxy/auth";
const char* const proxyUsername = "proxy/username";
const char* const proxyPassword= "proxy/password";

const char* const viewFullScreen = "view/fullscreen";
const char* const viewMaximized = "view/maximized";
const char* const viewFixedSize = "view/fixed-size";
const char* const viewFixedWidth = "view/fixed-width";
const char* const viewFixedHeight = "view/fixed-height";
const char* const viewMinimalWidth = "view/minimal-width";
const char* const viewMinimalHeight = "view/minimal-height";
const char* const viewKeyboard = "view/show_keyboard";

const char* const browserHomePage = "browser/homepage";
const char* const javascript = "browser/javascript";
const char* const javascriptCanOpenWindows = "browser/javascript_can_open_windows";
const char* const webgl = "browser/webgl";
const char* const plugins = "browser/plugins";
const char* const ignoreSslErrors = "browser/ignore_ssl_errors";

const char* const localStorageEnable = "localstorage/enable";
const char* const videoUrl = "video/url";

const char* const defaultOrganization = "The Qt Company";
const char* const defaultOrganizationDomain = "www.qt.io";
const char* const defaultApplicationName = "QtWebBrowserKiosk";
const char* const defaultApplicationVersion = "1.0.0";
const char* const defaultApplicationIcon = "qrc:///qml/assets/icons/AppLogoColor.png";
const char* const defaultVideoUrl = "qrc:///qml/assets/videos/Qt.m4v";

#endif // CONSTANT_H
