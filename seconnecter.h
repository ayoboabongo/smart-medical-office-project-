#ifndef SECONNECTER_H
#define SECONNECTER_H

#include <QDialog>

namespace Ui {
class SeConnecter;
}

class SeConnecter : public QDialog
{
    Q_OBJECT

public:
    explicit SeConnecter(QWidget *parent = nullptr);
    ~SeConnecter();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SeConnecter *ui;
};

#endif // SECONNECTER_H
