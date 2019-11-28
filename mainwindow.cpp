#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipement_para.h"
#include <QMessageBox>
#include <QSound>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableEquip->setModel(Eq.afficherEquip());
    ui->table_medicament->setModel(Med.afficherMed());
    ui->tableViewEqAffecter->setModel(Equip.listeEqAffecter());

}

MainWindow::~MainWindow()
{
    delete ui;
}

//medicament
// fonction permettant d'ajouter un medicament a la table apres click du bouton ajouter du GUI
void MainWindow::on_pushButton_ajouter_clicked()
{

    if((ui->lineEdit_id->text()=="") || (ui->lineEdit_nom->text()=="") || (ui->lineEdit_datefab->text()=="") || (ui->lineEdit_dateexp->text()=="" )|| (ui->lineEdit_type->text()=="") || (ui->lineEdit_dosage->text()=="") ||(ui->lineEditQuantite->text()==""))
    {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                    QObject::tr("Erreur  Veuillez remplir tous les champs!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

    else if ((ui->lineEdit_id->text().toInt()<=0) || (ui->lineEditQuantite->text().toInt()<=0)) {

        QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                    QObject::tr("Erreur  vous aviez entrer un id ou une quantite negative!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {
        int id = ui->lineEdit_id->text().toInt();
        QString nom= ui->lineEdit_nom->text();
        QString date_fab=ui->lineEdit_datefab->text() ;
        QString date_exp=ui->lineEdit_dateexp->text() ;
        QString type=ui->lineEdit_type->text() ;
        QString dosage=ui->lineEdit_dosage->text() ;
        int qte=ui->lineEditQuantite->text().toInt();

      medicament m(id,nom,date_fab,date_exp,type,dosage,qte);
      bool test=m.ajouterMed();
      if(test)
    {ui->table_medicament->setModel(Med.afficherMed());//refresh
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

//equipement
// fonction permettant d'ajouter un equipement a la table apres click du bouton ajouter du GUI
void MainWindow::on_pushButtonAjouterEquip_clicked()
{

    if((ui->lineEdit_idEquip->text()=="")||(ui->lineEdit_nomEquip->text()=="")||(ui->lineEdit_localisation->text()==""))
    {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un equipement"),
                    QObject::tr("Erreur  Veuillez remplir tous les champs!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

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
{ui->tableEquip->setModel(Eq.afficherEquip());//refresh
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


// suppression d'un medicament donné par son id entrer au niveau du GUI
void MainWindow::on_pushButton_suppMedi_clicked()
{
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

    else {

    int id = ui->lineEdit_id_supMed->text().toInt();
    bool test=Med.supprimerMed(id);
    if(test)
    {ui->table_medicament->setModel(Med.afficherMed());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un medicament"),
                    QObject::tr("medicament supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un medicament"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }

}

// suppression d'un equipement para-medical donné par son id entrer au niveau du GUI
void MainWindow::on_pushButton_suppEquip_clicked()
{
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

    else {


    int id = ui->lineEdit_id_supEquip->text().toInt();
    bool test=Eq.supprimerEquip(id);
    if(test)
    {ui->tableEquip->setModel(Eq.afficherEquip());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un equipement"),
                    QObject::tr("equipement supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un equipement"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



      }

}
/*
void MainWindow::on_pushButtonRechercherMed_clicked()
{
    QString nom = ui->lineEditRechercher->text();
   // QString id = ui->lineEditRechercher->text();
    bool test=Med.RechercherMed(nom);
    if(test)
    {ui->tableRechercheMed->setModel(Med.afficherMedRechercher(nom));//refresh
        QMessageBox::information(nullptr, QObject::tr("Rechercher un medicament"),
                    QObject::tr("medicament trouvé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Rechercher un medicament"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}*/
/*
void MainWindow::on_pushButtonRechercherEquip_clicked()
{
    QString id = ui->lineEditRechercherEquip->text();
    bool test=Eq.RechercherEquip_nom(id);
    if(test)
    {ui->tableRechercherEquip->setModel(Eq.afficherEqRechercher(id));//refresh
        QMessageBox::information(nullptr, QObject::tr("Rechercher un equipement"),
                    QObject::tr("equipement trouvé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Rechercher un equipement"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}*/

void MainWindow::on_pushButtonActualiserStat_clicked()
{
        ui->tableStat->setModel(Med.Statisques());
        QMessageBox::information(nullptr, QObject::tr("Statistiques"),
                    QObject::tr("Statistiques effectuee.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


//recherche et affichage d'un medicament donné par son identifiant  pour effectuer la  modification
void MainWindow::on_pushButton_clicked()
{
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

    else {
        int id = ui->lineEdit_id_to_update->text().toInt();
        medicament m ;
        m=Med.getMedicament(id) ;

                 ui->lineEdit_update_id->setText(ui->lineEdit_id_to_update->text());
                 ui->lineEdit_update_nom->setText( m.get_nom());
                 ui->lineEdit_update_type->setText(m.get_type());
                 ui->lineEdit_update_datef->setText(m.get_date_fab());
                 ui->lineEdit_update_dateexp->setText(m.get_date_exp());
                 ui->lineEdit_update_dosage->setText(m.get_dosage());
               //  ui->lineEdit_update_quantite->setText(m.get_Qte().toString());
            }

}


// fonction de mis a jour d'un medicament donné par son identifiant
void MainWindow::on_pushButton_UpdateMed_clicked()
{
    if(( ui->lineEdit_update_id->text()=="") || (ui->lineEdit_update_nom->text()=="") || (ui->lineEdit_update_datef->text()=="") || (ui->lineEdit_update_dateexp->text()=="" )|| (ui->lineEdit_update_type->text()=="") || (ui->lineEdit_update_dosage->text()=="") ||(ui->lineEdit_update_quantite->text()==""))
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier un medicament"),
                    QObject::tr("Erreur  Veuillez completez tous les champs!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

    else if ((ui->lineEdit_update_id->text().toInt()<=0) || (ui->lineEdit_update_quantite->text().toInt()<=0)) {

        QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                    QObject::tr("Erreur  vous aviez entrer un id ou une quantite negative!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {
        int id = ui->lineEdit_update_id->text().toInt();
        QString nom= ui->lineEdit_update_nom->text();
        QString date_fab=ui->lineEdit_update_datef->text() ;
        QString date_exp=ui->lineEdit_update_dateexp->text() ;
        QString type=ui->lineEdit_update_type->text() ;
        QString dosage=ui->lineEdit_update_dosage->text() ;
        int qte=ui->lineEdit_update_quantite->text().toInt();



      medicament m(id,nom,date_fab,date_exp,type,dosage,qte);
      bool test=m.updateMed(id);
      if(test)
    {ui->table_medicament->setModel(Med.afficherMed());//refresh
    QMessageBox::information(nullptr, QObject::tr("update medicament"),
                      QObject::tr("medicament mis a jour.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("update medicament"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }


}

//recherche et affichage d'un equipement donné par son identifiant  pour effectuer la  modification

void MainWindow::on_pushButton_rechercherEquip_update_clicked()
{
    if( ui->lineEdit_id_rechercheEquip->text()=="")
    {
        QMessageBox::critical(nullptr, QObject::tr("modifier un equipement"),
                    QObject::tr("Erreur , veuillez entrer l'identifiant de l'equipement à modifier !!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (ui->lineEdit_id_rechercheEquip->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("modifier un equipement"),
                    QObject::tr("Erreur ,vous aviez entré un identifiant non valide!!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {
        int id = ui->lineEdit_id_rechercheEquip->text().toInt();
        equipement_para E ;
            E=E.getEquipement(id);

                 ui->lineEdit_id_update_Eq->setText(ui->lineEdit_id_rechercheEquip->text());
                 ui->lineEdit_nom_update_Eq->setText(E.get_nom());
                 ui->lineEdit_localisation_update_Eq->setText(E.get_localisation());
    }



}

// fonction de mis a jour d'un equipement donné par son identifiant

void MainWindow::on_pushButton_update_Equip_clicked()
{
    if(( ui->lineEdit_id_update_Eq->text()=="")||(ui->lineEdit_nom_update_Eq->text()=="")||(ui->lineEdit_localisation_update_Eq->text()==""))
    {
        QMessageBox::critical(nullptr, QObject::tr("update  equipement"),
                    QObject::tr("Erreur  Veuillez completez tous les champs!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (ui->lineEdit_id_update_Eq->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("update  equipement"),
                    QObject::tr("Erreur  vous aviez entrer un id negatif!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {
        int id = ui->lineEdit_id_update_Eq->text().toInt();
        QString nom= ui->lineEdit_nom_update_Eq->text();
        QString localisation=ui->lineEdit_localisation_update_Eq->text();


      equipement_para Eq(id,nom,localisation);
      bool test=Eq.updateEquip(id);
      if(test)
    {ui->tableEquip->setModel(Eq.afficherEquip());//refresh
    QMessageBox::information(nullptr, QObject::tr("modifier un equipement para"),
                      QObject::tr("equipement mis a jour.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("modifier un equipement para"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }



}

void MainWindow::on_lineEditRechercherEquip_textChanged(const QString &arg1)
{
     ui->tableRechercherEquip->setModel(Eq.afficherEqRechercher(arg1));
}

void MainWindow::on_lineEditRechercher_textChanged(const QString &arg1)
{
    ui->tableRechercheMed->setModel(Med.afficherMedRechercher(arg1));
}

void MainWindow::on_pushButton_consulter_med_exp_clicked()
{
  ui->tableViewMedicament_exp->setModel(Med.listeMed_Exp());
}

void MainWindow::on_pushButton_rechercher_affect_clicked()
{
    if( ui->lineEditRechercher_affect->text()=="")
    {
        QMessageBox::critical(nullptr, QObject::tr("Affecter un equipement"),
                    QObject::tr("Erreur , veuillez entrer l'identifiant de l'equipement à affecter !!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (ui->lineEditRechercher_affect->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("Affecter un equipement"),
                    QObject::tr("Erreur ,vous aviez entré un identifiant non valide!!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {
        int id = ui->lineEditRechercher_affect->text().toInt();
        equipement_para E ;
            E=E.getEquipement(id);

                 ui->lineEdit_id_eq_affect->setText(ui->lineEditRechercher_affect->text());
                 ui->lineEdit_nom_eq_affect->setText(E.get_nom());
                 ui->lineEdit_localisation_eq_affect->setText(E.get_localisation());
    }

}

void MainWindow::on_pushButton_Affecter_clicked()
{
    if((ui->lineEdit_id_eq_affect->text()=="")||(ui->lineEdit_nom_eq_affect->text()=="")||(ui->lineEdit_localisation_eq_affect->text()=="")||(ui->lineEdit_id_salle_affect->text()==""))
    {
        QMessageBox::critical(nullptr, QObject::tr("Affecter un equipement"),
                    QObject::tr("Erreur  Veuillez completez  tous les champs!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else if (ui->lineEdit_id_eq_affect->text().toInt()<=0) {
        QMessageBox::critical(nullptr, QObject::tr("Affecter un equipement"),
                    QObject::tr("Erreur  vous aviez entrer un id negatif!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else {
    int id_eq = ui->lineEdit_id_eq_affect->text().toInt();
    QString id_salle=ui->lineEdit_id_salle_affect->text();
    QString nom= ui->lineEdit_nom_eq_affect->text();
    QString localisation=ui->lineEdit_localisation_eq_affect->text();

      Equip_affecte Equip(id_eq,id_salle,nom,localisation);


  bool test=Equip.ajouter_equip();
  if(test)
{    bool sup= Eq.supprimerEquip(id_eq);
      ui->tableViewEqAffecter->setModel(Equip.listeEqAffecter());//refresh
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
