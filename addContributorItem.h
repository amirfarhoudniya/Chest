#ifndef ADDCONTRIBUTORITEM_H
#define ADDCONTRIBUTORITEM_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>

namespace Ui {
class addContributorItem;
}

class addContributorItem : public QWidget
{
    Q_OBJECT

public:
    explicit addContributorItem(QWidget *parent = nullptr);
    ~addContributorItem();

signals:
    void contributorAdded(QString groupName) ;

private slots:
    void on_add_pushButton_clicked();

private:
    Ui::addContributorItem *ui;
};

#endif // ADDCONTRIBUTORITEM_H
