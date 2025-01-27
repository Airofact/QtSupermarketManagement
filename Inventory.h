#ifndef INVENTORY_H
#define INVENTORY_H

#include<QMap>
#include<QHash>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

#include "CargoType.h"

/**
 *  库存类
 * 支持 增加、修改、删除、查找商品
 */
class Inventory: public SerializableQObject
{
    Q_OBJECT
    friend class Login;

private:
    QHash<CargoType,int> *m_pInventory;
    static QMap<uint,Inventory*> m_regesteredInventory;
    uint m_id;
public:
    Inventory();
    ~Inventory();
    Inventory(const Inventory &inventory);
    Inventory(const QByteArray& json);
    //序列化
    bool toJsonObject(QJsonObject& json) const override;
    //反序列化
    bool fromJsonObject(const QJsonObject& json) override;
    static Inventory fromFile(const QString& path);
    // 增加商品 例addGoods(CargoType("Apple", 1.5, "Fruit"), 10);
    void addGoods(const CargoType &goods, int amount);
    // 修改商品信息 例editGoods("Apple", 2.5, 20);
    void editGoods(const QString &name, double price, int amount);
    // 删除商品 例removeGoods("Apple");
    // 若未指定删除数目 则直接把该项移除，若指定删除数目，如removeGoods("Apple",20); ->删除20个"Apple" 若Apple库存低于20 则直接删除该项
    void removeGoods(const QString &name, int amount = 0);
    // 获取商品 例getItem("Apple"); 返回一个item指针 通过item->first获取商品对象 通过item->second获取商品数量
    CargoType* getCargoType(const QString &name) const;
    // 获取某商品数量
    int getAmount(const QString& name) const;
    // 检查是否包含某商品
    bool contains(const QString& name) const;
    bool contains(const CargoType& type) const;
    // 交换商品
    bool transferGoods(Inventory& other, const QString& name, int amout = 0);
    // 返回库存列表
    const QHash<CargoType, int>* getInventory() const;
    // 测试打印用
    void print() const;
    // 获取id
    uint getId() const;
    bool setId(uint id);
    uint constructId();
    static Inventory* getInstance(uint id);
    static void registerInstance(Inventory* inventory);
};

#endif
