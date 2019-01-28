import QtQuick 2.11
import QtMultimedia 5.8

Item {
    id: videoOverlay

    anchors.fill: parent
    visible: true

    onVisibleChanged: {
        if (visible)
            mediaPlayer.play()
        else
            timer.start()
    }

    MediaPlayer {
        id: mediaPlayer
        autoPlay: true
        loops: MediaPlayer.Infinite
    }
    VideoOutput {
        anchors.fill: parent
        source: mediaPlayer
    }
    Playlist {
        id: playList
    }
    MouseArea {
        id: playArea
        anchors.fill: parent
        onPressed: {
            mediaPlayer.pause();
            videoOverlay.visible = false
        }
    }

    Component.onCompleted:  {
        var list = AppEngine.getQStringList("video/playlist")
        for (var i = 0, len = list.length; i < len; i++)
            playList.insertItem(i, list[i])
        mediaPlayer.playlist = playList
    }
}
