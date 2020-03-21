#include <iostream>
#include "pacmanwindow.h"

using namespace std;

PacmanWindow::PacmanWindow(QWidget *pParent, Qt::WindowFlags flags):QFrame(pParent, flags)
{
    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    if (pixmapPacman.load("./data/pacman.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman.png"<<endl;
        exit(-1);
    }

    if (pixmapFantome.load("./data/fantome.bmp")==false)
    {
        cout<<"Impossible d'ouvrir fantome.bmp"<<endl;
        exit(-1);
    }

    if (pixmapMur.load("./data/mur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir mur.bmp"<<endl;
        exit(-1);
    }

    jeu.init();

    QTimer *timer = new QTimer(this);
    connect(timer, QTimer::timeout, this, PacmanWindow::handleTimer);
    timer->start(100);

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    resize(jeu.getNbCasesX()*largeurCase, jeu.getNbCasesY()*hauteurCase+3*hauteurCase);

//    Ajout button "Ajout Fantome"
    PacmanButton *btn_ajout = new PacmanButton(this);
    btn_ajout->setFixedSize(100,20);
    btn_ajout->setText("Ajout Fantome");
    btn_ajout->move(10,10);
    connect(btn_ajout, PacmanButton::clicked, this, PacmanWindow::ajoutFantome);

//  Ajout button "Suppr Fantome"
    PacmanButton *btn_suppr = new PacmanButton(this);
    btn_suppr->setFixedSize(100,20);
    btn_suppr->setText("Suppr Fantome");
    btn_suppr->move(120,10);
    connect(btn_suppr, PacmanButton::clicked, this, PacmanWindow::supprFantome);
}

void PacmanWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    list<Fantome>::const_iterator itFantome;
    int x, y;

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    // Dessine les cases
    for (y=0;y<jeu.getNbCasesY();y++)
        for (x=0;x<jeu.getNbCasesX();x++)
			if (jeu.getCase(x,y)==MUR)
                painter.drawPixmap(x*largeurCase, y*hauteurCase+3*hauteurCase, pixmapMur);

    // Dessine les fantomes
    for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++)
        painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase+3*hauteurCase, pixmapFantome);

	// Dessine Pacman
	painter.drawPixmap(jeu.getPacmanX()*largeurCase, jeu.getPacmanY()*hauteurCase+3*hauteurCase, pixmapPacman);
}

void PacmanWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Left)
        jeu.deplacePacman(GAUCHE);
    else if (event->key()==Qt::Key_Right)
        jeu.deplacePacman(DROITE);
    else if (event->key()==Qt::Key_Up)
        jeu.deplacePacman(HAUT);
    else if (event->key()==Qt::Key_Down)
        jeu.deplacePacman(BAS);
    //Pacman mange un Fantom
    for(auto it = jeu.fantomes.begin(); it != jeu.fantomes.end(); it++){
        if(it->getPosX() == jeu.getPacmanX() && it->getPosY() == jeu.getPacmanY())
            jeu.fantomes.erase(it);
    }
    update();
}

void PacmanWindow::handleTimer()
{
    jeu.evolue();
    repaint();
}

void PacmanWindow::ajoutFantome()
{
    Fantome f;
    int x, y;
    Direction dir;
    // Initialize random position et direction
}

void PacmanWindow::supprFantome()
{
    if (!jeu.fantomes.empty())
        jeu.fantomes.pop_back();
}

// Classe PacmanButton
PacmanButton::PacmanButton(QWidget *parent) : QPushButton(parent) { }

void PacmanButton::keyPressEvent(QKeyEvent *e)
{
    if(parent() != NULL)
        QCoreApplication::sendEvent(parent(), e);
}

Form::Form(QWidget *parent)
    : QWidget(parent) {

    QLineEdit *nameEdit = new QLineEdit(this);
    QLineEdit *addrEdit = new QLineEdit(this);
    QLineEdit *occpEdit = new QLineEdit(this);
    PacmanButton *btn_commence = new PacmanButton(this);
    btn_commence->setText("Commmencer");

    QFormLayout *formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->addRow("Name:", nameEdit);
    formLayout->addRow("Nombre de Fantome:", addrEdit);
    formLayout->addRow("Vitesse:", occpEdit);
    formLayout->addRow("",btn_commence);
    btn_commence->setText("Commmencer");

//    QMessageBox gagnerBox;
//    gagnerBox.setText("Felicitations ! YOLO");
//    gagnerBox.setInformativeText(nameEdit->text());

    connect(btn_commence, PacmanButton::clicked, this, handleCommence);

    setLayout(formLayout);
}
void Form:: handleCommence()
{

    PacmanWindow * wnd = new PacmanWindow;
    wnd->show();
}
