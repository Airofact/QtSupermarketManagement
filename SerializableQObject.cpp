#include"SerializableQObject.h"
#include<QJsonDocument>

bool SerializableQObject::serialize(QByteArray& json) const{
    QJsonObject jsonObj;
    this->toJsonObject(jsonObj);
    QJsonDocument jsonDoc(jsonObj);
    json = jsonDoc.toJson();
    return true;
}

bool SerializableQObject::toJsonObject(QJsonObject& json) const{
    Q_UNUSED(json);
    return true;
}

bool SerializableQObject::deserialize(const QByteArray& json){
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json);
    QJsonObject jsonObj = jsonDoc.object();
    return this->fromJsonObject(jsonObj);
}

bool SerializableQObject::fromJsonObject(const QJsonObject& json){
    Q_UNUSED(json);
    return true;
}
