import QtQuick

Item {
    id: page

    required property GameEngine game

    signal levelChosen(int index)
    signal backRequested()

    Column {
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.9, 360)
        spacing: 22

        GameLabel {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 30
            text: qsTr("SELECT LEVEL")
        }

        Grid {
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 3
            spacing: 12

            Repeater {
                model: page.game.levelCount

                delegate: LevelTile {
                    game: page.game
                    onClicked: page.levelChosen(index)
                }
            }
        }

        PopButton {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 180
            tint: "#96693c"
            text: qsTr("BACK")
            onClicked: page.backRequested()
        }
    }
}
