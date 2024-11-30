
#include "qapplication.h"
#include <QGridLayout>
#include <QRect>
#include <QScreen>
#include <QTabWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QLineEdit>
#include <QTextDocumentWriter>
#include <QDebug>
#include <QFileSystemModel>
#include <QTreeView>
#include <QFileInfo>
#include <QMessageBox>
#include <iostream>

#include "syntaxhighlighter.h"
#include "getqstringfromnewwidget.h"
#include "uiclass.h"
#include "QWidget"
#include "ArraySequence.h"
//#include "PrintSeq.h"
#include "classtosortint.h"
#include "memberofmodel.h"


UIClass::UIClass() :
    model_(new SorterTableModel(0)),
    viewModel_(new QTableView) {


    //viewModel_->show();

    currentSorter_ = static_cast<Sorters>(0);

    screen_ = new QRect(QApplication::screens().at(0)->geometry());
//---------------------------------- Main Pages-------------
    mainPageFirst_= new QWidget;
    mainPageSecond_ = new QWidget;

    mainPageFirst_->resize(QSize(screen_->width() / 3, screen_->height() / 2));
    mainPageSecond_->resize(QSize(screen_->width() / 3, screen_->height() / 2));

    mainPageFirst_->move(screen_->width() / 5, screen_->height() / 5);
    mainPageSecond_->move(screen_->width() / 5, screen_->height() / 5);

    QGridLayout* gridLayoutFirst = new QGridLayout;
    QGridLayout* gridLayoutSecond = new QGridLayout;

    QHBoxLayout* hLayoutFirst = new QHBoxLayout;
    QHBoxLayout* hLayoutSecond = new QHBoxLayout;

    QWidget* widgetTopFirst = new QWidget;
    widgetBottomFirst_ = new QWidget;
    QWidget* widgetTopSecond = new QWidget;
    QWidget* widgetBottomSecond = new QWidget;
    QWidget* widgetText = new QWidget;
    QWidget* widgetFileHierarhy = new QWidget;

    QPushButton* pushButtonToFirstFromFirst = new QPushButton("first page");
    QPushButton* pushButtonToSecondFromFirst = new QPushButton("second page");
    QPushButton* pushButtonToFirstFromSecond = new QPushButton("first page");
    QPushButton* pushButtonToSecondFromSecond = new QPushButton("second page");

    connect(pushButtonToFirstFromFirst, SIGNAL(clicked(bool))
            , this, SLOT(slotOpenFirstWindow()));
    connect(pushButtonToSecondFromFirst, SIGNAL(clicked(bool))
            , this, SLOT(slotOpenSecondWindow()));
    connect(pushButtonToFirstFromSecond, SIGNAL(clicked(bool))
            , this, SLOT(slotOpenFirstWindow()));
    connect(pushButtonToSecondFromSecond, SIGNAL(clicked(bool))
            , this, SLOT(slotOpenSecondWindow()));

    hLayoutFirst->addWidget(pushButtonToFirstFromFirst);
    hLayoutFirst->addWidget(pushButtonToSecondFromFirst);

    hLayoutSecond->addWidget(pushButtonToFirstFromSecond);
    hLayoutSecond->addWidget(pushButtonToSecondFromSecond);

    gridLayoutFirst->addWidget(widgetTopFirst, 0, 0);
    gridLayoutFirst->addLayout(hLayoutFirst, 1, 0);
    gridLayoutFirst->addWidget(widgetBottomFirst_, 2, 0);

    gridLayoutSecond->addWidget(widgetTopSecond, 0, 0);
    gridLayoutSecond->addLayout(hLayoutSecond, 1, 0);
    gridLayoutSecond->addWidget(widgetBottomSecond, 2, 0);

    mainPageFirst_->setLayout(gridLayoutFirst);
    mainPageSecond_->setLayout(gridLayoutSecond);


mainPageFirst_->show();
    //mainPageSecond_->show();
//---------------------------------- First Page-------------

    QGridLayout* gridLayoutButtonsFirst = new QGridLayout;
    QGridLayout* gridLayoutTextFirst = new QGridLayout;

    QPushButton* pushButtonAutomaticallyCreateData = new QPushButton("Automatically"
                                                                     "Create Data");
    QPushButton* pushButtonWriteDataToFile = new QPushButton("writeDataToFile");
    pushButtonChooseFileToSort_ = new QPushButton("chooseFile");
    pushButtonChooseFileToSort_->setCheckable(true);
    QComboBox* comboBoxSorter = new QComboBox;
    comboBoxSorter->addItem("InvalidIndex"); comboBoxSorter->addItem("BubbleSorter");
    comboBoxSorter->addItem("InsertionSorter"); comboBoxSorter->addItem("ShellSorter");
    comboBoxSorter->addItem("MergeSorter"); comboBoxSorter->addItem("PiramidSorter");
    comboBoxSorter->addItem("QuickSorter");

    connect(pushButtonAutomaticallyCreateData, SIGNAL(clicked(bool))
            , this, SLOT(slotAutomaticallyCreateData()));
    connect(pushButtonChooseFileToSort_, SIGNAL(toggled(bool))
            , this, SLOT(slotChooseFile(bool)));
    connect(pushButtonWriteDataToFile, SIGNAL(clicked(bool))
            , this, SLOT(slotWriteDataToFile()));
    connect(comboBoxSorter, SIGNAL(activated(int))
            , this, SLOT(slotChangedSorter(int)));

    gridLayoutButtonsFirst->addWidget(pushButtonWriteDataToFile, 0, 0);
    gridLayoutButtonsFirst->addWidget(pushButtonAutomaticallyCreateData, 0, 1);
    gridLayoutButtonsFirst->addWidget(pushButtonChooseFileToSort_, 1, 0);
    gridLayoutButtonsFirst->addWidget(comboBoxSorter, 1, 1);

    gridLayoutButtonsFirst->setSpacing(0);
    gridLayoutButtonsFirst->setVerticalSpacing(0);
    gridLayoutButtonsFirst->setHorizontalSpacing(10);

   // widgetTopFirst->setFixedSize(mainPageFirst_->size().rwidth(), mainPageFirst_->size().rheight()/5);
    //QPalette pal(QPalette::Window, Qt::green);
    //widgetTopFirst->setAutoFillBackground(true);
    //widgetTopFirst->setPalette(pal);
   // widgetTopFirst->setContentsMargins(10, 10, 10, 10);

    widgetTopFirst->setLayout(gridLayoutButtonsFirst);
    widgetTopFirst->repaint();

    //widgetBottomFirst->setFixedSize(mainPageFirst_->size().rwidth(), mainPageFirst_->size().rheight() * 3/5);

    textEditFirst_ = new QTextEdit;
    SyntaxHighlighter* pHighlighter = new SyntaxHighlighter(textEditFirst_->document());

    QPushButton* pushButtonStartSort = new QPushButton("StartSort");
    textEditFirst_->resize(widgetBottomFirst_->size().rwidth(), widgetBottomFirst_->size().rheight() * 4/5);

    fileSystemModel_ = new QFileSystemModel;
    treeViewFileSystemModel_ = new QTreeView;
    fileSystemModel_->setRootPath(QDir::currentPath());
    treeViewFileSystemModel_->setModel(fileSystemModel_);
    treeViewFileSystemModel_->setRootIndex(fileSystemModel_->index(QDir::currentPath()));
    treeViewFileSystemModel_->resize(screen_->width() / 3, screen_->height() / 2);
    treeViewFileSystemModel_->move(screen_->width() * 3/5, screen_->height() / 5);
    fileSystemModel_->setNameFilters(QStringList() << "*.txt");
    fileSystemModel_->setReadOnly(false);

    connect(treeViewFileSystemModel_, SIGNAL(collapsed(QModelIndex))
            , this, SLOT(slotOpenFile(QModelIndex)));
    connect(pushButtonStartSort, SIGNAL(clicked(bool))
            , this, SLOT(slotStartSort()));

    //connect(treeViewFileSystemModel_, SIGNAL()
    //        , this, SLOT(slotSetUncheckedToggleButton()));

    gridLayoutTextFirst->addWidget(textEditFirst_, 0, 0);
    gridLayoutTextFirst->addWidget(pushButtonStartSort, 1, 0);


    widgetBottomFirst_->setLayout(gridLayoutTextFirst);

    widgetBottomFirst_->repaint();


//---------------------------------- Second Page-------------


    QGridLayout* gridLayoutButtonsSecond = new QGridLayout;
    QGridLayout* gridLayoutModelSecond = new QGridLayout;

    QPushButton* pushButtonPrintGraphics = new QPushButton("PrintGraphics");

    connect(pushButtonPrintGraphics, SIGNAL(clicked(bool))
            , this, SLOT(slotPrintGraphics()));

    gridLayoutButtonsSecond->addWidget(pushButtonPrintGraphics, 0, 0);

    //gridLayoutButtonsFirst->setRowStretch(0, mainPageFirst_->size().rwidth()/10);
    //gridLayoutButtonsFirst->setColumnStretch(0, mainPageFirst_->size().rheight()/10);
    //gridLayoutButtonsFirst->setHorizontalSpacing(mainPageFirst_->size().rwidth()/20);
    //gridLayoutButtonsFirst->setVerticalSpacing(5);
    //gridLayoutButtonsFirst->rowStretch(10);
    gridLayoutButtonsSecond->setSpacing(0);
    gridLayoutButtonsSecond->setVerticalSpacing(0);
    gridLayoutButtonsSecond->setHorizontalSpacing(10);

    widgetTopSecond->setLayout(gridLayoutButtonsSecond);

    //widgetTopFirst->repaint();
    viewModel_->setModel(model_);

    gridLayoutModelSecond->addWidget(viewModel_, 0, 0);
    //gridLayoutTextFirst->addWidget(pushButtonStartSort, 1, 0);
    widgetBottomSecond->setLayout(gridLayoutModelSecond);



    //widgetBottomSecond->repaint();
    mainPageSecond_->repaint();

}

// void UIClass::slotSetUncheckedToggleButton()
// {
//     qDebug() << "OOO";
//     pushButtonChooseFileToSort_->setChecked(false);
// }

void UIClass::slotOpenFirstWindow()
{
    mainPageSecond_->hide();
    mainPageFirst_->show();
}

void UIClass::slotOpenSecondWindow()
{
    mainPageFirst_->hide();
    mainPageSecond_->show();
}

void UIClass::slotAutomaticallyCreateData()
{
    getQStringFromNewWidget* obj = new getQStringFromNewWidget;
    connect(obj, SIGNAL(ButtonPushed(QString))
            , this, SLOT(slotAutomaticallyCreateDataFinal(QString)));
    obj->getString("Enter number of objects", "append");
}

void UIClass::slotAutomaticallyCreateDataFinal(QString strNumber)
{
    bool isNumber = 1;
    int number;
    number = strNumber.toInt(&isNumber, 10);
    if(!isNumber)
    {
        QWidget* wg = new QWidget;
        QMessageBox::critical(wg, "Pay Attention"
                              , "You have to enter int");
        return;
    }
    srand(time(NULL));
    for(int i = 0; i < number; i++)
    {
        textEditFirst_->append(QString::number(rand(), 10));
    }
}
void UIClass::slotWriteDataToFile()
{
    //mainPageFirst_->setEnabled(false);
    //mainPageSecond_->setEnabled(false);

    getQStringFromNewWidget* obj = new getQStringFromNewWidget;
    connect(obj, SIGNAL(ButtonPushed(QString))
            , this, SLOT(slotWriteDataToFileFinal(QString)));
    obj->getString("Enter file name", "Set");

}

void UIClass::slotWriteDataToFileFinal(QString str)
{
    if(QFile::exists(str + ".txt")){

        QWidget* wg = new QWidget;
        QMessageBox::critical(wg, "Pay Attention"
                             , "You already have file with the same name");
        return;
    }
    QTextDocumentWriter writer;
    writer.setFormat("txt");
    writer.setFileName(str + ".txt");

    writer.write(textEditFirst_->document());

    mainPageFirst_->setEnabled(true);
    mainPageSecond_->setEnabled(true);
}

void UIClass::slotChooseFile(bool arg)
{
    if(arg)
        treeViewFileSystemModel_->show();
    else
        treeViewFileSystemModel_->hide();
}

void UIClass::slotOpenFile(QModelIndex index)
{
    QFileInfo fileInfo = fileSystemModel_->fileInfo(index);
    qDebug() << fileInfo.fileName() << "OOOO";

    textEditFirst_->clear();
    char charBuffer[1024];
    QFile fileToOpen(fileInfo.absoluteFilePath());
    fileToOpen.open(QFile::ReadOnly);


    if(fileToOpen.isOpen()){
        int sizeWritten = fileToOpen.readLine(charBuffer
                                              , sizeof(charBuffer));
        while(sizeWritten != -1)
        {
            qDebug() << charBuffer;
            if(charBuffer[sizeWritten - 1] == '\n'){ //reaffile has '\n'
                                                        //append has '\n'
                charBuffer[sizeWritten - 1]  = '\0';
            }
            textEditFirst_->append(charBuffer);
            textEditFirst_->repaint();
            sizeWritten = fileToOpen.readLine(charBuffer
                                                  , sizeof(charBuffer));
        }
        fileToOpen.close();
    }
    else{
        qDebug() << "could not open file\n" << fileInfo.absoluteFilePath();
    }

}

void UIClass::slotChangedSorter(int newSorter)
{
    currentSorter_ = static_cast<Sorters>(newSorter);
    qDebug() << (int)currentSorter_ << "\n";
}

void UIClass::slotStartSort()
{
    if((int)currentSorter_ == 0){
        QWidget* wg = new QWidget;
        QMessageBox::critical(wg, "Pay Attention"
                              , "You have to choose Sorter");

        return;
    }

    QString strFullPlaneText = textEditFirst_->toPlainText();
    QStringList strListWithSpace = strFullPlaneText.split('\n');
    QStringList strList;
    for(int i = 0 ; i < strListWithSpace.size(); i++)
    {
        if(!strListWithSpace.at(i).isEmpty())
        {
            strList.append(strListWithSpace.at(i));
        }
    }

    MutableArraySequence<int>* mutArraySeqToSort;

    try{
     mutArraySeqToSort =
        new MutableArraySequence<int>(strList.size());
    }
    catch(...){
        QWidget* wg = new QWidget;
        QMessageBox::critical(wg, "Oops"
                              , "the program can not pick out Sequence");
        delete mutArraySeqToSort;
        return;
    }

    for(int i = 0; i < strList.size(); i++)
    {
        bool isNumber = 1;
        int number = 0;
        number = strList.at(i).toInt(&isNumber, 10);
        if(!isNumber)
        {
            QWidget* wg = new QWidget;
            QMessageBox::critical(wg, "Pay Attention"
                                  , "You data has wrong format");
            delete mutArraySeqToSort;
            return;
        }
        mutArraySeqToSort->Set(i, number);
    }

    //PrintSeq(mutArraySeqToSort);


    ClassToSortInt tmpClass;
    memberOfModel resultSlot(currentSorter_, tmpClass.Sort(mutArraySeqToSort, currentSorter_), mutArraySeqToSort->GetLength());

    int currentRow = model_->rowCount(model_->index(0, 0));
    model_->insertRows(currentRow, 1);

    QModelIndex index(model_->index(currentRow, 0));
    qDebug() << index.row() << "\t" << index.column() << "\n";

    model_->setData(model_->index(currentRow , 0), (int)resultSlot.getSorter(), Qt::EditRole);
    model_->setData(model_->index(currentRow , 1), resultSlot.getTime(), Qt::EditRole);
    model_->setData(model_->index(currentRow , 2), resultSlot.getSize(), Qt::EditRole);


    textEditFirst_->clear();

    for(int i = 0; i < strList.size(); ++i){
        textEditFirst_->append(QString::number(mutArraySeqToSort->Get(i), 10));
    }

    textEditFirst_->repaint();

}

void UIClass::slotPrintGraphics()
{

}
