#include <iostream>
#include "bienvenuewindow.h"
#include "pacmanwindow.h"
#include "joueurwindow.h"

using namespace std;

bienvenuewindow::bienvenuewindow(QWidget* pparent, Qt::WindowFlags flags) : QFrame(pparent, flags){
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setSpacing(1);

    QPushButton *oneP = new QPushButton("Un Joueur", this);
    oneP->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton *twoP = new QPushButton("Deux Joueur", this);
    twoP->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton *hMark = new QPushButton("Meilleur Marque", this);
    hMark->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton *exit = new QPushButton("Exit", this);
    exit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    vbox->addWidget(oneP);
    vbox->addWidget(twoP);
    vbox->addWidget(hMark);
    vbox->addWidget(exit);

    setLayout(vbox);

    connect(oneP, QPushButton::clicked, this, openOPW1);
    connect(twoP, QPushButton::clicked, this, openOPW2);
    connect(exit, QPushButton::clicked, this, close);
}

void bienvenuewindow::openOPW1(){
    Joueur* pwn = new Joueur;

    pwn->setNombre(1);
    pwn->evolue();
    pwn->show();
    close();
}

void bienvenuewindow::openOPW2(){
    Joueur* pwn = new Joueur;

    pwn->setNombre(2);
    pwn->evolue();
    pwn->show();
    close();
}

