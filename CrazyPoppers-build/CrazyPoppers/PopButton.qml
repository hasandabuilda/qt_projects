import QtQuick
import QtQuick.Controls.Basic

Button {
    id: control

    property color tint: Theme.accent

    implicitWidth: 210
    implicitHeight: 50
    scale: pressed ? 0.96 : 1.0
    opacity: enabled ? 1.0 : 0.45

    Behavior on scale {
        ScaleAnimator { duration: 90 }
    }

    background: Rectangle {
        radius: height / 2
        border.width: 2
        border.color: Qt.darker(control.tint, 1.6)
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.lighter(control.tint, 1.32) }
            GradientStop { position: 1.0; color: Qt.darker(control.tint, 1.18) }
        }

        Rectangle {
            width: parent.width * 0.82
            height: parent.height * 0.3
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height * 0.12
            radius: height / 2
            color: "#38ffffff"
        }
    }

    contentItem: GameLabel {
        text: control.text
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
