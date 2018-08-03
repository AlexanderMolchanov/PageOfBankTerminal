#ifndef TODOMODEL_H
#define TODOMODEL_H

#include <QAbstractListModel>

class CardList;

class CardModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(CardList *list READ list WRITE setList)

    CardList *mList;

public:
    explicit CardModel(QObject *parent = nullptr);

    enum {
        DoneRole = Qt::UserRole,
        DescriptionRole,
        CardNumberRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    CardList *list() const;
    void setList(CardList *list);

};

#endif // TODOMODEL_H
