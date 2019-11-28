#include "equipement_para.h"
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

equipement_para::equipement_para()
{
    id=0;
    nom="";
    localisation="";

}

equipement_para::equipement_para(int id,QString nom,QString localisation)
{
    this->id=id ;
    this->nom=nom;
    this->localisation=localisation;

}

int equipement_para::get_id(){return  id;} ;
QString equipement_para::get_nom(){return  nom ;};
QString equipement_para::get_localisation(){return  localisation ;};

void equipement_para::set_id(int id){this->id=id;}
void equipement_para::set_nom(QString nom){this->nom=nom ;}
void equipement_para::set_localisation(QString loc){this->localisation=loc ;}

bool equipement_para::ajouterEq()
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("INSERT INTO equipement (id, nom,localisation) "
                        "VALUES (:id, :nom, :localisation)");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":localisation", localisation);

    return    query.exec();

}

bool equipement_para::updateEquip(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("UPDATE equipement set id=:id,nom=:nom,localisation=:localisation where id=:id ");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":localisation", localisation);

    return    query.exec();

}



QSqlQueryModel * equipement_para ::afficherEquip()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from equipement");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Localisation"));

    return model;
}


bool equipement_para::supprimerEquip(int idd)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("Delete from equipement where id = :id ");
    query.bindValue(":id", res);
    return    query.exec();

}

bool equipement_para::RechercherEquip(int idd)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("Select *from equipement where id = :id ");
    query.bindValue(":id", res);
    return    query.exec();
}


bool equipement_para::RechercherEquip_nom(QString idd)
{
    QSqlQuery query;
  //  QString res= QString::number(idd);
    query.prepare("Select *from equipement where nom = :id ");
    query.bindValue(":id", idd);
    return    query.exec();

}

QSqlQueryModel * equipement_para::afficherEqRechercher(QString ident)
{
    QSqlQuery query;

     QSqlQueryModel * model = new QSqlQueryModel();

 model->setQuery("select *from equipement where nom like '%"+ident+"%' or  id like '%"+ident+"%' or localisation like '%"+ident+"%' order by nom ");
 query.addBindValue(ident);
 query.exec();
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Localisation"));




     return model;

}

equipement_para equipement_para::getEquipement(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("Select *from equipement where id = :id ");
    query.bindValue(":id", res);
    equipement_para eq;
    if(query.exec())
    {
        QMessageBox::information(nullptr, QObject::tr("modifier un equipement"),
                    QObject::tr("equipement trouvé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        while(query.next())
        {
             eq.set_id(query.value(0).toInt());
             eq.set_nom( query.value(1).toString());
             eq.set_localisation(query.value(2).toString());

        }

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Rechercher un equipement"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

    return  eq ;

}
