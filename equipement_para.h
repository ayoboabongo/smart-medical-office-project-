#ifndef EQUIPEMENT_PARA_H
#define EQUIPEMENT_PARA_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

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
};

#endif // EQUIPEMENT_PARA_H
