#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QVector>
struct Card
{
    bool done;
    QString cardNumber;
    QString description;
};

class CardList : public QObject
{
    Q_OBJECT

public:
    explicit CardList(QObject *parent = nullptr);

    QVector<Card> items() const;

    bool setItemAt(int index, const Card &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeCompletedItems();

private:
    QVector<Card> m_items;
};

#endif // TODOLIST_H
