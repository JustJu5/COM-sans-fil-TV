#include "mafenetre.h"
#include "ui_mafenetre.h"
#include "MfErrNo.h"
#include "Sw_Device.h"
#include "Sw_ISO14443A-3.h"
#include "Sw_Mf_Classic.h"
#include "Tools.h"
#include "TypeDefs.h"
#include <QDebug>

MaFenetre::MaFenetre(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MaFenetre)
{
    ui->setupUi(this);
}

MaFenetre::~MaFenetre()
{
    delete ui;
}

ReaderName MonLecteur;

void MaFenetre::on_pushButtonConnect_clicked()
{
    int16_t status = MI_OK;
    MonLecteur.Type = ReaderCDC;
    MonLecteur.device = 0;
    status = OpenCOM(&MonLecteur);
    qDebug() << "OpenCOM" << status;
}

void MaFenetre::on_pushButtonDeconnect_clicked()
{
    qDebug() << "Déconnexion Carte déconnectée !";
}

void MaFenetre::on_pushButtonQuitter_clicked()
{
    close();
}


void MaFenetre::on_pushButtonPayer_clicked()
{
    /*int solde = ui->labelSolde->text().toInt();
    int montant = ui->spinBoxDecrement->value();

    if (montant > solde) {
        QMessageBox::warning(this, "Erreur", "Solde insuffisant !");
    } else {
        solde -= montant;
        ui->labelSolde->setText(QString::number(solde));
        QMessageBox::information(this, "Paiement", QString::number(montant) + " unités payées.");
    }*/
}

void MaFenetre::on_pushButtonCharger_clicked()
{
    /*int solde = ui->labelSolde->text().toInt();
    int montant = ui->spinBoxIncrement->value();

    solde += montant;
    ui->labelSolde->setText(QString::number(solde));*/
    //QMessageBox::information(this, "Chargement", QString::number(montant) + " unités ajoutées.");
}


void MaFenetre::on_pushButtonMiseAJour_clicked()
{
   ////QString nom = ui->lineEditNom->text();

    //if (prenom.isEmpty() || nom.isEmpty()) {
        //QMessageBox::warning(this, "Erreur", "Veuillez remplir les deux champs !");
      /*  return;
    }

    // Conversion en tableau de char pour la librairie ODALID
    QByteArray prenomData = prenom.toUtf8();
    QByteArray nomData = nom.toUtf8();

    // Exemple fictif d’écriture dans la carte (à adapter avec les vraies fonctions ODALID)
    int status;

    // Authentifier le secteur 2 avec la clé B (index 2)
    status = Mf_Classic_Authenticate(readerHandle, 2, 2, KEY_B);
    if (status != 0) {
        //QMessageBox::critical(this, "Erreur", "Échec de l'authentification !");
        return;
    }

    // Écrire prénom dans le bloc 9
    status = Mf_Classic_Write_Block(readerHandle, 2, 9, prenomData.data());
    if (status != 0) {
        //QMessageBox::critical(this, "Erreur", "Échec de l’écriture du prénom !");
        return;
    }

    // Écrire nom dans le bloc 10
    status = Mf_Classic_Write_Block(readerHandle, 2, 10, nomData.data());
    if (status != 0) {
        //QMessageBox::critical(this, "Erreur", "Échec de l’écriture du nom !");
        return;
    }*/

    //QMessageBox::information(this, "Succès", "Identité enregistrée dans la carte !");
}


