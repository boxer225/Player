#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QDebug>
#include <QStyle>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer;
    player->setVolume(defaultVolume);
    ui->dial->setValue(defaultVolume);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_2->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    connect(player, SIGNAL(positionChanged(qint64)), this,  SLOT(onValue(qint64)));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this,  SLOT(setMediaPosition(int)));

}


MainWindow::~MainWindow()
{
    delete ui;
    delete player;
}

void MainWindow::on_pushButton_clicked()
{
    QString strFile = QFileDialog::getOpenFileName(this, "Open File");
    if ( !strFile.isEmpty()) {
    player->setMedia(QUrl::fromLocalFile(strFile));
    ui->pushButton_2->setEnabled(true);
    ui->label->setText(msecsToString(player->position()));
    ui->label->setText(msecsToString(player->duration()));
}
}


void MainWindow::on_pushButton_2_clicked()
{
    switch(player->state()) {
    case QMediaPlayer::PlayingState: player->pause();
    ui->pushButton_2->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    break;
    default: player->play();
        ui->pushButton_2->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    break;
    }
    ui->horizontalSlider->setRange(0, player->duration());
}

QString MainWindow::msecsToString(qint64 n) {
int nHours = (n / (60 * 60 * 1000));
int nMinutes = ((n % (60 * 60 * 1000))/ (60 * 1000));
int nSeconds = ( (n % (60 * 1000) ) / 1000);
return QTime(nHours, nMinutes, nSeconds).toString("hh:mm:ss");
}

void MainWindow::onValue(qint64 value) {
    ui->horizontalSlider->setValue(value);
    ui->label->setText(msecsToString(player->duration()));
    ui->label_2->setText(msecsToString(player->position()));
}

void MainWindow::setMediaPosition(int n) {
    player->setPosition(n);
}

void MainWindow::on_dial_actionTriggered(int action)
{
    player->setVolume(ui->dial->value());
}

