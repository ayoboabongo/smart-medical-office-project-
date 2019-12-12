#ifndef EQUIPEMENT_PARA_H
#define EQUIPEMENT_PARA_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

/*!
 * \author Ayobo Abongo
 * \file equipement_para.h
 * \date 07/12/2019
 * \version 1.1.1
 * \brief The equipement_para class
 * \details la classe equipement_para gere a l'aide de ces differentes methodes l'ensembles des
            equipements de 'hopital au sein de notre appli .
 */

class equipement_para
{
private:
int id;
QString nom,localisation;

public :
equipement_para();

equipement_para(int,QString,QString);

QString get_nom();

QString get_localisation();

int get_id();

void set_nom(QString);

void set_localisation(QString);

void set_id(int);

bool ajouterEq();

bool updateEquip(int);

QSqlQueryModel * afficherEquip();

bool supprimerEquip(int idd) ;

bool RechercherEquip(int idd);

bool RechercherEquip_nom(QString idd);

QSqlQueryModel * afficherEqRechercher(QString);

equipement_para getEquipement(int);

bool verifEquip(int) ;
};

#endif // EQUIPEMENT_PARA_H
