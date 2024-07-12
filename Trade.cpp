#include "Trade.h"

#include <iostream>

Trade::Trade(Inventory *linkedInventory)
    : linkedInventory(linkedInventory)
{
    tradeList = new std::list<tradeListItem>;
}

Trade::~Trade()
{
    if (tradeList != nullptr)
        delete tradeList;
}

tradeListItem *Trade::getTradeListItem(const QString &name) const
{
    for (auto &i : *tradeList)
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
    if (getTradeListItem(name) != nullptr)
    {
        return false;
    }
    tradeList->push_back(std::make_pair(name, inven));
    for (const auto &type : inven.getInventory()->keys())
    {
        linkedInventory->removeGoods(type.getName(), inven.getAmount(name));
    }
    return true;
}

bool Trade::removeTradeListItemByName(const QString &name)
{
    auto it = tradeList->begin();
    for (; it != tradeList->end(); ++it)
    {
        if (it->first == name)
        {
            auto inventory = *it->second.getInventory();
            for (auto pair = inventory.begin(); pair != inventory.end(); ++pair)
            {
                linkedInventory->addGoods(pair.key(),pair.value());
            }
            tradeList->erase(it);

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
    for (auto &i : *tradeList)
    {
        std::cout << i.first.toStdString() << std::endl;
        i.second.print();
    }
}

std::list<tradeListItem> *Trade::getTradeList() const
{
    return tradeList;
}
