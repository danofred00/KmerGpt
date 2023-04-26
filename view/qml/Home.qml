import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "./Components" as Components

Page {

    // property string title: "KmerGpt"

    id: homePage
    anchors.fill: parent

    header: ToolBar {

        ToolButton {
            text: "\u2630"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                console.log("Drawer Button Clicked")
                drawer.open()
            }
        }

        Text {
            text: "KmerGPT"
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: 300
        height: parent.height

    }

    ListView {

        id: chatListView
        model: chatModel
        width: parent.width * 0.95
        anchors.horizontalCenter: parent.horizontalCenter
        height: sendMessage.y // parent.height - sendMessage.height
        clip: true
        Component.onCompleted: chatListView.positionViewAtEnd()
        delegate: Components.ChatMessageDelegate { }
        spacing: 10

        Components.TmpChatListModel {
                    id: chatModel
                }
    }


    Item {

        id: sendMessage
        width: parent.width * 0.9
        height: 60
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10

        RowLayout {
            anchors.fill: parent
                ScrollView {
                    Layout.maximumHeight: sendMessage.height
                    Layout.fillWidth: true
                    height: parent.height
                    TextArea {
                        id: userMessage
                        anchors.fill: parent
                        verticalAlignment: Qt.AlignVCenter
                        placeholderText: qsTr("Type any text")
                        placeholderTextColor: "black"
                        wrapMode: Text.Wrap

                    }
                }

            Button {
                text: "send"
                onClicked: {
                    console.log("message Send")
                    chatModel.append(
                    {
                        "role": 'user',
                        "message": userMessage.text
                    })

                    // clear the area after sending message
                    userMessage.clear();

                    // scroll to the last message
                    chatListView.positionViewAtEnd()
                }
            }
        }
    }

}
