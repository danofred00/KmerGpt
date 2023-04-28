import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    width: 360
    height: 740
    visible: true
    title: qsTr("KmerGpt")

    FirstScreen {
        id: firstScreen
        anchors.fill: parent
    }

    Loader {
        id: loader
    }

    StackView {

        id: stack
        initialItem: firstScreen
        anchors.fill: parent
    }


}
