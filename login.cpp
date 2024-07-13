#include "login.h"
#include "ui_login.h"
#include<QDir>


Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    //从登陆界面开始
    ui->stackedWidget->setCurrentWidget(ui->loginpage);

    //密码隐藏
    ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
    ui->assign_password_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_password_edit->setEchoMode(QLineEdit::Password);


    //登陆界面的图片
    pixl=QPixmap(".\\pics\\睁眼登录左.png");
    ui->loginleft->setPixmap(pixl);

    pixr=QPixmap(".\\pics\\睁眼登录右.png");
    ui->loginright->setPixmap(pixr);

    pixl1=QPixmap(".\\pics\\闭眼登录左.png");
    pixr2=QPixmap(".\\pics\\闭眼登录右.png");


    //商品
    //good.setHorizontalHeaderLabels({"商品名称", "商品类型", "商品价格","商品数量"});
    // ui->goodtable->setModel(&good);
    // ui->goodtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // //trade.setHorizontalHeaderLabels({"商品名称", "数量浮动", "原因"});
    // ui->tradetable->setModel(&trade);
    // ui->tradetable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    //预设信息
    members.emplace_back(new Member("乔鹏博","yun211314","798370740@qq.com",15525125026LL,".\\pics\\ph3.png"));

    //双击图片进行更改
    ui->touxiang->installEventFilter(this);


}

Login::~Login()
{

    delete ui;
}


bool Login::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui->touxiang && event->type() == QEvent::MouseButtonDblClick) {
        QString fileName = QFileDialog::getOpenFileName(this, "选择头像", "", "Images (*.png *.jpg *.jpeg *.bmp)");
        if (!fileName.isEmpty()) {
            QPixmap pixmap(fileName);
            ui->touxiang->setPixmap(pixmap.scaled(ui->touxiang->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            // 更新头像路径到成员信息
            (*IT)->setimage(fileName.toStdString());
        }
        return true; // 事件已处理
    }
    return QMainWindow::eventFilter(obj, event);
}


void Login::on_loginpushButton_released()
{
    //创建指向容器尾部的迭代器，如果容器中有对应的用户，更新该迭代器
    auto it1=members.end();

    for(auto it = members.begin(); it != members.end(); ++it)
    {
        if(ui->userlineEdit->text().toStdString() == (*it)->getuser() &&
            ui->passwordlineEdit->text().toStdString() == (*it)->getpassword())
        {
            IT=it;
            it1=it;
            //切换到主菜单页面
            ui->stackedWidget->setCurrentWidget(ui->menupage);

        }
    }
    //it1未被更新，容器中无对应用户
    if(it1==members.end())
    {
        QMessageBox::warning(this,"warning","杂鱼~信息错误");
    }
}


void Login::on_messagepushButton_released()
{
    //切换到个人信息
    ui->stackedWidget->setCurrentWidget(ui->messagepage);

    ui->name ->setText(QString::fromStdString((*IT)->getuser()));
    ui->email->setText(QString::fromStdString((*IT)->getemail()));
    ui->phone->setText(QString::number((*IT)->getphone()));
    pix=QPixmap(QString::fromStdString((*IT)->getimage()));
    ui->touxiang->setPixmap(pix);



}


void Login::on_goodspushButton_released()
{
    //切换到库存信息
    ui->stackedWidget->setCurrentWidget(ui->goodspage);
}


void Login::on_tradepushButton_released()
{
    //切换到交易信息
    ui->stackedWidget->setCurrentWidget(ui->tradepage);
}


void Login::on_menuesc_released()
{
    ui->stackedWidget->setCurrentWidget(ui->loginpage);
    ui->userlineEdit->clear();
    ui->passwordlineEdit->clear();
    ui->loginleft->setPixmap(pixl);
    ui->loginright->setPixmap(pixr);
}


void Login::on_goodsesc_released()
{
    ui->stackedWidget->setCurrentWidget(ui->menupage);
}


void Login::on_messageesc_released()
{
    ui->stackedWidget->setCurrentWidget(ui->menupage);
}


void Login::on_tradeesc_released()
{
    ui->stackedWidget->setCurrentWidget(ui->menupage);
}



void Login::on_passwordlineEdit_textChanged(const QString &arg1)
{

    ui->loginleft->setPixmap(pixl1);
    ui->loginright->setPixmap(pixr2);
}



void Login::on_passwordlineEdit_editingFinished()
{
    ui->loginleft->setPixmap(pixl);

    ui->loginright->setPixmap(pixr);
}



void Login::on_createesc_released()
{
    ui->stackedWidget->setCurrentWidget(ui->loginpage);
    ui->userlineEdit->clear();
    ui->passwordlineEdit->clear();
    ui->loginleft->setPixmap(pixl);
    ui->loginright->setPixmap(pixr);
}

//保存新的信息到容器中
void Login::on_confirm_released()
{
    //验证是否有已存在的用户
    for(auto it = members.begin(); it != members.end(); ++it)
    {
        if(ui->user_edit->text().toStdString() == (*it)->getuser())
        {
            QMessageBox::warning(this,"warn","该用户已存在");
            return;
        }
    }

    //验证密码
    if(ui->assign_password_edit->text()==ui->confirm_password_edit->text())
    {
        //两次密码相同，录入信息
        auto m=new Member;
        m->setemail(ui->assign_email_edit->text().toStdString());
        m->setphone(ui->assign_phonenumber_edit->text().toLongLong());
        m->setuser(ui->user_edit->text().toStdString());
        m->setpassword(ui->assign_password_edit->text().toStdString());
        members.emplace_back(m);
        QMessageBox::information(this,"恭喜","注册成功");

        //返回登录界面
        ui->stackedWidget->setCurrentWidget(ui->loginpage);
        ui->userlineEdit->clear();
        ui->passwordlineEdit->clear();
        ui->loginleft->setPixmap(pixl);
        ui->loginright->setPixmap(pixr);
    }
    else
    {
        QMessageBox::warning(this,"warn","密码不一致");
    }
}


void Login::on_create_released()
{
    ui->stackedWidget->setCurrentWidget(ui->createpage);
}


void Login::on_editmessage_released()
{
    EditDialog dialog(this);
    dialog.setText1(QString::number((*IT)->getphone()));//电话
    dialog.setText2(QString::fromStdString((*IT)->getemail()));//邮箱
    dialog.setText3(QString::fromStdString((*IT)->getuser()));//用户名
    if(dialog.exec()==QDialog::Accepted)
    {
        //更新信息
        (*IT)->setemail(dialog.getText2().toStdString());
        (*IT)->setphone(dialog.getText1().toLongLong());
        (*IT)->setuser(dialog.getText3().toStdString());
        //个人资料界面更新
        ui->name ->setText(QString::fromStdString((*IT)->getuser()));
        ui->email->setText(QString::fromStdString((*IT)->getemail()));
        ui->phone->setText(QString::number((*IT)->getphone()));
    }
}
