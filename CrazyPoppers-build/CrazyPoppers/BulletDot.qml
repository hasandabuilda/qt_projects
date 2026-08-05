import QtQuick

Item {
    id: dot

    required property real gridX
    required property real gridY
    required property int directionX
    required property int directionY

    property real cellSize: 0

    readonly property color tint: Theme.tierColor[4]
    readonly property real dotSize: cellSize * 0.24

    width: dotSize
    height: dotSize
    x: (gridX + 0.5) * cellSize - width / 2
    y: (gridY + 0.5) * cellSize - height / 2
    Accessible.ignored: true

    // A zero-sized pivot: rotating it aims the trail backwards along the
    // travel direction without needing a gradient per direction.
    Item {
        anchors.centerIn: parent
        rotation: dot.directionX !== 0 ? (dot.directionX > 0 ? 0 : 180)
                                       : (dot.directionY > 0 ? 90 : 270)

        Rectangle {
            width: dot.cellSize * 0.62
            height: dot.dotSize * 0.62
            x: -width
            y: -height / 2
            radius: height / 2
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: "#00e2402f" }
                GradientStop { position: 1.0; color: "#96e2402f" }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: dot.tint
        border.width: Math.max(1, width * 0.13)
        border.color: Qt.darker(dot.tint, 1.7)
    }

    Rectangle {
        width: parent.width * 0.34
        height: width
        x: parent.width * 0.2
        y: parent.height * 0.16
        radius: width / 2
        color: "#b3ffffff"
    }
}
