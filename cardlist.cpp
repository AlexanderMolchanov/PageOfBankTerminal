#include "cardlist.h"

CardList::CardList(QObject *parent) : QObject(parent)
{
    m_items.append({ false, QStringLiteral("4561 9874 3215 7895"), QStringLiteral("Credit Card") });
    m_items.append({ false, QStringLiteral("7894 6511 2384 5682"), QStringLiteral("Deposit Card") });
    m_items.append({ false, QStringLiteral("9541 2378 9609 7603"), QStringLiteral("Salary Card") });
}

QVector<Card> CardList::items() const
{
    return m_items;
}

bool CardList::setItemAt(int index, const Card &item)
{
    if (index < 0 || index >= m_items.size())
        return false;

    const Card &oldItem = m_items.at(index);
    if (item.done == oldItem.done && item.description == oldItem.description)
        return false;

    m_items[index] = item;
    return true;
}

void CardList::appendItem()
{
    emit preItemAppended();

    Card item;
    item.done = false;
    item.description = "Your new card";
    item.cardNumber = "0000 0000 0000 0000";
    m_items.append(item);

    emit postItemAppended();
}

void CardList::removeCompletedItems()
{
    for (int i = 0; i < m_items.size(); ) {
        if (m_items.at(i).done) {
            emit preItemRemoved(i);

            m_items.removeAt(i);

            emit postItemRemoved();
        } else {
            ++i;
        }
    }
}
