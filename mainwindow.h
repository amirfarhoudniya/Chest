#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QRandomGenerator>
#include <algorithm> // for std::shuffle
#include <QStringList>

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

signals :
    void addGroupPageSignal() ;
    void addContributorPageSignal() ;


private slots:
    void on_draw_pushButton_clicked();

private:
    Ui::mainWindow *ui;

    //variables
    QString lastGroupNameCalled ;

    //funcs
    void addRawGroupNameItem() ;
    void addRawContributorsName() ;
    void refreshGroupsName() ;
    void refreshContributorName(QString _groupName) ;
    void addGroupPageCalld() ;
    void addContributorPageCalled() ;
    void enableDrawPushButton(bool _enable) ;
};

#endif // MAINWINDOW_H
