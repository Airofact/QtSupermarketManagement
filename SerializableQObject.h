#ifndef SERIALIZABLEQOBJECT_H
#define SERIALIZABLEQOBJECT_H

#include <QObject>
#include "ISerializable.h"

class SerializableQObject: public QObject, public ISerializable{
    Q_OBJECT
public:
    //序列化
    virtual bool serialize(QByteArray& json) const override;
    virtual bool toJsonObject(QJsonObject& json) const override;
    // 反序列化
    virtual bool deserialize(const QByteArray& json) override;
    virtual bool fromJsonObject(const QJsonObject& json) override;
};

#endif // SERIALIZABLEQOBJECT_H
