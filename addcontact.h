#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include <QDialog>

namespace Ui {
class AddContact;
}

class AddContact : public QDialog
{
    Q_OBJECT

public:
    explicit AddContact(QWidget *parent = nullptr);
    ~AddContact();
    void setIDAuto(QString id);


signals: void renderConversation();

private slots:

    void on_pushButton_10_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::AddContact *ui;

    QString img_path; // Member variable to store the selected image path


};

#endif // ADDCONTACT_H
