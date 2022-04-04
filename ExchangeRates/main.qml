import QtQuick
import Qt.labs.platform 1.1

import "qml/"

Window {
    property variant clickPos: "1,1"

    id: mainWindow
    width: 500
    height: 500
    title: qsTr("Exchange Rate Notifications")
    flags: Qt.FramelessWindowHint | Qt.WindowMinimized | Qt.Dialog
    color: Qt.rgba(0,0,0,0);
    modality: Qt.ApplicationModal
    visible: false

    Component.onCompleted: {
        showNormal()
    }

    SystemTrayIcon {
        visible: true
        icon.source: "qrc:/res/trayicon.png"

        onMessageClicked: notificationWindow.showNormal()
        Component.onCompleted: showMessage("Message title", "Something important came up. Click this to know more.")

        menu: Menu {

            MenuItem {
                text: qsTr("Restore")
                onTriggered: showNormal()
            }

            MenuSeparator {

            }

            MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }
    }

    Rectangle {
        x: 0
        y: 0
        width: parent.width
        height: 26
        color: "#2c3e50"
        radius: 10
        border.width: 0

        Rectangle {
            x: 5
            y: 5
            z: 2
            width: 16
            height: 16
            radius: 15
            color: "#f1c40f"

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    mainWindow.hide()
                }
            }
        }

        Rectangle {
            x: 0
            y: 13
            width: 30
            height: 13
            z: 1

            color: "#2c3e50"
        }

        Rectangle {
            x: parent.width - 30
            y: 13
            width: 30
            height: 13
            z: 1

            color: "#2c3e50"
        }

        MouseArea {
            anchors.fill: parent

            onPressed: {
                clickPos  = Qt.point(mouse.x,mouse.y)
            }

            onPositionChanged: {
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                mainWindow.x += delta.x;
                mainWindow.y += delta.y;
            }
        }
    }

    Rectangle {
        x: 0
        y: 26
        width: 500
        height: 474
        radius: 10

        Rectangle {
            x: 0
            y: 0
            height: 10
            width: 10
            color: "white"
        }

        Rectangle {
            x: parent.width - 10
            y: 0
            height: 10
            width: 10
            color: "white"
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            y: 20
            font.family: "nunito"
            text: "Exchange Rates"
            font.pixelSize: 35
        }
    }

    NotificationWindow {
        id: notificationWindow
        Component.onCompleted: hide()
    }


    FontLoader
    {
        id: nunito;
        source: "qrc:/res/Fonts/NunitoSans-Regular.ttf"
    }
}
