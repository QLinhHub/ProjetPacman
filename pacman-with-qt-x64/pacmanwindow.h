#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

#include "result.h"
#include "jeu.h"


class PacmanWindow : public QFrame
{
  private:
    QLabel* label_countdown;
    QLabel* label_markA;
    QLabel* label_markB;
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
