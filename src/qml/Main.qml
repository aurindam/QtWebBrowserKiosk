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

import QtQuick 2.5
import QtQuick.Controls 2.12
import QtQuick.Window 2.0
import QtWebEngine 1.8

ApplicationWindow {
    id: window
    width: AppEngine.getUInt("view/fixed-width")
    height: AppEngine.getUInt("view/fixed-height")
    minimumWidth: AppEngine.getUInt("view/minimal-width")
    minimumHeight: AppEngine.getUInt("view/minimal-height")
    visible: true
    title: AppEngine.getQString("application/name")

    property bool fullScreen: AppEngine.getBool("view/fullscreen")
    property bool maximized: AppEngine.getBool("view/maximized")
    property bool fixedSize: AppEngine.getBool("view/fixed-size")

    Component.onCompleted: {
        if (window.fullScreen)
            window.showFullScreen()
        else {
            x = Screen.width / 2 - width / 2
            y = Screen.height / 2 - height / 2
            if (window.maximized)
                window.showMaximized()
            else if (window.fixedSize)
                window.showNormal()
        }
    }

    BrowserWindow{
        id: root
        anchors.fill: parent
        Keyboard{
            id: inputPanel
            windowHeight: root.height
            animationDuration: root.animationDuration
        }
    }
}
