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
    ui->remove_pushButton->setStyleSheet("background-color:red ; ");
    ui->remove_pushButton->setCursor(Qt::PointingHandCursor);

    //groupName pushButton's style
    ui->groupName_pushButton->setCursor(Qt::PointingHandCursor);
    ui->groupName_pushButton->setStyleSheet("QPushButton:hover:!pressed{background-color: lightblue; color:black ;}");
    ui->groupName_pushButton->setFixedSize(150, 60);
}

groupItem::~groupItem()
{
    delete ui;
}

void groupItem::setName(QString _name , int _shareFactor)
{
    //set data to ui elements
    ui->groupName_pushButton->setText(_name +"\n"+ QString::number(_shareFactor));
}

void groupItem::on_remove_pushButton_clicked()
{
    //ask user to be sure of operation
    int ret = QMessageBox::warning(this, "" , "Are you you want to remove this group ?" , QMessageBox::No , QMessageBox::Yes) ;
    if(ret == QMessageBox::Yes) {
        //delete the item from dataBase
        QString groupName = this->property("groupName").toString();
        QSqlQuery query ;
        QSqlQuery query2 ;
        query.prepare("DELETE FROM groups WHERE name = :groupName ") ;
        query.bindValue(":groupName" , groupName);
        query2.prepare("DELETE FROM contributors WHERE groupsName = :groupsName ") ;
        query2.bindValue(":groupsName" , groupName);
        if(query.exec() && query2.exec()) {
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
    emit refreshContributorOfthisGroup(this->property("groupName").toString());
}

