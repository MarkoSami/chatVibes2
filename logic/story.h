#ifndef STORY_H
#define STORY_H

#include <QString>
#include "logic/contact.h"

class Story
{
private:
    QString imgPath;
    QString publisherImgPath;
    QString caption;
    Contact* publisher;


public:

    Story(QString _caption, QString _imgPath, Contact* _publisher );

    QString getImgPath() const;
    void setImgPath(const QString &value);

    QString getCaption() const;
    void setCaption(const QString &value);


    Contact* getPublisher();
    void setPublisher(Contact* publisher);


};

#endif // STORY_H
