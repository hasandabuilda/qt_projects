import QtQuick
import QtQuick.Layouts

Rectangle {
    id: bar

    required property GameEngine game

    signal pauseRequested()

    implicitHeight: 56
    color: Theme.bar

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 2
        color: Theme.barEdge
        opacity: 0.55
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 16
        anchors.rightMargin: 12
        spacing: 12

        HudStat {
            Layout.alignment: Qt.AlignVCenter
            label: qsTr("SCORE:")
            value: bar.game.score
        }

        Item {
            Layout.fillWidth: true
        }

        HudStat {
            Layout.alignment: Qt.AlignVCenter
            label: qsTr("TOUCHES LEFT:")
            value: bar.game.tapsRemaining
        }

        PauseButton {
            Layout.alignment: Qt.AlignVCenter
            visible: bar.game.phase === GameEngine.Idle || bar.game.phase === GameEngine.Resolving
            onClicked: bar.pauseRequested()
        }
    }
}
