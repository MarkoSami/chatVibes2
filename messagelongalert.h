#ifndef MESSAGELONGALERT_H
#define MESSAGELONGALERT_H

#include <QDialog>

namespace Ui {
class messageLongAlert;
}

class messageLongAlert : public QDialog
{
    Q_OBJECT

public:
    explicit messageLongAlert(QWidget *parent = nullptr);
    ~messageLongAlert();

private slots:
    void on_pushButton_clicked();

private:
    Ui::messageLongAlert *ui;
};

#endif // MESSAGELONGALERT_H
