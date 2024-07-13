#ifndef CARGOTYPE_H
#define CARGOTYPE_H

#include "SerializableQObject.h"

/*
 * 商品类
 * 包含商品名称、价格、类型
 * 可获得商品名称、价格、类型
 * 可修改商品名称、价格
 */
class CargoType: public SerializableQObject
{
	Q_OBJECT
private:
    QString m_name;
    Q_PROPERTY(QString name MEMBER m_name READ getName WRITE setName NOTIFY nameChanged FINAL);
    double m_price;
    Q_PROPERTY(double price MEMBER m_price READ getPrice WRITE setPrice NOTIFY priceChanged FINAL);
    QString m_type;
    Q_PROPERTY(QString type MEMBER m_type READ getType WRITE setType NOTIFY typeChanged FINAL);

public:
    CargoType(const QString &name, double price, const QString &type);
    CargoType(const CargoType &goods);
    CargoType(const QByteArray& json);
    CargoType();
    CargoType fromFile(const QString& path);
	// 获得商品名称 例getName();
    QString getName() const;
	// 获得商品价格 例getPrice();
	double getPrice() const;
	// 获得商品类型 例getType();
    QString getType() const;
	// 设置商品名称 例setName("Apple");
    void setName(const QString &name);
	// 设置商品价格 例setPrice(1.5);
	void setPrice(double price);
    // 设置标签
    void setType(const QString& type);
    // 判断两个货物是否为同一种
    bool operator==(const CargoType& other) const;
signals:
    void nameChanged(const QString& name);
    void priceChanged(const double& price);
    void typeChanged(const QString& type);
};

inline uint qHash(const CargoType &key, uint seed) {
    return qHash(key.getName() + key.getType(), seed);
}

#endif
