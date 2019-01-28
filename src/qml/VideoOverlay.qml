import QtQuick 2.11
import QtMultimedia 5.8

Item {
    id: videoOverlay

    anchors.fill: parent
    visible: true

    MediaPlayer {
        id: mediaPlayer
        source: AppEngine.getQString("video/url")
        autoPlay: true
        loops: MediaPlayer.Infinite
    }
    VideoOutput {
        anchors.fill: parent
        source: mediaPlayer
    }
    MouseArea {
        id: playArea
        anchors.fill: parent
        onPressed: {
            mediaPlayer.stop();
            videoOverlay.visible = false
        }
    }
    onVisibleChanged: {
        if (visible)
            mediaPlayer.play()
        else
            timer.start()
    }
}
