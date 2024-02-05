import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0


Window {
    visible: true
    width:  500
    height:	620
    id: root
    title: qsTr("Testing Fingerprint Grow RX305")

    onWidthChanged: {
        if (root.width > root.height) {
            container.width = root.height
            container.height = root.width
            container.rotation = -90
            buttonsWidth = 350
            buttonsHeight = 100
            pixelSize = 32
        }
    }

    property int buttonsWidth: 140
    property int buttonsHeight: 40
    property int pixelSize: 14

    Item {
        id: container
        width:  500
        height:	620
        anchors.centerIn: parent

        Rectangle {
            id: input
            anchors {
                top: container.top
                topMargin: 40
                left: parent.left
                leftMargin: 40
            }
            border.color: "black"
            height: 40
            width: 300
            clip: true

            TextInput{
                id: commandToSend
                anchors{
                    fill: parent
                    verticalCenter: parent.verticalCenter
                }
                text: "EF01ffffffff010003010005"
                padding: 10
                validator: RegExpValidator { regExp: /[0-9A-Fa-f]{1,200}/ }
            }
        }

        Button {
            id: btnSendCommand
            text: "Send command"
            width: buttonsWidth
            height: buttonsHeight
            font.pixelSize: pixelSize
            anchors.top: input.bottom
            anchors.topMargin: 40
            anchors.left: input.left
            onClicked: {
                serialPort.write(commandToSend.text)
            }
        }
    }
}
