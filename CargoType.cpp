#include "CargoType.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include<qmessagebox.h>

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
CargoType::CargoType():
    CargoType("N/A",0,"N/A")
{}
CargoType::CargoType(const QByteArray& json)
{
    this->deserialize(json);
}
CargoType CargoType::fromFile(const QString& path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return CargoType();
    }
    QByteArray json = file.readAll();
    return CargoType(json);
}
bool CargoType::toJsonObject(QJsonObject& json) const{
    json["name"] = m_name;
    json["price"] = m_price;
    json["type"] = m_type;
    return true;
}
bool CargoType::fromJsonObject(const QJsonObject& json){
    setName(json["name"].toString());
    setPrice(json["price"].toDouble());
    setType(json["type"].toString());
    return true;
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
