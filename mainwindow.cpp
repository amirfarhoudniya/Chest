#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Chest");

    //prevent growing the window
    this->setFixedSize(this->size());

    //load groupsName from dataBase to group_listWidget
    refreshGroupsName();

    //draw pushButton's style
    ui->draw_pushButton->setEnabled(false);
    ui->draw_pushButton->setCursor(Qt::PointingHandCursor);
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
    //clear all items in group's listWidget
    ui->groups_listWidget->clear();

    //get the group's name from dataBase
    QSqlQuery query ;
    QSqlRecord record ;
    query.prepare("SELECT * FROM groups") ;
    if(query.exec()) {
        while(query.next()) {
            record = query.record() ;
            QListWidgetItem *item = new QListWidgetItem() ;
            item->setSizeHint(QSize(0 , 80));

            groupItem *group_item = new groupItem() ;
            group_item->setProperty("shareFactor" , record.value("shareFactor").toString() ) ;
            group_item->setProperty("groupName" , record.value("name").toString()) ;
            group_item->setName(record.value("name").toString() , record.value("shareFactor").toInt());
            connect(group_item , &groupItem::refreshGroupListWidget , this , &mainWindow::refreshGroupsName) ;
            connect(group_item , &groupItem::refreshContributorOfthisGroup , this , &mainWindow::refreshContributorName) ;
            ui->groups_listWidget->addItem(item);
            ui->groups_listWidget->setItemWidget(item , group_item);
        }
    }

    addRawGroupNameItem();
}

void mainWindow::refreshContributorName(QString _groupName)
{
    //clear all items in contributor's listWidget
    ui->contributors_listWidget->clear();

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
        if(record.value("turn").toInt() == 0 ){
            enableDrawPushButton(true);
            lastGroupNameCalled = _groupName ;
            addRawContributorsName() ;
        } else {
            enableDrawPushButton(false);
        }
    }

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
    item->setGroupName(lastGroupNameCalled);
    connect(item , &addContributorItem::contributorAdded , this , &mainWindow::refreshContributorName) ;
    item->show() ;
}

void mainWindow::enableDrawPushButton(bool _enable)
{
    if(_enable) {
        ui->draw_pushButton->setEnabled(_enable);
        ui->draw_pushButton->setStyleSheet("background-color:yellow ; color:black ;" );
    } else {
        ui->draw_pushButton->setEnabled(false);
        ui->draw_pushButton->setStyleSheet("" );
    }
}

void mainWindow::on_draw_pushButton_clicked()
{
    //fetch the list of contributors
    QStringList contributors;
    QSqlQuery query;
    query.prepare("SELECT fullName FROM contributors WHERE groupsName = :groupsName");
    query.bindValue(":groupsName", lastGroupNameCalled);

    if (query.exec()) {
        while (query.next()) {
            contributors << query.value(0).toString();
        }
    } else {
        qDebug() << query.lastError().text();
        return;
    }

    //shuffle the list of contributors
    std::shuffle(contributors.begin(), contributors.end(), *QRandomGenerator::global());

    //set draw result to dataBase
    for (int i = 0; i < contributors.size(); ++i) {
        query.prepare("UPDATE contributors SET turn = :turn WHERE fullName = :fullName AND groupsName = :groupsName");
        query.bindValue(":turn" , i + 1 );
        query.bindValue(":fullName" , contributors[i]);
        query.bindValue(":groupsName" , lastGroupNameCalled);
        query.exec() ;
    }

    //set data to .csv file
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QFile csvFile (desktopPath + "/" + lastGroupNameCalled + ".csv");
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream stream(&csvFile) ;
        stream << "full name\t" << "turn\n\r" ;
        for(int i= 0 ; i < contributors.size() ; i++) {
            stream << contributors[i]+ "\t" +  QString::number(i+1)  <<"\n\r";
        }
    }

    refreshContributorName(lastGroupNameCalled);
}

