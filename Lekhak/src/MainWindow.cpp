#include <QtGui>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QFontDialog>
#include "MainWindow.hpp"

MainWindow::MainWindow()
{
    resize(600,400);

    textEdit = new QPlainTextEdit;
    setCentralWidget(textEdit);

    CreateActions();
    CreateMenus();
    CreateToolBars();
    CreateStatusBar();

    ReadSettings();

    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(DocumentWasModified()));

    SetCurrentFile("");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (MayBeSave())
    {
        WriteSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::NewFile()
{
    if (MayBeSave()) {
        textEdit->clear();
        SetCurrentFile("");
    }
}

void MainWindow::Open()
{
    if (MayBeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"),
                                                        QDir::homePath(),
                                                        "All files (*.*)");
        if (!fileName.isEmpty())
            LoadFile(fileName);
    }
}

bool MainWindow::Save()
{
    if (curFile.isEmpty())
    {
        return SaveAs();
    }
    else
    {
        return SaveFile(curFile);
    }
}

bool MainWindow::SaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save As..."),QDir::homePath(),"All files (*.*)");
    if (fileName.isEmpty())
        return false;

    return SaveFile(fileName);
}

void MainWindow::About()
{
   QMessageBox::about(this, tr("About Editor"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}

void MainWindow::DocumentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}

void MainWindow::CreateActions()
{
    // File group
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(NewFile()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(Open()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(Save()));

    saveAsAct = new QAction(QIcon(":/images/saveas.png"),tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(SaveAs()));

    exitAct = new QAction(QIcon(":/images/exit.png"),tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    // Edit group
    undoAct = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo's the current changes"));

    redoAct = new QAction(QIcon(":/images/redo.png"), tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo's the current changes"));

    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    cutAct->setEnabled(false);
    connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));
    connect(textEdit, SIGNAL(copyAvailable(bool)), cutAct, SLOT(setEnabled(bool)));

    copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    copyAct->setEnabled(false);
    connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy())); 
    connect(textEdit, SIGNAL(copyAvailable(bool)), copyAct, SLOT(setEnabled(bool)));

    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

    selectallAct = new QAction(QIcon(":/images/selectall.png"), tr("Select Al&l"), this);
    selectallAct->setShortcuts(QKeySequence::SelectAll);
    selectallAct->setStatusTip(tr("Select all deselect the document contents"));
    connect(selectallAct, SIGNAL(triggered()), textEdit, SLOT(selectAll()));

    // View
    findAct = new QAction(QIcon(":/images/find.png"),tr("Find"), this);
    findAct->setStatusTip(tr("Search for a text or a phrase"));
    findAct->setShortcuts(QKeySequence::Find);
    connect(findAct, SIGNAL(triggered()), this, SLOT(Find()));

    replaceAct = new QAction(QIcon(":/images/replace.png"),tr("Replace"), this);
    replaceAct->setStatusTip(tr("Replace a text or a phrase"));
    replaceAct->setShortcuts(QKeySequence::Replace);
    connect(replaceAct, SIGNAL(triggered()), this, SLOT(Replace()));

    fontAct = new QAction(QIcon(":/images/font.png"),tr("Font"), this);
    fontAct->setStatusTip(tr("Search for a text or a phrase"));
    connect(fontAct, SIGNAL(triggered()), this, SLOT(ChangeFont()));

    // About group
    aboutAct = new QAction(QIcon(":/images/editor.png"),tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(About()));

    aboutQtAct = new QAction(QIcon(":/images/qtlogo.png"),tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::CreateMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(selectallAct);

    viewMenu = menuBar()->addMenu(tr("Vie&w"));
    viewMenu->addAction(findAct);
    viewMenu->addAction(replaceAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fontAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::CreateToolBars()
{
    appToolBar = addToolBar(tr("File"));
    appToolBar->addAction(newAct);
    appToolBar->addAction(openAct);
    appToolBar->addAction(saveAct);
    appToolBar->addSeparator();
    appToolBar->addAction(cutAct);
    appToolBar->addAction(copyAct);
    appToolBar->addAction(pasteAct);
    appToolBar->setFloatable(false);
    appToolBar->setMovable(false);
    appToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

void MainWindow::ChangeFont()
{
    textEdit->setFont(QFontDialog::getFont(0, textEdit->font()));
}

void MainWindow::CreateStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::ReadSettings()
{
//    QSettings settings("Trolltech", "Application Example");
//    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
//    QSize size = settings.value("size", QSize(400, 400)).toSize();
//    resize(size);
//    move(pos);
}

void MainWindow::WriteSettings()
{
//    QSettings settings("Trolltech", "Application Example");
//    settings.setValue("pos", pos());
//    settings.setValue("size", size());
}

bool MainWindow::MayBeSave()
{
    if (textEdit->document()->isModified())
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Editor"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return Save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::LoadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Editor"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    SetCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::SaveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Editor"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    SetCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::SetCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

QString MainWindow::StrippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

bool MainWindow::IsValidTextFile(QString fileName)
{
    if(fileName.length()<2 || fileName.isEmpty())
    {
        return false;
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    return true;
}

void MainWindow::Find()
{
    frDlg.setModal(false);
    frDlg.show();
}

void MainWindow::Find(QString text)
{

    QString searchString = textEdit->toPlainText();
    QTextDocument *document = textEdit->document();

    bool found = false;

    if (isFirstTime == false)
        document->undo();

    searchString = text;

    if (searchString.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Search Field"),
                "The search field is empty. Please enter a word and click Find.");
    }
    else
    {

        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);

        cursor.beginEditBlock();

        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setForeground(Qt::white);
        colorFormat.setBackground(Qt::darkBlue);

        while (!highlightCursor.isNull() && !highlightCursor.atEnd())
        {
            highlightCursor = document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);

            if (!highlightCursor.isNull())
            {
                found = true;
                highlightCursor.movePosition(QTextCursor::WordRight,
                                       QTextCursor::KeepAnchor);
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }

        cursor.endEditBlock();
        isFirstTime = false;

        if (found == false) {
            QMessageBox::information(this, tr("Word Not Found"),
                "Sorry, the word cannot be found.");
        }
    }

}

void MainWindow::Replace()
{
}

void MainWindow::Replace(QString origtext, QString newtext)
{

}
