import QtQuick 2.15

Rectangle {

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

