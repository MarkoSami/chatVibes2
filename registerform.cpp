#include "registerform.h"
#include "ui_registerform.h"
#include <QPixmap>
registerform::registerform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerform)
{
    ui->setupUi(this);
}

registerform::~registerform()
{
    delete ui;
}
