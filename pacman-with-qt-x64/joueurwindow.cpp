#include <iostream>
#include "bienvenuewindow.h"
#include "pacmanwindow.h"
#include "joueurwindow.h"

using namespace std;
Joueur::Joueur(QWidget* pparent, Qt::WindowFlags flags) : QFrame(pparent, flags){

    labelNF = new QLabel("0", this);
    labelVT = new QLabel("0", this);
}

void Joueur::evolue()
{
    QFormLayout *formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
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


    PacmanButton *btn_commence = new PacmanButton(this);
    btn_commence->setText("Commmencer");

    PacmanButton *btn_retourne = new PacmanButton(this);
    btn_retourne->setText("Retourner");

    //formLayout->addRow("Nombre de Fantome:", numFantomes);
    formLayout->addRow("", s_numFantomes);
    formLayout->addRow("Nombre de Fantomes: ", labelNF);
    formLayout->addRow("", s_vitesse);
    formLayout->addRow("Vitesse:", labelVT);
    formLayout->addRow(btn_retourne,btn_commence);
    btn_commence->setText("Commmencer");

    connect(btn_commence, PacmanButton::clicked, this, handleCommence);
    connect(btn_retourne, PacmanButton::clicked, this, handleRetourne);

    connect(s_numFantomes, &QSlider::valueChanged, labelNF, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(s_vitesse, &QSlider::valueChanged, labelVT, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    setLayout(formLayout);
}


void Joueur:: handleCommence()
{

    PacmanWindow * wnd = new PacmanWindow();

    wnd->show();

    close();
}

void Joueur:: handleRetourne()
{

    bienvenuewindow * wnd = new bienvenuewindow();

    wnd->show();

    close();
}
