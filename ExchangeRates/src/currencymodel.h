#pragma once

#include <QAbstractListModel>
#include <QStringList>

class Currency
{
public:
    Currency(const QString &name, const QString &value);

    QString name() const;
    QString value() const;

private:
    QString m_name;
    QString m_value;
};

class CurrencyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum AnimalRoles {
        NameRole = Qt::UserRole + 1,
        ValueRole
    };

    CurrencyModel(QObject *parent = 0);

    void addCurrency(const Currency &currency);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Currency> m_currencies;
};


