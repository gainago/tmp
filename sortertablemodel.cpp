#include "sortertablemodel.h"
#include <QDebug>

SorterTableModel::SorterTableModel(int cRows, QObject* pObject)
    :   QAbstractTableModel(pObject)
    ,   cColumns_(5)
    ,   dArray_(DynamicArray<memberOfModel>(cRows))
{
}

QVariant SorterTableModel::data(const QModelIndex& index, int nRole) const
{
    if(!index.isValid()){
        return QVariant();
    }

    if((nRole == Qt::DisplayRole || nRole == Qt::EditRole) &&
        dArray_.GetCapacity() > index.row()){
        switch(index.column()){
            case 0:{
            switch((int)dArray_.Get(index.row()).getSorter()){
                case 0:{
                return QString("InvalidIndex");
                    break;
                }
                case 1:{
                    return QString("BubbleSorter");
                    break;
                }
                case 2:{
                    return QString("InsertionSorter");
                    break;
                }
                case 3:{
                    return QString("ShellSorter");
                    break;
                }
                case 4:{
                    return QString("MergeSorter");
                    break;
                }
                case 5:{
                    return QString("PiramidSorter");
                    break;
                }
                case 6:{
                    return QString("QuickSorter");
                    break;
                }
            }
                break;
            }
            case 1:{
                return (double)(dArray_.Get(index.row())).getTime();
                break;
            }
            case 2:{
                return (int)(dArray_.Get(index.row())).getSize();
                break;
            }
            case 3:{
                return (QString)(dArray_.Get(index.row())).getStrFileNameInput();
                break;
            }
            case 4:{
                return (QString)(dArray_.Get(index.row())).getStrFileNameOutput();
                break;
            }
            default: break;
        }
    }

    return QVariant();


}

bool SorterTableModel::setData(const QModelIndex& index,
             const QVariant&    value,
             int                nRole)
{
    /*if(index.isValid())
        qDebug() << "AAA";

    if(nRole == Qt::EditRole)
        qDebug() << "BBB";

    if(index.row() < dArray_.GetCapacity())
        qDebug() << "CCC";*/

    if((index.isValid()) && (nRole == Qt::EditRole) && (index.row() < dArray_.GetCapacity())) {
        memberOfModel priviousMember = dArray_.Get(index.row());
        switch(index.column()){
        case 0:{
            Sorters tmpSorter  = static_cast<Sorters>(value.value<int>());
            memberOfModel tmpMember(tmpSorter, priviousMember.getTime(),
                                    priviousMember.getSize(),
                                    priviousMember.getStrFileNameInput(),
                                    priviousMember.getStrFileNameOutput());
            dArray_.Set(index.row(), tmpMember);
            emit dataChanged(index, index);
            return true;
            break;
        }
        case 1:{
            double tmpTime(value.value<double>());
            memberOfModel tmpMember(priviousMember.getSorter(), tmpTime,
                                    priviousMember.getSize(),
                                    priviousMember.getStrFileNameInput(),
                                    priviousMember.getStrFileNameOutput());
            dArray_.Set(index.row(), tmpMember);
            emit dataChanged(index, index);
            return true;
            break;
        }
        case 2:{
            int tmpSize(value.value<int>());
            memberOfModel tmpMember(priviousMember.getSorter(),
                                    priviousMember.getTime(),
                                    tmpSize,
                                    priviousMember.getStrFileNameInput(),
                                    priviousMember.getStrFileNameOutput());
            dArray_.Set(index.row(), tmpMember);
            emit dataChanged(index, index);
            return true;
            break;
        }
        case 3:{
            QString tmpStr(value.value<QString>());
            memberOfModel tmpMember(priviousMember.getSorter(), priviousMember.getTime(),
                                    priviousMember.getSize(),
                                    tmpStr,
                                    priviousMember.getStrFileNameOutput());
            dArray_.Set(index.row(), tmpMember);
            emit dataChanged(index, index);
            return true;
            break;
        }
        case 4:{
            QString tmpStr(value.value<QString>());
            memberOfModel tmpMember(priviousMember.getSorter(), priviousMember.getTime(),
                                    priviousMember.getSize(),
                                    priviousMember.getStrFileNameInput(),
                                    tmpStr);
            dArray_.Set(index.row(), tmpMember);
            emit dataChanged(index, index);
            return true;
            break;
        }
        default: break;
        }
    }
    //emit dataChanged(index, index);
    return false;
}

QVariant SorterTableModel::headerData(int             nSection,
                                        Qt::Orientation orientation,
                                        int             nRole) const
{
    if(nRole != Qt::DisplayRole){
        return QVariant();
    }
    if(orientation == Qt::Horizontal){
        switch(nSection){
            case 0:{
                return QVariant(QString("sorter"));
                break;
            }
            case 1:{
                return QVariant(QString("time"));
                break;
            }
            case 2:{
                return QVariant(QString("size"));
                break;
            }
            case 3:{
                return QVariant(QString("input file"));
                break;
            }
            case 4:{
                return QVariant(QString("output file"));
                break;
            }
            default:{
                break;
            }
        }
    } else{
        return QVariant(nSection);
    }

    return QVariant();
}


int SorterTableModel::rowCount(const QModelIndex&) const
{
    return dArray_.GetCapacity();
}

int SorterTableModel::columnCount(const QModelIndex&) const
{
    return cColumns_;
}

bool SorterTableModel::insertRows(int         nRow,
                int         nCount,
                const QModelIndex& parent)
{
    if(parent.isValid() || nRow != dArray_.GetCapacity()){
        return false;
    }

    beginInsertRows(QModelIndex(), nRow, nRow + nCount -1);
    for(int i = 0; i < nCount; ++i){
        dArray_.ReCapacity(dArray_.GetCapacity() + 1);
    }
    endInsertRows();

    return true;
}

Qt::ItemFlags SorterTableModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if(index.isValid()){
        return (Qt::ItemIsEditable | flags);
    }
    return flags;
}
