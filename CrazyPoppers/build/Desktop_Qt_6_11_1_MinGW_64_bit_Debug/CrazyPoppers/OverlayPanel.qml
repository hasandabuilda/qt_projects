import QtQuick

Item {
    id: overlay

    property string title: ""
    property color titleColor: Theme.ink
    default property alias content: column.data

    Rectangle {
        anchors.fill: parent
        color: Theme.scrim
    }

    // Swallows taps so the board underneath stays untouched.
    /*
    MouseArea {
        anchors.fill: parent
    }
    */

    Rectangle {
        id: panel

        anchors.centerIn: parent
        width: Math.min(overlay.width * 0.86, 380)
        height: column.implicitHeight + 54
        radius: 24
        color: Theme.panel
        border.width: 3
        border.color: Theme.panelEdge
        scale: 0.82
        opacity: 0

        Column {
            id: column

            anchors.centerIn: parent
            width: parent.width - 44
            spacing: 14

            GameLabel {
                width: parent.width
                text: overlay.title
                color: overlay.titleColor
                font.pixelSize: 27
                horizontalAlignment: Text.AlignHCenter
            }
        }

        ParallelAnimation {
            running: true

            ScaleAnimator {
                target: panel
                from: 0.82
                to: 1.0
                duration: 240
                easing.type: Easing.OutBack
            }
            OpacityAnimator {
                target: panel
                from: 0.0
                to: 1.0
                duration: 190
            }
        }
    }
}
