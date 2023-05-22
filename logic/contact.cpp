
#include "contact.h"
#include <string.h>
#include<iostream>
#include <list>
#include <assert.h>
Contact::Contact( std::string _ID , std::string _imgPath  , std::string _name  ,bool _isAdded)
{
    this->ID = _ID;
    this->imgPath = (_imgPath.empty())? ":/imgs/Profile (2).png" : _imgPath;
    this->name = _name;
    this->isAdded = _isAdded;
}

Contact::Contact(){

}

std::string Contact::getID(){
//    assert(!this->ID.empty()); // Check if ID is not empty

    return this->ID;
}

void Contact::setIsAdded(bool _isAdded) {
    this->isAdded = _isAdded;
}

bool Contact::getIsAdded() {
    return this->isAdded;
}


void Contact::setID(std::string ID){
    this->ID = ID;
}
std::string Contact::getImgPath()
{
    return imgPath;
}

void Contact::setImgPath(std::string imgPath)
{
    this->imgPath = imgPath;
}

std::string Contact::getName()
{
    return name;
}

void Contact::setName(std::string name)
{
    this->name = name;
}


