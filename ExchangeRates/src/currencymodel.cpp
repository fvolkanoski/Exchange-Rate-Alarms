#include "src/currencymodel.h"

Currency::Currency(const QString &name, const QString &value)
    : m_name(name), m_value(value)
{
}

QString Currency::name() const
{
    return m_name;
}

QString Currency::value() const
{
    return m_value;
}

CurrencyModel::CurrencyModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void CurrencyModel::addCurrency(const Currency &currency)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_currencies << currency;
    endInsertRows();
}

int CurrencyModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_currencies.count();
}

QVariant CurrencyModel::data(const QModelIndex & index, int role) const
{
    if (index.row() < 0 || index.row() >= m_currencies.count())
        return QVariant();

    const Currency &currency = m_currencies[index.row()];
    if (role == NameRole)
        return currency.name();
    else if (role == ValueRole)
        return currency.value();
    return QVariant();
}

void CurrencyModel::clear()
{
    beginResetModel();
    m_currencies.clear();
    endResetModel();
}

QHash<int, QByteArray> CurrencyModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ValueRole] = "value";
    return roles;
}
