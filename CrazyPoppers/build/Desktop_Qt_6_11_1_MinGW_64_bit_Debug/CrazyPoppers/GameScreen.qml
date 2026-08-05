import QtQuick

Item {
    id: screen

    required property GameEngine game

    property bool levelSelectOpen: false

    focus: true
    Keys.onEscapePressed: {
        if (screen.levelSelectOpen)
            screen.levelSelectOpen = false;
        else if (screen.game.phase === GameEngine.Idle || screen.game.phase === GameEngine.Resolving)
            screen.game.paused = !screen.game.paused;
    }

    WoodBackground {
        anchors.fill: parent
    }

    TopBar {
        id: topBar

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        game: screen.game
        onPauseRequested: screen.game.paused = true
    }

    BottomBar {
        id: bottomBar

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        game: screen.game
    }

    BoardView {
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 14
        game: screen.game
    }

    Loader {
        anchors.fill: parent
        active: !screen.levelSelectOpen
                && (screen.game.phase === GameEngine.Won || screen.game.phase === GameEngine.Lost)
        sourceComponent: resultComponent
    }

    Loader {
        anchors.fill: parent
        active: screen.game.paused && !screen.levelSelectOpen
        sourceComponent: pauseComponent
    }

    Loader {
        anchors.fill: parent
        active: screen.levelSelectOpen
        sourceComponent: levelsComponent
    }

    Component {
        id: resultComponent

        ResultOverlay {
            game: screen.game
            onLevelsRequested: screen.levelSelectOpen = true
        }
    }

    Component {
        id: pauseComponent

        PauseOverlay {
            game: screen.game
            onLevelsRequested: screen.levelSelectOpen = true
        }
    }

    Component {
        id: levelsComponent

        LevelSelectOverlay {
            game: screen.game
            onClosed: {
                screen.levelSelectOpen = false;
                screen.game.paused = false;
            }
        }
    }
}
