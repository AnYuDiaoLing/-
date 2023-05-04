#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QCustomPlot* customPlot = ui->customPlot;
        customPlot->addGraph();
        customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));//曲线1蓝色
        customPlot->addGraph();
        customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));//曲线2红色
        //坐标轴使用时间刻度
        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%h:%m:%s");
        customPlot->xAxis->setTicker(timeTicker);
        //四边安上坐标轴
        customPlot->axisRect()->setupFullAxesBox();
        //设置y轴范围
        customPlot->yAxis->setRange(-1.2, 1.2);
        // 使上下轴、左右轴范围同步
        connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
        //定时器连接槽函数realtimeDataSlot
        connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
        dataTimer.start(0); // 间隔时间 0ms表示尽可能快的触发
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::realtimeDataSlot()
{
    QCustomPlot* customPlot = ui->customPlot;
   static QTime time(QTime::currentTime());

    double key = time.elapsed()/1000.0; // 开始到现在的时间，单位秒
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.1) // 大约2ms添加一次数据
     {
       // 添加数据到graph
       customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
       customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
       //记录当前时刻
       lastPointKey = key;
        }
      // 曲线能动起来的关键在这里，设定x轴范围为最近8个时刻
       // customPlot->xAxis->setRange(key, 10, Qt::AlignRight);
    customPlot->xAxis->setRange(key,10, Qt::AlignRight);
     //绘图
        customPlot->replot();
     //计算帧数
        //     static int frameCount;
        //     double  lastFpsKey;
        //     ++frameCount;
        //     if (key-lastFpsKey > 2) // 每2秒求一次平均值
        //     {
        //        //状态栏显示帧数和数据总数
        //      ui->statusBar->showMessage(
        //             QString("%1 FPS, Total Data points: %2")
        //             .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
        //             .arg(customPlot->graph(0)->data()->size()+customPlot->graph(1)->data()->size())
        //       lastFpsKey = key;
        //       frameCount = 0;
        //    }
}
