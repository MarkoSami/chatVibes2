
#ifndef USER_H
#define USER_H
#include<iostream>
#include <string.h>
#include<list>
#include<stack>
#include <queue>
#include <map>
#include "logic/contact.h"
#include "logic/conversation.h"


class User
{
private:
    std::string ID;
    std::string user_name;
    std::string first_name;
    std::string last_name;
    std::string password;
    std::list<Contact*> contacts;
    std::stack<Conversation*> conversations;
    std::string imgPath;
    bool loggedIn;
    Contact *UserConatct;
    bool showImg  ;

    std::unordered_map<QString,QString> settings;



public:
    class Comparator {
    public:
        bool operator()(const std::pair<int, Conversation*>& lhs, const std::pair<int, Conversation*>& rhs) const {
            // Compare the pairs based on their first element (the number of messages)
            return lhs.first < rhs.first;
        }
    };

    User(std::string _ID, std::string _user_name, std::string _first_name, std::string _last_name ,std::string _password, std::string _imgPath = ":/imgs/Profile (2).png", bool _loggedIn = false);
    // getters and setters
    std::string getUserID();
    void setUserID(std::string ID);

    bool getShowImg();
    void setShowImg(bool showImg);

    std::string getUserName();
    void setUserName(std::string userName);

    std::string getUserPassword();
    void setUserPassword(std::string password);

    std::list<Contact*>& getUserContacts();
    void setUserContacts(std::list<std::string> &contacts);

    std::string getIMGpath();
    void setIMGpath(std::string image);

    std::string getlastName();
    void setlastName(std::string name);

    std::string getFirstName();
    void setFirstName(std::string name);

    std::stack<Conversation*>& getConversations();
    void addNewConversation(Conversation* conversation);

    std::unordered_map<QString,QString>& getSettings();
    void modifySetting(QString settingKey ,QString settingValue);

    // user logic functions
    bool isLoggedIn();
    void setLoggedIn(bool value) ;
    bool addContact(  Contact* newContact);
    bool removeContact(std::string contactID);
    Contact* findContact(std::string contactID);

    // Getter for UserContact
    Contact* getUserContact();

    // Setter for UserContact
    void setUserContact(Contact* contact);



    std::priority_queue<std::pair<int, Conversation*>, std::vector<std::pair<int, Conversation*>>, Comparator> getConversationsQueue();


};

#endif // USER_H
