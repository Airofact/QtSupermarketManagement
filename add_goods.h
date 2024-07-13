#ifndef ADD_GOODS_H
#define ADD_GOODS_H

#include <QWidget>
#include<Inventory.h>
namespace Ui {
class add_goods;
}

class add_goods : public QWidget
{
    Q_OBJECT
public:
    explicit add_goods(QWidget *parent = nullptr);
    ~add_goods();


private slots:
    void on_pushButton_clicked();

private:
    Ui::add_goods *ui;
};

#endif // ADD_GOODS_H
