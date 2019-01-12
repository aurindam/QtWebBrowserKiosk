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
import QtWebEngine 1.8

import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0

import "assets"

Item {
    id: root

    property string uiColor: "#46a2da"
    property string defaultFontFamily: "Open Sans"

    property int animationDuration: 200

    visible: true

    Item {
        id: browserWindow
        property bool interactive: {
            if (sslDialog.visible)
                return false
            return true
        }

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }

        height: inputPanel.y

        WebEngineView {
            id: webEngineView

            anchors.fill: parent

            enabled: browserWindow.interactive

            settings.javascriptEnabled: AppEngine.getBool("browser/javascript")
            settings.javascriptCanOpenWindows: AppEngine.getBool("browser/javascript_can_open_windows")
            settings.pluginsEnabled: AppEngine.getBool("browser/plugins")
            settings.webGLEnabled: AppEngine.getBool("browser/plugins")
            settings.localStorageEnabled: AppEngine.getBool("localstorage/enable")

            onCertificateError: {
                if (!acceptedCertificates.shouldAutoAccept(error)){
                    error.defer()
                    sslDialog.enqueue(error)
                } else{
                    error.ignoreCertificateError()
                }
            }
        }

        Desaturate {
            id: desaturate
            visible: desaturation != 0.0
            anchors.fill: webEngineView
            source: webEngineView
            desaturation: browserWindow.interactive ? 0.0 : 1.0

            Behavior on desaturation {
                NumberAnimation { duration: animationDuration }
            }
        }

        FastBlur {
            id: blur
            visible: radius != 0.0
            anchors.fill: desaturate
            source: desaturate
            radius: desaturate.desaturation * 25
        }

        Rectangle {
            opacity: {
                if (inputPanel.state === "visible")
                    return 0.0
                if (webEngineView.url == "" || webEngineView.url == "about:blank")
                    return 1.0
                return 0.0
            }
            anchors.fill: parent
            visible: opacity != 0.0
            color: "white"
            Image {
                id: placeholder
                y: placeholder.height
                anchors.horizontalCenter: parent.horizontalCenter
                source: "assets/icons/AppLogoColor.png"
            }
            Text {
                id: label
                anchors {
                    top: placeholder.bottom
                    topMargin: 20
                    horizontalCenter: placeholder.horizontalCenter
                }
                font.family: defaultFontFamily
                font.pixelSize: 28
                color: uiColor
                text: "Qt WebBrowser Kiosk"
            }

            Behavior on opacity {
                NumberAnimation { duration: animationDuration }
            }
        }

        Component.onCompleted: {
            webEngineView.url = AppEngine.homeUrl
        }
    }

    QtObject{
        id: acceptedCertificates

        property var acceptedUrls : []

        function shouldAutoAccept(certificateError){
            var domain = AppEngine.domainFromString(certificateError.url)
            return acceptedUrls.indexOf(domain) >= 0
        }
    }

    MessageDialog {
        id: sslDialog

        property var certErrors: []
        property var currentError: null
        visible: certErrors.length > 0 && !AppEngine.getBool("ignore_ssl_errors")
        icon: StandardIcon.Warning
        standardButtons: StandardButton.No | StandardButton.Yes
        title: "Server's certificate not trusted"
        text: "Do you wish to continue?"
        detailedText: "If you wish so, you may continue with an unverified certificate. " +
                      "Accepting an unverified certificate means " +
                      "you may not be connected with the host you tried to connect to.\n" +
                      "Do you wish to override the security check and continue?"
        onYes: {
            var cert = certErrors.shift()
            var domain = AppEngine.domainFromString(cert.url)
            acceptedCertificates.acceptedUrls.push(domain)
            cert.ignoreCertificateError()
            presentError()
        }
        onNo: reject()
        onRejected: reject()

        function reject(){
            certErrors.shift().rejectCertificate()
            presentError()
        }
        function enqueue(error){
            currentError = error
            certErrors.push(error)
            presentError()
        }
        function presentError(){
            informativeText = "SSL error from URL\n\n" + currentError.url + "\n\n" + currentError.description + "\n"
        }
    }
}
