#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include<sstream>
#include<QString>
#include <stack>
#include <iostream>
#include "logic/conversation.h"





class utils
{
public:
    utils();

    static QString convertAddressToString(void* address){
        std::stringstream ss ;
        ss << address;
        std::string stringAddress = ss.str();
        return stringAddress.c_str();
    }

    static void* convertStringToaddress(QString str){
        std::stringstream ss(str.toStdString());
        void* address;
        ss >> address;// Read the address from the stringstream.
        return address;
    }

    static void moveToTop(std::stack<Conversation*>& conversations,Conversation* targetConversation){
        std::stack<Conversation*> temp;
        while(!conversations.empty()){
            Conversation* topConversastion = conversations.top();
            conversations.pop();

            if(topConversastion == targetConversation){

                while(!temp.empty()){
                    conversations.push(temp.top());
                    temp.pop();
                }
                conversations.push(topConversastion);
                return;
            }
            temp.push(topConversastion);

        }

    }


};

#endif // UTILS_H
