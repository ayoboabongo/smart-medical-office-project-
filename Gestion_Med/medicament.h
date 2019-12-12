#ifndef MEDICAMENT_H
#define MEDICAMENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>


/*!
 * \author Ayobo Abongo
 * \file medicament.h
 * \date 07/12/2019
 * \version 1.1.1
 * \brief The medicament class
 * \details la classe medicament gere a l'aide de ces differentes methodes l'ensembles des
           medicaments de 'hopital au sein de notre appli .
 */
class medicament
{
    private:
    int id,qte;
    QString nom,type,dosage;
    QDate date_exp,date_fab;

    public :
    medicament();

    medicament(int,QString,QDate,QDate,QString,QString,int);

    QString get_nom();

    QDate get_date_exp();

    QDate get_date_fab();

    QString get_type();

    QString get_dosage();

    int get_id();

    int get_Qte();

    void set_nom(QString);

    void set_date_exp(QDate);

    void set_date_fab(QDate);

    void set_type(QString);

    void set_dosage(QString);

    void set_id(int);

    void set_Qte(int);

    bool ajouterMed();

    bool updateMed(int);

    QSqlQueryModel * afficherMed();

     QSqlQueryModel * afficherMedRechercher(QString);

    bool supprimerMed(int) ;

   bool RechercherMed(int);

   bool RechercherMed(QString);

   QSqlQueryModel * Statisques();

   QSqlQueryModel * listeMed_Exp();

   medicament getMedicament(int);

   bool verifMed(int);

};

#endif // MEDICAMENT_H
