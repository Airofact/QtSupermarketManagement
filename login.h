#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMessageBox>
#include "member.h"
#include <vector>
#include <memory>
#include <QFileDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include<QTableWidget>
#include "editdialog.h"
#include"Inventory.h"
#include"find.h"
#include"Trade.h"
#include"QCompleter"
QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QStringList good;
    QStringList tradeHead;
    Ui::find *find_ui;

    QPixmap Rounded(QPixmap &pix);//将图片设置为圆形
    void keyPressEvent(QKeyEvent *event) override;//登录界面敲击回车执行登录操作


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

    void on_pushButton_clicked();

    void on_import_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();




    void on_export_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();


    void on_radioButton_2_toggled(bool checked);

    void onTextEdited();
    void hideText();


    void updateGoodsTable();

    void on_PBAddGood_clicked();


    void on_PBCancel_clicked();

    void on_PBConfirm_clicked();

    void updateTradeTable();

    void on_tradetable_itemDoubleClicked(QTableWidgetItem *item);

    void on_lineEditSearch_textChanged(const QString &arg1);



    void on_PBUpdate_clicked();



    void on_PBExport_clicked();

    void on_PBImport_clicked();


    void on_tradetable_cellClicked(int row, int column);

    void on_tradetable_customContextMenuRequested(const QPoint &pos);

private:
    Ui::Login *ui;
    QPixmap pixl;
    QPixmap pixr;
    QPixmap pixl1;
    QPixmap pixr2;

    QPixmap pix;//头像
    QTimer *timer;//计时器
    //自动补全
    QCompleter* m_pCompleter;

    //人员信息
    std::vector<std::unique_ptr<Member>> members;
    //用于记录所登录的用户
    std::vector<std::unique_ptr<Member>>::iterator IT;

    Inventory *m_pDisplayingInventory;
    QHash<CargoType, int>::const_iterator i;
    Trade *trade;
};
#endif // LOGIN_H
