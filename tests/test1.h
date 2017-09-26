#ifndef TEST1_H
#define TEST1_H

#include <QDialog>

namespace Ui {
class Test1;
}

class Test1 : public QDialog
{
    Q_OBJECT

public:
    explicit Test1(QWidget *parent = 0);
    ~Test1();

private slots:
    void on_pbnTest1_clicked();
    void on_pbnTest2_clicked();
private:
    Ui::Test1 *ui;
    QStringList articles;
    int rowsToInsert;
};

#endif // TEST1_H
