#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class MaFenetre;
}
QT_END_NAMESPACE
class MaFenetre : public QWidget
{
    Q_OBJECT

public:
    MaFenetre(QWidget *parent = nullptr);
    ~MaFenetre();

private slots:
    void on_pushButtonConnect_clicked();
    void on_pushButtonDeconnect_clicked();
    void on_pushButtonPayer_clicked();
    void on_pushButtonCharger_clicked();
    void on_pushButtonQuitter_clicked();
    void on_pushButtonMiseAJour_clicked();  // ← pour le bouton "Mise à jour"


private:
    Ui::MaFenetre *ui;
};

#endif // MAFENETRE_H
