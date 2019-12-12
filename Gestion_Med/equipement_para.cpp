#include "equipement_para.h"
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFile>
#include <QDate>
#include <QTextStream>



/*!
 * \author Ayobo Abongo
 * \file equipement_para.cpp
 * \date 07/12/2019
 * \version 1.1.1
 */

equipement_para::equipement_para()
{
    id=0;
    nom="";
    localisation="";

}

/*!
 * \brief equipement_para::equipement_para
 * \param id
 * \param nom
 * \param localisation
 * \details Constructeur
 */
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

/*!
 * \brief equipement_para::ajouterEq
 * \return true si l'ajout s'effectue tres bien et false sinon
 * \details permet d'ajouter un nouveau equipement dans la table
 */
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

/*!
 * \brief equipement_para::updateEquip
 * \param id
 * \return true si la modification s'effectue tres bien et false sinon
 *  \details permet de modifier un equipement donne par son id
 */

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

/*!
 * \brief equipement_para::afficherEquip
 * \return le modele sql pour l'affichage
 * \details affiche tous les equipements de la table
 */

QSqlQueryModel * equipement_para ::afficherEquip()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from equipement");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Localisation"));

    return model;
}

/*!
 * \brief equipement_para::supprimerEquip
 * \param idd
 * \return true si la suppression s'effectue tres bien et false sinon
 *  \details permet de supprimer un equipement donné par son id et ajoute l'equipement supprimé dans un fichier txt afin de'en garder l'historiques
 */
bool equipement_para::supprimerEquip(int idd)
{
    QSqlQuery query,qur;
    QString res= QString::number(idd);
    QDate dater;
    QFile file("corbeille_equip.txt") ;
    if(!file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        QMessageBox::information(nullptr, QObject::tr("supprimer un equipement"),
                    QObject::tr("impossible d'ouvrir le corbeille.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {

        QTextStream  out(&file) ;
        qur.prepare("Select *from equipement where id = :id ");
        qur.bindValue(":id", res);
        qur.exec();
        out<<"---------------------equipement supprime------------------------------ "<<endl;
        while(qur.next())
        {
            out<<"Identifiant : "<<qur.value(0).toInt()<<endl << "Nom : "  <<qur.value(1).toString()<<endl <<"Localisation : "  <<qur.value(2).toString()<<endl;
            out<<"date suppression : "<<dater.currentDate().toString() ;
        }
        file.flush() ;
        file.close() ;
    }
    query.prepare("Delete from equipement where id = :id ");
    query.bindValue(":id", res);
    return    query.exec();

}

/*!
 * \brief equipement_para::RechercherEquip
 * \param idd
 * \return true s'il trouve l'equipement sinon false
 * \details recherche un equipement donné par som identifiant
 */
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

/*!
 * \brief equipement_para::afficherEqRechercher
 * \param ident
 * \return le modele sql pour l'affichage
  * \details affiche les equipements dont les champs sont identiques à la variable passée en parametre
 */
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

/*!
 * \brief equipement_para::getEquipement
 * \param id
 * \return equipement_para
  * \details recherche un equipement donné par son identifiant
 */

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

/*!
 * \brief equipement_para::verifEquip
 * \param id
 * \return true si le medicament existe sinon false
  * \details verifie l'existence d'un medicament
 */
bool equipement_para::verifEquip(int id)
{
    bool test=false ;
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("Select *from equipement where id = :id ");
    query.bindValue(":id", res);
    if(query.exec())
    {
       while(query.next())
        {
           if(id==query.value(0).toInt())
           {
               test=true ;
           }

        }

    }

    return  test ;
}
