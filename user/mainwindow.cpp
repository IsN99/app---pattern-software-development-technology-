#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
    nextBlockSize = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1",2323);
}

void MainWindow::SendToServer(QString str)
{
    Data.clear(); //чистим QByteArray Data перед каждым использованием
    QDataStream out (&Data, QIODevice::WriteOnly); //передаем массив данных только на чтение
    out.setVersion(QDataStream::Qt_5_9);
    out<<quint16(0)<<str; // потоковый ввод строки в QDataStream out
    out.device()->seek(0);
    out<<quint16(Data.size()-sizeof(quint16));
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::SendToServer(QImage img)
{
    Data.clear(); //чистим QByteArray Data перед каждым использованием
    QDataStream out (&Data, QIODevice::WriteOnly); //передаем массив данных только на чтение
    out.setVersion(QDataStream::Qt_5_9);
    out<<quint16(0)<<img; // потоковый ввод строки в QDataStream out
    out.device()->seek(0);
    out<<quint16(Data.size()-sizeof(quint16));
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_9);
    if (in.status()==QDataStream::Ok)
    {
        /* QString str;
        in >> str;
        ui->textBrowser->append(str); */
        while(true)
        {
            if(nextBlockSize == 0)
            {
                if(socket->bytesAvailable() < 2)
                {
                    break;
                }
                in >> nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                break;
            }

            QString str;
            in>>str;
            nextBlockSize = 0;
            qDebug()<<"debug"<<str;
            switch(str.toInt()){
            case 11:
                SendToServer(*img);
                disconnect(socket,&QTcpSocket::readyRead,this,&MainWindow::slotReadyRead);
                connect (socket, &QTcpSocket::readyRead, this, &MainWindow::slotRR_ChA);
                break;
            case 22:
                //
                break;
            case 3:

                break;
            case 4:

                break;
            default:
                break;
            }
        }
    }
    else
    {
        ui->label_2->setText("Error");
    }
}

void MainWindow::slotRR_ChA()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_9);
    if (in.status()==QDataStream::Ok)
    {
        /* QString str;
        in >> str;
        ui->textBrowser->append(str); */
        while(true)
        {
            if(nextBlockSize == 0)
            {
                if(socket->bytesAvailable() < 2)
                {
                    break;
                }
                in >> nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                break;
            }

            QImage AccFlag;
            in>>AccFlag;
            nextBlockSize = 0;


            //вывод значения
            if(!AccFlag.isNull())
            {
                ui->label_2->setText("Доступ подтвержден");
                qDebug()<<AccFlag;
                ui->label->setPixmap(QPixmap::fromImage(AccFlag));
            }
            else
            {
                ui->label_2->setText("Доступ не подтвержден");
            }

            disconnect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotRR_ChA);
            connect(socket,&QTcpSocket::readyRead,this,&MainWindow::slotReadyRead);
        }
    }
    else
    {
        ui->label_2->setText("Error");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString path = ui->lineEdit->text();
    img = new QImage (path,"JPG");
    ui->label_3->clear();
    ui->label_2->clear();
//    QPixmap Empt;
    ui->label->clear();
    ui->label_3->setPixmap(QPixmap::fromImage(*img));
    SendToServer("1");
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString path = ui->lineEdit->text();
    img = new QImage (path,"JPG");
    ui->label_3->clear();
    ui->label_2->clear();
//    QPixmap Empt;
    ui->label->clear();
    ui->label_3->setPixmap(QPixmap::fromImage(*img));
    SendToServer("1");
}
