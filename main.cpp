#include "chooselanguage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    chooseLanguage w;
    w.show();
    return a.exec();
}
