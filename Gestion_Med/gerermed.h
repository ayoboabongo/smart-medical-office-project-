#ifndef GERERMED_H
#define GERERMED_H

#include <QMainWindow>
#include "medicament.h"
#include "equipement_para.h"
#include "equip_affecte_.h"
#include "arduino.h"

namespace Ui {
class GererMed;
}

/*!
 * \author Ayobo Abongo
 * \file geremed.h
 * \date 07/12/2019
 * \version 1.1.1
 * \brief The GererMed class
 * \details la classe GererMed est le widget principal accessible par le Doctor ou autre agent
            elle lui affiche des interfaces permettants de gerer l'ensemble des medicament et des equipements
 */
class GererMed : public QMainWindow
{
    Q_OBJECT

public:
    explicit GererMed(QWidget *parent = nullptr);
    ~GererMed();

private slots:
    void makePlot() ;

    void on_pushButton_ajouter_clicked();

    void on_pushButtonAjouterEquip_clicked();

    void on_pushButton_suppMedi_clicked();

    void on_pushButton_suppEquip_clicked();

    void on_lineEditRechercher_textChanged(const QString &arg1);

    void on_lineEditRechercherEquip_textChanged(const QString &arg1);

    void on_pushButtonActualiserStat_clicked();

    void on_pushButtonR_update_clicked();

    void on_pushButton_UpdateMed_clicked();

    void on_pushButton_rechercherEquip_update_2_clicked();

    void on_pushButton_update_Equip_2_clicked();

    void on_pushButton_consulter_med_exp_clicked();

    void on_pushButton_rechercher_affect_2_clicked();

    void on_pushButton_Affecter_2_clicked();

    void on_pushButton_clicked();

    void on_export_to_doc_clicked();

    void on_pushButton_Exporter_Equip_clicked();

private:
    Ui::GererMed *ui;
    medicament Med;
    equipement_para Eq;
    Equip_affecte Equip ;
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire
};

#endif // GERERMED_H
