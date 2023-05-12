
#ifndef GUI_RENDER_H
#define GUI_RENDER_H

#include <QMainWindow>

#include "customGUI/qclickablegroubox.h"
#include "logic/story.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QLabel"
#include "QDate"
#include "application/application.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib/utils.h"



class GUI_render
{
public:
    GUI_render();

    static void renderStories(MainWindow* mainWindow){
        QLayout* layout = mainWindow->getUI()->horizontalGroupBox_3->layout();
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (item->widget() != mainWindow->getUI()->label_3) {
                delete item->widget(); // delete the widget associated with the item
                delete item; // delete the item itself
            }
        }


        QLayout* layout2 = mainWindow->getUI()->StoriesContainer->layout();
        QLayoutItem* item2;
        while ((item2 = layout2->takeAt(0)) != nullptr) {
            delete item2->widget(); // delete the widget associated with the item
            delete item2; // delete the item itself
        }


        if (Application::stories[Application::loggedUser->getUserName()].size() > 0) {
            QClickableGroupBox* storyBoxLoggedUser = renderStory(Application::stories[Application::loggedUser->getUserName()].front() , Application::loggedUser->getUserName());
            MainWindow::connect(storyBoxLoggedUser, &QClickableGroupBox::clicked, [=]() {
                MainWindow::handleStoryClicked(storyBoxLoggedUser , Application::stories[Application::loggedUser->getUserName()] , mainWindow);
            });
            mainWindow->getUI()->horizontalGroupBox_3->layout()->addWidget(storyBoxLoggedUser) ;
        }

        for(auto& contact : Application::loggedUser->getUserContacts()){
            std::list<Story*> storiesList = Application::stories[contact->getName()];
            if (storiesList.empty()) continue ;

            QClickableGroupBox* storyBox = renderStory(storiesList.front() , contact->getName());
                MainWindow::connect(storyBox, &QClickableGroupBox::clicked, [=]() {
                    MainWindow::handleStoryClicked(storyBox , storiesList , mainWindow);
                });
                mainWindow->getUI()->StoriesContainer->layout()->addWidget(storyBox);

        }

    }


    static QClickableGroupBox* renderStory(Story* story , std::string contactName){

        QHBoxLayout *hLayout = new QHBoxLayout;
        QVBoxLayout *VLayout = new QVBoxLayout ;
        QHBoxLayout *hLabelChild = new QHBoxLayout ;
        QHBoxLayout *hLabelName = new QHBoxLayout ;
        QLabel *pic = new QLabel() ;

        QString IMG_PATH = QString::fromStdString(story->getPublisher()->getImgPath());
        QSize imgMaxSize = (IMG_PATH == ":/imgs/Profile (2).png")? *new QSize(40,40) : *new QSize(50,40);

        if(IMG_PATH == ":/imgs/Profile (2).png")
            pic->setMaximumSize(imgMaxSize);

        pic->setMinimumSize(imgMaxSize);

        QString imgType = IMG_PATH == ":/imgs/Profile (2).png"? "image" : "border-image";
        pic->setStyleSheet( imgType+  ":url(" + IMG_PATH + ");border-radius:8px");

        QLabel *senderName = new QLabel(QString::fromStdString(contactName)) ;
        QLabel *textmsg = new QLabel() ;
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
        QGroupBox *VGroupBox = new QGroupBox();
        VGroupBox->setContentsMargins(0,0,0,0);
        VLayout->setSpacing(4);
        VGroupBox->setLayout(VLayout);
        VGroupBox->setStyleSheet("background:#161a1d; font-size:15px ; color:white ;font-weight:bold ");
        hLayout->addWidget(pic);
        hLayout->addWidget(VGroupBox);

        QClickableGroupBox* storyGroupBox = new QClickableGroupBox();

        storyGroupBox->setLayout(hLayout);
        QSpacerItem* hSpacer = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        storyGroupBox->layout()->addItem(hSpacer);

        QLabel *datemsg = new QLabel();
        datemsg->setText(QDate::currentDate().toString());
        datemsg->setStyleSheet("color:grey; font-size:11px ; background:transparent");

        storyGroupBox->layout()->addWidget(datemsg);
        storyGroupBox->setStyleSheet("QGroupBox { border:none; background :#161a1d ;border-radius : 5px;}") ;

        storyGroupBox->setCursor(Qt::PointingHandCursor);
        storyGroupBox->setObjectName(utils::convertAddressToString(story));

        return storyGroupBox;
    }

    static QLabel* renderFavMessage(Message message) {
        QLabel* favMessage = new QLabel() ;
        QString messageText = QString::fromStdString(message.getMessageTxt());
        QString wraptext = Application::breakText(messageText,40);
        favMessage->setText(wraptext);
        favMessage->setStyleSheet("background : rgb(22, 26, 29); padding :16px 20px;border-radius:8px;color:white ; font-weight:bold ; ")  ;
        favMessage->setMinimumHeight(61);
        favMessage->setWordWrap(true);
        favMessage->setMaximumWidth(340);
        return favMessage ;
    }

    static void renderConversations(MainWindow* mainWindow,bool reversed){

        // Make a copy of the original stack
        std::stack<Conversation*> tempConversations ;

        qDebug()<<Application::loggedUser->getUserName() ;
        qDebug()<<Application::loggedUser->getConversations().size();

        // Render the copied conversations
        while (!Application::loggedUser->getConversations().empty()) {

            qDebug()<<"con Name: "<<Application::loggedUser->getConversations().top()->getName();
            Conversation* conversationPtr = (Application::loggedUser->getConversations().top());
            tempConversations.push(conversationPtr);

            // Convert the address to a string
            std::stringstream ss;
            ss << conversationPtr;
            std::string conversationAddress = ss.str();

            // Create the QClickableGroupBox widget
            QClickableGroupBox *renderConversation = Application::renderConversation(conversationPtr)->outerLayout;
            conversationPtr->setConversationGroupBoxAddress(renderConversation);
            renderConversation->setObjectName(QString::fromStdString(conversationAddress));
            if(!reversed)
                mainWindow->getUI()->contactsCont->layout()->addWidget(renderConversation);
            else{
                QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(mainWindow->getUI()->contactsCont->layout());
                if (layout) {
                    layout->insertWidget(0, renderConversation);
                }

            }
            renderConversation->setEnabled(true);

            // Connect the clicked() signal to a lambda function
            MainWindow::connect(renderConversation, &QClickableGroupBox::clicked, [=]() {
                mainWindow->handleClickedConversation(renderConversation);
            });

            Application::loggedUser->getConversations().pop();
        }

        while(!tempConversations.empty()){
            Application::loggedUser->getConversations().push(tempConversations.top());
            tempConversations.pop();
        }
    }


};

#endif // GUI_RENDER_H
