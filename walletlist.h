#ifndef WALLETLIST_H
#define WALLETLIST_H

#include <QObject>
#include <QVector>

struct Wallet
{
    bool done;
    QString description;
};

class WalletList : public QObject
{
    Q_OBJECT

public:
    explicit WalletList(QObject *parent = nullptr);

    QVector<Wallet> items() const;

    bool setItemAt(int index, const Wallet &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeCompletedItems();

private:
    QVector<Wallet> m_items;
};

#endif // WALLETLIST_H
