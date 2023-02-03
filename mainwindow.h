#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void onValue(qint64 value);

    void setMediaPosition(int n);

    void on_dial_actionTriggered(int action);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QString msecsToString(qint64 n);
    int defaultVolume=50;
};
#endif // MAINWINDOW_H
