#include "walletlist.h"

WalletList::WalletList(QObject *parent) : QObject(parent)
{
    m_items.append({ false, QStringLiteral("GBP") });
    m_items.append({ false, QStringLiteral("USD") });
    m_items.append({ false, QStringLiteral("UAH") });
    m_items.append({ false, QStringLiteral("RUB") });
}

QVector<Wallet> WalletList::items() const
{
    return m_items;
}

bool WalletList::setItemAt(int index, const Wallet &item)
{
    if (index < 0 || index >= m_items.size())
        return false;

    const Wallet &oldItem = m_items.at(index);
    if (item.done == oldItem.done && item.description == oldItem.description)
        return false;

    m_items[index] = item;
    return true;
}

void WalletList::appendItem()
{
    emit preItemAppended();

    Wallet item;
    item.done = false;
    item.description = "New wallet";
    m_items.append(item);

    emit postItemAppended();
}

void WalletList::removeCompletedItems()
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
