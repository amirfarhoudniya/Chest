#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>

#include "addGroupItem.h"
#include "groupItem.h"
#include "addItem.h"
#include "contributorItem.h"
#include "addContributorItem.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

    void addRawGroupNameItem() ;
    void addRawContributorsName() ;
    void refreshGroupsName() ;
    void refreshContributorName(QString _groupName) ;
    void addGroupPageCalld() ;
    void addContributorPageCalled() ;

signals :
    void addGroupPageSignal() ;
    void addContributorPageSignal() ;


private:
    Ui::mainWindow *ui;
    int language ;
};

#endif // MAINWINDOW_H
