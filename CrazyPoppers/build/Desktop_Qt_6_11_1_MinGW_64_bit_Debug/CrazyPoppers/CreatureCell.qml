import QtQuick

Item {
    id: cell

    required property int tier
    required property int cellRow
    required property int cellColumn

    property real cellSize: 0

    readonly property bool alive: tier > 0
    // Empty cells keep the red tint so a pop fades out in its own colour.
    readonly property color tint: Theme.tierColor[tier > 0 ? tier : 4]
    property bool revealed: false

    width: cellSize
    height: cellSize
    x: cellColumn * cellSize
    y: cellRow * cellSize
    Accessible.ignored: true

    // Staggered along the diagonal so a new level rolls in as a wave.
    Timer {
        interval: 24 * (cell.cellRow + cell.cellColumn)
        running: true
        onTriggered: cell.revealed = true
    }

    Item {
        id: body

        anchors.centerIn: parent
        width: cell.cellSize
        height: cell.cellSize
        scale: cell.revealed && cell.alive ? Theme.tierScale[cell.tier] : 0.0
        opacity: cell.alive ? 1.0 : 0.0

        Behavior on scale {
            ScaleAnimator {
                duration: 200
                easing.type: Easing.OutBack
                easing.overshoot: 1.5
            }
        }
        Behavior on opacity {
            OpacityAnimator { duration: 140 }
        }

        Rectangle {
            width: parent.width
            height: parent.height
            y: parent.height * 0.055
            radius: width / 2
            color: "#3d000000"
        }

        Rectangle {
            anchors.fill: parent
            radius: width / 2
            border.width: Math.max(1, width * 0.04)
            border.color: Qt.darker(cell.tint, 1.55)
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.lighter(cell.tint, 1.5) }
                GradientStop { position: 0.52; color: cell.tint }
                GradientStop { position: 1.0; color: Qt.darker(cell.tint, 1.32) }
            }
        }

        Rectangle {
            width: parent.width * 0.48
            height: parent.height * 0.24
            x: parent.width * 0.19
            y: parent.height * 0.09
            radius: height / 2
            color: "#5cffffff"
        }

        Repeater {
            model: 2

            delegate: Item {
                id: eye

                required property int index

                width: body.width * 0.30
                height: width
                x: body.width * (index === 0 ? 0.17 : 0.53)
                y: body.height * 0.23

                Rectangle {
                    anchors.fill: parent
                    radius: width / 2
                    color: "#fffdf6"
                    border.width: Math.max(1, width * 0.07)
                    border.color: "#2e000000"
                }

                Rectangle {
                    width: parent.width * 0.46
                    height: width
                    x: parent.width * 0.27
                    y: parent.height * 0.32
                    radius: width / 2
                    color: "#1c140a"

                    Rectangle {
                        width: parent.width * 0.38
                        height: width
                        x: parent.width * 0.14
                        y: parent.height * 0.14
                        radius: width / 2
                        color: "#c4ffffff"
                    }
                }
            }
        }
    }
}
