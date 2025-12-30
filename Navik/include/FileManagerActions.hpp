#ifndef FILEMANAGERACTIONS_H
#define FILEMANAGERACTIONS_H
#include<QtCore>
#include<QIcon>
#include<QAction>
#include<QToolBar>
#include<QMenu>
#include<QMenuBar>

class FileManagerActions
{
public:
    FileManagerActions();
    void CreateActions();
    void PopulateToolbar(QToolBar &tbar);
    void PopulateMenubar(QMenuBar &mbar);
private:
    QAction* fileExit;
    QAction* editCopy;
    QAction* editCut;
    QAction* editPaste;
    QAction* editMoveto;
    QAction* editCopyto;
    QAction* editSelectAll;
    QAction* viewDetailed;
    QAction* viewHidden;
    QAction* viewIcon;
    QAction* viewThumbnail;
    QAction* viewHome;
    QAction* viewUp;
    QAction* toolDisk;
    QAction* toolPreferences;
    QAction* toolProperties;
    QAction* toolSearch;
    QAction* toolTerminal;
    QAction* help;

    QMenu fileMenu, editMenu, viewMenu, toolMenu, helpMenu;
};

#endif // FILEMANAGERACTIONS_H
