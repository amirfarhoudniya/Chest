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

    //
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
    name = _name ;
    turn = _turn ;
    payment = _payment ;
    ui->contributor_pushButton->setText(name + " --> " + QString::number(payment) + " $");
    ui->turn_label->setText(QString::number(_turn));
}

void contributorItem::on_contributor_pushButton_clicked()
{
    contributorItemExtended *item = new contributorItemExtended() ;
    connect(item , &contributorItemExtended::changesApplied , this , &contributorItem::refreshContributorReq) ;
    item->setInfo(name ,turn , payment );
    item->show();
}

void contributorItem::refreshContributorReq()
{
    emit changesApplied(this->property("groupName").toString());
}

