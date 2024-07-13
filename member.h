#ifndef MEMBER_H
#define MEMBER_H

#endif // MEMBER_H
#include <string>
#include <iostream>

class Member
{
private:
    std::string user;
    std::string password;
    std::string email;
    long long phone;
    std::string image;


public:
    Member(std::string user,
           std::string password,
           std::string email,
           long long phone,
           std::string image):user(user),password(password),email(email),phone(phone),image(image){};

    std::string getuser(){return user;};
    std::string getpassword(){return password;};
    std::string getemail(){return email;};
    long long getphone(){return phone;};
    std::string getimage(){return image;};
};
