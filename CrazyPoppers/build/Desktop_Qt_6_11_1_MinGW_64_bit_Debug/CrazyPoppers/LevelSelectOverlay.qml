import QtQuick

OverlayPanel {
    id: overlay

    required property GameEngine game

    signal closed()

    title: qsTr("LEVELS")

    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 3
        spacing: 10

        Repeater {
            model: overlay.game.levelCount

            delegate: LevelTile {
                game: overlay.game
                onClicked: {
                    overlay.game.startLevel(index);
                    overlay.closed();
                }
            }
        }
    }

    PopButton {
        width: parent.width
        tint: "#96693c"
        text: qsTr("CLOSE")
        onClicked: overlay.closed()
    }
}
