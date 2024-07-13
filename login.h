#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMessageBox>
#include "member.h"
#include <vector>
#include <memory>
#include <QFileDialog>
#include <QMouseEvent>
#include "editdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();


private slots:
    void on_loginpushButton_released();

    void on_messagepushButton_released();

    void on_goodspushButton_released();

    void on_tradepushButton_released();

    void on_menuesc_released();

    void on_goodsesc_released();

    void on_messageesc_released();

    void on_tradeesc_released();

    void on_passwordlineEdit_textChanged(const QString &arg1);

    void on_passwordlineEdit_editingFinished();

    void on_createesc_released();

    void on_confirm_released();

    bool eventFilter(QObject *obj, QEvent *event) override;

    void on_create_released();

    void on_editmessage_released();

private:
    Ui::Login *ui;
    QPixmap pixl;
    QPixmap pixr;
    QPixmap pixl1;
    QPixmap pixr2;

    QPixmap pix;//头像
    //人员信息
    std::vector<std::unique_ptr<Member>> members;
    //用于记录所登录的用户
    std::vector<std::unique_ptr<Member>>::iterator IT;

};
#endif // LOGIN_H
