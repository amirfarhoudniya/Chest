#ifndef CONTRIBUTORITEMEXTENDED_H
#define CONTRIBUTORITEMEXTENDED_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDoubleValidator>

#include "dataBase.h"

namespace Ui {
class contributorItemExtended;
}

class contributorItemExtended : public QWidget
{
    Q_OBJECT

public:
    explicit contributorItemExtended(QWidget *parent = nullptr);
    ~contributorItemExtended();

    void setInfo(QString _name, QString _groupName, int _turn, double _lastPayments) ;


signals :
    void changesApplied() ;

private slots:
    void on_apply_pushButton_clicked();

private:
    Ui::contributorItemExtended *ui;
};

#endif // CONTRIBUTORITEMEXTENDED_H
