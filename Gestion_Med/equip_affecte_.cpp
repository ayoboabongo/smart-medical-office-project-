#include "equip_affecte_.h"
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

/*!
 * \file equip_affecte.cpp
 * \brief Equip_affecte::Equip_affecte
 */
Equip_affecte::Equip_affecte()
{
    this->id_equip=0;
    this->id_salle="";
    this->nom="" ;
    this->localisation="" ;

}

Equip_affecte::Equip_affecte(int id_eq,QString id_salle,QString nom,QString localisation)
{
    this->id_equip=id_eq;
    this->id_salle=id_salle;
    this->nom=nom;
    this->localisation=localisation ;

}

bool Equip_affecte::ajouter_equip()
{
      QSqlQuery query;
        QString res= QString::number(id_equip);
        query.prepare("INSERT INTO equipement_affect (id_eq,id_salle, nom,localisation) "
                            "VALUES (:id,:id_salle,:nom, :localisation)");
        query.bindValue(":id", res);
        query.bindValue(":id_salle", id_salle);
        query.bindValue(":nom", nom);
        query.bindValue(":localisation", localisation);


        return    query.exec();
}

QSqlQueryModel * Equip_affecte::listeEqAffecter()
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from equipement_affect");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Equip"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Salle"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Localisation"));

        return model;

}
