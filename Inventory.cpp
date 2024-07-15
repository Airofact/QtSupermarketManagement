#include "Inventory.h"

#include <iostream>
#include <QFile>

Inventory::Inventory()
{
    m_pInventory = new QHash<CargoType,int>();
}
Inventory::~Inventory()
{
    delete m_pInventory;
    m_pInventory = nullptr;
}

Inventory::Inventory(const Inventory& inventory)
{
    m_pInventory = new QHash<CargoType,int>(*inventory.getInventory());
    if(inventory.getId() != 0){
        setId(QUuid::createUuid().toString().toInt());
    }
}

Inventory::Inventory(const QByteArray& json)
    :Inventory()
{
    this->deserialize(json);
}

Inventory Inventory::fromFile(const QString& path){
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return Inventory();
    }
    QByteArray json = file.readAll();
    return Inventory(json);
}
bool Inventory::toJsonObject(QJsonObject& json) const{
    for (const CargoType& type : m_pInventory->keys())
    {
        QJsonObject key;
        type.toJsonObject(key);
        QJsonObject pair;
        pair.insert("cargoType",key);
        pair.insert("amount",(*m_pInventory)[type]);
        json.insert(type.getName(), pair);
    }
    return true;
}
bool Inventory::fromJsonObject(const QJsonObject& json){
    for (const QString& key : json.keys())
    {
        QJsonObject pair = json[key].toObject();
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

    for(CargoType& type:m_pInventory->keys()){
        if(type.getName() == name){
            return &type;
        }
    }
    return nullptr;
}
int Inventory::getAmount(const QString& name) const {
    return (*m_pInventory)[*getCargoType(name)];
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
        //qDebug() << "found";
        (*m_pInventory)[type] += amount;
    }else{
           //qDebug() << "NOT found";
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
    qDebug()<<"5";
    for (auto pair = m_pInventory->begin(); pair != m_pInventory->end(); ++pair)
	{
        qDebug()<<"4";
        if (pair.key().getName() == name)
		{
			if (amount == 0)
            {qDebug()<<"3";
                m_pInventory->erase(pair);
			}
			else
			{
                qDebug()<<"2";
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
    if (m_id != 0)
    {
        return false;
    }
    m_id = id;
    return true;
}

uint Inventory::getNewId()
{
    return QUuid::createUuid().toString().toInt();
}

uint Inventory::getId() const
{
    return m_id;
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

