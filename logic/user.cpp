#include "user.h"
#include "contact.h"
#include <list>

User::User(std::string ID, std::string user_name, std::string first_name, std::string last_name, std::string password, std::string imgPath, bool loggedIn)
    : ID(ID), user_name(user_name), first_name(first_name), last_name(last_name), password(password), contacts(), imgPath(imgPath), loggedIn(loggedIn)
{
}

bool User::addContact(   Contact* newContact){
    this->contacts.push_back(newContact);
    for(auto &contact : this->contacts){
        qDebug()<<contact<<"\n";
    }
    return true;
}

void User::setUserID(std::string _id) {
    this->ID = _id ;
}

bool User::removeContact(std::string contactID) {
    for (auto it = contacts.begin(); it != contacts.end(); ++it) {
        if ((*it)->getID() == contactID) {
            contacts.erase(it);
            return true; // contact found and removed, return from function
        }
    }
    return false; // contact not found
}


Contact* User::findContact(std::string contactID) {

    for (auto &contact : this->contacts) {
        if (contact->getID() == contactID) {
            return contact;
        }
    }
    return nullptr;
    // contact not found
}

bool User::getShowImg() {
    return this->showImg;
}

void User::setShowImg(bool isShow){
    this->showImg = isShow;
}

std::stack<Conversation*>& User::getConversations(){
    return this->conversations;
}

void User::addNewConversation(Conversation* conversation){
    this->conversations.push(conversation);
}

// getters
std::string User::getFirstName(){
    return this->first_name;
}

std::string User::getlastName(){
    return this->last_name;
}

std::string User::getUserID(){
    return this->ID;
}

std::string User::getUserName(){
    return this->user_name;
}
void User::setUserName(std::string userName)
{
    this->user_name = userName;
}
std::string User::getUserPassword(){
    return this->password;
}

std::string User::getIMGpath(){
    return this->imgPath;
}
void User::setIMGpath(std::string img)
{
    this->imgPath = img;

}
std::list<Contact*>& User::getUserContacts(){
    return (this->contacts);
}

bool User::isLoggedIn(){
    return this->loggedIn;
}

void User::setLoggedIn(bool value) {
    this->loggedIn = value;
}

Contact* User::getUserContact(){
    return this->UserConatct;
}

void User::setUserContact(Contact* contact) {
    this->UserConatct = contact;
}

