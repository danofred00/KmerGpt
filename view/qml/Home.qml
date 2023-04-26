import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {

    // property string title: "KmerGpt"

    id: homePage
    anchors.fill: parent

    ListModel {
        id: chatModel
        ListElement {role:"assistant"; message:"Hi User"}
        ListElement {role:"user"; message:"Hi Assistant"}
        ListElement {role:"assistant"; message:"Hi User"}
        ListElement {role:"user"; message:"Hi Assistant"}
        ListElement {role:"assistant"; message:"Hi User"}
        ListElement {role:"user"; message:"Hi Assistant"}
        ListElement {role:"user"; message:"bonjou, je voudrai avoir si possible un nouveau item"}
        ListElement {role:"user"; message:"Hi Assistant"}
        ListElement {role:"assistant"; message:"Hi User"}
        ListElement {role:"user"; message:"Hi Assistant"}
        ListElement {role:"assistant"; message:"Hi User"}
        ListElement {role:"user"; message:"Hi Assistant"}
        ListElement {role:"assistant"; message:"Hi User"}
        ListElement {role:"user"; message:"Hi Assistant"}
        ListElement {role:"user"; message:"bonjou, je voudrai avoir si possible un nouveau item"}
        ListElement {role:"user"; message:"Hi Assistant"}
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

        delegate: Rectangle {

            property real maxWidth: chatListView.width * 0.65

            implicitWidth: textDelegate.implicitWidth > maxWidth ? maxWidth : textDelegate.implicitWidth
            x: model.role === "assistant" ? 0 : chatListView.width - width
            implicitHeight: textDelegate.implicitHeight
            color: model.role === "user" ? "red": "green"
            Text {
                id:textDelegate;
                text: model.message
                wrapMode: Text.Wrap
                anchors.fill: parent
                padding: 10
            }
            radius: 5
        }
        spacing: 10
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
                }
            }
        }
    }

}
