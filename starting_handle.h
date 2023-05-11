#ifndef STARTING_HANDLE_H
#define STARTING_HANDLE_H

#include <QDialog>
#include "loginform.h"
#include "registerfrom.h"

namespace Ui {
class Starting_Handle;
}

class Starting_Handle : public QDialog
{
    Q_OBJECT

public:
    explicit Starting_Handle(QWidget *parent = nullptr);
    ~Starting_Handle();

private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::Starting_Handle *ui;
    Registerfrom regWin ;
    loginForm logWin ;
};

#endif // STARTING_HANDLE_H
