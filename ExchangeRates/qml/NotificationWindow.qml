import QtQuick
import Qt.labs.platform 1.1

Window {
    id: notificationWindow
    width: 500
    height: 500
    title: qsTr("Exchange Rate Notifications")
    flags: Qt.FramelessWindowHint | Qt.WindowMinimized | Qt.Dialog
    color: Qt.rgba(0,0,0,0);
    modality: Qt.ApplicationModal

    Component.onCompleted: {
        showNormal()
    }

    Rectangle {
        x: 0
        y: 0
        width: 500
        height: 500
        radius: 10

        Rectangle {
            x: 5
            y: 5
            width: 16
            height: 16
            radius: 15
            color: "#e74c3c"

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    notificationWindow.close()
                }
            }
        }

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
