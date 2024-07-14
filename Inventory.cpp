#include "Inventory.h"

#include <iostream>
#include <QFile>

Inventory::Inventory()
{
    m_pInventory = new QHash<CargoType,int>();
}
Inventory::~Inventory()
{
	if (m_pInventory != nullptr)
	{
		delete m_pInventory;
	}
}

Inventory::Inventory(const Inventory& inventory)
{
    m_pInventory = new QHash<CargoType,int>(*inventory.getInventory());
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

void Inventory::addGoods(const CargoType& type, int amount)
{
    if(m_pInventory->contains(type)){
        (*m_pInventory)[type] += amount;
    }else{
        m_pInventory->insert(type,amount);
    }
}

void Inventory::print() const
{
    for (const CargoType& type : m_pInventory->keys())
	{
        std::cout << type.getName().toStdString() << " " << type.getPrice() << " " << (*m_pInventory)[type] << std::endl;
	}
}

void Inventory:: editGoods(const QString &name, double price, int amount)
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
const QHash<CargoType,int>* Inventory::getInventory() const
{
	return m_pInventory;
}

bool Inventory::transferGoods(Inventory& other, const QString& name, int amount){
    this->removeGoods(name, amount);
    other.addGoods(*getCargoType(name),amount);
    return true;
}


