import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.3

ApplicationWindow
{
    id: window
    visible: true
    width: 1024
    height: 768

    property int iconheight: 40
    property int iconwidth: 40

    title: "Lekhak Editor"
    Material.theme: Material.Light

    Row
    {
        id: rootlayout
        anchors.fill: parent;
        anchors.margins: 0

        Component.onCompleted:
        {
            drawer.close();
        }

        Drawer
        {
            id: drawer
            width: window.width * 0.25
            height: window.height

            Material.theme: Material.Light;

            Column
            {
                anchors.fill: parent

                ItemDelegate
                {
                    text: "&New"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "&Open ..."
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "&Save"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "Save &As ..."
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                MenuSeparator
                {
                    width: parent.width
                }

                ItemDelegate
                {
                    text: "S&elect All"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "&Copy"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "Cu&t"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "&Paste"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "&Undo"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "&Redo"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "&Find"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "Rep&lace"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                MenuSeparator
                {
                    width: parent.width
                }

                ItemDelegate
                {
                    text: "Settin&gs"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "&About"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                        //width: iconWidth
                        //height: iconHeight
                    }
                }

                ItemDelegate
                {
                    text: "E&xit"
                    width: parent.width

                    icon
                    {
                        source: "../images/MenuBlack.png"
                    }
                }
            }
        }

        Pane
        {
            id: navbar
            height: parent.height
            width: 48

            ToolButton
            {
                width:iconwidth
                height: iconheight
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                icon.source : "../images/MenuWhite.png";
                onClicked:
                {
                    drawer.open();
                }
                anchors.margins: 0
            }
        }

        Rectangle
        {
            id: clientarea
            height: parent.height
            width: parent.width - navbar.width
            anchors.margins: 0

            ScrollView
            {
                width: parent.width
                height: parent.height - statusbar.height
                anchors.margins: 0

                TextArea
                {
                    id: edittext
                    anchors.fill: parent;
                    anchors.margins: 0
                }
            }

            Pane
            {
                id: statusbar
                width: parent.width
                anchors.bottom: parent.bottom
                height: 40
            }
        }
    }
}
