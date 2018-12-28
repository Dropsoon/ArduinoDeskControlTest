/*
    Prawa do ikonki nie mam więc, muszę dodać to:
    <div>Icons made by <a href="http://www.freepik.com" title="Freepik">Freepik</a> from <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com</a> is licensed by <a href="http://creativecommons.org/licenses/by/3.0/" title="Creative Commons BY 3.0" target="_blank">CC 3.0 BY</a></div>
    Tylko w C++ xD
*/

#include <QtSerialPort/QSerialPort>
#include <QPalette>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include "settingswindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList List;
    QString tmp;
    for(int i=0; i<32; i++){
        tmp = "COM" + QString::number(i+1);
        List << tmp;
    }
    ui->cPort->addItems(List);
    iRedVal = 0;
    iGreenVal = 0;
    iBlueVal = 0;

    connect(ui->sRed, &QAbstractSlider::sliderMoved, this, &MainWindow::onColorChanged);
    connect(ui->sGreen, &QAbstractSlider::sliderMoved, this, &MainWindow::onColorChanged);
    connect(ui->sBlue, &QAbstractSlider::sliderMoved, this, &MainWindow::onColorChanged);
    onColorChanged();

    ui->gMonitor->setEnabled(false);
    ui->gListwa->setEnabled(false);
    ui->gSufit->setEnabled(false);
}

MainWindow::~MainWindow()
{
    serial.close();
    delete ui;
}

void MainWindow::on_bAutoUpload_clicked()
{
    if(bAutoEnabled){  //if auto update enabled disable auto update and enable manual update
        ui->bManualUpload->setEnabled(true);
        bAutoEnabled = false;
        ui->bAutoUpload->setText("Automatyczna zmiana");
    } else { // if auto update disabled disable manual update and enable auto update
        ui->bManualUpload->setEnabled(false);
        bAutoEnabled = true;
        ui->bAutoUpload->setText("Zatrzymaj");
   }
}

void MainWindow::on_bConnect_clicked()
{   
    if(bConnected){
        serial.close();
        ui->bConnect->setText("Połącz");
        ui->bAutoUpload->setEnabled(false);
        ui->bManualUpload->setEnabled(false);
        ui->sRed->setEnabled(false);
        ui->sGreen->setEnabled(false);
        ui->sBlue->setEnabled(false);
        ui->gMonitor->setEnabled(false);
        ui->gListwa->setEnabled(false);
        ui->gSufit->setEnabled(false);
        bConnected = !bConnected;
        if(bAutoEnabled){
            ui->bAutoUpload->setText("Automatyczna zmiana");
            bAutoEnabled =! bAutoEnabled;
        }
    } else {
        ui->bConnect->setText("Łączenie...");
        serial.setPortName(sComSelected);
        serial.setBaudRate(9600);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);
        if(serial.open(QIODevice::ReadWrite)){
            ui->bConnect->setText("Rozłącz");
            ui->bAutoUpload->setEnabled(true);
            ui->bManualUpload->setEnabled(true);
            ui->sRed->setEnabled(true);
            ui->sGreen->setEnabled(true);
            ui->sBlue->setEnabled(true);
            ui->gMonitor->setEnabled(true);
            ui->gListwa->setEnabled(true);
            ui->gSufit->setEnabled(true);
            bConnected = !bConnected;
        } else {
            ui->bConnect->setText("Błąd");
        }
    }
}

void MainWindow::on_cPort_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Wybierz"){
        ui->bConnect->setEnabled(false);
    } else {
        ui->bConnect->setEnabled(true);
        sComSelected = arg1;
    }
}

void MainWindow::on_bManualUpload_clicked()
{
    std::string sR, sG, sB, sSerial;
    sR = "R" + std::to_string(iRedVal);
    sG = "G" + std::to_string(iGreenVal);
    sB = "B" + std::to_string(iBlueVal);

    sSerial = sR + sG + sB;

    for(int i=0; i<13; i++){
        sSerial = sSerial + std::to_string(i);
    }

    char const *cSerial;
    cSerial = sSerial.c_str();

    serial.write(cSerial);
}

void MainWindow::on_sBlue_sliderMoved(int position)
{
    iBlueVal = position;
    if(bAutoEnabled){
        on_bManualUpload_clicked();
    }
}

void MainWindow::on_sGreen_sliderMoved(int position)
{
    iGreenVal = position;
    if(bAutoEnabled){
        on_bManualUpload_clicked();
    }
}

void MainWindow::on_sRed_sliderMoved(int position)
{
    iRedVal = position;
    if(bAutoEnabled){
        on_bManualUpload_clicked();
    }
}

void MainWindow::on_actionSettings_triggered()
{
    settui =new settingswindow(this);
    settui->show();
}

void MainWindow::onColorChanged()
{
    m_color.setRgb(ui->sRed->value(), ui->sGreen->value(), ui->sBlue->value());
    QPalette pal = ui->displayWidget->palette();
    pal.setColor(QPalette::Window, m_color);
    ui->displayWidget->setPalette(pal);
    emit colorChanged(m_color);
}

void MainWindow::on_bMonitorAll_clicked()
{
    ui->cMonPx1->setChecked(true);
    ui->cMonPx2->setChecked(true);
}

void MainWindow::on_bMonitorNone_clicked()
{
    ui->cMonPx1->setChecked(false);
    ui->cMonPx2->setChecked(false);
}

void MainWindow::on_bListwaAll_clicked()
{
    ui->cListPx1->setChecked(true);
    ui->cListPx2->setChecked(true);
    ui->cListPx3->setChecked(true);
    ui->cListPx4->setChecked(true);
    ui->cListPx5->setChecked(true);
    ui->cListPx6->setChecked(true);
    ui->cListPx7->setChecked(true);
    ui->cListPx8->setChecked(true);
    ui->cListPx9->setChecked(true);
    ui->cListPx10->setChecked(true);
    ui->cListPx11->setChecked(true);
}

void MainWindow::on_bListwaNone_clicked()
{
    ui->cListPx1->setChecked(false);
    ui->cListPx2->setChecked(false);
    ui->cListPx3->setChecked(false);
    ui->cListPx4->setChecked(false);
    ui->cListPx5->setChecked(false);
    ui->cListPx6->setChecked(false);
    ui->cListPx7->setChecked(false);
    ui->cListPx8->setChecked(false);
    ui->cListPx9->setChecked(false);
    ui->cListPx10->setChecked(false);
    ui->cListPx11->setChecked(false);
}

void MainWindow::chceckPx()
{
    if(ui->cMonPx1->checkState()) px[0] = 1; else px[0] = 0;
    if(ui->cMonPx2->checkState()) px[1] = 1; else px[1] = 0;

    if(ui->cListPx1->checkState()) px[2] = 1; else px[2] = 0;
    if(ui->cListPx2->checkState()) px[3] = 1; else px[3] = 0;
    if(ui->cListPx3->checkState()) px[4] = 1; else px[4] = 0;
    if(ui->cListPx4->checkState()) px[5] = 1; else px[5] = 0;
    if(ui->cListPx5->checkState()) px[6] = 1; else px[6] = 0;
    if(ui->cListPx6->checkState()) px[7] = 1; else px[7] = 0;
    if(ui->cListPx7->checkState()) px[8] = 1; else px[8] = 0;
    if(ui->cListPx8->checkState()) px[9] = 1; else px[9] = 0;
    if(ui->cListPx9->checkState()) px[10] = 1; else px[10] = 0;
    if(ui->cListPx10->checkState()) px[11] = 1; else px[11] = 0;
    if(ui->cListPx11->checkState()) px[12] = 1; else px[12] = 0;
}
