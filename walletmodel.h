#ifndef WALLETMODEL_H
#define WALLETMODEL_H

#include <QAbstractListModel>

class WalletList;

class WalletModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(WalletList *list READ list WRITE setList)

    WalletList *m_list;

public:
    explicit WalletModel(QObject *parent = nullptr);

    enum {
        DoneRole = Qt::UserRole,
        DescriptionRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    WalletList *list() const;
    void setList(WalletList *list);

};

#endif // WALLETMODEL_H
