#include "user.h"
#include "contact.h"
#include <list>
#include <map>

User::User(std::string ID, std::string user_name, std::string first_name, std::string last_name, std::string password, std::string imgPath, bool loggedIn)
    : ID(ID), user_name(user_name), first_name(first_name), last_name(last_name), password(password), contacts(), imgPath(imgPath), loggedIn(loggedIn)
{
    settings["sortBy"] = "Latest" ;
}

bool User::addContact(Contact* newContact){
    this->contacts[newContact->getID().c_str()] = newContact;
    return true;
}

void User::setUserID(std::string _id) {
    this->ID = _id ;
}

bool User::removeContact(std::string contactID) {
    this->contacts.erase(contactID.c_str());
    return false; // contact not found
}


Contact* User::findContact(std::string contactID) {

    Contact* contact = this->contacts.find(QString::fromStdString(contactID))->second;
    return contact;
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
std::unordered_map<QString,Contact*>& User::getUserContacts(){
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

std::unordered_map<QString,QString>& User::getSettings(){
    return this->settings;
}

void User::modifySetting(QString settingKey ,QString settingValue){
    this->settings[settingKey] = settingValue;
}


struct Comparator {
    bool operator() (const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        return p1.first > p2.first;
    }
};


std::priority_queue<std::pair<int, Conversation*>, std::vector<std::pair<int, Conversation*>>, User::Comparator> User::getConversationsQueue(){

    std::priority_queue<std::pair<int, Conversation*>, std::vector<std::pair<int, Conversation*>>, User::Comparator> queue;
    std::stack<Conversation*> temp;
    //constructing the priority queue
    while(!conversations.empty()){
        Conversation* topConv = conversations.top();
        conversations.pop();

        int numberOfMessages = topConv->getMessages().size();
        queue.push(std::make_pair( numberOfMessages,topConv));
        temp.push(topConv);
    }
    /// refilling the original stack
    while(!temp.empty()){
        Conversation* topConv = temp.top();
        temp.pop();
        conversations.push(topConv);
    }

//    std::list<std::pair<int, Conversation*>> tempConvs;
//    while(!queue.empty()){
//        qDebug()<<queue.top()<<"\n";
//        tempConvs.push_back(queue.top());
//        queue.pop();
//    }

//    for(auto &conv : tempConvs){
//        queue.push(conv);
//    }



    return queue;

}










