#include "Trade.h"

#include <QFile>
#include<QJsonArray>
#include <iostream>

Trade::Trade(Inventory *linkedInventory)
    : m_pLinkedInventory(linkedInventory)
{
    m_pTradeList = new std::list<tradeListItem>;
}

Trade::~Trade()
{
    if (m_pTradeList != nullptr)
        delete m_pTradeList;
}

Trade::Trade(const QByteArray &json)
{
    m_pTradeList = new std::list<tradeListItem>;
    this->deserialize(json);
}
bool Trade::toJsonObject(QJsonObject &json) const
{
    QJsonArray list;
    for (const auto &i : *m_pTradeList)
    {
        QJsonObject obj;
        obj.insert("name", i.first);
        QJsonObject inven;
        i.second.toJsonObject(inven);
        obj.insert("inventory", inven);
        list.append(obj);
    }
    json.insert("tradeList", list);
    return true;
}
Trade Trade::fromFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return Trade(nullptr);
    }
    QByteArray json = file.readAll();
    return Trade(json);
}
bool Trade::fromJsonObject(const QJsonObject &json)
{
    QJsonArray list = json["tradeList"].toArray();
    for (const auto &i : list)
    {
        QJsonObject obj = i.toObject();
        QString name = obj["name"].toString();
        Inventory inven;
        inven.fromJsonObject(obj["inventory"].toObject());
        m_pTradeList->push_back(std::make_pair(name, inven));
    }
    return true;
}

tradeListItem *Trade::getTradeListItem(const QString &name) const
{
    for (auto &i : *m_pTradeList)
    {
        if (i.first == name)
        {
            return &i;
        }
    }
    return nullptr;
}

bool Trade::addTradeListItem(const QString &name, Inventory &inven)
{
    m_pTradeList->push_back(std::make_pair(name, inven));
    for (auto pair = inven.getInventory()->begin(); pair != inven.getInventory()->end(); ++pair)
    {
        m_pLinkedInventory->removeGoods(pair.key().getName(),pair.value());
    }
    return true;
}

bool Trade::removeTradeListItemByName(const QString &name)
{
    auto it = m_pTradeList->begin();
    for (; it != m_pTradeList->end(); ++it)
    {
        if (it->first == name)
        {
            auto inventory = *it->second.getInventory();
            for (auto pair = inventory.begin(); pair != inventory.end(); ++pair)
            {
                m_pLinkedInventory->addGoods(pair.key(),pair.value());
            }
            m_pTradeList->erase(it);

            return true;
        }
    }
    return false;
}

bool Trade::editTradeListItem(const QString &name, Inventory &inven)
{
    tradeListItem *item = getTradeListItem(name);
    if (item == nullptr)
    {
        return false;
    }
    removeTradeListItemByName(name);
    addTradeListItem(name, inven);
    return true;
}

void Trade::printTradeList() const
{
    for (auto &i : *m_pTradeList)
    {
        std::cout << i.first.toStdString() << std::endl;
        i.second.print();
    }
}

std::list<tradeListItem> *Trade::getTradeList() const
{
    return m_pTradeList;
}
