#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include<QByteArray>

class ISerializable
{
public:
    ISerializable() = default;
    ISerializable(const QByteArray& json);
    virtual bool serialize(QByteArray& json) const = 0;
    virtual bool deserialize(const QByteArray& json) = 0;
};

#endif // ISERIALIZABLE_H
