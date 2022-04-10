import QtQuick
import QtQuick.Controls 2.15
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

    ComboBox{
        id: comboBox
        model: cbModel
        textRole: "name"
        displayText: "Main currency: " + currentText
        anchors.horizontalCenter: parent.horizontalCenter
        y: 80
        height: 50
        width: 350

        Component.onCompleted: currentIndex = 0

        background: Rectangle {
            color: "#e6e6e6"
            border.color: "white"
            radius: 5
        }

        indicator: Image{
              width:40; height:width;
              x: parent.width - 50
              anchors.verticalCenter: parent.verticalCenter
              source: comboBox.down ? "qrc:/res/arrow.png":"qrc:/res/arrow.png";
        }

        contentItem: Text {
              leftPadding: 20
              rightPadding: comboBox.indicator.width + comboBox.spacing

              text: comboBox.displayText
              color: "black"
              font.pixelSize: 25
              verticalAlignment: Text.AlignVCenter
              horizontalAlignment: Text.AlignLeft
              elide: Text.ElideRight
        }

        delegate: ItemDelegate{
            text: name
            width: comboBox.width
            onClicked: {
                appController.mainCurrency = name
                console.log("clicked:", name)
            }
        }
    }

    ListView {
        anchors.horizontalCenter: parent.horizontalCenter
        y: 150
        width: 150
        height: parent.height - 200

        model: currencyModel

        delegate: Text {
            required property string name
            required property string value

            text: name + " = " + value
            font.family: "nunito"
            font.pixelSize: 25
            color: name == "MKD" ? "green" : "black"
            font.bold: name == "MKD" ? true : false
        }
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
