import QtQuick
import QtQuick.Layouts

Rectangle {
    id: bar

    required property GameEngine game

    implicitHeight: 46
    color: Theme.bar

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 2
        color: Theme.barEdge
        opacity: 0.55
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 18
        anchors.rightMargin: 18

        HudStat {
            Layout.alignment: Qt.AlignVCenter
            fontSize: 14
            label: qsTr("TOUCHES:")
            value: bar.game.tapsUsed
        }

        Item {
            Layout.fillWidth: true
        }

        HudStat {
            Layout.alignment: Qt.AlignVCenter
            fontSize: 14
            label: qsTr("LEVEL:")
            value: bar.game.levelIndex + 1
        }

        Item {
            Layout.fillWidth: true
        }

        HudStat {
            Layout.alignment: Qt.AlignVCenter
            fontSize: 14
            label: qsTr("COMBO:")
            value: bar.game.combo
        }
    }
}
