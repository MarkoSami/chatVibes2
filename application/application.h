#ifndef APPLICATION_H
#define APPLICATION_H
#include <list>
#include <stack>
#include <map>
#include <QGraphicsBlurEffect>
#include"logic/user.h"
#include "logic/conversation.h"
#include "logic/story.h"
#include "lib/utils.h"
 class Application
{
public:

    Application();

    static std::list<User*> users ;
    static std::unordered_map<std::string,std::list<Story*>> stories ;

    static User* loggedUser;
    static bool logUserIn(User& user);
    static Conversation *currentConversation ;
    static Story* currentStory ;
    static std::list<Story*>currentStoryList ;

    static User* getLogInUser() {
        for (auto &user : Application::users)
        {
            if (user->isLoggedIn()) {
                return user ;
            }
        }
        return nullptr;
    }

    static bool isSubstringFound(const std::string& inputString, const std::string& substring) {
        return inputString.find(substring) != std::string::npos;
    }

    static User* searchForurUser(std::string userId) {

        for(auto *user : Application::users)
        {
            if( user != nullptr && userId == user->getUserName()) {
                return user;
            }
        }
        return nullptr;
    }

    static bool registerUser(User* user)
    {
        if(Application::isAlreadyRegistered(user)){
            return false;
        }
        Application::users.push_back(user);
        return true;
    }




    static bool isAlreadyRegistered(User* user)
    {
        std::string userID = user->getUserName();

        for(auto regUser : Application::users)
        {
            if(userID == regUser->getUserName())
                return true;
        }
        return false;
    }


    static bool loginUser(std::string id , std::string password)
    {
        if (id.empty() || password.empty()) {
            return false ;
        }

        User *targetUser = Application::searchForurUser(id);

        if(targetUser == nullptr || Application::isAlreadyLoggedIn(*targetUser) || password != targetUser->getUserPassword()){
            return false;
        }

        targetUser->setLoggedIn(true);
        return true;
    }

    static bool isAlreadyLoggedIn(User& user)
    {

        if ((&user) == nullptr || !user.isLoggedIn()) {
            return false;
        }

        return true ;
    }


    // get New Conversatoin


    static Conversation* getReceiverConversation(std::string receiverName) {
        Conversation *myConv = nullptr ;
        bool stop = false ;
        for (auto &user : Application::users )  {
                // Make a copy of the original stack
                std::stack<Conversation*> tempConversations ;
                // Render the copied conversations
                while (!user->getConversations().empty()) {
                    Conversation* conversationPtr = (user->getConversations().top());
                    tempConversations.push(conversationPtr);
                    user->getConversations().pop();
                }

                while(!tempConversations.empty()){
                    if (user->getUserName() == receiverName ) {
                        if (tempConversations.top()->getReceiver()->getName() == loggedUser->getUserName()) {
                            myConv = tempConversations.top();
                            stop = true ;
                        }
                }
                    user->getConversations().push(tempConversations.top());
                    tempConversations.pop();
                    if (stop) return myConv;
                }
            }

        if (myConv == nullptr) {
            for (auto &user : Application::users) {
                    if (user->getUserName() == receiverName) {
                        Contact *newContact = new Contact(loggedUser->getUserID()); // related to reciever
                        newContact->setName(loggedUser->getUserName());
                        Conversation *newConv = new Conversation(newContact , false , loggedUser->getUserID()) ;
                        myConv = newConv ;
                        user->addNewConversation(newConv);
                        break ;
                }
            }
        }

        return myConv;
    }

    static std::string findContactID(std::string name ) {
        for (auto &user : users) {
            if (user->getUserName() == name) {
                return user->getUserID() ;
            }
        }
        return "note:user doesn't exist in the Application!";
    }

    static Conversation* updatePhoto(std::string receiverName , std::string newImg) {

        for (auto &user : Application::users )  {
            // Make a copy of the original stack
            std::stack<Conversation*> tempConversations ;
            // Render the copied conversations
            while (!user->getConversations().empty()) {
                Conversation* conversationPtr = (user->getConversations().top());
                tempConversations.push(conversationPtr);
                user->getConversations().pop();
            }

            while(!tempConversations.empty()){
                if (user->getUserName() != loggedUser->getUserName() && tempConversations.top()->getReceiver()->getName() == receiverName ) {
                        tempConversations.top()->getReceiver()->setImgPath(newImg);
                }
                user->getConversations().push(tempConversations.top());
                tempConversations.pop();
            }
        }
    }

    static std::string renderWithPhoto(std::string receiverName) {

        for (auto &user : Application::users )  {
            if (user->getUserName() == receiverName) {
                return user->getIMGpath() ;
            }
        }
        return ":/imgs/Profile (2).png" ;
    }

    static QString breakText(QString& txt , int range){

        if(txt.size() <=range) return txt;
        QString leftText = txt.mid(0,txt.size()-range);
        QString rightText = txt.mid(txt.size()-range,txt.size()-1);
        return breakText(leftText,range) + "\n" + breakText(rightText,range);
    }

    static void handleNewConversations(Conversation* conv , User* user) {

          // Make a copy of the original stack
          std::stack<Conversation*> tempConversations ;
            if (loggedUser->getConversations().empty()) {
                loggedUser->addNewConversation(conv);
                return ;
            }

            while (!loggedUser->getConversations().empty()) {
                Conversation* conversationPtr = (loggedUser->getConversations().top());
                tempConversations.push(conversationPtr);
                loggedUser->getConversations().pop();
            }

            while(!tempConversations.empty()){
                if (tempConversations.top()->getName() == conv->getName()) {
                    tempConversations.top()->setName(user->getUserName());
                }
                loggedUser->getConversations().push(tempConversations.top());
                tempConversations.pop();
            }

    }
    struct messageLayout
    {
        QClickableGroupBox* outerLayout;
        QGroupBox * innerLAyout;
    };

    static messageLayout* renderMessage(Message* message){

        QString originalColour = (message->getReceiverId() == Application::loggedUser->getUserID())? "#161a1d" : "#3663fd";
        bool isFavouriteHandler = false ;
        for (auto &putFavUser : message->getMessageFavBy()) {
                if (putFavUser->getName() == Application::loggedUser->getUserContact()->getName() && message->isFavourite()) {
                    isFavouriteHandler = true;
                }
        }

            QHBoxLayout *hLayout = new QHBoxLayout;
            QVBoxLayout *VLayout = new QVBoxLayout ;
            QLabel *textmsg = new QLabel() ;
            textmsg->setObjectName("textmsg");
            textmsg->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
            textmsg->setText((message->isDeleted())? "Deleted message." : QString::fromStdString(message->getMessageTxt()));
            textmsg->setStyleSheet((message->isDeleted())? "color: #999999;": "color:white");
            textmsg->setTextInteractionFlags(Qt::TextSelectableByMouse);
            // Set the cursor to the I-beam cursor
            textmsg->setCursor(Qt::IBeamCursor);
            QLabel *datemsg = new QLabel();
            datemsg->setText(message->getSendDate().toString());
            QString txt = textmsg->text();
            textmsg->setText( breakText(txt,70));

            VLayout->addWidget(textmsg);
            VLayout->addWidget(datemsg);
            datemsg->setAlignment(Qt::AlignRight);
            datemsg->setStyleSheet("color:grey; font-size:8px");

            QGroupBox *VGroupBox = new QGroupBox();
            VLayout->setSpacing(0);
            VGroupBox->setLayout(VLayout);
            if (!message->isDeleted()) {
//            VGroupBox->setStyleSheet("background:#"+ (QString)((isFavouriteHandler)? "F0A500": originalColour ) +"; font-size:17px ; color: white ;font-weight:bold ");
            }
            QSpacerItem *hSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

            if (message->getReceiverId() == loggedUser->getUserID()) {
                hLayout->addItem(hSpacer);
                hLayout->addWidget(VGroupBox);
            }
            else {
                hLayout->addWidget(VGroupBox);
                hLayout->addItem(hSpacer);
            }
            VGroupBox->setStyleSheet("background:#"+ (QString)((isFavouriteHandler)? "F0A500": "3663fd" ) +"; font-size:17px ; color: white;font-weight:bold ");
            datemsg->setStyleSheet("color:white; font-size:8px");
            QClickableGroupBox *hGroupBox = new QClickableGroupBox();
            hGroupBox->setProperty("type","message");
            hGroupBox->setObjectName(utils::convertAddressToString(message));
            hGroupBox->setLayout(hLayout);

            messageLayout* msgLayout = new messageLayout;
            msgLayout->innerLAyout = VGroupBox;
            msgLayout->outerLayout = hGroupBox;
            QAction::connect(hGroupBox, &QClickableGroupBox::doubleClickDetected, [=]() {
                handleDoubleClicked(msgLayout);
            });

            return msgLayout;
    }



    static void handleDoubleClicked(messageLayout* message){
        qDebug()<<"Double clicked..!";
            Message* messagePtr = (Message*)utils::convertStringToaddress(message->outerLayout->objectName());
        messagePtr->toggleFavourite();
        if (messagePtr->isFavourite()) {
                messagePtr->setMessageFavBy(Application::loggedUser->getUserContact());
        }
        else {
                auto contacts = messagePtr->getMessageFavBy();
                for (auto contact = contacts.begin(); contact != contacts.end(); ++contact) {
                    if ((*contact)->getName() == Application::loggedUser->getUserContact()->getName()) {
                        contacts.erase(contact);
                        break;
                    }
                }
        }

        if (!messagePtr->isDeleted()){
        QString style = "background:#"+ ((QString)((messagePtr->isFavourite())? "F0A500": "3663fd" ) +"; font-size:17px ; color: white ;font-weight:bold ");
        message->innerLAyout->setStyleSheet(style);
        }
        qDebug()<<messagePtr->isFavourite();

    }

    struct conversationLayout
    {
        QClickableGroupBox* outerLayout;
        QLabel * lastmessage;
    };

    static conversationLayout* renderConversation(Conversation* conversation){

            QHBoxLayout *hLayout = new QHBoxLayout;
            QVBoxLayout *VLayout = new QVBoxLayout ;
            VLayout->setObjectName("VLayout");
            QHBoxLayout *hLabelChild = new QHBoxLayout ;
            hLabelChild->setObjectName("lastMsgBox");
            QHBoxLayout *hLabelName = new QHBoxLayout ;
            QLabel *pic = new QLabel() ;

            QString IMG_PATH =QString::fromStdString(conversation->getReceiver()->getImgPath());
            QSize imgMaxSize = (IMG_PATH == ":/imgs/Profile (2).png")? *new QSize(40,40) : *new QSize(50,40);

            if(IMG_PATH == ":/imgs/Profile (2).png")
                pic->setMaximumSize(imgMaxSize);

            pic->setMinimumSize(imgMaxSize);

            QString imgType = IMG_PATH == ":/imgs/Profile (2).png"? "image" : "border-image";
            pic->setStyleSheet( imgType+  ":url(" + IMG_PATH + ");border-radius:8px");
            QLabel *senderName = new QLabel(QString::fromStdString(conversation->getName())) ;
            QLabel *textmsg = new QLabel() ;
            textmsg->setObjectName("textmsg");
            QString texttest = QString::fromStdString((conversation->getMessages().empty())? "Chat now !" : conversation->getMessages().back()->getMessageTxt() );
            QSpacerItem* hchildSpacer = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
            QSpacerItem* hchildSpacerName = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
            hLabelName->addWidget(senderName);
            hLabelName->addItem(hchildSpacerName);
            hLabelName->setContentsMargins(0,0,0,0);
            hLabelChild->addWidget(textmsg) ;
            hLabelChild->addItem(hchildSpacer) ;
            hLabelChild->setContentsMargins(0,0,0,0);

            QGroupBox *hGroupBoxName = new QGroupBox();
            QGroupBox *hGroupBoxChild = new QGroupBox();
            hGroupBoxName->setLayout(hLabelName);
            hGroupBoxChild->setLayout(hLabelChild);
            textmsg->setStyleSheet("color:gray ; font-size :12px ");
            textmsg->setWordWrap(true);
            textmsg->setTextFormat(Qt::RichText);
            VLayout->addWidget(hGroupBoxName);
            VLayout->addWidget(hGroupBoxChild);
            int maxWidth = 130; // Maximum width in pixels
            QFont font("Arial", 12);
            QFontMetrics fontMetrics(font);
            QString elidedText = fontMetrics.elidedText(texttest, Qt::ElideRight, maxWidth);
            textmsg->setText(elidedText);
            QGroupBox *VGroupBox = new QGroupBox();
            VGroupBox->setContentsMargins(0,0,0,0);
            VLayout->setSpacing(4);
            VGroupBox->setLayout(VLayout);
            VGroupBox->setStyleSheet("background:#161a1d; font-size:15px ; color:white ;font-weight:bold ");
            hLayout->addWidget(pic);
            hLayout->addWidget(VGroupBox);

            QClickableGroupBox *hGroupBox = new QClickableGroupBox();

            hGroupBox->setProperty("type","conversation");
            hGroupBox->setProperty("msgText","conversation");
            hGroupBox->setProperty("labelAddress",utils::convertAddressToString(textmsg));
            hGroupBox->setProperty("ContactNameAddress",utils::convertAddressToString(senderName));

            hGroupBox->setLayout(hLayout);
            QSpacerItem* hSpacer = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
            hGroupBox->layout()->addItem(hSpacer);

            QLabel *datemsg = new QLabel();
            datemsg->setText(QDate::currentDate().toString());
            datemsg->setStyleSheet("color:grey; font-size:11px ; background:transparent");

            hGroupBox->layout()->addWidget(datemsg);
            hGroupBox->setStyleSheet("QGroupBox { border:none; background :#161a1d ;border-radius : 5px;}") ;

            hGroupBox->setCursor(Qt::PointingHandCursor);

            conversationLayout* convLayout = new conversationLayout;

            convLayout->outerLayout = hGroupBox ;
            convLayout->lastmessage =  textmsg ;


            return convLayout ;

    }
};

#endif // APPLICATION_H
