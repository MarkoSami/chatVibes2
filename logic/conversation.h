
#ifndef CONVERSATION_H
#define CONVERSATION_H
#include<iostream>
#include<string.h>
#include "logic/contact.h"
#include "logic/message.h"
#include "customGUI/qclickablegroubox.h"
#include <list>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QGroupBox>
#include <QTextOption>


class Conversation
{
private:

    Contact* receiver;   // consider it as sender not reciever
    std::list<Message*> messages;
    std::string name;
    QClickableGroupBox* conversationGroupBoxAddress;
    bool isFavourite;
    bool deleted;


public:

    enum messageSide  {
        right ,
        left
    };



    Conversation(Contact *_receiver, bool _isFavourite = false,std::string _name = "",bool deleted = false);
    // Setters
    void setReceiver(Contact _receiver) {
        receiver->setName(_receiver.getName());
        receiver->setImgPath(_receiver.getImgPath());
    }

    bool isDeleted();
    void toggleDeleted();

    void setName(std::string _name) { name = _name; }
    void setIsFavourite(bool _isFavourite) { isFavourite = _isFavourite; }

    // Getters
    Contact* getReceiver(){ return receiver; }
    std::list<Message*> getMessages()   { return messages; }
    std::string getName(){ return name; }
    bool getIsFavourite(){ return isFavourite; }// get is the conversation favourite or not

    bool addNewMessage( Message *message );
    void setAsFavouriteMessage(std::string messageID);



    void unsetAsFavouriteMessage(std::string messageID);


    QClickableGroupBox* getConversationGroupBoxAddress();
    void setConversationGroupBoxAddress(QClickableGroupBox*);






};

#endif // CONVERSATION_H
