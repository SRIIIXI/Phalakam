#include "DirectoryView.hpp"

DirectoryView::DirectoryView()
{
    dirDetailedView = NULL;
    dirIconView = NULL;
}

DirectoryView::~DirectoryView()
{
}

void DirectoryView::Initialize(QWidget *parent, ViewMode vmode, QString pathname)
{
    ptrParent = parent;
    dirViewMode = vmode;
    curDir = pathname;
    SetSelectedDirectory(pathname);
}

QWidget* DirectoryView::GetWidget()
{
    switch(dirViewMode)
    {
        case Thumbnails:
            {
             return NULL;
            }
        case Icons:
            {
                return dirIconView;
            }
        default:
        case Detailed:
            {
                return  dirDetailedView;
            }
    }
}

void DirectoryView::SetViewMode(ViewMode vmode)
{
    dirViewMode = vmode;
    SetSelectedDirectory(curDir);
}

void DirectoryView::SetSelectedDirectory(QString pathname)
{   
    curDir = pathname;
    QModelIndex rootModelIndex = dirModel.setRootPath(pathname);

    switch(dirViewMode)
    {
        case Thumbnails:
            {
             break;
            }
        case Icons:
            {
                if(dirIconView == NULL)
                {
                     dirIconView = new QListView(ptrParent);
                     dirIconView->setMinimumWidth(400);
                     dirIconView->setModel(&dirModel);
                     dirIconView->setViewMode(QListView::IconMode);
                }
                dirIconView->setRootIndex(rootModelIndex);
                break;
            }
        default:
        case Detailed:
            {
                if(dirDetailedView == NULL)
                {
                    dirDetailedView = new QTreeView(ptrParent);
                    dirDetailedView->setMinimumWidth(600);
                    dirDetailedView->setColumnWidth(0,350);
                    dirDetailedView->setModel(&dirModel);
                }
                dirDetailedView->setRootIndex(rootModelIndex);
                break;
            }
    }
}
