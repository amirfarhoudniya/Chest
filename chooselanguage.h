#ifndef CHOOSELANGUAGE_H
#define CHOOSELANGUAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class chooseLanguage;
}
QT_END_NAMESPACE

class chooseLanguage : public QWidget
{
    Q_OBJECT

public:
    chooseLanguage(QWidget *parent = nullptr);
    ~chooseLanguage();

private:
    Ui::chooseLanguage *ui;
};
#endif // CHOOSELANGUAGE_H
