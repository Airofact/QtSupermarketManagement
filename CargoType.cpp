#include "CargoType.h"

#include <QJsonObject>
#include <QJsonDocument>

CargoType::CargoType(const QString &name, double price, const QString &type)
    : m_name(name), m_price(price), m_type(type)
{
}
CargoType::CargoType(const CargoType &goods)
{
    m_name = goods.m_name;
    m_price = goods.m_price;
    m_type = goods.m_type;
}
CargoType::CargoType(const QByteArray& json)
{
    this->deserialize(json);
}
CargoType::CargoType():
    CargoType("N/A",0,"N/A")
{

}
QString CargoType::getName() const
{
    return m_name;
}

double CargoType::getPrice() const
{
    return m_price;
}

QString CargoType::getType() const
{
    return m_type;
}

void CargoType::setName(const QString &name)
{
    this->m_name = name;
    emit nameChanged(name);
}

void CargoType::setPrice(double price)
{
    this->m_price = price;
    emit priceChanged(price);
}

void CargoType::setType(const QString& type){
    this->m_type = type;
    emit typeChanged(type);
}

bool CargoType::operator==(const CargoType& other) const{
    return getName() == other.getName();
}
