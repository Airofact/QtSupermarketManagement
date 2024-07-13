#include "login.h"
#include "ui_login.h"
#include<QDir>


Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    //密码隐藏
    ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
    ui->stackedWidget->setCurrentWidget(ui->loginpage);

    pixl.load("F:\\qt homework\\login\\image\\睁眼登录左.png");
    scaledPixmap=pixl.scaled(174,162,Qt::KeepAspectRatio);
    ui->loginleft->setPixmap(scaledPixmap);
    ui->loginleft->resize(scaledPixmap.size());


    pixr.load("/image/睁眼登录右.png");
    ui->loginleft->resize(pixr.size());
    ui->loginright->setPixmap(pixr);


    pixl1=QPixmap(".\\image\\闭眼登录左.png");
    pixr2=QPixmap(".\\image\\闭眼登录右.png");

    good.setHorizontalHeaderLabels({"商品名称", "商品类型", "商品价格","商品数量"});
    ui->goodtable->setModel(&good);
    ui->goodtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    trade.setHorizontalHeaderLabels({"商品名称", "数量浮动", "原因"});
    ui->tradetable->setModel(&trade);
    ui->tradetable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //预设信息
    members.emplace_back(new Member("乔鹏博","yun211314","798370740@qq.com",15525125026LL,".\\image\\1.png"));

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
            (*IT)->getimage()=fileName.toStdString();
        }
        return true; // 事件已处理
    }
    return QMainWindow::eventFilter(obj, event);
}


void Login::on_loginpushButton_released()
{
    for(auto it = members.begin(); it != members.end(); ++it)
    {
        if(ui->userlineEdit->text().toStdString() == (*it)->getuser() &&
            ui->passwordlineEdit->text().toStdString() == (*it)->getpassword())
        {
            IT=it;
            //切换到主菜单页面
            ui->stackedWidget->setCurrentWidget(ui->menupage);

        }
        else
        {
            QMessageBox::warning(this,"warn","用户名或者密码错误");
        }
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
}

//保存新的信息到容器中
void Login::on_confirm_released()
{

}


void Login::on_create_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->createpage);
}

