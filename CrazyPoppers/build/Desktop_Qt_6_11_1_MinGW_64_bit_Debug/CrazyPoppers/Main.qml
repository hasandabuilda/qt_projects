import QtQuick

Window {
    id: window

    width: 480
    height: 820
    minimumWidth: 340
    minimumHeight: 600
    visible: true
    title: qsTr("Crazy Poppers")
    color: Theme.woodBottom

    GameEngine {
        id: engine
    }

    GameScreen {
        anchors.fill: parent
        game: engine
    }
}
