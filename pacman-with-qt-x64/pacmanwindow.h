#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"
#include "joueurwindow.h"

class PacmanWindow : public QFrame
{
  private:
    QLabel* label_countdown;
    QTime countdown;

  protected:
    Jeu jeu;

    QPixmap pixmapPacman, pixmapTime, pixmapFantome, pixmapMur, pixmapGod;
    QPixmap pixmapPacHaut, pixmapPacBas, pixmapPacGauche, pixmapPacDroite;
  public:
    PacmanWindow(QWidget *pParent=0, Qt::WindowFlags flags=0);

    void configurer(int ,int ,int, int);
    void startJeu();

    void handleTimer();
    void handleCountdown();


    void ajoutFantome();        // ajouter un fantome
    void supprFantome();        // supprimer un fantome

    bool isCollision();
    void handleCollision();

    bool isCollisionTime();
    bool handleCollisionTime();


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
