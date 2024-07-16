#include "Inventory.h"

#include <iostream>
#include <QFile>
#include <QMessageBox>

QMap<uint,Inventory*> Inventory::m_regesteredInventory;

Inventory::Inventory()
{
    m_pInventory = new QHash<CargoType,int>();
    setId(constructId());
    registerInstance(this);
}
Inventory::~Inventory()
{
    delete m_pInventory;
    m_pInventory = nullptr;
}

Inventory::Inventory(const Inventory& inventory)
{
    m_pInventory = new QHash<CargoType,int>(*inventory.getInventory());
    setId(constructId());
    registerInstance(this);
}
Inventory::Inventory(const QByteArray& json)
{
    m_pInventory = new QHash<CargoType,int>();
    deserialize(json);
    registerInstance(this);
}

Inventory Inventory::fromFile(const QString& path){
    QFile file(path);
    if(!file.exists()){
        return Inventory();
    }
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return Inventory();
    }
    QByteArray json = file.readAll();
    return Inventory(json);
}
bool Inventory::toJsonObject(QJsonObject& json) const{
    json.insert("id",QVariant(getId()).toJsonValue());
    QJsonObject content;
    for (const CargoType& type : m_pInventory->keys())
    {
        QJsonObject key;
        type.toJsonObject(key);
        QJsonObject pair;
        pair.insert("cargoType",key);
        pair.insert("amount",(*m_pInventory)[type]);
        content.insert(type.getName(), pair);
    }
    json.insert("content",content);
    return true;
}
bool Inventory::fromJsonObject(const QJsonObject& json){
    if(!json.contains("id")){
        setId(constructId());
        QMessageBox::warning(nullptr,"Inventory","未找到id，已自动生成");
    }else{
        setId(json["id"].toInt());
    }
    QJsonObject content = json["content"].toObject();
    for (const QString& key : content.keys())
    {
        QJsonObject pair = content[key].toObject();
        CargoType type;
        if(!type.fromJsonObject(pair["cargoType"].toObject())){
            return false;
        };
        m_pInventory->insert(type,pair["amount"].toInt());
    }
    return true;
}

CargoType* Inventory::getCargoType(const QString &name) const
{
    for (auto it = m_pInventory->begin(); it != m_pInventory->end(); ++it)
    {
        if (it.key().getName() == name)
        {
            return const_cast<CargoType*>(&it.key());
        }
    }
    return nullptr;
}
int Inventory::getAmount(const QString& name) const {
    for(CargoType& type:m_pInventory->keys()){
        QString typeName = type.getName();
        if(typeName == name){
            return (*m_pInventory)[type];
        }
    }
    return 0;
}

bool Inventory::contains(const QString& name) const
{
    return getCargoType(name) != nullptr;
}
bool Inventory::contains(const CargoType& type) const
{
    return m_pInventory->contains(type);
}

void Inventory::addGoods(const CargoType& type, int amount)
{
    if(m_pInventory->contains(type)){
        // qDebug() << "found";
        (*m_pInventory)[type] += amount;
    }else{
           // qDebug() << "NOT found";
        m_pInventory->insert(type,amount);
    }
}
void Inventory::editGoods(const QString &name, double price, int amount)
{
    CargoType* type = getCargoType(name);
    type->setPrice(price);
    (*m_pInventory)[*type] = amount;
}
void Inventory::removeGoods(const QString &name, int amount)
{

    for (auto pair = m_pInventory->begin(); pair != m_pInventory->end(); ++pair)
    {

        if (pair.key().getName() == name)
        {
            if (amount == 0)
            {
                m_pInventory->erase(pair);
            }
            else
            {

                pair.value() -= amount;
                if (pair.value() <= 0)
                {
                    m_pInventory->erase(pair);
                }
            }
            break;
        }
    }
}
bool Inventory::transferGoods(Inventory& other, const QString& name, int amount){
    this->removeGoods(name, amount);
    other.addGoods(*getCargoType(name),amount);
    return true;
}

bool Inventory::setId(unsigned int id)
{
    m_id = id;
    return true;
}
uint Inventory::constructId()
{
    auto uuid = QUuid::createUuid();
    return uuid.toUInt128();
}
uint Inventory::getId() const
{
    return m_id;
}

Inventory* Inventory::getInstance(uint id){
    if(!m_regesteredInventory.contains(id)){
        return nullptr;
    }
    return m_regesteredInventory[id];
}
void Inventory::registerInstance(Inventory* inventory){
    m_regesteredInventory[inventory->getId()] = inventory;
}

const QHash<CargoType,int>* Inventory::getInventory() const
{
    return m_pInventory;
}

void Inventory::print() const
{
    for (const CargoType& type : m_pInventory->keys())
    {
        std::cout << type.getName().toStdString() << " " << type.getPrice() << " " << (*m_pInventory)[type] << std::endl;
    }
}

