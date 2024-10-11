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
    int language ;

signals :
    void refreshGroupListWidget() ;

private slots:
    void on_pushButton_clicked();

private:
    Ui::groupItem *ui;
};

#endif // GROUPITEM_H
