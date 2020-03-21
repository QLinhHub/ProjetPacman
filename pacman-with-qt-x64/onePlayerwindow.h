#ifndef ONEPLAYERWINDOW_H
#define ONEPLAYERWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"

class onePlayer : public QFrame{

  public:
    onePlayer(QWidget* pparent=0, Qt::WindowFlags flags=0);
    void handleCommence();

    int getVitesse()
    {
        return (labelVT->text()).toInt();
    }

    int getnumFantomes()
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

  private:

    QLineEdit *name1;
    QLineEdit *name2;
    QLabel *labelNF;
    QLabel *labelVT;
    int nombreJoueur;
};


#endif
