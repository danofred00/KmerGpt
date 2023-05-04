import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Drawer {

    required property Page page
    required property SystemPalette palette

    id: root
    width: 300
    height: parent.height

//    function assets(relativePath) {
//        return "qrc:/assets/" + relativePath;
//    }

    ColumnLayout {
        height: parent.height //* 0.97
        width: parent.width //* 0.97
        // anchors.centerIn: parent
        spacing: 5

        ToolBar {
            id: toolBar
            Layout.fillWidth: true
            Label {
                anchors.centerIn: parent
                text: qsTr("KmerGpt")
                font.pixelSize: 32
            }
        }

        // list of imtes
        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 5
            model: ListModel {
                ListElement {name:"Youtube"; url:"https://youtube.com/@Harptutos"; image: "qrc:/view/assets/png/youtube.png"}
                ListElement {name:"Telegram"; url:"https://t.me/Harptutos"; image: "qrc:/view/assets/png/telegram.png"}
                ListElement {name:"Github"; url:"https://github.com/danofred00/kmergpt"; image: "qrc:/view/assets/png/github.png"}
            }

            delegate: ItemDelegate {
                id: item

                width: listView.width

                contentItem: Row{
                    spacing: 5
                    Image {
                        source: model.image
                        fillMode: Image.PreserveAspectFit
                        width: item.icon.width
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        text: model.name
                        anchors.verticalCenter: parent.verticalCenter
                        color: palette.text.toString()
                    }
                }

                onClicked: {
                    Qt.openUrlExternally(model.url)
                }

            }

        }

        // footer
        Rectangle {
            color: "#000"
            Layout.fillWidth: true
            height: 30

            Label {
                anchors.centerIn: parent
                text: qsTr("*** By @Danofred ***")
                font.pixelSize: 14
                color: "#fff"
                font.bold: Font.Bold
            }
        }


    }
}
