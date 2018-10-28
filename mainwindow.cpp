/*
    Prawa do ikonki nie mam więc, muszę dodać to:
    <div>Icons made by <a href="http://www.freepik.com" title="Freepik">Freepik</a> from <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com</a> is licensed by <a href="http://creativecommons.org/licenses/by/3.0/" title="Creative Commons BY 3.0" target="_blank">CC 3.0 BY</a></div>
    Tylko w C++ xD
*/

#include <QtSerialPort/QSerialPort>
//#include <QSerialPort>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_bAutoUpload_clicked()
{
    serial.setPortName("COM5");
    serial.setBaudRate(9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.open(QIODevice::ReadWrite);
    //serial.write("255");
    serial.close();


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



//serial.setPortName("COM1");
//serial.setBaudRate(QSerialPort::Baud9600);
//serial.setDataBits(QSerialPort::Data8);
//serial.setParity(QSerialPort::NoParity);
//serial.setStopBits(QSerialPort::OneStop);
//serial.setFlowControl(QSerialPort::NoFlowControl);
//serial.open(QIODevice::ReadWrite); serial.write("hello");
//serial.close();

void MainWindow::on_bConnect_clicked()
{
    if(bConnected){
        bConnected = false;
        ui->bConnect->setText("Połącz");
    } else {
        ui->bConnect->setText("Łączenie...");
        //serial->setPortName(sPort);
        bConnected = true;
        ui->bConnect->setText("Rozłącz");
    }

}

void MainWindow::on_cPort_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Wybierz"){
        ui->bConnect->setEnabled(false);
    } else {
        ui->bConnect->setEnabled(true);
    }

    //sPort = arg1;
}
