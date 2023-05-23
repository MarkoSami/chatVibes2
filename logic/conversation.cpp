#include "logic/conversation.h"
#include<string.h>
#include "logic/contact.h"
#include <string>
#include <vector>
#include "application/application.h"

Conversation::Conversation(Contact* _receiver, bool _isFavourite, std::string _name,bool _deleted)
    : receiver(_receiver) , isFavourite(_isFavourite),deleted(_deleted)
{
    this->name = (_name == "")? _receiver->getID(): _name;
}


bool Conversation::isDeleted(){
    return this->deleted;
}

void Conversation::toggleDeleted(){
    this->deleted = !this->deleted;
}

bool Conversation::addNewMessage( Message* newMessage){
    this->messages.push_back(newMessage);
    return true;
}

QClickableGroupBox* Conversation::getConversationGroupBoxAddress(){
    return this->conversationGroupBoxAddress;
}

void Conversation::setConversationGroupBoxAddress(QClickableGroupBox* address){
    this->conversationGroupBoxAddress = address;
}

void Conversation::setConvID(std::string id) {
    this->ConvID = id ;
}

std::string Conversation::getConvID() {
    return this->ConvID;
}


