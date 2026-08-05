import QtQuick

Rectangle {
    Accessible.ignored: true

    gradient: Gradient {
        GradientStop { position: 0.0; color: Theme.woodTop }
        GradientStop { position: 0.28; color: Theme.woodCore }
        GradientStop { position: 0.72; color: Theme.woodLow }
        GradientStop { position: 1.0; color: Theme.woodBottom }
    }

    // Darkened side edges stand in for a radial vignette, which QtQuick's core
    // gradients cannot express on their own.
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: "#59000000" }
            GradientStop { position: 0.22; color: "transparent" }
            GradientStop { position: 0.78; color: "transparent" }
            GradientStop { position: 1.0; color: "#59000000" }
        }
    }
}
