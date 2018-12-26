/*
    Prawa do ikonki nie mam więc, muszę dodać to:
    <div>Icons made by <a href="http://www.freepik.com" title="Freepik">Freepik</a> from <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com</a> is licensed by <a href="http://creativecommons.org/licenses/by/3.0/" title="Creative Commons BY 3.0" target="_blank">CC 3.0 BY</a></div>
    Tylko w C++ xD
*/

#include <QtSerialPort/QSerialPort>
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
