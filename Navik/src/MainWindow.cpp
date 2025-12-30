#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int ht =768;
    int wd = 1024;

    // Get the primary screen object
    QScreen *screen = QGuiApplication::primaryScreen();

    // Get the available geometry (excludes taskbars/panels)
    QRect availGeom = screen->availableGeometry();

    ht = availGeom.height();
    wd = availGeom.width();
    QRect rect(wd*0.15,ht*0.15,wd*0.7,ht*0.7);
    setGeometry(rect);
}

MainWindow::~MainWindow()
{
}

bool MainWindow::Initialize()
{
    setStatusBar(&appStatusBar);

    fmActions.CreateActions();
    fmActions.PopulateMenubar(appMenuBar);
    fmActions.PopulateToolbar(appToolBar);
    addToolBar(&appToolBar);
    setMenuBar(&appMenuBar);

    InitDirNavigationPane();
    InitDirDetailsPane();

    setCentralWidget(&appCentralWidget);

    return true;
}

void MainWindow::InitDirNavigationPane()
{
    QString rootPathstr = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    dirModel.setRootPath(rootPathstr);
    dirModel.setFilter(QDir::AllDirs|QDir::Drives|QDir::NoDotAndDotDot|QDir::Hidden);

    QModelIndex rootModelIndex = dirModel.setRootPath(rootPathstr);

    dirTree.expand(rootModelIndex);

    dirTree.setModel(&dirModel);

    dirTree.setHeaderHidden(false);
    dirTree.setColumnHidden(1,true);
    dirTree.setColumnHidden(2,true);
    dirTree.setColumnHidden(3,true);
    dirTree.setColumnWidth(0,200);
    dirTree.setMinimumWidth(200);
    dirTree.setMaximumWidth(200);
    dirTree.setAnimated(true);
    dirTree.setExpandsOnDoubleClick(true);

    connect(&dirTree,SIGNAL(activated(const QModelIndex)), this,SLOT(DirectoryItemSelected(const QModelIndex)));

    appCentralWidget.addWidget(&dirTree);
}

void MainWindow::InitDirDetailsPane()
{
    QString rootPathstr = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    ViewMode vmode;
    vmode = (ViewMode)0;
    dirDetailedView.Initialize(&appCentralWidget,vmode,rootPathstr);
    appCentralWidget.addWidget(dirDetailedView.GetWidget());
}

void MainWindow::DirectoryItemSelected(const QModelIndex & index)
{
    QFileInfo inf = dirModel.fileInfo(index);
    dirDetailedView.SetSelectedDirectory( inf.absoluteFilePath());
}
