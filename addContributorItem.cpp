#include "addContributorItem.h"
#include "ui_addContributorItem.h"

addContributorItem::addContributorItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addContributorItem)
{
    ui->setupUi(this);

    //pushButton's style
    ui->add_pushButton->setFixedSize(70 , 35);
    ui->add_pushButton->setStyleSheet("background-color:green ; border-radius: 5px ;");
    ui->add_pushButton->setCursor(Qt::PointingHandCursor);

    //set payment label to get just numbers
    ui->payment_lineEdit->setValidator(new QDoubleValidator(0, 100, 2, this));


    //set comboBox items
    QSqlQuery query ;
    QSqlRecord record ;
    query.prepare("SELECT * FROM groups") ;
    if(query.exec()) {
        while(query.next()) {
            record = query.record() ;
            ui->group_comboBox->addItem(record.value("name").toString());
        }
    }
}

addContributorItem::~addContributorItem()
{
    delete ui;
}

void addContributorItem::on_add_pushButton_clicked()
{
    //add group's name to dataBase
    QSqlQuery query ;
    query.prepare("INSERT INTO contributors (groupsName , fullName ,"
                  " turn , paid ) VALUES (? , ? , ? , ? )") ;

    query.addBindValue(ui->group_comboBox->currentText());
    query.addBindValue(ui->name_lineEdit->text());
    query.addBindValue(0);
    query.addBindValue(ui->payment_lineEdit->text().toInt());
    query.exec() ;

    emit contributorAdded(ui->group_comboBox->currentText());
    this->close() ;
}
