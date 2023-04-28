import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "./Components" as Components

Page {

    id: root
    anchors.fill: parent

    property string username

    function addToChat(role, message)
    {
        chatModel.append(
        {
            "role": role,
            "message": message
        });
    }

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
                        // placeholderTextColor: "black"
                        wrapMode: Text.Wrap

                    }
                }

            RoundButton {

                icon.source: "qrc:/view/assets/png/send-message.png"
                display: Button.IconOnly
                onClicked: {

                    const msg = userMessage.text
                    if(msg === "")
                        return;

                    // send the message to a bot
                    OpenAI.send(msg)
                    // clear the area after sending message
                    userMessage.clear();
                    // scroll to the last message
                    chatListView.positionViewAtEnd()
                }
            }
        }
    }

    Component.onCompleted: {
        // init OpenAI services when page is loaded
        OpenAI.init()
    }

    Connections {
        target: OpenAI
        function onResponseReceived(response) {
            // response object is updated when this signal is emit
            // OpenAI.logger.d("New response from Assistant")
            console.log("New response from Assistant")
            var message = OpenAI.response.message
            addToChat(message.role, message.content)
        }

        // when request is send
        function onRequestSend() {
            // just add the message to a chat
            addToChat("user", userMessage.text)
        }
    }

}
