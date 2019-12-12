#ifndef CONNEXION_H
#define CONNEXION_H

#include <QSqlDatabase>
/*!
    \class Connexion
    \brief  la classe connexion permet d'etablir
            la connexion entre Qt et la base de données
*/

class Connexion
{
private:
    QSqlDatabase db;
public:
    Connexion();
    bool ouvrirConnexion();
    void fermerConnexion();
};

#endif // CONNEXION_H
