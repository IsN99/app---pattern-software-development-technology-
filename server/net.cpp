#include "net.h"

net::net(QSqlDatabase &db)
{
    if(this->listen(QHostAddress::Any, 2323)) //проверка сервера на включение (ip-любой, порт-2323 для tcp соединения)
    {
        qDebug()<<"start";
    }
    else
    {
        qDebug()<<"error";
    }
    nextBlockSize = 0;
    this->db=db;
}

void net::incomingConnection(qintptr socketDescriptor) //входящее соединение
{
    socket = new QTcpSocket; //создаем сокет в динамической памяти
    socket->setSocketDescriptor(socketDescriptor); //назначаем передаваемый дескриптор сокету


    connect (socket, &QTcpSocket::readyRead, this, &net::slotReadyRead); //сигнально-слотовое соединение readyread сокета с таким же методом сервера
    connect (socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater); //сигнально-слотовое соединение отсоединения с удалением сокета

    Sockets.push_back(socket); // добавление созданного при соединении сокета в вектор сокетов
    qDebug() <<"client connected"<<socketDescriptor; //вывод сообщения
}

void net::slotReadyRead()
{
    socket = static_cast<QTcpSocket*>(sender()); //записываем по указателю сокет с которого пришел запрос
    QDataStream in (socket); //Получаем поток данных из сокета
    in.setVersion(QDataStream::Qt_5_9);
    if (in.status() == QDataStream::Ok) //при положительном считывании
    {
        qDebug()<<"read...";
        /* QString str;
        in >> str; //преобразуем в строку
        qDebug()<<str; //выводим строку
        SendToClient(str); */
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
            qDebug()<<str.toInt();
            switch (str.toInt()) {
            case 1:
                str = "11";
                SendToClient (str);
                disconnect (socket, &QTcpSocket::readyRead, this, &net::slotReadyRead);
                connect (socket, &QTcpSocket::readyRead, this, &net::slotRR_ChA);
                break;
            case 2:
                //
                break;
            case 3:

                break;
            case 4:

                break;
            default:
                break;
            }
//            SendToClient(str);//исправить
            break;
        }
    }
    else
    {
        qDebug()<<"DataStream error";
    }
}

void net::slotRR_ChA()
{
    socket = static_cast<QTcpSocket*>(sender()); //записываем по указателю сокет с которого пришел запрос
    QDataStream in (socket); //Получаем поток данных из сокета
    in.setVersion(QDataStream::Qt_5_9);
    if (in.status() == QDataStream::Ok) //при положительном считывании
    {
        qDebug()<<"read...";
        /* QString str;
        in >> str; //преобразуем в строку
        qDebug()<<str; //выводим строку
        SendToClient(str); */
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

            QImage img;
            in>>img;
            nextBlockSize = 0;
            tb_mod X(db);
            SendToClient(X.CheckAccess(img));
            qDebug()<<X.CheckAccess(img);
            disconnect (socket, &QTcpSocket::readyRead, this, &net::slotRR_ChA);
            connect (socket, &QTcpSocket::readyRead, this, &net::slotReadyRead);

            break;
        }
    }
    else
    {
        qDebug()<<"DataStream error";
    }
}

void net::SendToClient(QString str)
{
    Data.clear(); //чистим QByteArray Data перед каждым использованием
    QDataStream out (&Data, QIODevice::WriteOnly); //передаем массив данных только на чтение
    out.setVersion(QDataStream::Qt_5_9);
    out<<quint16(0)<<str; // потоковый ввод строки в QDataStream out
//    qDebug()<<str;
    out.device()->seek(0);
    out<<quint16(Data.size()-sizeof(quint16));
    for(int i=0; i<Sockets.size(); i++)
    {
        Sockets[i]->write(Data);
    }
}

void net::SendToClient(QImage access)
{
    Data.clear(); //чистим QByteArray Data перед каждым использованием
    QDataStream out (&Data, QIODevice::WriteOnly); //передаем массив данных только на чтение
    out.setVersion(QDataStream::Qt_5_9);
    out<<quint16(0)<<access; // потоковый ввод строки в QDataStream out
    out.device()->seek(0);
    out<<quint16(Data.size()-sizeof(quint16));
    for(int i=0; i<Sockets.size(); i++)
    {
        Sockets[i]->write(Data);
    }
}


