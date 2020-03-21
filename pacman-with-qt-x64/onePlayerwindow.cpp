#include <iostream>
#include "bienvenuewindow.h"
#include "pacmanwindow.h"
#include "onePlayerwindow.h"

using namespace std;

onePlayer::onePlayer(QWidget* pparent, Qt::WindowFlags flags) : QFrame(pparent, flags){
    QLineEdit *name = new QLineEdit(this);
    //QLineEdit *numFantomes = new QLineEdit(this);
    QSlider* s_numFantomes = new QSlider(Qt::Horizontal , this);
    //QLineEdit *vitesse = new QLineEdit(this);
    QSlider* s_vitesse = new QSlider(Qt::Horizontal , this);
    PacmanButton *btn_commence = new PacmanButton(this);
    btn_commence->setText("Commmencer");
    QLabel *labelNF = new QLabel("0", this);
    QLabel *labelVT = new QLabel("0", this);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->addRow("Name:", name);
    //formLayout->addRow("Nombre de Fantome:", numFantomes);
    formLayout->addRow("", s_numFantomes);
    formLayout->addRow("Nombre de Fantomes: ", labelNF);
    formLayout->addRow("", s_vitesse);
    formLayout->addRow("Vitesse:", labelVT);
    formLayout->addRow("",btn_commence);
    btn_commence->setText("Commmencer");

    connect(btn_commence, PacmanButton::clicked, this, handleCommence);
    connect(s_numFantomes, &QSlider::valueChanged, labelNF, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(s_vitesse, &QSlider::valueChanged, labelVT, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    setLayout(formLayout);
    //connect(exit, QPushButton::clicked, this, openPW);

    QString strNF;
    strNF = labelNF->text();

    numFantomes = strNF.toInt();
}
void onePlayer:: handleCommence()
{
    PacmanWindow * wnd = new PacmanWindow;
    wnd->show();

    close();
}

//void bienvenuewindow::openPW(){
//    PacmanWindow* pwn = new PacmanWindow();
//    pwn->show();
//}
