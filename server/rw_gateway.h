#pragma once
#ifndef RW_GATEWAY_H
#define RW_GATEWAY_H
#include <QString>
#include <QImage>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QBuffer>
#include <QMessageBox>
class rw_gateway
{
public:
    //конструктор
    rw_gateway();
    rw_gateway(QString &Lastname,QString &Firstname,QImage &Photo,QSqlDatabase &db);

    //геттеры
    QString getLastname();
    QString getFirstname();
    QImage getPhoto();
    int getId();
    //сеттеры
    void setLastname(QString &Lastname);
    void setFirstname(QString &Firstname);
    void setPhoto(QImage &Photo);

    //CRUD
    void Insert();
    void Update();
    void Delete();
    //статический метод поиска
    static rw_gateway Finder(int findID,QSqlDatabase &db);
    static std::vector <rw_gateway> allFinder(QSqlDatabase &db);
private:
    int Id;
    static int count;

    QString Lastname;
    QString Firstname;
    QByteArray Photo;
    QSqlDatabase db;

    void setId(int Id);
};


#endif // RW_GATEWAY_H
