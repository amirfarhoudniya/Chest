#ifndef ADDGROUPITEM_H
#define ADDGROUPITEM_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class addGroupItem;
}

class addGroupItem : public QWidget
{
    Q_OBJECT

public:
    explicit addGroupItem(QWidget *parent = nullptr);
    ~addGroupItem();

signals :
    void groupNameAdded() ;

private slots:
    void on_save_pushButton_clicked();

    void on_shareFactor_lineEdit_textChanged();

private:
    Ui::addGroupItem *ui;
};

#endif // ADDGROUPITEM_H
