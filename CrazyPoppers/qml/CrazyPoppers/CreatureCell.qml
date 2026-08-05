import QtQuick

Item {
    id: cell

    required property int tier
    required property int cellRow
    required property int cellColumn

    property real cellSize: 0

    readonly property bool alive: tier > 0
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

    Creature {
        id: body

        anchors.centerIn: parent
        width: cell.cellSize
        height: cell.cellSize
        // Empty cells keep the last colour so a pop fades out in its own tint.
        tier: cell.alive ? cell.tier : 4
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
            OpacityAnimator { duration: 150 }
        }
    }
}
