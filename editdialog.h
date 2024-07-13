#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = nullptr);
    ~EditDialog();

    QString getText1() const;
    void setText1(const QString &text);
    QString getText2() const;
    void setText2(const QString &text);
    QString getText3() const;
    void setText3(const QString &text);

private slots:

    void on_confirm_released();

private:
    Ui::EditDialog *ui;
    QString text1;
    QString text2;
    QString text3;

};

#endif // EDITDIALOG_H
