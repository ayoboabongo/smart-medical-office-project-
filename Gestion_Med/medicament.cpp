#include "medicament.h"
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDate>

/*!
 * \author Ayobo Abongo
 * \file medicament.cpp
 * \date 07/12/2019
 * \version 1.1.1
 */


/*!
 * \brief medicament::medicament
 */
medicament::medicament()
{

}
/*!
 * \brief medicament::medicament
 * \param id
 * \param nom
 * \param date_fab
 * \param date_exp
 * \param type
 * \param dosage
 * \param qte
 * \details Constructeur
 */
medicament::medicament(int id,QString nom,QDate date_fab,QDate date_exp,QString type,QString dosage,int qte)
{
    this->id=id ;
    this->nom=nom;
    this->date_fab=date_fab;
    this->date_exp=date_exp;
    this->type=type;
    this->dosage=dosage;
    this->qte=qte;
}

int medicament::get_id(){return  id;} ;
QString medicament::get_nom(){return  nom ;};
QDate medicament::get_date_exp(){return  date_exp ;};
QDate medicament::get_date_fab(){return  date_fab ;};
QString medicament::get_type(){return  type ;};
QString medicament::get_dosage(){return  dosage ;};
int medicament::get_Qte(){return qte ;};

void medicament::set_id(int ident){this->id=ident;}
void medicament::set_Qte(int qte){this->qte=qte;}
void medicament::set_nom(QString nom){this->nom=nom;}
void medicament::set_date_fab(QDate date1){this->date_fab=date1;}
void medicament::set_date_exp(QDate date2){this->date_exp=date2;}
void medicament::set_type(QString type){this->type=type;}
void medicament::set_dosage(QString dosage){this->dosage=dosage;}

/*!
 * \brief medicament::ajouterMed
 * \return true si l'ajout s'effectue tres bien et false sinon
 * \details permet d'ajouter un nouveau medicament dans la table
 */

bool medicament::ajouterMed()
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString Qte=QString::number(qte);
    query.prepare("INSERT INTO MED (id, nom,date_fab,date_exp,type,dosage,quantite) "
                        "VALUES (:id, :nom, :date_fab,:date_exp,:type,:dosage,:qte)");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":date_fab", date_fab);
    query.bindValue(":date_exp", date_exp);
    query.bindValue(":type", type);
    query.bindValue(":dosage", dosage);
    query.bindValue(":qte",Qte);

    return    query.exec();

}
/*!
 * \brief medicament::updateMed
 * \param id
 * \return true si la modification s'effectue tres bien et false sinon
 *  \details permet de modifier un medicament donne par son id
 */

bool medicament::updateMed(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString Qte=QString::number(qte);
    query.prepare("UPDATE MED set id= :id,nom= :nom,date_fab= :date_fab,date_exp= :date_exp,type= :type,dosage= :dosage,quantite= :qte where id =:id ");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":date_fab", date_fab);
    query.bindValue(":date_exp", date_exp);
    query.bindValue(":type", type);
    query.bindValue(":dosage", dosage);
    query.bindValue(":qte",Qte);

    return    query.exec();

}

/*!
 * \brief medicament::afficherMed
 * \return le modele sql pour l'affichage
 * \details affiche tous les medicaments de la table
 */

QSqlQueryModel * medicament::afficherMed()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from MED");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Fab"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Exp"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Dosage"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Quantite"));
    return model;
}

/*!
  * \brief medicament::afficherMedRechercher
  * \param ident
  * \return le modele sql pour l'affichage
  * \details affiche les medicaments dont les champs sont identiques à la variable passée en parametre
  */
 QSqlQueryModel * medicament::afficherMedRechercher(QString ident)
 {
    QSqlQuery query;

     QSqlQueryModel * model = new QSqlQueryModel();

 model->setQuery("select *from MED where nom like '%"+ident+"%' or id like '%"+ident+"%'  or type like '%"+ident+"%' or date_fab like '%"+ident+"%' or date_exp like '%"+ident+"%' or dosage like '%"+ident+"%' or quantite like '%"+ident+"%' order by nom ");
 query.addBindValue(ident);
 query.exec();
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Fab"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Exp"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("Dosage"));
 model->setHeaderData(6, Qt::Horizontal, QObject::tr("Quantite"));



     return model;

 }

 /*!
   * \brief medicament::listeMed_Exp
   * \return le modele sql
   * \details affiche les medicaments dont les date d'expiration sont deja passées
   */
  QSqlQueryModel * medicament::listeMed_Exp()
  {
     // QDate dat;
      QSqlQuery query;

       QSqlQueryModel * model = new QSqlQueryModel();
   model->setQuery("select *from MED where date_exp <= to_char(sysdate ,'dd/mm/yyyy') ");
  // query.bindValue(":date",dat.currentDate().toString());

   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Fab"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Exp"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("Dosage"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("Quantite"));


   return model;
  }

  /*!
 * \brief medicament::supprimerMed
 * \param idd
 * \return  true si la suppression s'effectue tres bien et false sinon
 *  \details permet de supprimer un medicament donne par son id et ajoute le medicament supprimé dans un fichier txt afin de'en garder l'historiques
 */

bool medicament::supprimerMed(int idd)
{
    QSqlQuery query,qur;
    QDate dater;
    QString res= QString::number(idd);
    QFile file("corbeille.txt") ;
    if(!file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        QMessageBox::information(nullptr, QObject::tr("supprimer un medicament"),
                    QObject::tr("impossible d'ouvrir le corbeille.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {

        QTextStream  out(&file) ;
        qur.prepare("Select *from MED where id = :id ");
        qur.bindValue(":id", res);
        qur.exec();
        out<<"---------------------medicameent supprime------------------------------ "<<endl;
        while(qur.next())
        {
            out<<"Identifiant : "<<qur.value(0).toInt()<<endl << "Nom : "  <<qur.value(1).toString()<<endl <<"Type : "  <<qur.value(4).toString()<<endl<<"Date fab : " <<qur.value(2).toString()<<endl <<"Date exp : "  <<qur.value(3).toString( )<<endl << "Dosage : " <<qur.value(5).toString()<<endl << "Quantite : "<<qur.value(6).toInt()<<endl;
            out<<"date suppression : "<<dater.currentDate().toString() ;
        }
        file.flush() ;
        file.close() ;
    }


    query.prepare("Delete from MED where id = :id ");
    query.bindValue(":id", res);
    return    query.exec();

}

/*!
 * \brief medicament::RechercherMed
 * \param id
 * \return true si le medicament est trouvé sinon false
 * \details recherche un medicament donne par son identifiant
 */
bool medicament::RechercherMed(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("Select *from MED where id = :id ");
    query.bindValue(":id", id);
   // ui->tableRechercheMed->setModel(Med.afficherMedRechercher(id))
    //afficherMedRechercher()
   return    query.exec();

}

bool medicament::RechercherMed(QString nom)
{
    QSqlQuery query;
    query.prepare("Select *from MED where nom = :id ");
    query.bindValue(":id", nom);
   // ui->tableRechercheMed->setModel(Med.afficherMedRechercher(id))
    //afficherMedRechercher()
   return    query.exec();


}


 QSqlQueryModel * medicament::Statisques()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select nom,type, sum(quantite) as qte_total,count(nom) as Nbre_Total from MED group by nom,type ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Qte Totale "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nbre Total "));

    return model;

}

 /*!
  * \brief medicament::getMedicament
  * \param id
  * \return medicament
  * \details recherche un medicament donne par son identifiant
  */
 medicament medicament::getMedicament(int id)
 {
     QSqlQuery query;
     QString res= QString::number(id);
     query.prepare("Select *from MED where id = :id ");
     query.bindValue(":id", res);
     medicament Med ;
     if(query.exec())
     {
         QMessageBox::information(nullptr, QObject::tr("modifier un medicament"),
                     QObject::tr("medicament trouvé.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

         while(query.next())
         {
               Med.set_id(query.value(0).toInt());
               Med.set_nom(query.value(1).toString());
               Med.set_type(query.value(4).toString());
               Med.set_date_fab(query.value(2).toDate());
               Med.set_date_exp(query.value(3).toDate());
               Med.set_dosage(query.value(5).toString());
               Med.set_Qte(query.value(6).toInt());
         }

     }
     else
     {
         QMessageBox::critical(nullptr, QObject::tr("Rechercher un medicament"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

     }

     return Med;
 }
 /*!
  * \brief medicament::verifMed
  * \param id
  * \return true si le medicament existe sinon false
  * \details verifie l'existence d'un medicament
  */

 bool medicament::verifMed(int id)
 {
     bool test=false ;
     QSqlQuery query;
     QString res= QString::number(id);
     query.prepare("Select *from MED where id = :id ");
     query.bindValue(":id", res);
     medicament Med ;
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

