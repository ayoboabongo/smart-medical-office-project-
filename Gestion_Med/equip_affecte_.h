#ifndef EQUIP_AFFECTE_H
#define EQUIP_AFFECTE_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

/*!
 * \author Ayobo Abongo
 * \file equip_affecte.h
 * \date 07/12/2019
 * \version 1.1.1
 * \brief The Equip_affecte class
 * \details la classe Equip_affecte gere a l'aide de ces differentes methodes l'ensembles des
            equipements affectes a de salles  de 'hopital au sein de notre appli .
 */
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
