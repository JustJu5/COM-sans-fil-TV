#include "mafenetre.h"
#include "ui_mafenetre.h"

#include "MfErrNo.h"
#include "Sw_Device.h"
#include "Sw_Mf_Classic.h"
#include "Sw_ISO14443A-3.h"
#include "Tools.h"
#include "TypeDefs.h"

#include <QDebug>
#include <QCoreApplication>

ReaderName MonLecteur;
bool lecteurConnecte = false;

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

void MaFenetre::on_Connect_clicked()
{
    MonLecteur.Type = ReaderCDC;
    MonLecteur.device = 0;
    RF_Power_Control(&MonLecteur, TRUE, 0);

    if (OpenCOM(&MonLecteur) != MI_OK) {
        ui->Affichage->setText("Erreur connexion lecteur.");
        return;
    }

    Version(&MonLecteur);
    ui->Affichage->setText("Connecté : " + QString(MonLecteur.version));
    lecteurConnecte = true;
}

void MaFenetre::on_Disconnect_clicked()
{
    RF_Power_Control(&MonLecteur, FALSE, 0);
    LEDBuzzer(&MonLecteur, LED_OFF);
    CloseCOM(&MonLecteur);
    ui->Affichage->setText("Déconnecté.");
    lecteurConnecte = false;
}

void MaFenetre::on_Quitter_clicked()
{
    if (lecteurConnecte) {
        RF_Power_Control(&MonLecteur, FALSE, 0);
        LEDBuzzer(&MonLecteur, LED_OFF);
        CloseCOM(&MonLecteur);
    }
    QCoreApplication::quit();
}


void MaFenetre::on_LireCarte_clicked()
{
    uint8_t atq[2];
    uint8_t sak[1];
    uint8_t uid[10];
    uint16_t uidLength = 0;

    int16_t status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uidLength);

    if (status != MI_OK || uidLength == 0) {
        ui->Affichage->setText("Carte non détectée.");
        return;
    }

    QString uidStr;
    for (int i = 0; i < uidLength; ++i) {
        uidStr += QString("%1 ").arg(uid[i], 2, 16, QChar('0')).toUpper();
    }

    ui->Affichage->setText("Carte détectée : UID = " + uidStr.trimmed());
}

void MaFenetre::on_MiseAJour_clicked()
{
    QString nom = "zaiem";
    QString prenom = "juliette";

    uint8_t cle[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    // Authentification sur le secteur 1 avec clé A externe
    int16_t status = Mf_Classic_Authenticate(&MonLecteur, AuthKeyA, FALSE, 1, cle, 1);
    if (status != MI_OK) {
        ui->Affichage->setText("Échec de l'authentification.");
        return;
    }

    // Préparation des données
    QByteArray nomData = nom.left(16).toUtf8().leftJustified(16, '\0');
    QByteArray prenomData = prenom.left(16).toUtf8().leftJustified(16, '\0');





    ui->Affichage->setText("Identité enregistrée : " + nom.toUpper() + " " + prenom.toUpper());
}



void MaFenetre::on_Payer_clicked()
{
    int montant = ui->unitsToPay->value();
    if (montant <= 0) {
        ui->Affichage->setText("Montant invalide.");
        return;
    }

    uint8_t cle[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    int16_t status;

    status = Mf_Classic_Authenticate(&MonLecteur, AuthKeyA, TRUE, 3, cle, 3);
    if (status != MI_OK) {
        ui->Affichage->setText("Échec authentification.");
        return;
    }

    status = Mf_Classic_Decrement_Value(&MonLecteur, TRUE, 14, montant, 14, AuthKeyA, 3);
    if (status != MI_OK) {
        ui->Affichage->setText("Erreur décrémentation.");
        return;
    }

    ui->Affichage->setText("Paiement effectué !");
}


void MaFenetre::on_Charger_clicked()
{
    int montant = ui->unitsToAdd->value();
    if (montant <= 0) {
        ui->Affichage->setText("Montant invalide.");
        return;
    }

    uint8_t cle[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    int16_t status;

    status = Mf_Classic_Authenticate(&MonLecteur, AuthKeyB, TRUE, 3, cle, 3);
    if (status != MI_OK) {
        ui->Affichage->setText("Échec authentification.");
        return;
    }

    status = Mf_Classic_Increment_Value(&MonLecteur, TRUE, 14, montant, 14, AuthKeyB, 3);
    if (status != MI_OK) {
        ui->Affichage->setText("Erreur incrémentation.");
        return;
    }

    ui->Affichage->setText("Chargement effectué !");
}

