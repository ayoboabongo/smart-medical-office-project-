#ifndef EQUIP_AFFECTE_H
#define EQUIP_AFFECTE_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Equip_affecte
{
private :
    int id_equip;
    QString id_salle;
    QString nom;
    QString localisation ;
public:
    Equip_affecte();

    Equip_affecte(int,QString,QString,QString);

    bool ajouter_equip() ;

    QSqlQueryModel * listeEqAffecter();
};

#endif // EQUIP_AFFECTE_H
