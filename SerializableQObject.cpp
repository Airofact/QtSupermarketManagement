  #include "SerializableQObject.h"

#include<QJsonObject>
#include<QJsonDocument>
#include<QMetaObject>
#include<QMetaProperty>
#include<QJsonArray>
#include<QFile>

SerializableQObject SerializableQObject::fromFile(const QString& path){
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return SerializableQObject();
    }
    QByteArray json = file.readAll();
    file.close();
    return SerializableQObject(json);
}

bool SerializableQObject::serialize(QByteArray& json) const {
    QJsonObject object;
    if(!toJsonObject(object)){
        return false;
    }
    json = QJsonDocument(object).toJson();
    return true;
}

bool SerializableQObject::deserialize(const QByteArray& json) {
    QJsonDocument document = QJsonDocument::fromJson(json);
    QJsonObject object = document.object();
    return fromJsonObject(object);
}
