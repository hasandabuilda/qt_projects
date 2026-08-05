import QtQuick
import QtQuick.Controls.Basic

Button {
    id: tile

    required property int index
    required property GameEngine game

    readonly property bool unlocked: index <= game.highestUnlockedLevel
    readonly property int best: game.bestScore(index)

    implicitWidth: 94
    implicitHeight: 84
    enabled: unlocked
    opacity: unlocked ? 1.0 : 0.42
    scale: pressed ? 0.94 : 1.0

    Behavior on scale {
        ScaleAnimator { duration: 90 }
    }

    background: Rectangle {
        radius: 14
        border.width: 2
        border.color: tile.game.levelIndex === tile.index ? Theme.panelEdge : "#5e3a18"
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#a06c38" }
            GradientStop { position: 1.0; color: "#6d4420" }
        }
    }

    contentItem: Column {
        spacing: 1

        GameLabel {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 26
            text: tile.index + 1
        }

        GameLabel {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 11
            color: Theme.inkDim
            text: tile.game.tapBudgetAt(tile.index) === 1
                  ? qsTr("1 TOUCH")
                  : qsTr("%1 TOUCHES").arg(tile.game.tapBudgetAt(tile.index))
        }

        GameLabel {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 11
            color: Theme.accent
            text: tile.best > 0 ? qsTr("BEST %1").arg(tile.best) : "—"
        }
    }
}
