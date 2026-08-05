import QtQuick

OverlayPanel {
    id: overlay

    required property GameEngine game

    signal levelsRequested()
    signal homeRequested()

    title: qsTr("PAUSED")

    GameLabel {
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15
        color: Theme.inkDim
        text: qsTr("Level %1 — %2").arg(overlay.game.levelIndex + 1).arg(overlay.game.levelName)
    }

    PopButton {
        width: parent.width
        tint: "#7cb832"
        text: qsTr("RESUME")
        onClicked: overlay.game.paused = false
    }

    PopButton {
        width: parent.width
        text: qsTr("RESTART LEVEL")
        onClicked: overlay.game.restartLevel()
    }

    PopButton {
        width: parent.width
        tint: "#96693c"
        text: qsTr("LEVELS")
        onClicked: overlay.levelsRequested()
    }

    PopButton {
        width: parent.width
        tint: "#96693c"
        text: qsTr("HOME")
        onClicked: overlay.homeRequested()
    }
}
