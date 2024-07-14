#ifndef MEMBER_H
#define MEMBER_H

#endif // MEMBER_H
#include <string>
#include <iostream>
#include "SerializableQObject.h"

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
    Member()=default;
    Member(std::string user,
           std::string password,
           std::string email,
           long long phone,
           std::string image):user(user),password(password),email(email),phone(phone),image(image){};
    Member(const QByteArray& json);
    //序列化
    bool toJsonObject(QJsonObject& json) const;
    //反序列化
    bool fromJsonObject(const QJsonObject& json);
    Member fromFile(const QString& path);


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
