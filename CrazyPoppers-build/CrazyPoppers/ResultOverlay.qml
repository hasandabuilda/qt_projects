import QtQuick

OverlayPanel {
    id: overlay

    required property GameEngine game

    signal levelsRequested()

    readonly property bool won: game.phase === GameEngine.Won
    readonly property bool hasNext: game.levelIndex + 1 < game.levelCount

    title: won ? qsTr("LEVEL CLEAR!") : qsTr("OUT OF TOUCHES")
    titleColor: won ? "#9ade3f" : Theme.danger

    GameLabel {
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15
        color: Theme.inkDim
        wrapMode: Text.WordWrap
        text: overlay.won
              ? qsTr("SCORE %1    BEST %2").arg(overlay.game.score)
                                           .arg(overlay.game.bestScore(overlay.game.levelIndex))
              : qsTr("Creatures are still standing. Every level can be cleared in exactly %1.")
                .arg(overlay.game.tapBudget === 1 ? qsTr("1 touch")
                                                  : qsTr("%1 touches").arg(overlay.game.tapBudget))
    }

    GameLabel {
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15
        color: Theme.accent
        wrapMode: Text.WordWrap
        visible: overlay.won && !overlay.hasNext
        text: qsTr("That was the last level. Nicely done.")
    }

    PopButton {
        width: parent.width
        visible: overlay.won && overlay.hasNext
        tint: "#7cb832"
        text: qsTr("NEXT LEVEL")
        onClicked: overlay.game.nextLevel()
    }

    PopButton {
        width: parent.width
        tint: overlay.won ? Theme.accent : "#e2762f"
        text: overlay.won ? qsTr("REPLAY") : qsTr("TRY AGAIN")
        onClicked: overlay.game.restartLevel()
    }

    PopButton {
        width: parent.width
        tint: "#96693c"
        text: qsTr("LEVELS")
        onClicked: overlay.levelsRequested()
    }
}
