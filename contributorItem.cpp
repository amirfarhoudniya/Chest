#include "contributorItem.h"
#include "ui_contributorItem.h"

contributorItem::contributorItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::contributorItem)
{
    ui->setupUi(this);

    //remove pushButton's style
    ui->remove_pushButton->setFixedSize(25,25);
    ui->remove_pushButton->setStyleSheet("background-color:red");
    ui->remove_pushButton->setCursor(Qt::PointingHandCursor);

    //contributor pushButton's style
    ui->contributor_pushButton->setCursor(Qt::PointingHandCursor);

    //turn label's style
    ui->turn_label->setStyleSheet("background-color:lightgreen ; color:black ; ");
    ui->turn_label->setFrameShape(QFrame::Panel);
    ui->turn_label->setFrameShadow(QFrame::Sunken);
    ui->turn_label->setLineWidth(3);

}

contributorItem::~contributorItem()
{
    delete ui;
}

void contributorItem::setInfo(QString _name, double _payment , int _turn)
{
    //set data to ui elements
    name = _name ;
    turn = _turn ;
    payment = _payment ;
    ui->contributor_pushButton->setText(name + " --> " + QString::number(payment) + " $");
    ui->turn_label->setText(QString::number(_turn));

    //if draw is done in group's contributors, contributors can not be removed
    if(_turn != 0) {
        ui->remove_pushButton->setEnabled(0);
        ui->remove_pushButton->setStyleSheet("background-color: gray ;");
    }
}

void contributorItem::on_contributor_pushButton_clicked()
{
    //open contributor's page
    contributorItemExtended *item = new contributorItemExtended() ;
    connect(item , &contributorItemExtended::changesApplied , this , &contributorItem::refreshContributorReq) ;
    item->setInfo(name , this->property("groupName").toString() , turn , payment );
    item->show();
}

void contributorItem::refreshContributorReq()
{
    emit changesApplied(this->property("groupName").toString());
}


void contributorItem::on_remove_pushButton_clicked()
{
    //remove contributor from dataBase
    QSqlQuery query ;
    query.prepare("DELETE FROM contributors WHERE fullName = :fullName AND groupsName = :groupsName") ;
    query.bindValue(":fullName" , this->property("fullName").toString());
    query.bindValue(":groupsName" , this->property("groupName").toString());

    if(query.exec()) {
        QMessageBox::information(this , "" , "done" );
        refreshContributorReq();
    } else {
        QMessageBox::critical(this , "" , "dataBase Error !") ;
    }

}

