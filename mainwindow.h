#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnStart_clicked();
    void tick();

    void on_btnStop_clicked();

    void on_btnReset_clicked();

    void on_btnLap_clicked();

private:
    QString formatMS(int ms);
    QString prependZeros(int number, int count);

    Ui::MainWindow *ui;
    QTime time;
    QTime lapTime;
    int elapsed;
    int elapsedLap;
    bool running;
    bool isNull;
    QTimer timer;
    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
