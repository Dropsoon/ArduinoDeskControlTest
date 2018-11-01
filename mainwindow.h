#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "settingswindow.h"
//#include <QtSerialPort/QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSerialPort serial;

    bool bAutoEnabled = false;
    bool bConnected = false;
    int iRedVal, iGreenVal, iBlueVal;
    QString sComSelected;

private slots:
    void on_bAutoUpload_clicked();

    void on_bConnect_clicked();

    void on_cPort_currentIndexChanged(const QString &arg1);

    void on_bManualUpload_clicked();

    void on_sBlue_sliderMoved(int position);

    void on_sGreen_sliderMoved(int position);

    void on_sRed_sliderMoved(int position);

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
    settingswindow *settui;
};

#endif // MAINWINDOW_H
