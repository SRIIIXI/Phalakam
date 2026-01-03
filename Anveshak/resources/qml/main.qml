import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtWebEngine

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 768
    title: "Anveshak Browser"
    
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        
        // Toolbar
        ToolBar {
            Layout.fillWidth: true
            
            RowLayout {
                anchors.fill: parent
                spacing: 5
                
                ToolButton {
                    text: "←"
                    enabled: webView.canGoBack
                    onClicked: webView.goBack()
                }
                
                ToolButton {
                    text: "→"
                    enabled: webView.canGoForward
                    onClicked: webView.goForward()
                }
                
                ToolButton {
                    text: "⟳"
                    onClicked: webView.reload()
                }
                
                TextField {
                    id: addressBar
                    Layout.fillWidth: true
                    placeholderText: "Enter URL..."
                    text: webView.url
                    selectByMouse: true
                    
                    onAccepted: {
                        var url = text
                        if (url.indexOf("://") === -1) {
                            if (url.indexOf(".") === -1) {
                                // Search query
                                url = "https://www.google.com/?q=" + encodeURIComponent(url)
                            } else {
                                // Domain without protocol
                                url = "https://" + url
                            }
                        }
                        webView.url = url
                    }
                }
                
                ToolButton {
                    text: webView.loading ? "✕" : "⌂"
                    onClicked: {
                        if (webView.loading) {
                            webView.stop()
                        } else {
                            webView.url = "https://www.google.com"
                        }
                    }
                }
            }
        }
        
        // Progress bar
        ProgressBar {
            Layout.fillWidth: true
            Layout.preferredHeight: 3
            visible: webView.loading
            value: webView.loadProgress / 100.0
        }
        
        // Web view
        WebEngineView {
            id: webView
            Layout.fillWidth: true
            Layout.fillHeight: true
            url: "https://www.google.com"
            
            onLoadingChanged: function(loadRequest) {
                if (loadRequest.status === WebEngineView.LoadSucceededStatus) {
                    addressBar.text = webView.url
                }
            }
            
            onUrlChanged: {
                addressBar.text = url
            }
        }
        
        // Status bar
        ToolBar {
            Layout.fillWidth: true
            
            Label {
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                text: webView.loading ? "Loading..." : "Ready"
            }
        }
    }
}
