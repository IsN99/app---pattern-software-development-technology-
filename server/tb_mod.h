#ifndef TB_MOD_H
#define TB_MOD_H

#include "rw_gateway.h"
#include <ctime>

class tb_mod
{
public:
    tb_mod(QSqlDatabase &db);
    //методы польз-ля
    QImage CheckAccess(QImage &Face1);
    //методы менеджера доступа
    void AddPerson(QString Lastname,QString Firstname,QImage &Photo);
    void ChangePers(int Id,QString Lastname,QString Firstname,QImage &Photo);
    void DelPerson(int Id);
    //метод имитирущий распознавание лица
    int FaceRec(QImage &Face1, QImage &Face2);
private:
    QSqlDatabase db;
};


#endif // TB_MOD_H
