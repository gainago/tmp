#ifndef UICLASS_H
#define UICLASS_H

#include <QObject>
#include <QWidget>

#include <QRect>
#include <QGridLayout>
#include <QTextEdit>
#include <QFileSystemModel>
#include <QTreeView>
#include <QPushButton>
#include "enumsorters.h"
#include "sortertablemodel.h"
#include "QTableView"

class UIClass : QObject
{
    Q_OBJECT
private:
    SorterTableModel* model_;
    QTableView* viewModel_;
    QRect* screen_;
    QWidget* mainPageFirst_;
    QWidget* mainPageSecond_;
    Sorters currentSorter_;
    QTextEdit* textEditFirst_;
    QWidget* widgetBottomFirst_;
    QGridLayout* gridLayoutTextFirst_;
    QTreeView* treeViewFileSystemModel_;
    QFileSystemModel* fileSystemModel_;
    QPushButton* pushButtonChooseFileToSort_ ;


public:
    UIClass();

private slots:
    void slotOpenFirstWindow();
    void slotOpenSecondWindow();
    void slotAutomaticallyCreateData();
    void slotAutomaticallyCreateDataFinal(QString strNumber);
    void slotWriteDataToFile();
    void slotWriteDataToFileFinal(QString strName);
    void slotChooseFile(bool);
    void slotChangedSorter(int);
    void slotOpenFile(QModelIndex);
    void slotStartSort();
    void slotPrintGraphics();
    //void slotSetUncheckedToggleButton();


};

#endif // UICLASS_H
