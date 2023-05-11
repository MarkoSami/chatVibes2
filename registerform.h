#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QDialog>

namespace Ui {
class registerform;
}

class registerform : public QDialog
{
    Q_OBJECT

public:
    explicit registerform(QWidget *parent = nullptr);
    ~registerform();

private:
    Ui::registerform *ui;
};

#endif // RIGISTERFORM_H
