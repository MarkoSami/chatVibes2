#include "story.h"

Story::Story(QString _caption, QString _imgPath, Contact* _publisher )
    : caption(_caption), imgPath(_imgPath), publisher(_publisher)
{}

QString Story::getImgPath() const
{
    return imgPath;
}

void Story::setImgPath(const QString &value)
{
    imgPath = value;
}

QString Story::getCaption() const
{
    return caption;
}

void Story::setCaption(const QString &value)
{
    caption = value;
}

Contact* Story::getPublisher(){
    return this->publisher;
}
void Story::setPublisher(Contact* publisher){
    this->publisher = publisher;
}





















