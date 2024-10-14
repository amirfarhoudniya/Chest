#ifndef GROUPITEM_H
#define GROUPITEM_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>

#include "dataBase.h"

namespace Ui {
class groupItem;
}

class groupItem : public QWidget
{
    Q_OBJECT

public:
    explicit groupItem(QWidget *parent = nullptr);
    ~groupItem();

    void setName(QString _name) ;

signals :
    void refreshGroupListWidget() ;
    void refreshContributorOfthisGroup(QString _groupName) ;

private slots:
    void on_remove_pushButton_clicked();

    void on_groupName_pushButton_clicked();

private:
    Ui::groupItem *ui;
};

#endif // GROUPITEM_H
