#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "net.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("./DB.db");
    if(db.open())
    {
        qDebug ("open");
    }
    else
    {
        qDebug ("no open");
    }

//    QSqlQuery *qr = new QSqlQuery;
//    qr=new QSqlQuery(db);
//    qr->exec("DROP TABLE Empl");
//    qr->exec("CREATE TABLE Empl ("
//             "id_em    INTEGER NOT NULL,"
//             "Lastname	TEXT NOT NULL,"
//             "Firstname	TEXT NOT NULL,"
//             "Photo	BLOB NOT NULL,"
//             "PRIMARY KEY(id_em));");

//    tb_mod N(db);

//        QImage img1("1.jpg");
//        N.AddPerson("Фамилия1","Имя1",img1);

//        QImage img2("2.jpg");
//        N.AddPerson("Фамилия2","Имя2",img2);

//        QImage img3("3.jpg");
//        N.AddPerson("Фамилия3","Имя3",img3);

//        QImage img4("4.jpg");
//        N.AddPerson("Фамилия4","Имя4",img4);

//        QImage img5("5.jpg");
//        N.AddPerson("Фамилия5","Имя5",img5);

//        QImage img6("6.jpg");
//        N.AddPerson("Фамилия6","Имя6",img6);

//        QImage img7("7.jpg");
//        N.AddPerson("Фамилия7","Имя7",img7);

//        QImage img8("8.jpg");
//        N.AddPerson("Фамилия8","Имя8",img8);

//    delete qr;

    net S(db);
    model = new QSqlTableModel (this, db);
    model->setTable("Empl");
    model->select();

    ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    tb_mod T(db);
    QString Ln = ui->lineEdit->text();
    QString Fn = ui->lineEdit_2->text();
    QString path = ui->lineEdit_3->text();
    QImage im (path);
    T.AddPerson(Ln,Fn,im);

    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_2_clicked()
{
    tb_mod T(db);
    int Id = ui->lineEdit_4->text().toInt();
    QString Ln = ui->lineEdit_5->text();
    QString Fn = ui->lineEdit_6->text();
    QString path = ui->lineEdit_7->text();
    QImage im (path);
    T.ChangePers(Id,Ln,Fn,im);

    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_3_clicked()
{
    tb_mod T(db);
    int Id = ui->lineEdit_8->text().toInt();
    T.DelPerson(Id);
    model->select();
    ui->tableView->setModel(model);
}
