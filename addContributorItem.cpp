#include "addContributorItem.h"
#include "ui_addContributorItem.h"

addContributorItem::addContributorItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addContributorItem)
{
    ui->setupUi(this);

    //pushButton's style
    ui->add_pushButton->setFixedSize(70 , 35);
    ui->add_pushButton->setStyleSheet("QPushButton {"
                                      "    background-color: lightgreen;"
                                      "    color:black "
                                      "}"
                                      "QPushButton:hover:!pressed {"
                                      "    background-color: green;"
                                      "    color: black;"
                                      "}");
    ui->add_pushButton->setCursor(Qt::PointingHandCursor);

    //set payment label to get just numbers
    ui->payment_lineEdit->setValidator(new QDoubleValidator(0, 100, 2, this));

}

addContributorItem::~addContributorItem()
{
    delete ui;
}

void addContributorItem::setGroupName(QString _groupName)
{
    //set group's name
    ui->group_label->setText("Selected Group : ");
    ui->group_label2->setText(_groupName);
    this->setProperty("groupName" , _groupName) ;
}

void addContributorItem::on_add_pushButton_clicked()
{
    //add group's name to dataBase
    QSqlQuery query ;
    query.prepare("INSERT INTO contributors (groupsName , fullName ,"
                  " turn , paid ) VALUES (? , ? , ? , ? )") ;

    query.addBindValue(this->property("groupName").toString());
    query.addBindValue(ui->name_lineEdit->text());
    query.addBindValue(0);
    query.addBindValue(ui->payment_lineEdit->text().toInt());
    query.exec() ;

    emit contributorAdded(this->property("groupName").toString());
    this->close() ;
}
