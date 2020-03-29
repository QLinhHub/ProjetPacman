#include <iostream>
#include "bienvenuewindow.h"
#include "pacmanwindow.h"
#include "joueurwindow.h"
#include "jeu.h"

using namespace std;
Joueur::Joueur(QWidget* pparent, Qt::WindowFlags flags) : QFrame(pparent, flags){

    labelNF = new QLabel("10", this);
    labelVT = new QLabel("10", this);

    resize(500, 500);

}

void Joueur::evolue()
{
    QFormLayout *formLayout = new QFormLayout;
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


    QRadioButton *radio1 = new QRadioButton(tr("Normal Mode"));
    QRadioButton *radio2 = new QRadioButton(tr("Advanced Mode"));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addStretch(1);

    PacmanButton *btn_commence = new PacmanButton(this);
    btn_commence->setText("Commmencer");
    PacmanButton *btn_retourne = new PacmanButton(this);
    btn_retourne->setText("Retourner");

    //formLayout->addRow("Nombre de Fantome:", numFantomes);
    formLayout->addRow("Nombre de Fantomes: ", labelNF);
    formLayout->addRow("", s_numFantomes);
    formLayout->addRow("Vitesse:", labelVT);
    formLayout->addRow("", s_vitesse);

    formLayout->addRow("Mode",vbox);
    formLayout->addRow(btn_retourne,btn_commence);

    connect(s_numFantomes, &QSlider::valueChanged, labelNF, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(s_vitesse, &QSlider::valueChanged, labelVT, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(radio1, QRadioButton::toggled, this, setNumMode);
    radio1->setChecked(true);


    connect(btn_commence, QPushButton::clicked, this, handleCommence);
    connect(btn_retourne, QPushButton::clicked, this, handleRetourne);


    setLayout(formLayout);
}


void Joueur:: handleCommence()
{
    PacmanWindow * wnd = new PacmanWindow();
    wnd->configurer(getNombre(),getNombreFantomes(),getVitesse(),getNumMode());
    wnd->startJeu();
    wnd->show();
    close();
}

void Joueur::handleRetourne()
{

    bienvenuewindow * wnd = new bienvenuewindow();
    wnd->show();
    close();
}
