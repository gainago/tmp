#include <QApplication>
#include "sortertablemodel.h"
#include "memberofmodel.h"
#include "QTableView"
#include "uiclass.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UIClass example;

    return a.exec();
}
