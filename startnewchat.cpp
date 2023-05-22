#include "startnewchat.h"
#include "ui_startnewchat.h"
#include "application/application.h"
#include <QThread>
#include <QProgressBar>
#include <QTimer>
StartNewChat::StartNewChat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartNewChat)
{
    ui->setupUi(this);
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
}

StartNewChat::~StartNewChat()
{
    delete ui;
}

void StartNewChat::on_pushButton_clicked()
{
    std::string id = ui->contactName->text().toStdString(); // assign unique id to each contact
    std::string messageContent = ui->messageContent->text().toStdString();
    bool isExist = false ;

        std::stack<Conversation*> tempConversations ;
        // Render the copied conversations
        while (!Application::loggedUser->getConversations().empty()) {
            Conversation* conversationPtr = (Application::loggedUser->getConversations().top());
            if (conversationPtr->getName() == id ) isExist = true ;
            tempConversations.push(conversationPtr);
            Application::loggedUser->getConversations().pop();
        }

        while(!tempConversations.empty()){
            Application::loggedUser->getConversations().push(tempConversations.top());
            tempConversations.pop();
        }

    if ((Application::loggedUser) != nullptr) {
        if (id != "" && messageContent != "" && !isExist) {
            Contact *newContact = new Contact(id); // mark // username
            newContact->setName(newContact->getID());
            newContact->setID(Application::findContactID(newContact->getName()));
            Conversation* newConversation = new Conversation(newContact , false , newContact->getName());
            Application::loggedUser->addNewConversation(newConversation);

            Message *messageText = new Message(Application::loggedUser->getUserID(), messageContent, newConversation->getReceiver()->getID() , QDateTime::currentDateTime(), false, false);
            newConversation->addNewMessage(messageText);

            emit renderConversationAnonymously();

            Conversation* crnt = newConversation;
            QClickableGroupBox* gb = crnt->getConversationGroupBoxAddress();
            QString addrs = gb->property("labelAddress").toString(); // message label
            QLabel* messageLabelAddress = (QLabel*)utils::convertStringToaddress(addrs);

            messageLabelAddress->setText(messageText->getMessageTxt().c_str());


//            QClickableGroupBox* ConversationgroubBoxAddress  = Application::currentConversation->getConversationGroupBoxAddress();

            Conversation *receiverConv = Application::getReceiverConversation(newConversation->getReceiver()->getName());
            if(receiverConv != nullptr)
            receiverConv->addNewMessage(messageText);
            this->close();
        }
        else {
            if(isExist && ui->messageContent->text() == "") ui->messgAlert->setText("type message please") ;
            else if (isExist) ui->messgAlert->setText("Conversation is already exist") ;
            else {
            ui->messgAlert->setText("fill all the fields") ;
            }
        }
    }
}


void StartNewChat::on_pushButton_5_clicked()
{
    this->close();
}

