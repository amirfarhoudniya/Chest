#include <QSqlDatabase>
#include <QApplication>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //init dateBase
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataBase.db");
    db.open();

    mainWindow m ;
    m.show();

    return a.exec();
}
