#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QTreeView>
#include <QtCore>
#include <QFileSystemModel>
#include <QSplitter>
#include <QDesktopServices>
#include <QScreen>
#include <QStatusBar>
#include <QStandardPaths>

#include "DirectoryView.hpp"
#include "FileManagerActions.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool Initialize();
protected:
    void InitDirNavigationPane();
    void InitDirDetailsPane();
protected slots:
    void DirectoryItemSelected(const QModelIndex & index);
private:
    QToolBar appToolBar;
    QMenuBar appMenuBar;
    QStatusBar appStatusBar;

    FileManagerActions fmActions;

    QSplitter appCentralWidget;

    QTreeView   dirTree;
    QFileSystemModel dirModel;

    DirectoryView dirDetailedView;
};

#endif // MAINWINDOW_H
