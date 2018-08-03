#include "cardmodel.h"
#include "cardlist.h"

CardModel::CardModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int CardModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant CardModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const Card item = mList->items().at(index.row());
    switch (role) {
    case DoneRole:
        return QVariant(item.done);
    case DescriptionRole:
        return QVariant(item.description);
    case CardNumberRole:
        return QVariant(item.cardNumber);
    }

    return QVariant();
}

bool CardModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    Card item = mList->items().at(index.row());
    switch (role) {
    case DoneRole:
        item.done = value.toBool();
        break;
    case DescriptionRole:
        item.description = value.toString();
        break;
    case CardNumberRole:
        item.cardNumber = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CardModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> CardModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DoneRole] = "done";
    names[DescriptionRole] = "description";
    names[CardNumberRole] = "cardNumber";
    return names;
}

CardList *CardModel::list() const
{
    return mList;
}

void CardModel::setList(CardList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &CardList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &CardList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &CardList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &CardList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
