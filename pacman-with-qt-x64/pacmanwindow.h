#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"
#include "joueurwindow.h"

class PacmanWindow : public QFrame
{
  private:
    int vitesse_time;
  protected:
    Jeu jeu;
    QPixmap pixmapPacman, pixmapTime, pixmapFantome, pixmapMur ;

    QPixmap pixmapPacHaut, pixmapPacBas, pixmapPacGauche, pixmapPacDroite;



  public:
    PacmanWindow(QWidget *pParent=0, Qt::WindowFlags flags=0);
    void evolue_window();
    void handleTimer();
    void ajoutFantome();        // ajouter un fantome
    void supprFantome();        // supprimer un fantome

    bool isCollision();
    void handleCollision();

    bool isCollisionTime();
    bool handleCollisionTime();

    void resultat();

    void setVitessetime(int n){
        vitesse_time = n;
    }

    void set_nbFantomes(int n){
        jeu.setNbFantomes(n);
    }

    void set_mode(bool b){
        jeu.setMode(b);
    }
    protected:
        void paintEvent(QPaintEvent *);
        void keyPressEvent(QKeyEvent *);
};

class PacmanButton : public QPushButton
{
    protected:
        void keyPressEvent(QKeyEvent *);
    public:
        PacmanButton(QWidget *parent=0);

};


#endif
