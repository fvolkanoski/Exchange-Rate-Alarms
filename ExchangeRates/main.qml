import QtQuick

Window {
    width: 500
    height: 500
    visible: true
    title: qsTr("Exchange Rate Notifications")

    Rectangle {
        x: 0
        y: 0
        width: 500
        height: 500

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            y: 30
            font.family: "nunito"
            text: "Rates changed!"
            font.pixelSize: 35
        }
    }

    FontLoader
    {
        id: nunito;
        source: "qrc:/res/Fonts/NunitoSans-Regular.ttf"
    }
}
