import QtQuick

Item {
    id: root

    required property GameEngine game

    readonly property int columns: game.board.columns
    readonly property int rows: game.board.rows
    readonly property real cellSize: Math.min(width / Math.max(columns, 1),
                                              height / Math.max(rows, 1))

    property int waveCursor: 0

    Item {
        id: grid

        anchors.centerIn: parent
        width: root.cellSize * root.columns
        height: root.cellSize * root.rows

        Rectangle {
            anchors.fill: parent
            anchors.margins: -root.cellSize * 0.14
            radius: root.cellSize * 0.4
            color: "#21000000"
            border.width: 2
            border.color: "#1cffe0b0"
        }

        Repeater {
            model: root.game.board

            delegate: CreatureCell {
                cellSize: root.cellSize
            }
        }

        Repeater {
            model: root.game.bullets

            delegate: BulletDot {
                cellSize: root.cellSize
            }
        }

        Repeater {
            id: shockwaves

            model: 16

            delegate: Shockwave {
                ringSize: root.cellSize * 0.95
            }
        }

        MouseArea {
            anchors.fill: parent
            enabled: root.game.phase === GameEngine.Idle && !root.game.paused
            onClicked: mouse => root.game.tap(Math.floor(mouse.y / root.cellSize),
                                              Math.floor(mouse.x / root.cellSize))
        }
    }

    Connections {
        target: root.game

        function onPopped(row, column, tier) {
            const wave = shockwaves.itemAt(root.waveCursor);
            root.waveCursor = (root.waveCursor + 1) % shockwaves.count;
            if (wave) {
                wave.burst((column + 0.5) * root.cellSize,
                           (row + 0.5) * root.cellSize,
                           Theme.tierColor[tier]);
            }
        }
    }
}
