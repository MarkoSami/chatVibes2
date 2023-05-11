#include "qclickablegroubox.h"
#include "lib/utils.h"
#include "logic/message.h"
#include "logic/conversation.h"
#include "application/application.h"
#include <QMouseEvent>
#include <QDebug>
#include <QString>
#include <QLabel>

QClickableGroupBox::QClickableGroupBox(QWidget *parent) : QGroupBox(parent)
{
    // Create the context menu and connect the actions to their slots
    createContextMenu();
}

void QClickableGroupBox::createContextMenu()
{
    m_contextMenu = new QMenu(this);
    m_contextMenu->setStyleSheet("background:grey;font-weight:bold;padding:5px");
    m_contextMenu->setCursor(QCursor(Qt::PointingHandCursor));


    m_favAction = m_contextMenu->addAction("Favourite");
    m_favAction->setIcon(*(new QIcon(":/imgs/star.png")));

    m_deleteAction = m_contextMenu->addAction("Delete");
    m_deleteAction->setIcon(*(new QIcon(":/imgs/delete.png")));

    connect(m_favAction, &QAction::triggered, this, &QClickableGroupBox::handleFavAction);
    connect(m_deleteAction, &QAction::triggered, this, &QClickableGroupBox::handleDeleteAction);
}

void QClickableGroupBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        m_contextMenu->exec(event->globalPos());
    } else {
        emit clicked();
    }
}

void QClickableGroupBox::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit doubleClickDetected();
    }
}

void QClickableGroupBox::handleFavAction()
{
    // Show the preview window here
    qDebug() << "favclicked";
}

void QClickableGroupBox::handleDeleteAction()
{
    // Delete the selected item here
    qDebug() << "Item deleted";
    void* object = utils::convertStringToaddress(this->objectName());
    if(this->property("type") == "message"){
        // changing the GUI of the message to be deleted
        QLabel* msgText = this->findChild<QLabel*>("textmsg");
        msgText->setText("Deleted Message.");
        msgText->setStyleSheet("color: #607380;");
        //casting the address to be of type Message
        Message* messagePtr = (Message*)object;
        messagePtr->toggleDeleted();
    }
    else{
        Conversation* conversationPtr = (Conversation*)object;
        conversationPtr->toggleDeleted();
        this->deleteLater();
    }


}





