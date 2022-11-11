#ifndef NET_H
#define NET_H

#include "tb_mod.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>

class net: public QTcpServer
{
    Q_OBJECT
public:
    net(QSqlDatabase &db); //конструктор
    QTcpSocket *socket; //создаем указатель на сокет

private:
    QVector <QTcpSocket*> Sockets; //вектор куда будут сохраняться сокеты всех соединений
    QByteArray Data; //данные для передачи через сокеты
    void SendToClient(QString str);
    void SendToClient(QImage access);
    quint16 nextBlockSize;
    QSqlDatabase db;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
    void slotRR_ChA();


};

#endif // NET_H
