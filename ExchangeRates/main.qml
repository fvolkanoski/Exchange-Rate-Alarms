import QtQuick
import Qt.labs.platform 1.1

import "qml/"

Window {
    id: mainWindow
    width: 500
    height: 500
    title: qsTr("Exchange Rate Notifications")

    SystemTrayIcon {
        id: trayIcon
        visible: true
        icon.source: "qrc:/res/trayicon.png"

        onMessageClicked: mainWindow.showNormal()

        menu: Menu {

            MenuItem {
                text: qsTr("Minimize")
                onTriggered: showMinimized()
            }

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

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        y: 20
        font.family: "nunito"
        text: "Exchange Rates"
        font.pixelSize: 35
    }

    FontLoader
    {
        id: nunito;
        source: "qrc:/res/Fonts/NunitoSans-Regular.ttf"
    }

    Connections {
        target: appController

        function onShowTrayMessage(title, msg) {
            trayIcon.showMessage(title, msg)
        }
    }
}
