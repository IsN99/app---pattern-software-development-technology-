#include "tb_mod.h"



tb_mod::tb_mod(QSqlDatabase &db)
{
    this->db=db;
}

QImage tb_mod::CheckAccess(QImage &Face1)
{
    std::vector <rw_gateway> A1 = rw_gateway::allFinder(db);

    for(auto i: A1){
       QImage Face2 = i.getPhoto();
       qDebug()<<i.getLastname()<<" "<<i.getFirstname()<<" "<<i.getPhoto();
       int O = FaceRec(Face1,Face2);
       qDebug()<< O;
       if(O>50){
           return Face2;
       }
    }
    QImage False;
    return False;
}



void tb_mod::AddPerson(QString Lastname,QString Firstname,QImage &Photo)
{
    rw_gateway RowGate (Lastname,Firstname,Photo, db);
    RowGate.Insert();
}

void tb_mod::ChangePers(int Id,QString Lastname,QString Firstname,QImage &Photo)
{
   rw_gateway RowGate = rw_gateway::Finder(Id, db);
   RowGate.setLastname(Lastname);
   RowGate.setFirstname(Firstname);
   RowGate.setPhoto(Photo);
   RowGate.Update();
}

void tb_mod::DelPerson(int Id)
{
    rw_gateway RowGate = rw_gateway::Finder(Id, db);
    RowGate.Delete();
}

int tb_mod::FaceRec(QImage &Face1, QImage &Face2)
{

    int r = rand()%(50)+2;
    return r;
}
