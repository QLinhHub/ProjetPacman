#include <iostream>
#include <string>
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

    if (pixmapGod.load("./data/godFantome.png")==false)
    {
        cout<<"Impossible d'ouvrir god fantome.bmp"<<endl;
        exit(-1);
    }

    if (pixmapMur.load("./data/mur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir mur.bmp"<<endl;
        exit(-1);
    }

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    resize(jeu.getNbCasesX()*largeurCase*2, jeu.getNbCasesY()*hauteurCase);
}

void PacmanWindow::configurer(int nJoueur, int nFantome, int vit, int mode)
{
    jeu.setInfoJeu(nJoueur,nFantome,vit, mode);
    jeu.init();
}

void PacmanWindow::startJeu()
{
    QTimer *timer = new QTimer(this);
    connect(timer, QTimer::timeout, this, PacmanWindow::handleTimer);
    timer->start(jeu.getVitesse());

    if(jeu.getNombreJoueur() == 1)
    {
        label_countdown = new QLabel("0:20", this);
        label_countdown->setGeometry(QRect(QPoint(900, 45), QSize(130, 50)));
        label_countdown->setFont(QFont("Arial", 30));

        countdown.setHMS(0,0,20,0);
        QTimer *time = new QTimer(this);
        connect(time, QTimer::timeout, this, PacmanWindow::handleCountdown);
        time->start(1000);

        QLabel* labelA = new QLabel("Mark: ", this);
        labelA->setGeometry(QRect(QPoint(730, 90), QSize(300, 100)));
        labelA->setFont(QFont("Arial", 30));

        label_markA = new QLabel(this);
        label_markA->setGeometry(QRect(QPoint(1100, 90), QSize(200, 100)));
        label_markA->setFont(QFont("Arial", 30));
        label_markA->setText(QString::fromStdString(std::to_string(jeu.pacmanA.mark)));
    }
    else
    {
        QLabel* labelA = new QLabel("Joueur A: ", this);
        labelA->setGeometry(QRect(QPoint(730, 90), QSize(300, 100)));
        labelA->setFont(QFont("Arial", 30));

        QLabel* labelB = new QLabel("Joueur B: ", this);
        labelB->setGeometry(QRect(QPoint(730, 180), QSize(300, 100)));
        labelB->setFont(QFont("Arial", 30));

        label_markA = new QLabel(this);
        label_markA->setGeometry(QRect(QPoint(1100, 90), QSize(200, 100)));
        label_markA->setFont(QFont("Arial", 30));
        label_markA->setText(QString::fromStdString(std::to_string(jeu.pacmanA.mark)));

        label_markB = new QLabel(this);
        label_markB->setGeometry(QRect(QPoint(1100, 180), QSize(2000, 100)));
        label_markB->setFont(QFont("Arial", 30));
        label_markB->setText(QString::fromStdString(std::to_string(jeu.pacmanB.mark)));
    }
}


void PacmanWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    list<Fantome>::const_iterator itFantome;
    list<GodFantome>::const_iterator itGod;
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

    // Dessine les gods
    for (itGod=jeu.godFantomes.begin(); itGod!=jeu.godFantomes.end(); itGod++)
        painter.drawPixmap(itGod->getPosX()*largeurCase, itGod->getPosY()*hauteurCase, pixmapGod);

	// Dessine Pacman
	painter.drawPixmap(jeu.pacmanA.getPosX()*largeurCase, jeu.pacmanA.getPosY()*hauteurCase, pixmapPacman);
	if (jeu.getNombreJoueur() == 2)
        painter.drawPixmap(jeu.pacmanB.getPosX()*largeurCase, jeu.pacmanB.getPosY()*hauteurCase, pixmapPacman);

}

void PacmanWindow::keyPressEvent(QKeyEvent *event)
{

    if (event->key()==Qt::Key_Left)
        jeu.deplacePacman(jeu.pacmanA,GAUCHE);
    else if (event->key()==Qt::Key_Right)
        jeu.deplacePacman(jeu.pacmanA,DROITE);
    else if (event->key()==Qt::Key_Up)
        jeu.deplacePacman(jeu.pacmanA,HAUT);
    else if (event->key()==Qt::Key_Down)
        jeu.deplacePacman(jeu.pacmanA,BAS);

    if (jeu.getNombreJoueur() == 2){
        if (event->key()==Qt::Key_A)
            jeu.deplacePacman(jeu.pacmanB,GAUCHE);
        else if (event->key()==Qt::Key_D)
            jeu.deplacePacman(jeu.pacmanB,DROITE);
        else if (event->key()==Qt::Key_W)
            jeu.deplacePacman(jeu.pacmanB,HAUT);
        else if (event->key()==Qt::Key_S)
            jeu.deplacePacman(jeu.pacmanB,BAS);}

    if(jeu.getNombreJoueur() == 1){
        jeu.mangerA();
    }else{
        jeu.mangerA();
        jeu.mangerB();
    }
    update();
}

void PacmanWindow::handleTimer()
{
    jeu.evolue();
    if(jeu.getNombreJoueur() == 1)
        label_markA->setText(QString::fromStdString(std::to_string(jeu.pacmanA.mark)));
    else{
        label_markA->setText(QString::fromStdString(std::to_string(jeu.pacmanA.mark)));
        label_markB->setText(QString::fromStdString(std::to_string(jeu.pacmanB.mark)));
    }
    repaint();
}

void PacmanWindow::handleCountdown()
{
    QMessageBox msg;
    msg.resize(300, 300);
    msg.setFont(QFont("Arial", 50));

    if(jeu.getNombreJoueur() == 1)
    {
        countdown = countdown.addSecs(-1);
        label_countdown->setText(countdown.toString("m:ss"));
        if(label_countdown->text() == "0:00" && (jeu.pacmanA.mark < (jeu.getNombreFantome() + 9)))
        {
            msg.setText("Your bad! You loss!");
            jeu.setNombreFantome(0);

            msg.exec();
            result* RWD = new result();
            close();
            RWD->show();
        }
        if(label_countdown->text() != "0:00" && (jeu.pacmanA.mark == (jeu.getNombreFantome() + 9)))
        {
            msg.setText("Trop fort! You win!");
            jeu.setNombreFantome(0);

            msg.exec();
            result* RWD = new result();
            close();
            RWD->show();
        }
    }

    else
    {
        if((jeu.pacmanA.mark + jeu.pacmanB.mark) == (jeu.getNombreFantome() + 9))
        {
            if(jeu.pacmanA.mark < jeu.pacmanB.mark)
                msg.setText("B win! Nope A!");
            else if(jeu.pacmanA.mark == jeu.pacmanB.mark)
                msg.setText("You all trop fort!");
            else
                msg.setText("A win! Nope B!");
            msg.exec();
            result* RWD = new result();
            close();
            RWD->show();

            cout << jeu.getNombreFantome();
            jeu.setNombreFantome(0);
        }
    }
}

// Classe PacmanButton
PacmanButton::PacmanButton(QWidget *parent) : QPushButton(parent) { }

void PacmanButton::keyPressEvent(QKeyEvent *e)
{
    if(parent() != NULL)
        QCoreApplication::sendEvent(parent(), e);
}
