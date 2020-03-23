#ifndef ONEPLAYERWINDOW_H
#define ONEPLAYERWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"

class Joueur : public QFrame{

  public:
    Joueur(QWidget* pparent=0, Qt::WindowFlags flags=0);
    void evolue();

//    void handleCommence();
    void handleRetourne();
    void handleCommence();

    int getVitesse()
    {
        return (labelVT->text()).toInt();
    }

    int getNombreFantomes()
    {
        return (labelNF->text()).toInt();
    }

    string getName1()
    {
    return (name1->text()).toStdString();
    }

    string getName2()
    {
    return (name2->text()).toStdString();
    }

    void setNombre(int a){
        nombreJoueur = a;
    }

    int getNombre(){
        return nombreJoueur;
    }

    void setNumMode(){
        if (numeroMode != 1)
            numeroMode = 1;
        else numeroMode = 2;
    }

    int getNumMode(){
        return numeroMode;
    }

  private:
    QLineEdit *name1;
    QLineEdit *name2;
    QLabel *labelNF;
    QLabel *labelVT;
    int numeroMode;
    int nombreJoueur;

};


#endif
