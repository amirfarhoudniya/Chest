#include "addGroupItem.h"
#include "ui_addGroupItem.h"

addGroupItem::addGroupItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addGroupItem)
{
    ui->setupUi(this);

    //pushButton's style
    ui->save_pushButton->setFixedSize(70 , 35);
    ui->save_pushButton->setStyleSheet("QPushButton {"
                                        "    background-color: lightgreen;"
                                        "    color:black ;"
                                        "    border-radius: 5px ;"
                                        "}"
                                        "QPushButton:hover:!pressed {"
                                        "    background-color: green;"
                                        "    color: black;"
                                        "    border-radius: 5px ;"
                                        "}");
    ui->save_pushButton->setCursor(Qt::PointingHandCursor);
}

addGroupItem::~addGroupItem()
{
    delete ui;
}

void addGroupItem::on_save_pushButton_clicked()
{
    //check fields to not be empty
    if(ui->groupsName_lineEdit->text().isEmpty()) {
        ui->shareFactor_lineEdit->setStyleSheet("color:red ;");
        ui->shareFactor_lineEdit->setPlaceholderText("this field can't be empty");
        return ;
    } else if (ui->shareFactor_lineEdit->text().isEmpty()) {
        ui->groupsName_lineEdit->setStyleSheet("color:red");
        ui->shareFactor_lineEdit->setStyleSheet("this field can't be empty");
        return ;
    }

    //insert group's data to dataBase
    QSqlQuery query ;
    query.prepare("INSERT INTO groups (name , shareFactor) VALUES (? , ? )") ;
    query.addBindValue(ui->groupsName_lineEdit->text());
    query.addBindValue(ui->shareFactor_lineEdit->text());
    query.exec() ;

    emit groupNameAdded();
    this->close() ;
}


void addGroupItem::on_shareFactor_lineEdit_textChanged()
{
    ui->groupsName_lineEdit->setStyleSheet("");
    ui->shareFactor_lineEdit->setStyleSheet("");
}

