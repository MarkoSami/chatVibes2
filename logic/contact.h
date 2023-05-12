
#ifndef CONTACT_H
#define CONTACT_H
#include<iostream>
#include<string.h>

class Contact
{
private:
    std::string ID;
    std::string name;
    std::string imgPath;
    bool isAdded ;

public:
    Contact( std::string _ID , std::string _imgPath = ":/imgs/Profile (2).png", std::string _name = "");
    Contact();
    std::string getID();
    void setID(std::string ID);

    bool getIsAdded();
    void setIsAdded(bool isAdded) ;

    std::string getImgPath();
    void setImgPath(std::string imgPath);

    std::string getName();
    void setName(std::string name);

};

#endif // CONTACT_H
