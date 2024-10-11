#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Chest");

    refreshGroupsName();

    QSqlQuery query ;
    QSqlRecord record ;
    query.prepare("SELECT * FROM groups") ;
    if( query.exec() && query.next()) {
        record = query.record() ;
        refreshContributorName(record.value("name").toString());
    }
}

mainWindow::~mainWindow()
{
    delete ui;
}


void mainWindow::addRawGroupNameItem()
{
    QListWidgetItem *item = new QListWidgetItem() ;
    item->setSizeHint(QSize(0 , 40));

    addItem *add_group_item = new addItem() ;
    add_group_item->setProperty("property" , "groupName") ;
    connect(add_group_item , &addItem::addGroupPageSignal , this , &mainWindow::addGroupPageCalld) ;
    ui->groups_listWidget->addItem(item) ;
    ui->groups_listWidget->setItemWidget(item , add_group_item) ;
}

void mainWindow::addRawContributorsName()
{
    QListWidgetItem *item = new QListWidgetItem() ;
    item->setSizeHint(QSize(0 , 40));

    addItem *add_contributor_Item = new addItem() ;
    add_contributor_Item->setProperty("property" , "contributorName") ;
    connect(add_contributor_Item , &addItem::addContributorPageSignal , this , &mainWindow::addContributorPageCalled) ;
    ui->contributors_listWidget->addItem(item);
    ui->contributors_listWidget->setItemWidget(item , add_contributor_Item);
}

void mainWindow::refreshGroupsName()
{
    ui->groups_listWidget->clear();

    //get the group's name from dataBase
    QSqlQuery query ;
    QSqlRecord record ;
    query.prepare("SELECT name FROM groups") ;
    if(query.exec()) {
        while(query.next()) {
            record = query.record() ;
            QListWidgetItem *item = new QListWidgetItem() ;
            item->setSizeHint(QSize(0 , 40));

            groupItem *group_item = new groupItem() ;
            group_item->language = language ;
            group_item->setName(record.value("name").toString());
            connect(group_item , &groupItem::refreshGroupListWidget , this , &mainWindow::refreshGroupsName) ;
            ui->groups_listWidget->addItem(item);
            ui->groups_listWidget->setItemWidget(item , group_item);
        }
    }

    addRawGroupNameItem();
}

void mainWindow::refreshContributorName(QString _groupName)
{
    ui->contributors_listWidget->clear();
    qDebug() << _groupName ;
    //get the contibutors from dataBase based on their group's name
    QSqlQuery query ;
    QSqlRecord record ;
    query.prepare("SELECT * FROM contributors WHERE groupsName = :groupsName ") ;
    query.bindValue(":groupsName" , _groupName);

    if(query.exec()) {
        while(query.next()) {
            record = query.record() ;
            QListWidgetItem *item = new QListWidgetItem() ;
            item->setSizeHint(QSize(0 , 40));

            contributorItem *contributor_item = new contributorItem() ;
            connect(contributor_item , &contributorItem::changesApplied , this , &mainWindow::refreshContributorName) ;
            contributor_item->setInfo(record.value("fullName").toString() , record.value("paid").toDouble() ,
            record.value("turn").toInt() );
            contributor_item->setProperty("groupName" , record.value("groupsName").toString()) ;
            contributor_item->setProperty("fullName" , record.value("fullName").toString()) ;
            ui->contributors_listWidget->addItem(item);
            ui->contributors_listWidget->setItemWidget(item , contributor_item);
        }
    }
    addRawContributorsName() ;
}

void mainWindow::addGroupPageCalld()
{
    addGroupItem *item = new addGroupItem() ;
    connect(item , &addGroupItem::groupNameAdded , this , &mainWindow::refreshGroupsName) ;
    item->show();
}

void mainWindow::addContributorPageCalled()
{
    addContributorItem *item = new addContributorItem() ;
    connect(item , &addContributorItem::contributorAdded , this , &mainWindow::refreshContributorName) ;
    item->show() ;
}




