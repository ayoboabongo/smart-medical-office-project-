#include "medicament.h"
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>


medicament::medicament()
{
    id=0;
    nom="";
    date_fab="";
    date_exp="";
    type="";
    dosage="";
    qte=0;
}

medicament::medicament(int id,QString nom,QString date_fab,QString date_exp,QString type,QString dosage,int qte)
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
QString medicament::get_date_exp(){return  date_exp ;};
QString medicament::get_date_fab(){return  date_fab ;};
QString medicament::get_type(){return  type ;};
QString medicament::get_dosage(){return  dosage ;};
int medicament::get_Qte(){return qte ;};

void medicament::set_id(int ident){this->id=ident;}
void medicament::set_Qte(int qte){this->qte=qte;}
void medicament::set_nom(QString nom){this->nom=nom;}
void medicament::set_date_fab(QString date1){this->date_fab=date1;}
void medicament::set_date_exp(QString date2){this->date_exp=date2;}
void medicament::set_type(QString type){this->type=type;}
void medicament::set_dosage(QString dosage){this->dosage=dosage;}

bool medicament::ajouterMed()
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString Qte=QString::number(qte);
    query.prepare("INSERT INTO medicament (id, nom,date_fab,date_exp,type,dosage,quantite) "
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

bool medicament::updateMed(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString Qte=QString::number(qte);
    query.prepare("UPDATE medicament set id= :id,nom= :nom,date_fab= :date_fab,date_exp= :date_exp,type= :type,dosage= :dosage,quantite= :qte where id =:id ");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":date_fab", date_fab);
    query.bindValue(":date_exp", date_exp);
    query.bindValue(":type", type);
    query.bindValue(":dosage", dosage);
    query.bindValue(":qte",Qte);

    return    query.exec();

}



QSqlQueryModel * medicament::afficherMed()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from medicament");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Fab"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Exp"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Dosage"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Quantite"));
    return model;
}

 QSqlQueryModel * medicament::afficherMedRechercher(QString ident)
 {
    QSqlQuery query;

     QSqlQueryModel * model = new QSqlQueryModel();

 model->setQuery("select *from medicament where nom like '%"+ident+"%' or id like '%"+ident+"%'  or type like '%"+ident+"%' or date_fab like '%"+ident+"%' or date_exp like '%"+ident+"%' or dosage like '%"+ident+"%' or quantite like '%"+ident+"%' order by nom ");
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

  QSqlQueryModel * medicament::listeMed_Exp()
  {
      QSqlQuery query;

       QSqlQueryModel * model = new QSqlQueryModel();

   model->setQuery("select *from medicament where date_exp like '14-03-2016' order by nom ");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Fab"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Exp"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("Dosage"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("Quantite"));

   return model;
  }

bool medicament::supprimerMed(int idd)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("Delete from medicament where id = :id ");
    query.bindValue(":id", res);
    return    query.exec();

}

bool medicament::RechercherMed(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("Select *from medicament where id = :id ");
    query.bindValue(":id", id);
   // ui->tableRechercheMed->setModel(Med.afficherMedRechercher(id))
    //afficherMedRechercher()
   return    query.exec();

}

bool medicament::RechercherMed(QString nom)
{
    QSqlQuery query;
    query.prepare("Select *from medicament where nom = :id ");
    query.bindValue(":id", nom);
   // ui->tableRechercheMed->setModel(Med.afficherMedRechercher(id))
    //afficherMedRechercher()
   return    query.exec();


}


 QSqlQueryModel * medicament::Statisques()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select nom,type, sum(quantite) as qte_total,count(nom) as Nbre_Total from medicament group by nom,type ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Qte Totale "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nbre Total "));

    return model;

}

 medicament medicament::getMedicament(int id)
 {
     QSqlQuery query;
     QString res= QString::number(id);
     query.prepare("Select *from medicament where id = :id ");
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
               Med.set_date_fab(query.value(2).toString());
               Med.set_date_exp(query.value(3).toString());
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

