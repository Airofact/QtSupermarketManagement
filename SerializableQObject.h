#ifndef SERIALIZABLEQOBJECT_H
#define SERIALIZABLEQOBJECT_H

#include <QObject>
#include "ISerializable.h"

class SerializableQObject: public QObject, public ISerializable{
    Q_OBJECT
public:
    //序列化
    bool serialize(QByteArray& json) const override;
    // 反序列化
    bool deserialize(const QByteArray& json) override;
};

#endif // SERIALIZABLEQOBJECT_H
