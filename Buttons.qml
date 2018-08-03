import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle{
    id: wrapBtn
    state: "hideBtn"
    height: 0
    anchors.bottom: parent.bottom
    width: parent.width

    Button{
        id: view
        width: parent.width/2
        height: parent.height
        anchors.left: parent.left
        onClicked: {

        }
    }
    Button{
        id: add
        width: parent.width/2
        height: parent.height
        anchors.right: parent.right
        onClicked: {
            fileDialog.open();
        }
    }


    states: [
        State {
            name: "showBtn"
            PropertyChanges {target: wrapBtn; height: 40}
            PropertyChanges {target: add; text:"Add"}
            PropertyChanges {target: view; text:"View"}

        },
        State {
            name: "hideBtn"
            PropertyChanges {target: wrapBtn; height: 0}
            PropertyChanges {target: add; text:""}
            PropertyChanges {target: view; text:""}
        }
    ]

    transitions: [
        Transition {
            from: "*"
            to: "*"
            PropertyAnimation{target: wrapBtn; properties: "height"; duration: 500}
        }
    ]

    MouseArea{
        id:mouseBTN
        anchors.fill: parent
    }
    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        //visible: true
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
            //Qt.quit()
        }
    }
}
