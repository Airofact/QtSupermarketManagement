#ifndef TRADE_H
#define TRADE_H
#include "Inventory.h"

/**
 * 交易类
 * tradeListItem为交易列表的元素类型
 *  存储的元素类型为pair，其first为顾客名称，second为顾客的购入商品的列表（其实际类型为Inventory)
 * 支持 添加、删除、修改、查找交易列表元素
 */
using tradeListItem = std::pair<QString, Inventory>;
class Trade: public SerializableQObject
{
    Q_OBJECT
private:
    Inventory *m_pLinkedInventory;
    std::list<tradeListItem> *m_pTradeList;

public:
    Trade(Inventory *linkedInventory);
    ~Trade();
    Trade(const QByteArray& json);
    //序列化
    bool toJsonObject(QJsonObject& json) const override;
    //反序列化
    bool fromJsonObject(const QJsonObject& json) override;
    static Trade fromFile(const QString& path);
    // 添加交易列表元素 例addTradeListItem("customer", inventory); 其中inventory需要提前创建
    bool addTradeListItem(const QString &name, Inventory &inven);
    // 删除交易列表元素 例removeTradeListItemByName("customer");
    bool removeTradeListItemByName(const QString &name);
    // 修改交易列表元素 例editTradeListItem("customer", inventory); 其中inventory需要提前创建
    bool editTradeListItem(const QString &name, Inventory &inven);
    // 获取交易列表元素 例getTradeListItem("customer"); 返回一个tradeListItem指针 通过item->first获取顾客名称 通过item->second获取商品列表
    tradeListItem *getTradeListItem(const QString &name) const;
    // 返回交易列表
    std::list<tradeListItem> *getTradeList() const;
    // 测试打印用
    void printTradeList() const;
    // //序列化
    // bool serialize(QByteArray& json) const override;
    // //反序列化
    // bool deserialize(const QByteArray& json) override;
};
#endif // TRADE_H
