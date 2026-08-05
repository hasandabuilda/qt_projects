import QtQuick

Item {
    id: wave

    property real ringSize: 40

    width: ringSize
    height: ringSize
    visible: false
    scale: 0.35
    opacity: 0
    Accessible.ignored: true

    function burst(centreX, centreY, tint) {
        wave.x = centreX - wave.width / 2;
        wave.y = centreY - wave.height / 2;
        ring.border.color = tint;
        anim.restart();
    }

    Rectangle {
        id: ring

        anchors.fill: parent
        radius: width / 2
        color: "transparent"
        border.width: Math.max(2, width * 0.12)
    }

    ParallelAnimation {
        id: anim

        // Animators keep the QML-side value stale while running, so visibility
        // is switched here rather than bound to opacity.
        onStarted: wave.visible = true
        onFinished: wave.visible = false

        ScaleAnimator {
            target: wave
            from: 0.35
            to: 1.95
            duration: 360
            easing.type: Easing.OutQuad
        }
        OpacityAnimator {
            target: wave
            from: 0.9
            to: 0.0
            duration: 360
            easing.type: Easing.OutQuad
        }
    }
}
