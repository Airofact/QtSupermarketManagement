#include "login.h"
#include "ui_login.h"
#include<QDir>
#include"CargoType.h"
#include"Inventory.h"

#include <filesystem>
#include <QPalette>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::Login)
{
    std::string folderPath = "Data";
    std::filesystem::create_directory(folderPath);


    ui->setupUi(this);
    // 初始化定时器
    timer = new QTimer(this);
    timer->setSingleShot(true);

    //从登陆界面开始
    ui->stackedWidget->setCurrentWidget(ui->loginpage);
    // 连接文本变化信号到槽
    connect(ui->passwordlineEdit, &QLineEdit::textEdited, this, &Login::onTextEdited);
    connect(timer, &QTimer::timeout, this, &Login::hideText);

    //密码隐藏
    ui->assign_password_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_password_edit->setEchoMode(QLineEdit::Password);


    //鼠标悬停在头像上显示信息
    ui->touxiang->setToolTip("双击头像进行更改");


    //登陆界面的图片
    pixl=QPixmap(":/pics/left_eye_open.png");
    ui->loginleft->setPixmap(pixl);

    pixr=QPixmap(":/pics/right_eye_open.png");
    ui->loginright->setPixmap(pixr);

    pixl1=QPixmap(":/pics/left_eye_close.png");
    pixr2=QPixmap(":/pics/right_eye_close.png");

    members.emplace_back(new Member("1","1","798370740@qq.com",15525125026LL,".\\pics\\ph3.png"));


    //双击图片进行更改
    ui->touxiang->installEventFilter(this);



    good<<"商品名称"<<"商品类型"<< "商品价格"<<"商品数量";
    ui->goodtable->setColumnCount(good.count());
    ui->goodtable->setHorizontalHeaderLabels(good);
    ui->goodtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tradeHead<<"顾客名称"<<"购入商品"<<"商品数量"<<"商品类型";
    ui->tradetable->setColumnCount(tradeHead.count());
    ui->tradetable->setHorizontalHeaderLabels(tradeHead);
    ui->tradetable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->tableEditingTradeGoods->setColumnCount(good.count());
    ui->tableEditingTradeGoods->setHorizontalHeaderLabels(good);
    ui->tableEditingTradeGoods->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_pDisplayingInventory=new Inventory;
    trade=new Trade(m_pDisplayingInventory);
}

Login::~Login()
{

    delete ui;
}

QPixmap Login::Rounded(QPixmap &pix)
{
    QPixmap roundedPixmap(pix.size());
    roundedPixmap.fill(Qt::transparent); // 填充透明背景

    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::white); // 设置背景颜色
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(0, 0, pix.width(), pix.height()); // 绘制圆形

    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, pix); // 绘制图片
    painter.end();
    return roundedPixmap;
}

void Login::keyPressEvent(QKeyEvent *event)
{
    // 检查是否按下回车键
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_loginpushButton_released(); // 调用相同的槽函数
    }
}


bool Login::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui->touxiang && event->type() == QEvent::MouseButtonDblClick) {
        QString fileName = QFileDialog::getOpenFileName(this, "选择头像", "", "Images (*.png *.jpg *.jpeg *.bmp)");
        if (!fileName.isEmpty()) {
            QPixmap pixmap(fileName);
            ui->touxiang->setPixmap(Rounded(pixmap).scaled(ui->touxiang->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
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

    ui->name_1 ->setText(QString::fromStdString((*IT)->getuser()));
    ui->email->setText(QString::fromStdString((*IT)->getemail()));
    ui->phone->setText(QString::number((*IT)->getphone()));


    pix=QPixmap(QString::fromStdString((*IT)->getimage()));
    //头像设置为圆形
    ui->touxiang->setPixmap(Rounded(pix));
    ui->touxiang->setFixedSize(100, 100);



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
    if (dialog.exec()==QDialog::Accepted){
        if(dialog.getText4().toStdString()==(*IT)->getpassword())//原密码输入正确
        {
            //更新信息
            (*IT)->setemail(dialog.getText2().toStdString());
            (*IT)->setphone(dialog.getText1().toLongLong());
            (*IT)->setuser(dialog.getText3().toStdString());
            (*IT)->setpassword(dialog.getText5().toStdString());
            //个人资料界面更新
            ui->name_1 ->setText(QString::fromStdString((*IT)->getuser()));
            ui->email->setText(QString::fromStdString((*IT)->getemail()));
            ui->phone->setText(QString::number((*IT)->getphone()));
            QMessageBox::information(this,"xx","修改成功");
        }
        else if(dialog.getText4().isEmpty())//原密码输入为空，密码不修改
        {
            //更新信息
            (*IT)->setemail(dialog.getText2().toStdString());
            (*IT)->setphone(dialog.getText1().toLongLong());
            (*IT)->setuser(dialog.getText3().toStdString());
            //个人资料界面更新
            ui->name_1 ->setText(QString::fromStdString((*IT)->getuser()));
            ui->email->setText(QString::fromStdString((*IT)->getemail()));
            ui->phone->setText(QString::number((*IT)->getphone()));
            QMessageBox::information(this,"xx","修改成功");
        }
        else if(!dialog.getText4().isEmpty()&&dialog.getText4().toStdString()!=(*IT)->getpassword())//原密码输入错误
        {
            QMessageBox::warning(this,"warn","原密码输入错误，请重新输入");
        }
    }

}

void Login::updateGoodsTable(){
    ui->goodtable->clearContents();
    ui->goodtable->setRowCount(0);
    QHash<CargoType, int>::const_iterator i;
    for(i=m_pDisplayingInventory->m_pInventory->begin();i!=m_pDisplayingInventory->m_pInventory->end();++i)
    {
        ui->goodtable->insertRow(ui->goodtable->rowCount());
        QTableWidgetItem *nameItem = new QTableWidgetItem(i.key().getName());
        ui->goodtable->setItem(ui->goodtable->rowCount()-1, 0, nameItem);
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(i.key().getPrice(),'f',2));
        ui->goodtable->setItem(ui->goodtable->rowCount()-1, 2, priceItem);
        QTableWidgetItem *typeItem = new QTableWidgetItem(i.key().getType());
        ui->goodtable->setItem(ui->goodtable->rowCount()-1, 1, typeItem);
        QTableWidgetItem *amountItem = new QTableWidgetItem(QString::number(i.value()));
        ui->goodtable->setItem(ui->goodtable->rowCount()-1, 3, amountItem);
    }
    QStringList goodsList;
    for(i=m_pDisplayingInventory->m_pInventory->begin();i!=m_pDisplayingInventory->m_pInventory->end();++i)
    {
        goodsList.append(i.key().getName());
    }
    m_pCompleter = new QCompleter(goodsList);
    ui->lineEditName->setCompleter(m_pCompleter);
    ui->findedit->setCompleter(m_pCompleter);
    ui->lineEditSearch->setCompleter(m_pCompleter);
}

void Login::on_import_2_clicked()
{
    ui->goodtable->clearContents();
    ui->goodtable->setRowCount(0);
    QString file_name= QFileDialog::getOpenFileName(this, "Load JSON", "", "JSON Files (*.json)");
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"","导入失败，请确认文件是否有效");
        return;
    }
    QByteArray json = file.readAll();
    delete m_pDisplayingInventory;
    m_pDisplayingInventory = new Inventory(json);
    trade->setLinkedInventory(m_pDisplayingInventory);
    updateGoodsTable();
    QMessageBox::information(this,"","成功导入");

}


void Login::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->addgoodpage);
}


void Login::on_pushButton_2_clicked()
{
    QMessageBox msg;
    CargoType a(ui->name->text(),(ui->price->text()).toDouble(),ui->type->text());
    m_pDisplayingInventory->addGoods(a,(ui->amount->text()).toInt());
    updateGoodsTable();
    msg.setText("添加成功");
    msg.exec();

}


void Login::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->goodspage);
}


void Login::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->tradepage);
}


void Login::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->addtradepage);
    ui->lineEditAmount->clear();
    ui->lineEditCustomer->clear();
    ui->lineEditName->clear();

    ui->tableEditingTradeGoods->clearContents();
    ui->tableEditingTradeGoods->setRowCount(0);
    QHash<CargoType, int>::const_iterator i;
    for(i=m_pDisplayingInventory->m_pInventory->begin();i!=m_pDisplayingInventory->m_pInventory->end();++i)
    {
        ui->tableEditingTradeGoods->insertRow(ui->tableEditingTradeGoods->rowCount());
        QTableWidgetItem *nameItem = new QTableWidgetItem(i.key().getName());
        ui->tableEditingTradeGoods->setItem(ui->tableEditingTradeGoods->rowCount()-1, 0, nameItem);
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(i.key().getPrice(),'f',2));
        ui->tableEditingTradeGoods->setItem(ui->tableEditingTradeGoods->rowCount()-1, 2, priceItem);
        QTableWidgetItem *typeItem = new QTableWidgetItem(i.key().getType());
        ui->tableEditingTradeGoods->setItem(ui->tableEditingTradeGoods->rowCount()-1, 1, typeItem);
        QTableWidgetItem *amountItem = new QTableWidgetItem(QString::number(i.value()));
        ui->tableEditingTradeGoods->setItem(ui->tableEditingTradeGoods->rowCount()-1, 3, amountItem);
    }

}


void Login::on_export_2_clicked()
{
    QByteArray data;
    QString path=QFileDialog::getSaveFileName(this, "Save JSON", "", "JSON Files (*.json)");
    if(path.isEmpty())
    {
        QMessageBox::warning(this,"","导出失败");
        return;
    }
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    m_pDisplayingInventory->serialize(data);
    file.write(data);
    file.close();
    QMessageBox::information(this,"","成功导出");
    // ToDo: MessageBox 成功导出
}


void Login::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->goodspage);
}


void Login::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->editpage);
}


void Login::on_pushButton_7_clicked()
{
    QString name = ui->editgood->text();
    QMessageBox msg;
    if( m_pDisplayingInventory->getCargoType(name) == nullptr)
    {
        msg.setText("无法找到该商品");
        msg.exec();

        return;
    }
    double price =!(ui->editprice->text()).toDouble() ? m_pDisplayingInventory->getCargoType(name)->getPrice() : (ui->editprice->text()).toDouble();
    int amount = !(ui->editamount->text()).toInt() ? m_pDisplayingInventory->getAmount(name) : (ui->editamount->text()).toDouble();
    m_pDisplayingInventory->editGoods(name, price, amount);
    updateGoodsTable();
    msg.setText("修改成功");
    msg.exec();

}


void Login::on_pushButton_10_clicked()
{
    QMessageBox msg;
    QString name = ui->editgood->text();
    if( m_pDisplayingInventory->getCargoType(name) == nullptr)
    {
        msg.setText("无法找到该商品");
        msg.exec();

        return;
    }
    m_pDisplayingInventory->removeGoods(name,(ui->editamount->text()).toInt());
    updateGoodsTable();
    msg.setText("删除成功");
    msg.exec();

}



void Login::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->goodspage);
}


void Login::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->findpage);
}


void Login::on_pushButton_12_clicked()
{
    CargoType *get;
    QMessageBox msg;
    get=m_pDisplayingInventory->getCargoType(ui->findedit->text());
    QString message=QString("该商品的类型为：%1\n该商品的价格为：%2\n该商品的数量为：%3").arg(get->getType()).arg(get->getPrice()).arg(m_pDisplayingInventory->getAmount(ui->findedit->text()));
    msg.setText(message);
    msg.exec();
}




void Login::on_radioButton_2_toggled(bool checked)
{
    if (ui->radioButton_2->isChecked()) {
        ui->assign_password_edit->setEchoMode(QLineEdit::Normal); // 显示密码
        ui->confirm_password_edit->setEchoMode(QLineEdit::Normal);

    } else {
        ui->assign_password_edit->setEchoMode(QLineEdit::Password); // 隐藏密码
        ui->confirm_password_edit->setEchoMode(QLineEdit::Password);

    }
}

void Login::onTextEdited()
{
    // 每次编辑文本时，设置显示文本几百毫秒
    ui->passwordlineEdit->setEchoMode(QLineEdit::Normal);
    timer->start(500);  // 500毫秒后隐藏文本
}

void Login::hideText()
{
    // 隐藏文本，将echoMode设置为Password
    ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
}


Inventory *tempInven = nullptr;

void helperUpdateTempInvenTable(QTableWidget* tableWidget){
    if(!tempInven)return;
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    QHash<CargoType, int>::const_iterator i;
    for(i=tempInven->getInventory()->begin();i!=tempInven->getInventory()->end();++i)
    {
        tableWidget->insertRow(tableWidget->rowCount());
        QTableWidgetItem *nameItem = new QTableWidgetItem(i.key().getName());
        tableWidget->setItem(tableWidget->rowCount()-1, 0, nameItem);
        QTableWidgetItem *amountItem = new QTableWidgetItem(QString::number(i.value()));
        tableWidget->setItem(tableWidget->rowCount()-1, 1, amountItem);
    }

}
void Login::on_PBAddGood_clicked()
{
    QString name = ui->lineEditCustomer->text();
    QString goodsName = ui->lineEditName->text();
    int amount = ui->lineEditAmount->text().toInt();

    if(!m_pDisplayingInventory->contains(goodsName))
    {
        QMessageBox::warning(this,"","无法找到该商品");
        return;
    }
    if(amount>m_pDisplayingInventory->getAmount(goodsName)){
        QMessageBox::warning(this,"","库存不足");
        return;
    }

    CargoType* goods = m_pDisplayingInventory->getCargoType(goodsName);

    if(!trade->getTradeListItem(name)){
        Inventory *newInven = new Inventory;

        if(goods){
            newInven->addGoods(*goods,amount);
            trade->addTradeListItem(name,*newInven);
            // qDebug()<<newInven->getAmount(goodsName);
        }
    }
    else if (goods){
        trade->getTradeListItem(name)->second.addGoods(*goods,amount);
    }
    QMessageBox::information(this,"","添加成功");
}



void Login::on_PBCancel_clicked()
{
    delete tempInven;
    tempInven = nullptr;
    ui->stackedWidget->setCurrentWidget(ui->tradepage);
}

void Login::updateTradeTable(){
    ui->tradetable->clearContents();
    ui->tradetable->setRowCount(0);
    auto i = trade->getTradeList()->begin();
    for(;i!=trade->getTradeList()->end();++i)
    {
        for(auto j = i->second.getInventory()->begin();j!=i->second.getInventory()->end();j++)
        {
            ui->tradetable->insertRow(ui->tradetable->rowCount());
            QTableWidgetItem *customerItem = new QTableWidgetItem(i->first);
            ui->tradetable->setItem(ui->tradetable->rowCount()-1, 0, customerItem);
            QTableWidgetItem *nameItem = new QTableWidgetItem(j.key().getName());
            ui->tradetable->setItem(ui->tradetable->rowCount()-1, 1, nameItem);
            QTableWidgetItem *amountItem = new QTableWidgetItem(QString::number(j.value()));
            ui->tradetable->setItem(ui->tradetable->rowCount()-1, 2, amountItem);
            QTableWidgetItem *typeItem = new QTableWidgetItem(j.key().getType());
            ui->tradetable->setItem(ui->tradetable->rowCount()-1, 3, typeItem);
        }
    }
}

void Login::on_PBConfirm_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->tradepage);
    updateTradeTable();
}


void Login::on_tradetable_itemDoubleClicked(QTableWidgetItem *item)
{

}


void Login::on_lineEditSearch_textChanged(const QString &arg1)
{

    QPalette palette = ui->lineEditSearch->palette();
    palette.setColor(QPalette::Text, Qt::gray);
    ui->lineEditSearch->setPalette(palette);

    updateTradeTable();
    if(arg1.isEmpty()){
        return;
    }


    auto getItem = trade->getTradeListItem(arg1);
    if(!getItem)return;
    ui->tradetable->clearContents();
    ui->tradetable->setRowCount(0);

    palette.setColor(QPalette::Text, Qt::black);
    ui->lineEditSearch->setPalette(palette);

    for(auto j = getItem->second.getInventory()->begin();j!=getItem->second.getInventory()->end();j++)
    {
        ui->tradetable->insertRow(ui->tradetable->rowCount());
        QTableWidgetItem *customerItem = new QTableWidgetItem(getItem->first);
        ui->tradetable->setItem(ui->tradetable->rowCount()-1, 0, customerItem);
        QTableWidgetItem *nameItem = new QTableWidgetItem(j.key().getName());
        ui->tradetable->setItem(ui->tradetable->rowCount()-1, 1, nameItem);
        QTableWidgetItem *amountItem = new QTableWidgetItem(QString::number(j.value()));
        ui->tradetable->setItem(ui->tradetable->rowCount()-1, 2, amountItem);
        QTableWidgetItem *typeItem = new QTableWidgetItem(j.key().getType());
        ui->tradetable->setItem(ui->tradetable->rowCount()-1, 3, typeItem);
    }
}

void Login::on_PBUpdate_clicked()
{
    QMessageBox msg;
    updateGoodsTable();
    msg.setText("更新成功");
    msg.exec();

}

void Login::on_PBExport_clicked()
{
    QByteArray data;
    QString path=QFileDialog::getSaveFileName(this, "Save JSON", "", "JSON Files (*.json)");
    if(path.isEmpty())
    {
        QMessageBox::warning(this,"","导出失败");
        return;
    }
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    trade->serialize(data);
    file.write(data);
    file.close();
    QMessageBox::information(this,"","导出成功");

}


void Login::on_PBImport_clicked()
{

    QString path = QFileDialog::getOpenFileName(this, "Load JSON", "", "JSON Files (*.json)");
    delete trade;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"","导入失败，请确认文件是否有效");
        return;
    }
    QByteArray json = file.readAll();
    bool ok;
    trade = new Trade(json,&ok);
        trade->setLinkedInventory(m_pDisplayingInventory);
    if(!ok){
        QMessageBox::warning(this,"","导入失败，当前库存为空或无效");
        return;
    }
    updateTradeTable();
    QMessageBox::information(this,"","导入成功");

}



void Login::on_tradetable_cellClicked(int row, int column)
{
    Q_UNUSED(row)
    Q_UNUSED(column)
}


void Login::on_tradetable_customContextMenuRequested(const QPoint &pos)
{
    QTableWidgetItem* item = ui->tradetable->itemAt(pos);
    int row = item->row();
    QMenu *menu = new QMenu(this);
    QAction *deleteAction = new QAction("删除", this);
    menu->addAction(deleteAction);
    connect(deleteAction, &QAction::triggered, this, [=](){
        QTableWidgetItem* customerItem = ui->tradetable->item(row, 0);
        QTableWidgetItem* goodsItem = ui->tradetable->item(row, 1);
        trade->getTradeListItem(customerItem->text())->second.removeGoods(goodsItem->text());
        updateTradeTable();
    });
    menu->exec(QCursor::pos());
}

