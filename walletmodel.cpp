#include "walletmodel.h"
#include "walletlist.h"

WalletModel::WalletModel(QObject *parent) : QAbstractListModel(parent), m_list(nullptr)
{
}

int WalletModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !m_list)
        return 0;

    return m_list->items().size();
}

QVariant WalletModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_list)
        return QVariant();

    const Wallet item = m_list->items().at(index.row());
    switch (role) {
    case DoneRole:
        return QVariant(item.done);
    case DescriptionRole:
        return QVariant(item.description);
    }

    return QVariant();
}

bool WalletModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!m_list)
        return false;

    Wallet item = m_list->items().at(index.row());
    switch (role) {
    case DoneRole:
        item.done = value.toBool();
        break;
    case DescriptionRole:
        item.description = value.toString();
        break;
    }

    if (m_list->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags WalletModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> WalletModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DoneRole] = "done";
    names[DescriptionRole] = "description";
    return names;
}

WalletList *WalletModel::list() const
{
   return m_list;
}

void WalletModel::setList(WalletList *list)
{
    beginResetModel();

    if (m_list)
        m_list->disconnect(this);

    m_list = list;

    if (m_list) {
        connect(m_list, &WalletList::preItemAppended, this, [=]() {
            const int index = m_list->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(m_list, &WalletList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(m_list, &WalletList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(m_list, &WalletList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
