
#ifndef MESSAGE_H
#define MESSAGE_H
#include<iostream>
#include<string.h>
#include<QDateTime>
#include <QGroupBox>
#include "logic/contact.h"
/*

Message text
Image or video -->extra
voice note without text --->extra
send date
seen
*/


class Message
{

private:
    std::string ID;
    std::string messageTxt;
    std::string receiverID;
    QDateTime sendDate;
    bool seen;
    bool Favourite;
    bool deleted;
    std::list<Contact *>messageFavBy ;

public:
    Message(std::string _ID, std::string _messageTxt ,std::string _receiverID , QDateTime _sendDate, bool _seen , bool Favourite ,bool deleted = false);
    std::string getID();
    std::string getMessageTxt();
    QDateTime getSendDate();
    std::string getReceiverId();
    bool isSeen();
    bool isFavourite();
    void toggleFavourite();
    void setSeenStatus(bool seenStatus);
    bool isDeleted();
    void toggleDeleted();
    std::list<Contact *>& getMessageFavBy();
    void setMessageFavBy(Contact * name);

};

#endif // MESSAGE_H
