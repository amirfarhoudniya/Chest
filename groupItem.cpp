#include "groupItem.h"
#include "ui_groupItem.h"
#include <QPushButton>

groupItem::groupItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::groupItem)
{
    ui->setupUi(this);

    //remove pushButton's style
    ui->remove_pushButton->setFixedSize(25,25);
    ui->remove_pushButton->setStyleSheet("background-color:red");
    ui->remove_pushButton->setCursor(Qt::PointingHandCursor);

    //groupName pushButton's style
    ui->groupName_pushButton->setCursor(Qt::PointingHandCursor);
    ui->groupName_pushButton->setStyleSheet("QPushButton:hover:!pressed{background-color: lightblue; color:black ;}");
    ui->groupName_pushButton->setFixedSize(150, 25);
}

groupItem::~groupItem()
{
    delete ui;
}

void groupItem::setName(QString _name)
{
    ui->groupName_pushButton->setText(_name);
}

void groupItem::on_remove_pushButton_clicked()
{
    //ask user to be sure of operation
    int ret = QMessageBox::warning(this, "" , "Are you you want to remove this group ?" , QMessageBox::No , QMessageBox::Yes) ;
    if(ret == QMessageBox::Yes) {
        //delete the item from dataBase
        QString groupName = ui->groupName_pushButton->text() ;
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


void groupItem::on_groupName_pushButton_clicked()
{
    emit refreshContributorOfthisGroup(ui->groupName_pushButton->text());
}

