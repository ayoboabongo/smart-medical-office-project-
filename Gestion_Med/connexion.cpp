#include "connexion.h"

#include <QSqlError>

Connexion::Connexion(){
                      }
/*!
 * \brief Connexion::ouvrirConnexion
 * \return true si la connexion est etablie false sinon
 * \details permet d'etablir la connexion entre la base de donées et  Qt
 */
bool Connexion::ouvrirConnexion()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
                           db.setDatabaseName("Source_Projet2A");
                           db.setUserName("damos");//inserer nom de l'utilisateur
                           db.setPassword("esprit20");//inserer mot de passe de cet utilisateur

if (db.open())
    test=true;

else throw QString ("Erreur Paramétres"+db.lastError().text());
return  test;
}
/*!
 * \brief Connexion::fermerConnexion
 * \details permet de fermer la connexion
 */
void Connexion::fermerConnexion()
{db.close();}
