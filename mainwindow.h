#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit   MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
private:
    Ui::MainWindow *ui;
    QTimer dataTimer;

private slots:
    void realtimeDataSlot();
};
#endif // MAINWINDOW_H
