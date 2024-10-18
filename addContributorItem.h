#ifndef ADDCONTRIBUTORITEM_H
#define ADDCONTRIBUTORITEM_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDoubleValidator>

namespace Ui {
class addContributorItem;
}

class addContributorItem : public QWidget
{
    Q_OBJECT

public:
    explicit addContributorItem(QWidget *parent = nullptr);
    ~addContributorItem();

    //funcs
    void setGroupName(QString _groupName) ;

signals:
    void contributorAdded(QString groupName) ;

private slots:
    void on_add_pushButton_clicked();

private:
    Ui::addContributorItem *ui;
};

#endif // ADDCONTRIBUTORITEM_H
