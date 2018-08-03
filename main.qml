import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Window {
    id: window
    visible: true
    width: 720
    height: 680
    title: qsTr("Account")

    Rectangle{
        id:rootbackground
        y: 160
        color:"white"
        anchors.fill: parent



        PersonalData {
            id: personalData
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.topMargin: 20
            anchors.top: parent.top
            z:100
        }

        ListOfWallets{
            anchors.top: personalData.bottom
            anchors.topMargin: 20
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.bottom: listOfCard.top
            anchors.bottomMargin: 20

        }

        ListOfCard {
            id: listOfCard
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
        }

    }
}



