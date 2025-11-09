#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include "TypeDefs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MaFenetre; }
QT_END_NAMESPACE

class MaFenetre : public QWidget
{
    Q_OBJECT

public:
    MaFenetre(QWidget *parent = nullptr);
    ~MaFenetre();

private slots:
    void on_Connect_clicked();
    void on_Disconnect_clicked();
    void on_Quitter_clicked();
    void on_LireCarte_clicked();
    void on_MiseAJour_clicked();
    void on_Payer_clicked();
    void on_Charger_clicked();

private:
    Ui::MaFenetre *ui;
};

#endif // MAFENETRE_H
