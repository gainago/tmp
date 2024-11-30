#ifndef MEMBEROFMODEL_H
#define MEMBEROFMODEL_H

#include "enumsorters.h"
#include "QString"

class memberOfModel
{
private:
    Sorters sorter_;
    double time_;
    int size_;
    QString strFileInputName_;
    QString strFileOutputName_;
public:
    memberOfModel(Sorters sorter, double time,
                  int size, QString strFileInputName = QString(), QString strFileOutputName = QString());
    memberOfModel();

    Sorters getSorter() const;
    double getTime() const;
    int getSize() const;
    QString getStrFileNameInput() const;
    QString getStrFileNameOutput() const;
};

#endif // MEMBEROFMODEL_H
