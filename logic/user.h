
#ifndef USER_H
#define USER_H
#include<iostream>
#include <string.h>
#include<list>
#include<stack>
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


public:
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


};

#endif // USER_H
