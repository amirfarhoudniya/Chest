#include "contributorItemExtended.h"
#include "ui_contributorItemExtended.h"

contributorItemExtended::contributorItemExtended(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::contributorItemExtended)
{
    ui->setupUi(this);

    //prevent growing the window
    this->setFixedSize(this->size());

    //apply pushButton's style
    ui->apply_pushButton->setStyleSheet("background-color:lightgreen ; color:black");
    ui->apply_pushButton->setCursor(Qt::PointingHandCursor);

    //turn label's style
    ui->turn_label->setStyleSheet("background-color:lightgreen ; color:black ; ");
    ui->turn_label->setFrameShape(QFrame::Panel);
    ui->turn_label->setFrameShadow(QFrame::Sunken);
    ui->turn_label->setLineWidth(3);

    //set payment label to get just numbers
    ui->payment_lineEdit->setValidator(new QDoubleValidator(0, 100, 2, this));
}

contributorItemExtended::~contributorItemExtended()
{
    delete ui;
}

void contributorItemExtended::setInfo(QString _name , QString _groupName , int _turn, double _lastPayments)
{
    ui->fullName_label->setText(_name);
    ui->groupName_label->setText("From " + _groupName);
    ui->turn_label->setText(QString::number(_turn));
    ui->lastPayment_label->setText(QString::number(_lastPayments));
}

void contributorItemExtended::on_apply_pushButton_clicked()
{
    double lastPayments = ui->lastPayment_label->text().toDouble() ;
    double newPayment = ui->payment_lineEdit->text().toDouble() ;

    double sum = lastPayments + newPayment ;

    QSqlQuery query ;
    query.prepare("UPDATE contributors SET paid = :sum WHERE fullname = :fullName") ;
    query.bindValue(":sum" , sum);
    query.bindValue(":fullName" , ui->fullName_label->text());
    if(query.exec()) {
        emit changesApplied();
        this->close() ;
    } else {
        QMessageBox::critical(this , "error" , "error" ) ;
    }

}

