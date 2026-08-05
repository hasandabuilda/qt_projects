import QtQuick

Item {
    id: home

    required property GameEngine game

    signal playRequested()

    Column {
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.86, 380)
        spacing: 6

        GameLabel {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 46
            font.letterSpacing: 2
            color: "#ffd97a"
            text: qsTr("CRAZY")
        }

        GameLabel {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 46
            font.letterSpacing: 2
            color: "#ffd97a"
            text: qsTr("POPPERS")
        }

        Item {
            width: parent.width
            height: 18
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Repeater {
                model: 4

                delegate: Item {
                    id: mascot

                    required property int index

                    width: 64
                    height: 64

                    // Sized by tier so the home screen shows the growth order.
                    Creature {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        width: mascot.width * Theme.tierScale[mascot.index + 1] / Theme.tierScale[4]
                        height: width
                        tier: mascot.index + 1
                    }

                    SequentialAnimation on y {
                        loops: Animation.Infinite

                        PauseAnimation {
                            duration: mascot.index * 130
                        }
                        NumberAnimation {
                            from: 0
                            to: -14
                            duration: 520
                            easing.type: Easing.OutQuad
                        }
                        NumberAnimation {
                            from: -14
                            to: 0
                            duration: 520
                            easing.type: Easing.InQuad
                        }
                        PauseAnimation {
                            duration: (3 - mascot.index) * 130
                        }
                    }
                }
            }
        }

        Item {
            width: parent.width
            height: 26
        }

        GameLabel {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            color: Theme.inkDim
            wrapMode: Text.WordWrap
            text: qsTr("Tap a creature to grow it. Tap a red one to pop it.")
        }

        Item {
            width: parent.width
            height: 20
        }

        PopButton {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 210
            tint: "#7cb832"
            text: qsTr("PLAY")
            onClicked: home.playRequested()
        }

        Item {
            width: parent.width
            height: 8
        }

        GameLabel {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 13
            color: Theme.inkDim
            text: qsTr("%1 of %2 levels unlocked").arg(home.game.highestUnlockedLevel + 1)
                                                  .arg(home.game.levelCount)
        }
    }
}
