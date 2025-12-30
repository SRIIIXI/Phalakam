#ifndef FINDANDREPLACEDIALOG_H
#define FINDANDREPLACEDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QtGui>

QT_BEGIN_NAMESPACE
class QAction;
class QLineEdit;
class QPushButton;
class QLabel;
QT_END_NAMESPACE

class FindAndReplaceDialog : public QDialog
{
    Q_OBJECT
public:
    FindAndReplaceDialog();
    FindAndReplaceDialog(QWidget * parent);

    virtual ~FindAndReplaceDialog();
private:
    QGridLayout dialogLayout;

    QLineEdit wdSearchString;
    QLineEdit wdReplaceString;

    QLabel wdSearchLabel;
    QLabel wdReplaceLabel;

    QPushButton wdFindFirst;
    QPushButton wdFindNext;
    QPushButton wdMarkAll;
    QPushButton wdReplaceFirst;
    QPushButton wdReplaceNext;
    QPushButton wdReplaceAll;
    QPushButton wdClose;

    void Initialize();
private slots:
            void DialogClose();
};
#endif
