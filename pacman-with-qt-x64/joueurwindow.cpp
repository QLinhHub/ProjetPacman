#include <iostream>
#include "bienvenuewindow.h"
#include "pacmanwindow.h"
#include "joueurwindow.h"
#include "jeu.h"

using namespace std;
Joueur::Joueur(QWidget* pparent, Qt::WindowFlags flags) : QFrame(pparent, flags){

    labelNF = new QLabel("0", this);
    labelVT = new QLabel("0", this);

    resize(500, 500);
}

void Joueur::evolue()
{
    QFormLayout *formLayout = new QFormLayout;
    //formLayout->setAlignment(Qt::AlignTop);
    formLayout->setSpacing(50);

    if (nombreJoueur == 1)
    {
        name1 = new QLineEdit(this);
        formLayout->addRow("Name:", name1);
    }
    else
    {
        name1 = new QLineEdit(this);
        name2 = new QLineEdit(this);
        formLayout->addRow("Name1:", name1);
        formLayout->addRow("Name2:", name2);
    }


    QSlider* s_numFantomes = new QSlider(Qt::Horizontal , this);
    QSlider* s_vitesse = new QSlider(Qt::Horizontal , this);

    QPushButton *btn_mode_normal = new QPushButton("Mode Normal", this);

    QPushButton *btn_mode_moderne = new QPushButton("Mode Moderne", this);

    QPushButton *btn_retourne = new QPushButton("Retourner", this);

    //formLayout->addRow("Nombre de Fantome:", numFantomes);
    formLayout->addRow("Nombre de Fantomes: ", labelNF);
    formLayout->addRow("", s_numFantomes);
    formLayout->addRow("Vitesse:", labelVT);
    formLayout->addRow("", s_vitesse);
    formLayout->addRow("", btn_mode_normal);
    formLayout->addRow("", btn_mode_moderne);
    formLayout->addRow("",btn_retourne);

    connect(btn_mode_normal, QPushButton::clicked, this, handleModeNormal);
    connect(btn_mode_moderne, QPushButton::clicked, this, handleModeModerne);
    connect(btn_retourne, QPushButton::clicked, this, handleRetourne);

    connect(s_numFantomes, &QSlider::valueChanged, labelNF, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(s_vitesse, &QSlider::valueChanged, labelVT, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    setLayout(formLayout);
}


//void Joueur:: handleCommence()
//{
//
//    PacmanWindow * wnd = new PacmanWindow();
//
//    wnd->show();
//
//    close();
//}

void Joueur:: handleRetourne()
{

    bienvenuewindow * wnd = new bienvenuewindow();

    wnd->show();

    close();
}

void Joueur::handleModeNormal()
{
    PacmanWindow * wnd = new PacmanWindow();
    wnd->set_mode(true);
    wnd->set_nbFantomes(getnumFantomes());
    wnd->setVitessetime(getVitesse());
    wnd->evolue_window();
    //wnd->update();
    wnd->show();
    close();
}

void Joueur::handleModeModerne()
{
    PacmanWindow * wnd = new PacmanWindow();
    wnd->set_mode(false);
    wnd->set_nbFantomes(getnumFantomes());
    wnd->setVitessetime(getVitesse());
    wnd->evolue_window();
    //wnd->update();
    wnd->show();
    close();
}
