pragma Singleton

import QtQuick

QtObject {
    readonly property string displayFont: "Trebuchet MS"

    readonly property color woodTop: "#5b3413"
    readonly property color woodCore: "#a06c38"
    readonly property color woodLow: "#8a5729"
    readonly property color woodBottom: "#4a2810"

    readonly property color bar: "#e63a1f0b"
    readonly property color barEdge: "#c08a4a"
    readonly property color panel: "#7a4a20"
    readonly property color panelEdge: "#e0b070"
    readonly property color scrim: "#b3140a02"

    readonly property color ink: "#fff1d6"
    readonly property color inkDim: "#d8b489"
    readonly property color inkShadow: "#2a1607"

    readonly property color accent: "#f2994a"
    readonly property color danger: "#e2402f"

    // Index by creature tier: 0 is an empty cell, 1..4 run blue, green, orange, red.
    readonly property var tierColor: ["#00000000", "#2f80ed", "#7cb832", "#f2994a", "#e2402f"]

    // Diameter as a fraction of one grid cell, so tier reads as size before colour.
    readonly property var tierScale: [0.0, 0.44, 0.60, 0.77, 0.94]
}
