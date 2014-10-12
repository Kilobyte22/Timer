#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    elapsed = 0;
    elapsedLap = 0;
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    model = new QStandardItemModel();
    ui->lstTimes->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnStart_clicked()
{
    time.start();
    lapTime.start();
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    ui->btnReset->setEnabled(true);
    ui->btnLap->setEnabled(true);
    isNull = false;
    running = true;
    timer.start(55);
}

QString MainWindow::prependZeros(int number, int count)
{
    QString str = QString::number(number);
    while (str.length() < count)
        str = "0" + str;
    return str;
}

QString MainWindow::formatMS(int input)
{
    int ms = input % 1000;
    input /= 1000;
    int sec = input % 60;
    input /= 60;
    int min = input % 60;
    input /= 60;
    int hr = input;
    return QString("%1:%2:%3.%4").arg(prependZeros(hr, 2)).arg(prependZeros(min, 2)).arg(prependZeros(sec, 2)).arg(prependZeros(ms, 3));
}

void MainWindow::tick()
{
    ui->lblCurrent->setText(formatMS(time.elapsed() + elapsed));
    ui->lblLap->setText(formatMS(lapTime.elapsed() + elapsedLap));
}

void MainWindow::on_btnStop_clicked()
{
    timer.stop();
    running = false;
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    elapsed += time.elapsed();
    elapsedLap += lapTime.elapsed();
}

void MainWindow::on_btnReset_clicked()
{
    elapsed = 0;
    elapsedLap = 0;
    running = false;
    isNull = true;
    timer.stop();
    ui->btnStop->setEnabled(false);
    ui->btnStart->setEnabled(true);
    ui->btnReset->setEnabled(false);
    ui->btnLap->setEnabled(false);
    model->clear();
    ui->lblCurrent->setText("00:00:00.00");
    ui->lblLap->setText("00:00:00.00");
}

void MainWindow::on_btnLap_clicked()
{
    QStandardItem *item = new QStandardItem();
    item->setData(QString("%1 -> %2").arg(formatMS(lapTime.elapsed() + elapsedLap)).arg(formatMS(time.elapsed() + elapsed)), Qt::DisplayRole);
    model->appendRow(item);
    lapTime.restart();
    elapsedLap = 0;
}
