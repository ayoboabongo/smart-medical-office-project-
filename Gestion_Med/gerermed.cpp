#include "gerermed.h"
#include "ui_gerermed.h"
#include "equipement_para.h"
#include <QMessageBox>
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "connexion.h"
#include "gerermed.h"
#include "seconnecter.h"
#include <QFile>
#include <QTextStream>
#include <QDate>


/*!
 * \author Ayobo Abongo
 * \file geremed.cpp
 * \date 07/12/2019
 * \version 1.1.1
 */


/*!
 * \brief GererMed::GererMed
 * \param parent
 */
GererMed::GererMed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GererMed)
{
    ui->setupUi(this);
    GererMed::makePlot() ;
    ui->tableEquip->setModel(Eq.afficherEquip());
    ui->table_medicament->setModel(Med.afficherMed());
    ui->tableViewEqAffecter_2->setModel(Equip.listeEqAffecter());
}

GererMed::~GererMed()
{
    delete ui;
}

void GererMed::makePlot()
{
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));



}


/*!
 * \brief GererMed::on_pushButton_ajouter_clicked
 * \return nothing
 * \details la methode ne prend aucun parametres et s'executer à la suite du click du bouton
             ajouter sur l'interface d'ajout
 */
void GererMed::on_pushButton_ajouter_clicked()
{
    // verif champ vide
    if((ui->lineEdit_id->text()=="") || (ui->lineEdit_nom->text()=="")  || (ui->lineEdit_dosage->text()=="") ||(ui->lineEditQuantite->text()==""))
    {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                    QObject::tr("Erreur  Veuillez remplir tous les champs!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
   // verif date valide
    else if (ui->dateFab->date()>=ui->dateExp_2->date()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                    QObject::tr("Erreur  date non valide.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
   // verif identifiant valide et quantite
    else if (ui->lineEdit_id->text().toInt()<=0) {

        QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                    QObject::tr("Erreur  vous aviez entrer un id non valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (ui->lineEditQuantite->text().toInt()<=0) {

        QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                    QObject::tr("Erreur  vous aviez entrer une quantite non valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {
        int id = ui->lineEdit_id->text().toInt();
        QString nom= ui->lineEdit_nom->text();
        QDate date_fab=ui->dateFab->date();
        QDate date_exp=ui->dateExp_2->date() ;
        QString type=ui->comboBox_ajouter->currentText();
        QString dosage=ui->lineEdit_dosage->text() ;
        int qte=ui->lineEditQuantite->text().toInt();

      medicament m(id,nom,date_fab,date_exp,type,dosage,qte);
      bool test=m.ajouterMed();
      if(test)
    {
          ui->table_medicament->setModel(Med.afficherMed());//refresh
          ui->lineEdit_id->setText("") ;
          ui->lineEdit_nom->setText("") ;
          ui->lineEdit_dosage->setText("") ;
          ui->lineEditQuantite->setText("");

    QMessageBox::information(nullptr, QObject::tr("Ajouter un medicament"),
                      QObject::tr("medicament ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

/*!
 * \brief GererMed::on_pushButtonAjouterEquip_clicked
 * \return nothing
 * \details  la methode ne prend aucun parametres et s'executer à la suite du click du bouton
             ajouter sur l'interface d'ajout
 */

void GererMed::on_pushButtonAjouterEquip_clicked()
{
    // verif champ vide
    if((ui->lineEdit_idEquip->text()=="")||(ui->lineEdit_nomEquip->text()=="")||(ui->lineEdit_localisation->text()==""))
    {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un equipement"),
                    QObject::tr("Erreur  Veuillez remplir tous les champs!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
  // id non valide
    else if (ui->lineEdit_idEquip->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un equipement"),
                    QObject::tr("Erreur  vous aviez entrer un id negatif!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else {
    int id = ui->lineEdit_idEquip->text().toInt();
    QString nom= ui->lineEdit_nomEquip->text();
    QString localisation=ui->lineEdit_localisation->text();


  equipement_para Eq(id,nom,localisation);
  bool test=Eq.ajouterEq();
  if(test)
{
      ui->tableEquip->setModel(Eq.afficherEquip());//refresh
      ui->lineEdit_idEquip->setText("") ;
      ui->lineEdit_nomEquip->setText("") ;
      ui->lineEdit_localisation->setText("");
QMessageBox::information(nullptr, QObject::tr("Ajouter un equipement para"),
                  QObject::tr("equipement ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un equipement para"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

/*!
 * \brief GererMed::on_pushButton_suppMedi_clicked
 * \return nothing
 * \details la methode ne prend aucun parametres et s'executer à la suite du click du bouton
            supprimer sur l'interface de suppression
            elle permet de supprimer s'il trouve un medicament donné par son identifiant
            l'identifiant est démande à l'utilisateur
            elle fait appel à la fonction \fn bool verif=Med.verifMed(ui->lineEdit_id_supMed->text().toInt())
            pour verifier l'existence du medicament
 */

void GererMed::on_pushButton_suppMedi_clicked()
{
    bool verif=Med.verifMed(ui->lineEdit_id_supMed->text().toInt()) ;
    if(ui->lineEdit_id_supMed->text()=="")
    {
        QMessageBox::critical(nullptr, QObject::tr("supprimer un medicament"),
                    QObject::tr("Erreur , veuillez entrer l'identifiant du medicament à supprimer !!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (ui->lineEdit_id_supMed->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("supprimer un medicament"),
                    QObject::tr("Erreur ,vous aviez entré un identifiant non valide!!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }  
    else if (verif==false) {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un medicament"),
                    QObject::tr("Erreur , Medicament non trouvé , veuillez entrer l'identifiant valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {

    int id = ui->lineEdit_id_supMed->text().toInt();
    bool test=Med.supprimerMed(id);
    if(test)
    {ui->table_medicament->setModel(Med.afficherMed());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un medicament"),
                    QObject::tr("medicament supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    }


}

/*!
 * \brief GererMed::on_pushButton_suppEquip_clicked
 * \return nothing
 * \details la methode ne prend aucun parametres et s'executer à la suite du click du bouton
           supprimer sur l'interface de suppression
           elle permet de supprimer s'il trouve un equipement donné par son identifiant
           l'identifiant est démande à l'utilisateur
           elle fait appel à la fonction \fn bool verif = Eq.verifEquip(ui->lineEdit_id_supEquip->text().toInt())
           pour verifier l'existence de l'equipement
 */

void GererMed::on_pushButton_suppEquip_clicked()
{
    bool verif = Eq.verifEquip(ui->lineEdit_id_supEquip->text().toInt()) ;

    if(ui->lineEdit_id_supEquip->text()=="")
    {
        QMessageBox::critical(nullptr, QObject::tr("supprimer un equipement"),
                    QObject::tr("Erreur , veuillez entrer l'identifiant de l'equipement à supprimer !!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

    else if (ui->lineEdit_id_supEquip->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("supprimer un equipement"),
                    QObject::tr("Erreur ,vous aviez entré un identifiant non valide!!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (verif==false) {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un equipement"),
                    QObject::tr("Erreur , Equipement non trouvé , veuillez un identifiant valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {


    int id = ui->lineEdit_id_supEquip->text().toInt();
    bool test=Eq.supprimerEquip(id);
    if(test)
    {ui->tableEquip->setModel(Eq.afficherEquip());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un equipement"),
                    QObject::tr("equipement supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

  }

}

/*!
 * \brief GererMed::on_lineEditRechercher_textChanged
 * \param arg1
 * \return nothing
 * \details la methode permet de rechercher un medicament dans la table
            elle prend en parametrer un \a arg qui n'est autre que le text entré dans la barre de recherche
            elle fait appel à la \fn ui->tableRechercheMed->setModel(Med.afficherMedRechercher(arg1));
            pour afficher les medicaments trouvés
 */

void GererMed::on_lineEditRechercher_textChanged(const QString &arg1)
{
     ui->tableRechercheMed->setModel(Med.afficherMedRechercher(arg1));
}

/*!
 * \brief GererMed::on_lineEditRechercherEquip_textChanged
 * \param arg1
 * \return nothing
 * \details  la methode permet de rechercher un equipement dans la table
             elle prend en parametrer un \a arg qui n'est autre que le text entré dans la barre de recherche
             elle fait appel à la \fn ui->tableRechercherEquip->setModel(Eq.afficherEqRechercher(arg1));
             pour afficher les equipements trouvés
 */
void GererMed::on_lineEditRechercherEquip_textChanged(const QString &arg1)
{
    ui->tableRechercherEquip->setModel(Eq.afficherEqRechercher(arg1));
}


//statistiques

void GererMed::on_pushButtonActualiserStat_clicked()
{
    ui->tableStat->setModel(Med.Statisques());
    QMessageBox::information(nullptr, QObject::tr("Statistiques"),
                QObject::tr("Statistiques effectuee.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

/*!
 * \brief GererMed::on_pushButtonR_update_clicked
 * \return nothing
 * \details la methode permet de rechercher un medicament dans la table afin de le  modifier
            elle est executée a la suite du click du boutton rechercher de modification
            Elle fait appel à la \fn m=Med.getMedicament(id) apres avoir trouvé afin de recupperer ces informations et les mettres sur l'interface de modification
 */
void GererMed::on_pushButtonR_update_clicked()
{
     bool verif=Med.verifMed(ui->lineEdit_id_to_update->text().toInt()) ;
    if(ui->lineEdit_id_to_update->text()=="")
    {
        QMessageBox::critical(nullptr, QObject::tr("modifier un medicament"),
                    QObject::tr("Erreur , veuillez entrer l'identifiant de l'equipement à modifier !!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (ui->lineEdit_id_to_update->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("modifier un medicament"),
                    QObject::tr("Erreur ,vous aviez entré un identifiant non valide!!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (verif==false) {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un medicament"),
                    QObject::tr("Erreur , Medicament non trouvé , veuillez entrer l'identifiant valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {
        int id = ui->lineEdit_id_to_update->text().toInt();
        medicament m ;
        m=Med.getMedicament(id) ;

                 ui->lineEdit_update_id->setText(ui->lineEdit_id_to_update->text());
                 ui->lineEdit_update_nom->setText( m.get_nom());
                 ui->comboBox_update->setCurrentText(m.get_type());
                 ui->dateEdit_update_fab->setDate((m.get_date_fab()))  ;
                 ui->dateEdit_2_update_exp->setDate((m.get_date_exp()));
                 ui->lineEdit_update_dosage->setText(m.get_dosage());
               //  ui->lineEdit_update_quantite->setText(m.get_Qte().toString());
            }

}


/*!
 * \brief GererMed::on_pushButton_UpdateMed_clicked
 * \return nothing
 * \details la methode permet de modifier ou metter a jour les informations d'un medicament
            apres le click du boutton update sur l'intreface de modification
 */
void GererMed::on_pushButton_UpdateMed_clicked()
{
    bool verif=Med.verifMed(ui->lineEdit_id_to_update->text().toInt()) ;
    if(( ui->lineEdit_update_id->text()=="") || (ui->lineEdit_update_nom->text()=="")  || (ui->lineEdit_update_dosage->text()=="") ||(ui->lineEdit_update_quantite->text()==""))
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier un medicament"),
                    QObject::tr("Erreur  Veuillez completez tous les champs!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

    else if (ui->dateEdit_update_fab->date()>=ui->dateEdit_2_update_exp->date()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                    QObject::tr("Erreur  date non valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

    else if (ui->lineEdit_update_id->text().toInt()<=0)  {

        QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                    QObject::tr("Erreur  vous aviez entrer un id non valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if  (ui->lineEdit_update_quantite->text().toInt()<=0) {

        QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                    QObject::tr("Erreur  vous aviez entrer une quantite non valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if (verif==false) {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un medicament"),
                    QObject::tr("Erreur , Medicament non trouvé , veuillez entrer l'identifiant valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {
        int id = ui->lineEdit_update_id->text().toInt();
        QString nom= ui->lineEdit_update_nom->text();
        QDate date_fab=ui->dateEdit_update_fab->date() ;
        QDate date_exp=ui->dateEdit_2_update_exp->date();
        QString type=ui->comboBox_update->currentText() ;
        QString dosage=ui->lineEdit_update_dosage->text() ;
        int qte=ui->lineEdit_update_quantite->text().toInt();



      medicament m(id,nom,date_fab,date_exp,type,dosage,qte);
      bool test=m.updateMed(id);
      if(test)
    {
          ui->table_medicament->setModel(Med.afficherMed());//refresh
          ui->lineEdit_update_id->setText("") ;
          ui->lineEdit_update_nom->setText("") ;
          ui->lineEdit_update_dosage->setText("") ;
          ui->lineEdit_update_quantite->setText("") ;
    QMessageBox::information(nullptr, QObject::tr("update medicament"),
                      QObject::tr("medicament mis a jour.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }

    }


}

/*!
 * \brief GererMed::on_pushButton_rechercherEquip_update_2_clicked
 * \return nothing
 * \details la methode permet de rechercher un equipement dans la table afin de le  modifier
            elle est executée a la suite du click du boutton  rechercher de modification
            Elle fait appel à la \fn  E=E.getEquipement(id); apres avoir trouvé afin de recupperer ces informations et les mettres sur l'interface de modification

 */

void GererMed::on_pushButton_rechercherEquip_update_2_clicked()
{
    bool verif = Eq.verifEquip(ui->lineEdit_id_rechercheEquip_2->text().toInt()) ;
    if( ui->lineEdit_id_rechercheEquip_2->text()=="")
    {
        QMessageBox::critical(nullptr, QObject::tr("modifier un equipement"),
                    QObject::tr("Erreur , veuillez entrer l'identifiant de l'equipement à modifier !!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (ui->lineEdit_id_rechercheEquip_2->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("modifier un equipement"),
                    QObject::tr("Erreur ,vous aviez entré un identifiant non valide!!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if (verif==false) {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un equipement"),
                    QObject::tr("Erreur , Equipement non trouvé , veuillez un identifiant valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }


    else {
        int id = ui->lineEdit_id_rechercheEquip_2->text().toInt();
        equipement_para E ;
            E=E.getEquipement(id);

                 ui->lineEdit_id_update_Eq_2->setText(ui->lineEdit_id_rechercheEquip_2->text());
                 ui->lineEdit_nom_update_Eq_2->setText(E.get_nom());
                 ui->lineEdit_localisation_update_Eq_2->setText(E.get_localisation());
    }

}


/*!
 * \brief GererMed::on_pushButton_update_Equip_2_clicked
 * \return nothing
 * \details la methode permet de modifier ou metter a jour les informations d'un equipement
            apres le click du boutton update sur l'intreface de modification
 */
void GererMed::on_pushButton_update_Equip_2_clicked()
{
     bool verif = Eq.verifEquip(ui->lineEdit_id_rechercheEquip_2->text().toInt()) ;
    if(( ui->lineEdit_id_update_Eq_2->text()=="")||(ui->lineEdit_nom_update_Eq_2->text()=="")||(ui->lineEdit_localisation_update_Eq_2->text()==""))
    {
        QMessageBox::critical(nullptr, QObject::tr("update  equipement"),
                    QObject::tr("Erreur  Veuillez completez tous les champs!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (ui->lineEdit_id_update_Eq_2->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("update  equipement"),
                    QObject::tr("Erreur  vous aviez entrer un id negatif!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if (verif==false) {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un equipement"),
                    QObject::tr("Erreur , Equipement non trouvé , veuillez un identifiant valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {
        int id = ui->lineEdit_id_update_Eq_2->text().toInt();
        QString nom= ui->lineEdit_nom_update_Eq_2->text();
        QString localisation=ui->lineEdit_localisation_update_Eq_2->text();


      equipement_para Eq(id,nom,localisation);
      bool test=Eq.updateEquip(id);
      if(test)
    {
          ui->tableEquip->setModel(Eq.afficherEquip());//refresh
          ui->lineEdit_id_update_Eq_2->setText("") ;
          ui->lineEdit_nom_update_Eq_2->setText("") ;
          ui->lineEdit_localisation_update_Eq_2->setText("") ;
    QMessageBox::information(nullptr, QObject::tr("modifier un equipement para"),
                      QObject::tr("equipement mis a jour.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
   }


}

/*!
 * \brief GererMed::on_pushButton_consulter_med_exp_clicked
 * \return nothing
 * \details la methode permet de consulter tous les medicaments expirés dans la table
            apres le click du boutton consulter sur l'intreface de medicament expirés
            l'affichage se fait grace à \fn ui->tableViewMedicament_exp->setModel(Med.listeMed_Exp());
 */
void GererMed::on_pushButton_consulter_med_exp_clicked()
{
     ui->tableViewMedicament_exp->setModel(Med.listeMed_Exp());
}

/*!
 * \brief GererMed::on_pushButton_rechercher_affect_2_clicked
 * \return nothing
 * \details  la methode permet de rechercher un equipement dans la table afin de l'e  modifier'affecter
             elle est executée a la suite du click du boutton de rechercher de l'affectation
             Elle fait appel à la \fn  E=E.getEquipement(id); apres avoir trouvé afin de recupperer ces informations et les mettres sur l'interface d'e modification'affectation

 */
void GererMed::on_pushButton_rechercher_affect_2_clicked()
{
     bool verif = Eq.verifEquip(ui->lineEditRechercher_affect_2->text().toInt()) ;
    if( ui->lineEditRechercher_affect_2->text()=="")
    {
        QMessageBox::critical(nullptr, QObject::tr("Affecter un equipement"),
                    QObject::tr("Erreur , veuillez entrer l'identifiant de l'equipement à affecter !!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (ui->lineEditRechercher_affect_2->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("Affecter un equipement"),
                    QObject::tr("Erreur ,vous aviez entré un identifiant non valide!!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (verif==false) {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un equipement"),
                    QObject::tr("Erreur , Equipement non trouvé , veuillez un identifiant valide!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {
        int id = ui->lineEditRechercher_affect_2->text().toInt();
        equipement_para E ;
            E=E.getEquipement(id);

                 ui->lineEdit_id_eq_affect_2->setText(ui->lineEditRechercher_affect_2->text());
                 ui->lineEdit_nom_eq_affect_2->setText(E.get_nom());
                 ui->lineEdit_localisation_eq_affect_2->setText(E.get_localisation());
    }

}

/*!
 * \brief GererMed::on_pushButton_Affecter_2_clicked
 * \return nothing
 * \details la methode permet d'e modifier ou metter a jour'affecter un equipement à une salle
            apres le click du boutton affecter  sur l'intreface d'affectation
            elle fait egalement appel à \fn bool sup= Eq.supprimerEquip(id_eq); pour supprimer l'equipement à affecter
            et à \fn bool test=Equip.ajouter_equip(); pour ajouter à la table d'affectation
 */
void GererMed::on_pushButton_Affecter_2_clicked()
{
    if((ui->lineEdit_id_eq_affect_2->text()=="")||(ui->lineEdit_nom_eq_affect_2->text()=="")||(ui->lineEdit_localisation_eq_affect_2->text()=="")||(ui->lineEdit_id_salle_affect_2->text()==""))
    {
        QMessageBox::critical(nullptr, QObject::tr("Affecter un equipement"),
                    QObject::tr("Erreur  Veuillez completez  tous les champs!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (ui->lineEdit_id_eq_affect_2->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("Affecter un equipement"),
                    QObject::tr("Erreur  vous aviez entrer un id negatif!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else {
    int id_eq = ui->lineEdit_id_eq_affect_2->text().toInt();
    QString id_salle=ui->lineEdit_id_salle_affect_2->text();
    QString nom= ui->lineEdit_nom_eq_affect_2->text();
    QString localisation=ui->lineEdit_localisation_eq_affect_2->text();

      Equip_affecte Equip(id_eq,id_salle,nom,localisation);


  bool test=Equip.ajouter_equip();
  bool sup= Eq.supprimerEquip(id_eq);
  if(test)
{
      ui->tableViewEqAffecter_2->setModel(Equip.listeEqAffecter());//refresh
      ui->lineEdit_id_eq_affect_2->setText("") ;
      ui->lineEdit_id_salle_affect_2->setText("");
      ui->lineEdit_nom_eq_affect_2->setText("") ;
      ui->lineEdit_localisation_eq_affect_2->setText("");
QMessageBox::information(nullptr, QObject::tr("Affecter un equipement para"),
                  QObject::tr("equipement affecté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Affecter un equipement para"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

/*!
 * \brief GererMed::on_pushButton_clicked
 * \return nothing
 * \details  cette methode permet de se deconnecter et ramene l'utilisateur sur l'interface principale d'authentification
 */

void GererMed::on_pushButton_clicked()
{
    hide();
    SeConnecter *S;
    S=new SeConnecter;
    S->showFullScreen() ;

}

/*!
 * \brief GererMed::on_export_to_doc_clicked
 * \return nothing
 * \details cette methode permet d'exporter tous les medicaments de la table vers un fichier
             medicament.txt
            evidement apres click du bouton Export to doc sur l'interface d'affichage
 */
void GererMed::on_export_to_doc_clicked()
{
    QSqlQuery qur;
    QFile file("medicament.txt") ;
    if(!file.open(QFile::WriteOnly | QFile::Text ))
    {
        QMessageBox::information(nullptr, QObject::tr("Exporter  medicaments"),
                    QObject::tr("impossible d'ouvrir le fichier medicament.txt .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {

        QTextStream  out(&file) ;
        qur.prepare("Select *from MED ");
        qur.exec();
        out<<"---------------------liste medicameent------------------------------ "<<endl;
        int i=1 ;
        while(qur.next())
        {
            out<<"-------medicameent : "<<i<<"-------------- "<<endl;
            out<<"Identifiant : "<<qur.value(0).toInt()<<endl << "Nom : "  <<qur.value(1).toString()<<endl <<"Type : "  <<qur.value(4).toString()<<endl<<"Date fab : " <<qur.value(2).toString()<<endl <<"Date exp : "  <<qur.value(3).toString( )<<endl << "Dosage : " <<qur.value(5).toString()<<endl << "Quantite : "<<qur.value(6).toInt()<<endl;
            i++ ;
        }
        //file.flush() ;
        file.close() ;
        QMessageBox::information(nullptr, QObject::tr("Exporter medicaments"),
                    QObject::tr("Tous les medicaments exportés vers medicament.txt .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

/*!
 * \brief GererMed::on_pushButton_Exporter_Equip_clicked
 * \return nothing
 * \details cette methode permet d'exporter tous les equipements de la table vers un fichier
            equipements.txt
            evidement apres click du bouton Export to doc sur l'interface d'affichage
 */
void GererMed::on_pushButton_Exporter_Equip_clicked()
{
    QSqlQuery qur;
    QFile file("equipement.txt") ;
    if(!file.open(QFile::WriteOnly | QFile::Text ))
    {
        QMessageBox::information(nullptr, QObject::tr("Exporter  equipements"),
                    QObject::tr("impossible d'ouvrir le fichier equipement.txt .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {

        QTextStream  out(&file) ;
        qur.prepare("Select *from equipement ");
        qur.exec();
        out<<"---------------------liste equipement------------------------------ "<<endl;
        int i=1 ;
        while(qur.next())
        {
            out<<"-------equipement : "<<i<<"-------------- "<<endl;
            out<<"Identifiant : "<<qur.value(0).toInt()<<endl << "Nom : "  <<qur.value(1).toString()<<endl <<"Localisation : "  <<qur.value(2).toString()<<endl;
            i++ ;
        }
        //file.flush() ;
        file.close() ;
        QMessageBox::information(nullptr, QObject::tr("Exporter equipements"),
                    QObject::tr("Tous les equipements exportés vers equipement.txt .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }


}
