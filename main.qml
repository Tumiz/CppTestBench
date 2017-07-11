import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import "./qml/views"
Window {
    visible: true
    width: 400
    height: 40
    title: qsTr("Hello World")
    Row{
        id: root
        width: 300
        anchors.leftMargin: 4
        anchors.rightMargin: 4
        anchors.fill: parent
        TextField{
            id:input
            width: 108
            height: 40
        }

        Button{
            text:"function"
            onClicked:editor.show()
            Editor{
                id:editor
            }
        }
        Text{
            anchors.verticalCenter: parent.verticalCenter
            text:CPP.result
        }
        Button{
            text:"run"
            onClicked: {
                CPP.gen(input.text,editor.text)
                CPP.run()
            }
        }
    }
}
