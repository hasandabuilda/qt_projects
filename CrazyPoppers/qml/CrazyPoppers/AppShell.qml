import QtQuick

Item {
    id: shell

    required property GameEngine game

    property string page: "home"

    WoodBackground {
        anchors.fill: parent
    }

    Loader {
        id: pageLoader

        anchors.fill: parent
        opacity: 0
        sourceComponent: shell.page === "home" ? homePage
                       : shell.page === "levels" ? levelsPage
                                                 : gamePage
        onLoaded: {
            if (item)
                item.forceActiveFocus();
            fade.restart();
        }

        OpacityAnimator {
            id: fade

            target: pageLoader
            from: 0.0
            to: 1.0
            duration: 200
        }
    }

    Component {
        id: homePage

        HomeScreen {
            game: shell.game
            onPlayRequested: shell.page = "levels"
        }
    }

    Component {
        id: levelsPage

        LevelSelectScreen {
            game: shell.game
            onBackRequested: shell.page = "home"
            onLevelChosen: index => {
                shell.game.startLevel(index);
                shell.page = "game";
            }
        }
    }

    Component {
        id: gamePage

        GameScreen {
            game: shell.game
            onLevelsRequested: {
                shell.game.paused = false;
                shell.page = "levels";
            }
            onHomeRequested: {
                shell.game.paused = false;
                shell.page = "home";
            }
        }
    }
}
