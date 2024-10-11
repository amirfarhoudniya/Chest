#ifndef CONTRIBUTORITEM_H
#define CONTRIBUTORITEM_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>

#include "contributorItemExtended.h"

namespace Ui {
class contributorItem;
}

class contributorItem : public QWidget
{
    Q_OBJECT

public:
    explicit contributorItem(QWidget *parent = nullptr);
    ~contributorItem();

    void setInfo(QString _name , double _payment , int _turn) ;

signals:
    void changesApplied(QString _groupName) ;

private slots:
    void on_contributor_pushButton_clicked();

private:
    Ui::contributorItem *ui;

    //variabels
    QString name ;
    double payment ;
    int turn ;

    //func
    void refreshContributorReq() ;
};

#endif // CONTRIBUTORITEM_H
