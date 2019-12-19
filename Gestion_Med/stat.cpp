#include "stat.h"
#include "ui_stat.h"
#include <QSqlQuery>

STAT::STAT(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::STAT)
{
    ui->setupUi(this);
    STAT::makePlot() ;
}

STAT::~STAT()
{
    delete ui;
}


void STAT::makePlot()
{
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot->setBackground(QBrush(gradient));

    QCPBars *ampoule=new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis) ;
    QCPBars *comprime=new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis) ;
    QCPBars *injection=new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis) ;
    QCPBars *gellules=new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis) ;
    QCPBars *sirop =new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis) ;
    QCPBars *pillule=new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis) ;
    QCPBars *pommade=new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis) ;
    QCPBars *goutte=new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis) ;
    QCPBars *effervesent=new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis) ;


    ampoule->setAntialiased(false);
    comprime->setAntialiased(false);
    injection->setAntialiased(false);
    gellules->setAntialiased(false);
    sirop->setAntialiased(false);
    pillule->setAntialiased(false);
    pommade->setAntialiased(false);
    goutte->setAntialiased(false);
    effervesent->setAntialiased(false);


    ampoule->setStackingGap(1);
    comprime->setStackingGap(1);
    injection->setStackingGap(1);
    gellules->setStackingGap(1);
    sirop->setStackingGap(1);
    pillule->setStackingGap(1);
    pommade->setStackingGap(1);
    goutte->setStackingGap(1);
    effervesent->setStackingGap(1);

    // set names and colors:


    ampoule->setName("ampoule");
    ampoule->setPen(QPen(QColor(0,0, 0).lighter(180)));
    ampoule->setBrush(QColor(0, 0, 0));

    comprime->setName("Comprime");
    comprime->setPen(QPen(QColor(255, 0, 0).lighter(170)));
    comprime->setBrush(QColor(255, 0, 0));

    injection->setName("Injection");
    injection->setPen(QPen(QColor(250, 170, 20).lighter(150)));
    injection->setBrush(QColor(250, 170, 20));

    gellules->setName("gellules");
    gellules->setPen(QPen(QColor(0, 255, 0).lighter(125)));
    gellules->setBrush(QColor(0, 255, 0));

    sirop->setName("sirop");
    sirop->setPen(QPen(QColor(0, 0, 255).lighter(145)));
    sirop->setBrush(QColor(0, 0, 255));

    pillule->setName("pillule");
    pillule->setPen(QPen(QColor(119, 136, 153).lighter(175)));
    pillule->setBrush(QColor(119, 136, 153));


    pommade->setName("pommade");
    pommade->setPen(QPen(QColor(210, 105, 30).lighter(90)));
    pommade->setBrush(QColor(210, 105, 30));

    goutte->setName("goutte");
    goutte->setPen(QPen(QColor(255, 105, 180).lighter(120)));
    goutte->setBrush(QColor(255, 105, 180));

    effervesent->setName("effervesent");
    effervesent->setPen(QPen(QColor(139, 0, 139).lighter(95)));
    effervesent->setBrush(QColor(139, 0, 139));



    // stack bars on top of each other:

    ampoule->moveAbove(comprime);
    comprime->moveAbove(injection);
    gellules->moveAbove(comprime);
    sirop->moveAbove(gellules);
    pillule->moveAbove(sirop);
    pommade->moveAbove(pillule);
    goutte->moveAbove(pommade);
    effervesent->moveAbove(goutte);

    // prepare x axis with country labels:
    QVector<double> ticks,tick;
    QVector<QString> labels,label;
     QVector<double> comprimedata,injectiondata,siropdata,pilluledata,gouttedata,pommadedate,ampouledata,effervesentdata,gellulesdata;
    QSqlQuery qur;
    qur.prepare("select nom,type,sum(quantite) qte from MED group by nom,type ");
            qur.exec();
       int i=1 ;
      if(qur.exec())
      {
         while(qur.next())
            {

                labels<<qur.value(0).toString() ;
                ticks<< i ;
                if(qur.value(1).toString()=="comprime")
                {
                    comprimedata<<qur.value(2).toInt();
                    injectiondata<<0;
                    siropdata<<0 ;
                    ampouledata<<0;
                    pilluledata<<0 ;
                    pommadedate<<0;
                    gouttedata<<0 ;
                    effervesentdata<<0 ;
                    gellulesdata<<0 ;
                }
                else if (qur.value(1).toString()=="injection") {
                    injectiondata<<qur.value(2).toInt();
                    comprimedata<<0;
                    siropdata<<0 ;
                    ampouledata<<0;
                    pilluledata<<0 ;
                    pommadedate<<0;
                    gouttedata<<0 ;
                    effervesentdata<<0 ;
                    gellulesdata<<0 ;
                }
                else if (qur.value(1).toString()=="sirop") {
                    siropdata<<qur.value(2).toInt();
                    comprimedata<<0;
                    injectiondata<<0;
                    ampouledata<<0;
                    pilluledata<<0 ;
                    pommadedate<<0;
                    gouttedata<<0 ;
                    effervesentdata<<0 ;
                    gellulesdata<<0 ;
                }
                else if (qur.value(1).toString()=="ampoule") {
                    ampouledata<<qur.value(2).toInt();
                    comprimedata<<0;
                    injectiondata<<0;
                    siropdata<<0 ;
                    pilluledata<<0 ;
                    pommadedate<<0;
                    gouttedata<<0 ;
                    effervesentdata<<0 ;
                    gellulesdata<<0 ;
                }

                else if (qur.value(1).toString()=="pillule") {
                    pilluledata<<qur.value(2).toInt();
                    comprimedata<<0;
                    injectiondata<<0;
                    siropdata<<0 ;
                    ampouledata<<0;
                    pommadedate<<0;
                    gouttedata<<0 ;
                    effervesentdata<<0 ;
                    gellulesdata<<0 ;
                }

                else if (qur.value(1).toString()=="pommade") {
                    pommadedate<<qur.value(2).toInt();
                    comprimedata<<0;
                    injectiondata<<0;
                    siropdata<<0 ;
                    ampouledata<<0;
                    pilluledata<<0 ;
                    gouttedata<<0 ;
                    effervesentdata<<0 ;
                    gellulesdata<<0 ;
                }
                else if (qur.value(1).toString()=="goutte") {
                    gouttedata<<qur.value(2).toInt();
                    comprimedata<<0;
                    injectiondata<<0;
                    siropdata<<0 ;
                    ampouledata<<0;
                    pilluledata<<0 ;
                    pommadedate<<0;
                    effervesentdata<<0 ;
                    gellulesdata<<0 ;
                }
                else if (qur.value(1).toString()=="comprime effervescent") {
                    effervesentdata<<qur.value(2).toInt();
                    comprimedata<<0;
                    injectiondata<<0;
                    siropdata<<0 ;
                    ampouledata<<0;
                    pilluledata<<0 ;
                    pommadedate<<0;
                    gouttedata<<0 ;
                    gellulesdata<<0 ;
                }
                else if (qur.value(1).toString()=="gellules") {
                    gellulesdata<<qur.value(2).toInt();
                    comprimedata<<0;
                    injectiondata<<0;
                    siropdata<<0 ;
                    ampouledata<<0;
                    pilluledata<<0 ;
                    pommadedate<<0;
                    gouttedata<<0 ;
                    effervesentdata<<0 ;
                }
                else
                {}


               // ticks<<i ;
                i++ ;
            }

      }

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0,4);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0,250);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Quantite totale");
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:

    comprime->setData(ticks,comprimedata);
    ampoule->setData(ticks,ampouledata);
    injection->setData(ticks,injectiondata);
    gellules->setData(ticks,gellulesdata);
    goutte->setData(ticks,gouttedata);
    pillule->setData(ticks,pilluledata);
    sirop->setData(ticks,siropdata);
    effervesent->setData(ticks,effervesentdata);
    pommade->setData(ticks,pommadedate);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}
