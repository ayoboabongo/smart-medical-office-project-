#ifndef STAT_H
#define STAT_H

#include <QMainWindow>

namespace Ui {
class STAT;
}

class STAT : public QMainWindow
{
    Q_OBJECT

public:
    explicit STAT(QWidget *parent = nullptr);
    ~STAT();
    void makePlot() ;

private:
    Ui::STAT *ui;
};

#endif // STAT_H
