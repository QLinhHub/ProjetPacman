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

    jeu.initMur();
    jeu.initFantomes_Pacman();


//    QTimer *timer = new QTimer(this);
//    connect(timer, QTimer::timeout, this, PacmanWindow::handleTimer);
//    timer->start(vitesse_time);

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    resize(jeu.getNbCasesX()*largeurCase*2, jeu.getNbCasesY()*hauteurCase);
}

void PacmanWindow::evolue_window()
{
    jeu.initMur();
    jeu.initFantomes_Pacman();

    QTimer *timer = new QTimer(this);
    connect(timer, QTimer::timeout, this, PacmanWindow::handleTimer);
    timer->start(vitesse_time);

    label_countdown = new QLabel("0:10", this);
    label_countdown->setGeometry(QRect(QPoint(900, 45), QSize(130, 50)));
    label_countdown->setFont(QFont("Arial", 30));

    countdown.setHMS(0,0,10,0);
    QTimer *time = new QTimer(this);
    connect(time, QTimer::timeout, this, PacmanWindow::handleCountdown);
    time->start(1000);
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
                painter.drawPixmap(x*largeurCase, y*hauteurCase, pixmapMur);

    // Dessine les fantomes
    for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++)
        painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase, pixmapFantome);

	// Dessine Pacman
	painter.drawPixmap(jeu.getPacmanX()*largeurCase, jeu.getPacmanY()*hauteurCase, pixmapPacman);
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

void PacmanWindow::handleCountdown()
{
    countdown = countdown.addSecs(-1);
    label_countdown->setText(countdown.toString("m:ss"));
}

// Classe PacmanButton
PacmanButton::PacmanButton(QWidget *parent) : QPushButton(parent) { }

void PacmanButton::keyPressEvent(QKeyEvent *e)
{
    if(parent() != NULL)
        QCoreApplication::sendEvent(parent(), e);
}
