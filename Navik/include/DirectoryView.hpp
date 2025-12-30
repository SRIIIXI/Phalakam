#ifndef DIRECTORYVIEW_H
#define DIRECTORYVIEW_H

#include <QTreeView>
#include <QListView>
#include <QtCore>
#include <QFileSystemModel>

enum ViewMode
{
    Detailed = 0,
    Icons = 1,
    Thumbnails =2
};

class DirectoryView
{
public:
    DirectoryView();
    ~DirectoryView();
    void Initialize(QWidget *parent, ViewMode vmode, QString pathname);
    void SetViewMode(ViewMode vmode);
    void SetSelectedDirectory(QString pathname);
    QWidget* GetWidget();
private:
    ViewMode dirViewMode;
    QWidget *ptrParent;
    QTreeView  *dirDetailedView;
    QListView *dirIconView;
    QFileSystemModel dirModel;
    QString curDir;
};

#endif // DIRECTORYVIEW_H
