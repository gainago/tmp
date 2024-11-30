#include "memberofmodel.h"

memberOfModel::memberOfModel(Sorters sorter, double time,
    int size, QString strFileInputName, QString strFileOutputName) :
    sorter_(sorter), time_(time), size_(size),
    strFileInputName_(strFileInputName),
    strFileOutputName_(strFileOutputName)
{}
memberOfModel::memberOfModel()
{
    sorter_ = Sorters::InvalidIndex;
    time_ = 0;
    size_ = 0;
    strFileInputName_ = QString();
    strFileOutputName_ = QString();
}
Sorters memberOfModel::getSorter() const
{
    return sorter_;
}

double memberOfModel::getTime() const
{
    return time_;
}

int memberOfModel::getSize() const
{
    return size_;
}

QString memberOfModel::getStrFileNameInput() const
{
    return strFileInputName_;
}

QString memberOfModel::getStrFileNameOutput() const
{
    return strFileOutputName_;
}

