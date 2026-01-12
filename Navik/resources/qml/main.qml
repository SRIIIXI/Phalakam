import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    id: root
    visible: true
    width: 1200
    height: 800

    title: "Navik File Manager"
    Material.theme: Material.Dark

    // Navigation Drawer
    Drawer {
        id: navDrawer
        width: 250
        height: root.height
        modal: true

        Material.theme: Material.Dark;

        Column {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 5

            Label {
                text: "Navigation"
                font.pixelSize: 18
                font.bold: true
            }

            Rectangle { width: parent.width; height: 1; color: "#cccccc" }

            ItemDelegate {
                text: "Home"
                width: parent.width
                icon.name: "user-home"
            }
            ItemDelegate {
                text: "Documents"
                width: parent.width
                icon.name: "folder-documents"
            }
            ItemDelegate {
                text: "Downloads"
                width: parent.width
                icon.name: "folder-download"
            }
            ItemDelegate {
                text: "Pictures"
                width: parent.width
                icon.name: "folder-pictures"
            }
            ItemDelegate {
                text: "Music"
                width: parent.width
                icon.name: "folder-music"
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Left Navigation Bar (48px)
        Rectangle {
            Layout.preferredWidth: 48
            Layout.fillHeight: true
            color: "#2c2c2c"

            Column {
                anchors.fill: parent
                spacing: 0

                Button {
                    width: 48
                    height: 48
                    flat: true
                    icon.source: "data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='white'%3E%3Cpath d='M3 18h18v-2H3v2zm0-5h18v-2H3v2zm0-7v2h18V6H3z'/%3E%3C/svg%3E"
                    onClicked: navDrawer.open()
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: "#444444"
                }

                Button {
                    width: 48
                    height: 48
                    flat: true
                    icon.source: "data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='white'%3E%3Cpath d='M10 20v-6h4v6h5v-8h3L12 3 2 12h3v8z'/%3E%3C/svg%3E"
                }

                Button {
                    width: 48
                    height: 48
                    flat: true
                    icon.source: "data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='white'%3E%3Cpath d='M20 6h-8l-2-2H4c-1.1 0-2 .9-2 2v12c0 1.1.9 2 2 2h16c1.1 0 2-.9 2-2V8c0-1.1-.9-2-2-2z'/%3E%3C/svg%3E"
                }

                Button {
                    width: 48
                    height: 48
                    flat: true
                    icon.source: "data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='white'%3E%3Cpath d='M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm-2 15-5-5 1.41-1.41L10 14.17l7.59-7.59L19 8l-9 9z'/%3E%3C/svg%3E"
                }
            }
        }

        // Middle Pane - Directory Tree (150px)
        Rectangle {
            Layout.preferredWidth: 150
            Layout.fillHeight: true
            color: "#f5f5f5"
            border.color: "#cccccc"
            border.width: 1

            ScrollView {
                anchors.fill: parent
                clip: true

                Column {
                    width: parent.width
                    spacing: 2
                    padding: 5

                    Label {
                        text: "USER"
                        font.pixelSize: 10
                        font.bold: true
                        color: "#666666"
                        leftPadding: 5
                    }

                    Repeater {
                        model: ["Home", "Documents", "Downloads", "Pictures"]
                        delegate: ItemDelegate {
                            width: parent.width - 10
                            height: 32
                            text: modelData
                            font.pixelSize: 12
                            onClicked: currentPath.text = "/home/user/" + modelData.toLowerCase()
                        }
                    }

                    Rectangle {
                        width: parent.width - 10
                        height: 1
                        color: "#cccccc"
                    }

                    Label {
                        text: "FILESYSTEM"
                        font.pixelSize: 10
                        font.bold: true
                        color: "#666666"
                        leftPadding: 5
                        topPadding: 5
                    }

                    ItemDelegate {
                        width: parent.width - 10
                        height: 32
                        text: "Root (/)"
                        font.pixelSize: 12
                        onClicked: currentPath.text = "/"
                    }

                    Rectangle {
                        width: parent.width - 10
                        height: 1
                        color: "#cccccc"
                    }

                    Label {
                        text: "DISKS"
                        font.pixelSize: 10
                        font.bold: true
                        color: "#666666"
                        leftPadding: 5
                        topPadding: 5
                    }

                    Repeater {
                        model: [
                            {name: "System (sda1)", size: "250 GB", mounted: true},
                            {name: "Data (sdb1)", size: "500 GB", mounted: true},
                            {name: "USB Drive", size: "32 GB", mounted: false}
                        ]
                        delegate: ItemDelegate {
                            width: parent.width - 10
                            height: 40

                            Column {
                                anchors.verticalCenter: parent.verticalCenter
                                spacing: 2

                                Label {
                                    text: modelData.name
                                    font.pixelSize: 11
                                }
                                Label {
                                    text: modelData.size + (modelData.mounted ? " • Mounted" : " • Unmounted")
                                    font.pixelSize: 9
                                    color: modelData.mounted ? "#4CAF50" : "#999999"
                                }
                            }
                        }
                    }
                }
            }
        }

        // Right Pane - File List
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"

            ColumnLayout {
                anchors.fill: parent
                spacing: 0

                // Top Bar - Path
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40
                    color: "#f9f9f9"
                    border.color: "#cccccc"
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 8
                        spacing: 8

                        Button {
                            text: "←"
                            Layout.preferredWidth: 30
                        }
                        Button {
                            text: "→"
                            Layout.preferredWidth: 30
                        }
                        Button {
                            text: "↑"
                            Layout.preferredWidth: 30
                        }

                        TextField {
                            id: currentPath
                            Layout.fillWidth: true
                            text: "/home/user/Documents"
                            selectByMouse: true
                        }
                    }
                }

                // File List
                ListView {
                    id: fileList
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true

                    model: ListModel {
                        ListElement { name: "Project Files"; type: "folder"; size: ""; modified: "Today" }
                        ListElement { name: "Report.pdf"; type: "file"; size: "2.4 MB"; modified: "Yesterday" }
                        ListElement { name: "Budget 2024.xlsx"; type: "file"; size: "156 KB"; modified: "Jan 10" }
                        ListElement { name: "Presentation.pptx"; type: "file"; size: "8.9 MB"; modified: "Jan 9" }
                        ListElement { name: "Archive"; type: "folder"; size: ""; modified: "Jan 5" }
                        ListElement { name: "Notes.txt"; type: "file"; size: "4 KB"; modified: "Jan 3" }
                    }

                    delegate: ItemDelegate {
                        width: fileList.width
                        height: 40

                        onClicked: {
                            fileList.currentIndex = index
                            selectedFile.text = name
                            selectedSize.text = type === "folder" ? "Folder" : size
                            selectedModified.text = "Modified: " + modified
                        }

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 8
                            spacing: 10

                            Label {
                                text: type === "folder" ? "📁" : "📄"
                                font.pixelSize: 16
                            }

                            Label {
                                text: name
                                Layout.fillWidth: true
                                font.pixelSize: 13
                            }

                            Label {
                                text: size
                                Layout.preferredWidth: 80
                                horizontalAlignment: Text.AlignRight
                                font.pixelSize: 11
                                color: "#666666"
                            }

                            Label {
                                text: modified
                                Layout.preferredWidth: 100
                                horizontalAlignment: Text.AlignRight
                                font.pixelSize: 11
                                color: "#666666"
                            }
                        }
                    }

                    highlight: Rectangle {
                        color: "#e3f2fd"
                    }
                }

                // Status Bar
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 30
                    color: "#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 8
                        spacing: 15

                        Label {
                            id: selectedFile
                            text: "6 items"
                            font.pixelSize: 11
                        }

                        Rectangle {
                            width: 1
                            height: 16
                            color: "#cccccc"
                        }

                        Label {
                            id: selectedSize
                            text: ""
                            font.pixelSize: 11
                        }

                        Label {
                            id: selectedModified
                            text: ""
                            font.pixelSize: 11
                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }
    }
}
