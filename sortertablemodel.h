#ifndef SORTERTABLEMODEL_H
#define SORTERTABLEMODEL_H

#include <QHash>
#include <QAbstractTableModel>
#include <QString>
#include "DynamicArray.h"
#include "memberofmodel.h"


class SorterTableModel : public QAbstractTableModel
{
private:
    //int cRows_; // c - count
    int cColumns_;
    QHash<QModelIndex, QVariant> hash_;
    DynamicArray<memberOfModel> dArray_;

public:
    SorterTableModel(int cRows, QObject* pObject = 0);

    QVariant data(const QModelIndex& index, int nRole) const;

    bool setData(const QModelIndex& index,
                 const QVariant&    value,
                 int                nRole);
    QVariant headerData(int             nSection,
                        Qt::Orientation orientation,
                        int             nRole = Qt::DisplayRole) const;

    int rowCount(const QModelIndex&) const;

    int columnCount(const QModelIndex&) const;

    bool insertRows(int         nRow,
                    int         nCount,
                    const QModelIndex& parent = QModelIndex());

    Qt::ItemFlags flags(const QModelIndex& index) const;


};

#endif // SORTERTABLEMODEL_H
