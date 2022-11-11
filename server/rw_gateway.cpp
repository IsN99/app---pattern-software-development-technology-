#include "rw_gateway.h"

int rw_gateway::count = 0;

QSqlQuery *qr;//static?

//конструкторы
rw_gateway::rw_gateway(/*QString &Lastname,QString &Firstname,QImage &Photo,QSqlDatabase &db*/)
{
//    setFirstname(Firstname);
//    setLastname(Lastname);
//    setPhoto(Photo);
//    this->db=db;
}
rw_gateway::rw_gateway(QString &Lastname,QString &Firstname,QImage &Photo,QSqlDatabase &db)
{
    setFirstname(Firstname);
    setLastname(Lastname);
    setPhoto(Photo);
    this->db=db;
}

//геттеры
QString rw_gateway::getLastname()
{
    return Lastname;
}

QString rw_gateway::getFirstname()
{
    return Firstname;
}

QImage rw_gateway::getPhoto()
{
    QImage ph;
    ph.loadFromData(Photo,"JPG");;
    return ph;
}

int rw_gateway::getId()
{
    return Id;
}

//сеттеры
void rw_gateway::setLastname(QString &Lastname)
{
    this->Lastname=Lastname;   
}

void rw_gateway::setFirstname(QString &Firstname)
{
    this->Firstname=Firstname;
}

void rw_gateway::setPhoto(QImage &Photo)
{
    QBuffer buffer(&this->Photo);
    buffer.open(QIODevice::WriteOnly);
    Photo.save(&buffer, "JPG");
    buffer.close();
}

void rw_gateway::setId(int Id)
{
    this->Id=Id;
}


//CRUD
void rw_gateway::Insert()
{
    Id=count;
    count++;
    try {
        qr=new QSqlQuery(db);
        qr->prepare("INSERT INTO Empl (id_em,Firstname,Lastname,Photo) VALUES (:id_em, :Firstname, :Lastname, :Photo)");
            qr->bindValue("id_em",Id);
            qr->bindValue(":Firstname",Firstname);
            qr->bindValue(":Lastname",Lastname);
            qr->bindValue(":Photo",Photo);
            qr->exec();
        delete qr;

    } catch (...) {

    }
}

void rw_gateway::Update()
{
    try {
        qr=new QSqlQuery(db);
        qr->prepare("UPDATE Empl SET Firstname = :Firstname, Lastname = :Lastname, Photo = :Photo WHERE id_em = :id");
            qr->bindValue(":Firstname",Firstname);
            qr->bindValue(":Lastname",Lastname);
            qr->bindValue(":Photo",Photo);
            qr->bindValue(":id",Id);
            qr->exec();
        delete qr;

    } catch (...) {

    }
}


void rw_gateway::Delete()
{
    try {        
        qr=new QSqlQuery(db);
        qr->prepare("DELETE FROM Empl WHERE id_em=:ID");
            qr->bindValue(":ID",Id);
            qr->exec();
        delete qr;

    } catch (...) {

    }
}

rw_gateway rw_gateway::Finder(int findID,QSqlDatabase &db)
{
        qr=new QSqlQuery(db);
        qr->prepare("SELECT * FROM Empl WHERE id_em = :id_em");
            qr->bindValue(":id_em",findID);
            qr->exec();
            qr->next();
        int tId = qr->value(0).toInt();
        QString tFirstname = qr->value(1).toString();
        QString tLastname = qr->value(2).toString();
        QByteArray tPhoto = qr->value(3).toByteArray();

        QImage ph;
        ph.loadFromData(tPhoto,"JPG");
        rw_gateway tRGW(tLastname,tFirstname,ph, db);

        tRGW.setId(tId);
        delete qr;
        return tRGW;
}

std::vector<rw_gateway> rw_gateway::allFinder(QSqlDatabase &db)
{
    std::vector <rw_gateway> Tvect(0);

    qr=new QSqlQuery(db);
    qr->prepare("SELECT * FROM Empl");
    qr->exec();
    while(qr->next()){
        int tId = qr->value(0).toInt();
        QString tFirstname = qr->value(1).toString();
        QString tLastname = qr->value(2).toString();
        QByteArray tPhoto = qr->value(3).toByteArray();

        QImage ph;
        ph.loadFromData(tPhoto,"JPG");

        rw_gateway tRGW(tLastname,tFirstname,ph, db);
        tRGW.setId(tId);
        Tvect.emplace_back(tRGW);
    }
    delete qr;
    return Tvect;
}

