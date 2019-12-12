#include "seconnecter.h"
#include "ui_seconnecter.h"
#include "equipement_para.h"
#include <QMessageBox>
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "connexion.h"
#include "gerermed.h"

SeConnecter::SeConnecter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeConnecter)
{
    ui->setupUi(this);
}

SeConnecter::~SeConnecter()
{
    delete ui;
}

void SeConnecter::on_pushButton_clicked()
{
    if(ui->Login->text()=="" || ui->Password->text()=="")
    {
        QMessageBox::information(nullptr, QObject::tr("Se Connecter"),
                    QObject::tr("Veuillez entrer le  Login et Password.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    QSqlQuery query;
    QString log=ui->Login->text() ;
    QString Pass=ui->Password->text() ;
    QString select="SELECT *from account where login like '%"+log+"%' and password like '%"+Pass+"%'";
    query.prepare(select);
    query.addBindValue(log);
    query.addBindValue(Pass);
    query.exec();

    QString login,password;
    if(query.exec())
    {
        while (query.next()) {
            login=query.value(0).toString();
            password=query.value(1).toString() ;
        }

      if(login==ui->Login->text() && password==ui->Password->text() )
       {
          QMessageBox::information(nullptr, QObject::tr("Se Connecter"),
                      QObject::tr("connected.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
          hide() ;
          GererMed *w;
          w = new GererMed ;
          w->showFullScreen() ;
      }
      else {
          QMessageBox::information(nullptr, QObject::tr("Se Connecter"),
                      QObject::tr("Incorrect Login or Password.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);


    }

 }

}
