#include "chooselanguage.h"
#include "ui_chooselanguage.h"

chooseLanguage::chooseLanguage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chooseLanguage)
{
    ui->setupUi(this);

    setWindowTitle("");

    //
    ui->iran_pushButton->setText("");
    ui->iran_pushButton->setIcon(QIcon(":/icons/icons/iranFlag.png"));
    ui->iran_pushButton->setIconSize(QSize(220,120));
    ui->iran_pushButton->setCursor(Qt::PointingHandCursor);

    ui->usa_pushButton->setText("");
    ui->usa_pushButton->setIcon(QIcon(":/icons/icons/usaFlag.jpg"));
    ui->usa_pushButton->setIconSize(QSize(220,120));
    ui->usa_pushButton->setCursor(Qt::PointingHandCursor);


}

chooseLanguage::~chooseLanguage()
{
    delete ui;
}
