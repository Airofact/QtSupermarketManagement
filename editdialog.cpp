#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditDialog)
{
    ui->setupUi(this);
}

EditDialog::~EditDialog()
{
    delete ui;
}


QString EditDialog::getText1() const {
    return text1;
}

void EditDialog::setText1(const QString &text) {
    ui->lineEdit->setText(text);
}

QString EditDialog::getText2() const {
    return text2;
}

void EditDialog::setText2(const QString &text) {
    ui->lineEdit_2->setText(text);
}


QString EditDialog::getText3() const {
    return text3;
}

void EditDialog::setText3(const QString &text) {
    ui->lineEdit_3->setText(text);
}


void EditDialog::on_confirm_released() {
    text1 = ui->lineEdit->text();
    text2 = ui->lineEdit_2->text();
    text3 = ui->lineEdit_3->text();
    accept();
}


\

