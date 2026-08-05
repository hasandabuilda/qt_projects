cmake_minimum_required(VERSION 3.16)

project(CrazyPoppers
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(crazypoppersapp
    src/main.cpp
    src/boardmodel.cpp
    src/boardmodel.h
    src/bulletmodel.cpp
    src/bulletmodel.h
    src/gameengine.cpp
    src/gameengine.h
    src/leveldata.cpp
    src/leveldata.h
)

# The generated type-registration file includes the backing target's headers as
# <boardmodel.h> and friends, so src/ has to be reachable as an include path.
target_include_directories(crazypoppersapp PRIVATE src)

set(crazypoppers_qml_files
    qml/CrazyPoppers/BoardView.qml
    qml/CrazyPoppers/BottomBar.qml
    qml/CrazyPoppers/BulletDot.qml
    qml/CrazyPoppers/CreatureCell.qml
    qml/CrazyPoppers/GameLabel.qml
    qml/CrazyPoppers/GameScreen.qml
    qml/CrazyPoppers/HudStat.qml
    qml/CrazyPoppers/LevelSelectOverlay.qml
    qml/CrazyPoppers/LevelTile.qml
    qml/CrazyPoppers/Main.qml
    qml/CrazyPoppers/OverlayPanel.qml
    qml/CrazyPoppers/PauseButton.qml
    qml/CrazyPoppers/PauseOverlay.qml
    qml/CrazyPoppers/PopButton.qml
    qml/CrazyPoppers/ResultOverlay.qml
    qml/CrazyPoppers/Shockwave.qml
    qml/CrazyPoppers/Theme.qml
    qml/CrazyPoppers/TopBar.qml
    qml/CrazyPoppers/WoodBackground.qml
)

# qt_add_qml_module derives each file's resource path from its location relative
# to this CMakeLists.txt. The .qml files sit two directories deeper, so alias
# every one back to its bare name to keep the module's resource tree flat and
# matching the CrazyPoppers URI. Both properties must be set before the module
# is declared.
foreach(qml_file IN LISTS crazypoppers_qml_files)
    get_filename_component(qml_name "${qml_file}" NAME)
    set_source_files_properties("${qml_file}" PROPERTIES
        QT_RESOURCE_ALIAS "${qml_name}"
    )
endforeach()

set_source_files_properties(qml/CrazyPoppers/Theme.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(crazypoppersapp
    URI CrazyPoppers
    QML_FILES ${crazypoppers_qml_files}
)

target_link_libraries(crazypoppersapp PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
)
