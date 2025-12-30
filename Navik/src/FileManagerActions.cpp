#include "FileManagerActions.hpp"

FileManagerActions::FileManagerActions()
{
}

void FileManagerActions::CreateActions()
{
    fileExit = new QAction(QIcon(":FILE-EXIT"),("Exit"),NULL);
    editCopy = new QAction(QIcon(":EDIT-COPY"),("Copy"),NULL);
    editCut = new QAction(QIcon(":EDIT-CUT"),("Cut"),NULL);
    editPaste = new QAction(QIcon(":EDIT-PASTE"),("Paste"),NULL);
    editMoveto = new QAction(QIcon(":EDIT-MOVETO"),("Move To..."),NULL);
    editCopyto = new QAction(QIcon(":EDIT-COPYTO"),("Copy To..."),NULL);
    editSelectAll = new QAction(QIcon(":EDIT-SELECTALL"),("Select All"),NULL);
    viewDetailed = new QAction(QIcon(":VIEW-DETAILED"),("Detailed"),NULL);
    viewHidden = new QAction(QIcon(":VIEW-HIDDEN"),("Show Hidden"),NULL);
    viewIcon = new QAction(QIcon(":VIEW-ICON"),("Icons"),NULL);
    viewThumbnail = new QAction(QIcon(":VIEW-THUMBNAIL"),("Thumbnails"),NULL);
    viewHome = new QAction(QIcon(":VIEW-HOME"),("Home"),NULL);
    viewUp = new QAction(QIcon(":VIEW-UP"),("Up"),NULL);
    toolDisk = new QAction(QIcon(":TOOL-DISK"),("Disks"),NULL);
    toolPreferences = new QAction(QIcon(":TOOL-PREFERENCE"),("Preferences"),NULL);
    toolProperties = new QAction(QIcon(":TOOL-PROPERTIES"),("Properties"),NULL);
    toolSearch = new QAction(QIcon(":TOOL-SEARCH"),("Search"),NULL);
    toolTerminal = new QAction(QIcon(":TOOL-TERMINAL"),("Terminal"),NULL);
    help = new QAction(QIcon(":HELP"),("Help"),NULL);
}

void FileManagerActions::PopulateToolbar(QToolBar &tbar)
{
    tbar.addAction(viewUp);
    tbar.addAction(viewHome);
    tbar.addSeparator();
    tbar.addAction(viewIcon);
    tbar.addAction(viewDetailed);
    tbar.addAction(viewThumbnail);
    tbar.addSeparator();
    tbar.addAction(editCopy);
    tbar.addAction(editMoveto);
    tbar.addSeparator();
    tbar.addAction(toolSearch);
    tbar.addAction(toolTerminal);
    tbar.addAction(toolPreferences);
    tbar.setMovable(false);
    tbar.setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void FileManagerActions::PopulateMenubar(QMenuBar &mbar)
{
    fileMenu.setTitle("File");
    fileMenu.addAction(fileExit);

    editMenu.setTitle("Edit");
    editMenu.addAction(editSelectAll);
    editMenu.addSeparator();
    editMenu.addAction(editCut);
    editMenu.addAction(editCopy);
    editMenu.addAction(editPaste);
    editMenu.addSeparator();
    editMenu.addAction(editCopyto);
    editMenu.addAction(editMoveto);

    viewMenu.setTitle("View");
    viewMenu.addAction(viewHidden);
    viewMenu.addAction(viewDetailed);
    viewMenu.addAction(viewIcon);
    viewMenu.addAction(viewThumbnail);
    viewMenu.addSeparator();
    viewMenu.addAction(viewUp);
    viewMenu.addAction(viewHome);

    toolMenu.setTitle("Tool");
    toolMenu.addAction(toolPreferences);
    toolMenu.addAction(toolSearch);
    toolMenu.addAction(toolDisk);
    toolMenu.addAction(toolTerminal);
    toolMenu.addAction(toolProperties);

    helpMenu.setTitle("Help");
    helpMenu.addAction(help);
    helpMenu.addSeparator();
    helpMenu.addAction(QIcon(":FILEMANAGER"),"About File Manager");
    helpMenu.addAction(QIcon(":QTLOGO"),"About Qt");

    mbar.addMenu(&fileMenu);
    mbar.addMenu(&editMenu);
    mbar.addMenu(&viewMenu);
    mbar.addMenu(&toolMenu);
    mbar.addMenu(&helpMenu);
}
