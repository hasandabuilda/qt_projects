import QtQuick
import QtQuick.Particles

/*
    White smoke puffs left behind by a pop. fuzzydot is one of Qt's built-in
    particle images — white and semi-transparent so it can be tinted and faded.
*/
Item {
    id: layer

    property real puffSize: 40

    Accessible.ignored: true

    function puff(centreX, centreY) {
        emitter.burst(8, centreX, centreY);
    }

    ParticleSystem {
        id: system

        running: layer.visible
    }

    // Particles blend additively, so a puff has to start almost transparent —
    // ten of them stacked on the spawn point would otherwise read as one solid
    // white disc instead of smoke.
    ImageParticle {
        system: system
        source: "qrc:///particleresources/fuzzydot.png"
        color: "#ffffff"
        colorVariation: 0
        alpha: 0.085
        alphaVariation: 0.04
        entryEffect: ImageParticle.Fade
    }

    Emitter {
        id: emitter

        system: system
        enabled: false
        lifeSpan: 450
        lifeSpanVariation: 150
        size: layer.puffSize * 0.14
        endSize: layer.puffSize * 0.7
        sizeVariation: layer.puffSize * 0.12
        velocity: AngleDirection {
            angleVariation: 360
            magnitude: 38
            magnitudeVariation: 22
        }
        acceleration: AngleDirection {
            angle: 270
            angleVariation: 45
            magnitude: 14
        }
    }
}
