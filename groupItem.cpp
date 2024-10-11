#include "groupItem.h"
#include "ui_groupItem.h"

groupItem::groupItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::groupItem)
{
    ui->setupUi(this);

    //pushButton's style
    ui->pushButton->setFixedSize(25,25);
    ui->pushButton->setStyleSheet("background-color:red");
    ui->pushButton->setCursor(Qt::PointingHandCursor);

    // label's style
    ui->groupName_label->setCursor(Qt::PointingHandCursor);
}

groupItem::~groupItem()
{
    delete ui;
}

void groupItem::setName(QString _name)
{
    ui->groupName_label->setText(_name);
}

void groupItem::on_pushButton_clicked()
{
    //ask user to be sure of operation
    int ret = QMessageBox::warning(this, "" , "Are you you want to remove this group ?" , QMessageBox::No , QMessageBox::Yes) ;
    if(ret == QMessageBox::Yes) {
        //delete the item from dataBase
        QString groupName = ui->groupName_label->text() ;
        QSqlQuery query ;
        query.prepare("DELETE FROM groups WHERE name = :groupName ") ;
        query.bindValue(":groupName" , groupName);
        if(query.exec()) {
            QMessageBox::information(this, "" , QString("%1 group deleted successfully").arg(groupName)) ;
            emit refreshGroupListWidget() ;
        } else {
            QMessageBox::critical(this , "error" , query.lastError().text()) ;
        }
    } else {
        return ;
    }

}

