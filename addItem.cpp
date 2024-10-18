#include "addItem.h"
#include "ui_addItem.h"

addItem::addItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addItem)
{
    ui->setupUi(this);

    //pushButton's style
    ui->pushButton->setStyleSheet(
        "QPushButton {"
        "    background-color: green;"
        "}"
        "QPushButton:hover:!pressed {"
        "    background-color: lightgreen;"
        "    color: black;"
        "}"
        );
    ui->pushButton->setCursor(Qt::PointingHandCursor);
}

addItem::~addItem()
{
    delete ui;
}

void addItem::on_pushButton_clicked()
{
    //check the property to call the related page
    if(this->property("property") == "groupName") {
        emit addGroupPageSignal();
    } else {
        emit  addContributorPageSignal();
    }

}



