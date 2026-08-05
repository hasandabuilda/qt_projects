import QtQuick
import QtQuick.Controls.Basic

Button {
    id: control

    implicitWidth: 38
    implicitHeight: 38
    scale: pressed ? 0.92 : 1.0

    Behavior on scale {
        ScaleAnimator { duration: 90 }
    }

    background: Rectangle {
        radius: width / 2
        border.width: 2
        border.color: "#8ad0f2"
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#5aa8e0" }
            GradientStop { position: 1.0; color: "#2f6fae" }
        }
    }

    contentItem: Item {
        Row {
            anchors.centerIn: parent
            spacing: 4

            Repeater {
                model: 2

                delegate: Rectangle {
                    width: 4
                    height: 14
                    radius: 1.5
                    color: Theme.ink
                }
            }
        }
    }
}
