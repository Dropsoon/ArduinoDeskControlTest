#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "settingswindow.h"
#include <QColor>
//#include <QtSerialPort/QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSerialPort serial;

    bool bAutoEnabled = false;
    bool bConnected = false;
    int iRedVal, iGreenVal, iBlueVal;
    int px[13];
    QString sComSelected;

    QColor color() const
    {
        return m_color;
    }

signals:
    void colorChanged(QColor color);

private slots:
    void on_bAutoUpload_clicked();

    void on_bConnect_clicked();

    void on_cPort_currentIndexChanged(const QString &arg1);

    void on_bManualUpload_clicked();

    void on_sBlue_sliderMoved(int position);

    void on_sGreen_sliderMoved(int position);

    void on_sRed_sliderMoved(int position);

    void on_actionSettings_triggered();

    void onColorChanged();

    void on_bMonitorAll_clicked();

    void on_bMonitorNone_clicked();

    void on_bListwaAll_clicked();

    void on_bListwaNone_clicked();

    void chceckPx();

private:
    Ui::MainWindow *ui;
    settingswindow *settui;
    QColor m_color;
};

#endif // MAINWINDOW_H
