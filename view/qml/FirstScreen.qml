import QtQuick 2.15
import QtQuick.Controls

Page {

    id: root

    function validateInput(input) {
        if (input) {
            var regex = new RegExp(/[a-zA-Z_ ]+[\da-zA-Z_ ]*/)
            if (regex.test(input.text))
                return true;
        }
        return false;
    }

    function goHome() {
        if (validateInput(usernameField)) {
            homePage.username = usernameField.text
            stack.push(homePage);
        }
    }

    header: ToolBar {
        ToolButton {
            icon.source: "qrc:/view/assets/png/arrow.png"
            onClicked: {
                console.log("Click")
            }
        }
    }

    Item {

        anchors.centerIn: parent
        implicitWidth: column.implicitWidth
        implicitHeight: column.implicitHeight
        //color: Qt.rgba(0,0,0,1)

        Column{
            id: column
            anchors.left: parent.left
            Label {
                text: qsTr("Your Name")
            }

            TextField {
                id: usernameField
                validator: RegularExpressionValidator {
                    regularExpression: /[a-zA-Z_ ]+[\da-zA-Z_ ]*/
                }
                onAccepted: goHome()
            }
        }
    }

    Button {
        id: btnStart
        text: qsTr("Start")
        anchors.bottomMargin: 10
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
        padding: 10

        onClicked: goHome()
    }
}
