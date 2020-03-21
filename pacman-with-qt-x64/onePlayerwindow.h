#ifndef ONEPLAYERWINDOW_H
#define ONEPLAYERWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"

class onePlayer : public QFrame{

  public:
    onePlayer(QWidget* pparent=0, Qt::WindowFlags flags=0);
    void handleCommence();
    int getVitesse(){
        return vitesse;
    }
    int getnumFantomes(){
        return numFantomes;
    }
    string getName(){
    return name;
    }
  private:
    int vitesse;
    int numFantomes;
    string name;
};


#endif
