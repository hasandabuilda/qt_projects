import QtQuick

/*
    One creature, drawn to fill its own bounds.

    The signature Crazy Poppers look is the pair of oversized eyes that bulge
    out past the top of the body rather than sitting inside it, which is what
    gives them their froggy character.
*/
Item {
    id: creature

    property int tier: 4

    readonly property color tint: Theme.tierColor[tier > 0 ? tier : 4]
    readonly property real diameter: Math.min(width, height)

    Accessible.ignored: true

    Rectangle {
        width: creature.diameter
        height: creature.diameter
        x: ball.x
        y: ball.y + creature.diameter * 0.06
        radius: width / 3
        color: "#42000000"
    }

    Rectangle {
        id: ball

        anchors.centerIn: parent
        width: creature.diameter
        height: creature.diameter
        radius: width / 3
        border.width: Math.max(1, width * 0.035)
        border.color: Qt.darker(creature.tint, 1.65)
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.lighter(creature.tint, 1.4) }
            GradientStop { position: 0.46; color: creature.tint }
            GradientStop { position: 1.0; color: Qt.darker(creature.tint, 1.38) }
        }
    }

    // Sheen sits low on the body because the eyes take up the top.
    Rectangle {
        width: creature.diameter * 0.5
        height: creature.diameter * 0.22
        x: ball.x + creature.diameter * 0.25
        y: ball.y + creature.diameter * 0.62
        radius: height / 2
        color: "#2effffff"
    }

    Repeater {
        model: 2

        delegate: Item {
            id: eye

            required property int index

            readonly property real eyeSize: creature.diameter * 0.44

            width: eyeSize
            height: eyeSize
            x: ball.x + creature.diameter * (index === 0 ? 0.05 : 0.51)
            y: ball.y - creature.diameter * 0.08

            Rectangle {
                anchors.fill: parent
                radius: width / 2
                color: "#fffefa"
                border.width: Math.max(1, width * 0.06)
                border.color: "#5c000000"
            }

            Rectangle {
                width: parent.width * 0.44
                height: width
                x: (parent.width - width) / 2
                y: parent.height * 0.33
                radius: width / 2
                color: "#171008"

                Rectangle {
                    width: parent.width * 0.36
                    height: width
                    x: parent.width * 0.1
                    y: parent.height * 0.1
                    radius: width / 2
                    color: "#ccffffff"
                }
            }
        }
    }
}
