#ifndef MEDICAMENT_H
#define MEDICAMENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class medicament
{
    private:
    int id,qte;
    QString nom,date_exp,date_fab,type,dosage;

    public :
    medicament();

    medicament(int,QString,QString,QString,QString,QString,int);

    QString get_nom();

    QString get_date_exp();

    QString get_date_fab();

    QString get_type();

    QString get_dosage();

    int get_id();

    int get_Qte();

    void set_nom(QString);

    void set_date_exp(QString);

    void set_date_fab(QString);

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

};

#endif // MEDICAMENT_H
