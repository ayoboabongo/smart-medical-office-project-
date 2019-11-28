#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "medicament.h"
#include "equipement_para.h"
#include "equip_affecte.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButtonAjouterEquip_clicked();

    void on_pushButton_suppMedi_clicked();

    void on_pushButton_suppEquip_clicked();

   // void on_pushButtonRechercherMed_clicked();

    //void on_pushButtonRechercherEquip_clicked();

    void on_pushButtonActualiserStat_clicked();

    void on_pushButton_clicked();

    void on_pushButton_UpdateMed_clicked();

    void on_pushButton_rechercherEquip_update_clicked();

    void on_pushButton_update_Equip_clicked();

    void on_lineEditRechercherEquip_textChanged(const QString &arg1);

    void on_lineEditRechercher_textChanged(const QString &arg1);

    void on_pushButton_consulter_med_exp_clicked();

    void on_pushButton_rechercher_affect_clicked();

    void on_pushButton_Affecter_clicked();

private:
    Ui::MainWindow *ui;
    medicament Med;
    equipement_para Eq;
    Equip_affecte Equip ;
};

#endif // MAINWINDOW_H
