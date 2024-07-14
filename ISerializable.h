#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include<QByteArray>
#include<QJsonObject>

class ISerializable
{
public:
    ISerializable() = default;
    ISerializable(const QByteArray& json);

    virtual bool serialize(QByteArray& json) const = 0;
    virtual bool toJsonObject(QJsonObject& json) const = 0;
    virtual bool deserialize(const QByteArray& json) = 0;
    virtual bool fromJsonObject(const QJsonObject& json) = 0;
};

#endif // ISERIALIZABLE_H
