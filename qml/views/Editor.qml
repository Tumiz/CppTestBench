import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
Window{
    id:editor
    width:400
    height: 400
    title:"Editor"
    property alias text: textArea.text
    ColumnLayout{
        anchors.fill: parent
        FileDialog{
            id:fileDialog
            nameFilters: ["Cpp file (*.cpp)","All files (*)"]
            onAccepted: {
                textArea.text=CPP.readFile(fileUrl)

            }
        }
        Row{
            spacing: 2
            Button{
                text:"打开文件"
                onClicked:fileDialog.open()
            }
            Button{
                text:"保存"
                onClicked: CPP.saveFile(textArea.text)
            }
        }
        TextArea{
            id:textArea
            Layout.fillHeight: true
            Layout.fillWidth: true
            selectByMouse: true
        }
    }
}
