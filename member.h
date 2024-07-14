#ifndef MEMBER_H
#define MEMBER_H

#endif // MEMBER_H
#include <string>
#include "SerializableQObject.h"
#include <QFile>

class Member: public SerializableQObject
{
    Q_OBJECT
private:
    std::string user;
    std::string password;
    std::string email;
    long long phone;
    std::string image;


public:
    Member():
        user(""),password(""),email(""),phone(0),image(""){};
    Member(std::string user,
           std::string password,
           std::string email,
           long long phone,
           std::string image):user(user),password(password),email(email),phone(phone),image(image){};
    Member(const Member& member):user(member.user),password(member.password),email(member.email),phone(member.phone),image(member.image){};

    Member(const QByteArray& json);
    //序列化
    bool toJsonObject(QJsonObject& json) const{
        json["user"]=QString::fromStdString(user);
        json["password"]=QString::fromStdString(password);
        json["email"]=QString::fromStdString(email);
        json["phone"]=QString::number(phone);
        json["image"]=QString::fromStdString(image);
        return true;
    };
    //反序列化
    bool fromJsonObject(const QJsonObject& json){
        user=json["user"].toString().toStdString();
        password=json["password"].toString().toStdString();
        email=json["email"].toString().toStdString();
        phone=json["phone"].toString().toLong();
        image=json["image"].toString().toStdString();
        return true;
    };
    Member fromFile(const QString& path){
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            return Member();
        }
        QByteArray json = file.readAll();
        return Member(json);
    };


    //获取信息
    std::string getuser() const{return user;};
    std::string getpassword() const{return password;};
    std::string getemail() const{return email;};
    long long getphone() const{return phone;};
    std::string getimage() const{return image;};

    //修改信息
    void setuser(std::string user){this->user=user;};
    void setpassword(std::string password){this->password=password;};
    void setemail(std::string email){this->email=email;};
    void setphone(long long phone){this->phone=phone;};
    void setimage(std::string image){this->image=image;};


};
