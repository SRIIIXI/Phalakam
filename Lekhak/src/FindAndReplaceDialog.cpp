#include "FindAndReplaceDialog.hpp"

FindAndReplaceDialog::FindAndReplaceDialog()
{
    Initialize();
}

FindAndReplaceDialog::FindAndReplaceDialog(QWidget * parent)
{
    setParent(parent);
    Initialize();
}

void FindAndReplaceDialog::Initialize()
{
    wdSearchLabel.setText("Search for word or phrase");
    wdReplaceLabel.setText("Replace by word or phrase");

    wdSearchString.resize(180,24);
    wdReplaceString.resize(180,24);

    wdFindFirst.setText("Find First");
    wdFindNext.setText("Find Next");
    wdMarkAll.setText("Mark All");
    wdReplaceFirst.setText("Replace First");
    wdReplaceNext.setText("Replace Next");
    wdReplaceAll.setText("Replace All");

    wdClose.setText("Close");
    wdClose.setAutoDefault(true);
    dialogLayout.addWidget(&wdClose,8,2);

    dialogLayout.addWidget(&wdSearchLabel,0,0);
    dialogLayout.addWidget(&wdSearchString,1,0,1,3);
    dialogLayout.addWidget(&wdFindFirst,2,0);
    dialogLayout.addWidget(&wdFindNext,2,1);
    dialogLayout.addWidget(&wdMarkAll,2,2);

    dialogLayout.addWidget(&wdReplaceLabel,4,0);
    dialogLayout.addWidget(&wdReplaceString,5,0,1,3);
    dialogLayout.addWidget(&wdReplaceFirst,6,0);
    dialogLayout.addWidget(&wdReplaceNext,6,1);
    dialogLayout.addWidget(&wdReplaceAll,6,2);

    setLayout(&dialogLayout);

    //
    connect(&wdClose,SIGNAL(clicked()),this,SLOT(DialogClose()));
}

FindAndReplaceDialog::~FindAndReplaceDialog()
{
}

void FindAndReplaceDialog::DialogClose()
{
    this->close();
}
