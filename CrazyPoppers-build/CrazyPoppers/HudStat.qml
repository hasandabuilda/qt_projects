import QtQuick

Row {
    id: stat

    property alias label: labelText.text
    property alias value: valueText.text
    property int fontSize: 15

    spacing: 5

    GameLabel {
        id: labelText

        color: Theme.inkDim
        font.pixelSize: stat.fontSize
    }

    GameLabel {
        id: valueText

        font.pixelSize: stat.fontSize
    }
}
