import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import DoWallet 1.0

GroupBox {
    id: control
    title: qsTr("GroupBox")
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
        width: parent.width * 0.7
        height: title.font.pixelSize
        radius: 10
        Text {
            id: title
            text: qsTr("My wallets")
            anchors.centerIn: parent
            font.pixelSize: 28
        }
    }

    ColumnLayout {
       Frame {
            width: control.width - 20


            ListView {
                implicitWidth: parent.width
                implicitHeight: 80
                anchors.fill: parent
                clip: true
                orientation: ListView.Horizontal

                model: WalletModel {
                    list: walletList
                }

                delegate: RowLayout {
                    width: parent.width

                    CheckBox {
                        checked: model.done
                        onClicked: model.done = checked
                    }
                    Image{
                        id:card
                        source: "image/account.png"
                        sourceSize.height: 70
                    }
                    GridLayout{
                        rows: 2
                        columns: 1
                        TextInput {
                            text: model.description
                            onEditingFinished: model.description = text
                            Layout.fillWidth: true
                        }

                    }
                }
            }
        }

        RowLayout {
            Button {
                text: qsTr("Add new item")
                onClicked: walletList.appendItem()
                Layout.fillWidth: true
            }
            Button {
                text: qsTr("Remove completed")
                onClicked: walletList.removeCompletedItems()
                Layout.fillWidth: true
            }
        }
    }


}

