import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2



Rectangle{
    id:persData
    height: personalData.height
    color: "transparent"

    Image{
        id: mainphoto
        state: "return"
        source: "image/old_fox.jpg"
        //        anchors.centerIn: rootbackground
        opacity: 1
        visible: false
        z:101

        MouseArea{
            id: outFrom
            anchors.fill: parent
            hoverEnabled: true
            onEntered:{
                out.visible = true
                back.visible = true
            }
            onExited: {
                out.visible = false
                back.visible = false
            }
            onClicked: {
                photomousearea.hoverEnabled = true
                mainphoto.visible = false
            }

        }
        Rectangle{
            id: back
            anchors.fill: parent
            color:"#000"
            opacity: 0.5
            visible: false
        }
        Image{
            id:out
            source: "image/out.png"
            anchors.centerIn: parent
            sourceSize.height:50
            visible: false
        }
    }

    //    Rectangle{
    //        id: backGroundMainPhoto
    //        anchors.fill: rootbackground
    //        color:"black"
    //        opacity: 0.6
    //        visible: false
    //        z:100
    //    }

    GroupBox{
        id:personalData
        //Layout.fillWidth: true
        anchors{ left: parent.left; right: parent.right}

        background: Rectangle {
            width: parent.width
            height: parent.height
            color: "transparent"
            border.color: "#4b0101"
            radius: 10
        }

        label: Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.top
            anchors.bottomMargin: -height/2
            color: "white"
            border.color: "#4b0101"
            radius: 10
            width: parent.width * 0.7
            height: title.font.pixelSize
            Text {
                id: title
                text: qsTr("Personal Data")
                anchors.centerIn: parent
                font.pixelSize: 28
            }
        }

        RowLayout{
            width: parent.width
            spacing: 20

            Image{
                id: photo
                source: "image/old_fox.jpg"
                Layout.column: 0
                sourceSize.height: 120
                sourceSize.width: 120

                MouseArea {
                    id:photomousearea
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered:{
                        backZoom.visible = true
                        zoom.visible = true
                    }
                    onExited: {
                        backZoom.visible = false
                        zoom.visible = false
                    }
                    onClicked:{
                        mainphoto.visible = true
                        photomousearea.hoverEnabled = false
                    }
                    Rectangle{
                        id:backZoom
                        anchors.fill: parent
                        color:"black"
                        opacity: 0.5
                        visible: false
                    }

                    Image {
                        id: zoom
                        source: "image/in.png"
                        anchors.centerIn: parent
                        visible: false
                        sourceSize {height: 30; width: 30}
                    }
                }
            }


            GridLayout{
                x: photo.width + 20
                rows: 4
                flow: GridLayout.TopToBottom
                columnSpacing: 20

                Text{ text: "FirstName:" }
                Text{ text: "LastName:" }
                Text{ text: "Age:" }
                Text{ text: "Company:" }

                TextInput{text: "Alexander";font.pointSize: 9}
                TextInput{text: "Anisimov";font.pointSize: 9}
                TextInput{text: "21";font.pointSize: 9}
                TextInput{text: "IT-Company"; font.pointSize: 9}

                Text{text: "email:" }
                TextInput{text: "example_mail@gmail.com";font.pointSize: 9; Layout.column: 4}
            }

            Button{
                id: editBtn
                text: "Edit"
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                onClicked: {

                }
            }
        }
    }
}

