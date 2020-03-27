#include "jeu.h"
#include <iostream>
#include <assert.h>
#include <fstream>

Objet :: Objet()
{
    posX = 0;
    posY = 0;
    dir = BAS;
}

int Objet::getPosX() const
{
    return posX;
}

int Objet::getPosY() const
{
    return posY;
}

Jeu::Jeu()
{
    terrain = NULL;
    largeur = 20; hauteur = 15;
}

Jeu::~Jeu()
{
    if (terrain!=NULL)
        delete[] terrain;
}

void Jeu::setInfoJeu(int nJoueur, int nFantome, int vit, int mode)
{
    nombreJoueur = nJoueur;
    nombreFantome = nFantome;
    vitesse = vit;
    numeroMode = mode;
}


bool Jeu::init()
{
	int x, y;
	list<Fantome>::iterator itFantome;
	list<GodFantome>::iterator itGod;

//	const char terrain_defaut[15][21] = {
//		"####################",
//		"#........##........#",
//		"#.#####..##...####.#",
//		"#........##........#",
//		"#..................#",
//		"#......#....#......#",
//		"#......#...##......#",
//		"#####..#....#..#####",
//		"#......##...#......#",
//		"#......#....#......#",
//		"#..................#",
//		"#..................#",
//		"#.....#......#.....#",
//		"#.....#......#.....#",
//        "####################"
//    };
    ifstream mur;
    mur.open("mur.txt");
    char terrain_defaut[15][21] = {};

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 20; j++)
            mur >> terrain_defaut[i][j];
    }
	largeur = 20;
	hauteur = 15;

	terrain = new Case[largeur*hauteur];

	for(y=0;y<hauteur;++y)
		for(x=0;x<largeur;++x)
            if (terrain_defaut[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else
                terrain[y*largeur+x] = VIDE;

    fantomes.resize(nombreFantome);

	for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
        do {
            x = rand()%largeur;
            y = rand()%hauteur;
        } while (terrain[y*largeur+x]!=VIDE);

        itFantome->posX = x;
        itFantome->posY = y;
        itFantome->dir = (Direction)(rand()%4);
    }


    godFantomes.resize(3);

    for (itGod=godFantomes.begin(); itGod!=godFantomes.end(); itGod++)
    {
        do {
            x = rand()%largeur;
            y = rand()%hauteur;
        } while (terrain[y*largeur+x]!=VIDE);

        itGod->posX = x;
        itGod->posY = y;
        itGod->dir = (Direction)(rand()%4);
    }

    do {
        x = rand()%largeur;
        y = rand()%hauteur;
    } while (terrain[y*largeur+x]!=VIDE);

    pacmanA.posX = x;
    pacmanA.posY = y;

    if (nombreJoueur == 2){
        do {
            x = rand()%largeur;
            y = rand()%hauteur;
        } while (terrain[y*largeur+x]!=VIDE);

        pacmanB.posX = x;
        pacmanB.posY = y;
    }

    return true;
}

void Jeu::evolue()
{
    int testX, testY;
	list<Fantome>::iterator itFantome;
	list<GodFantome>::iterator itGod;

    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};

    for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
       testX = itFantome->posX + depX[itFantome->dir];
       testY = itFantome->posY + depY[itFantome->dir];

        if (terrain[testY*largeur+testX]==VIDE)
        {
            itFantome->posX = testX;
            itFantome->posY = testY;
        }
        else
            // Changement de direction
            itFantome->dir = (Direction)(rand()%4);
    }

    for (itGod=godFantomes.begin(); itGod!=godFantomes.end(); itGod++)
    {
       testX = itGod->posX + depX[itGod->dir];
       testY = itGod->posY + depY[itGod->dir];

        if (terrain[testY*largeur+testX]==VIDE)
        {
            itGod->posX = testX;
            itGod->posY = testY;
        }
        else
            // Changement de direction
            itGod->dir = (Direction)(rand()%4);
    }

//    for(auto it = fantomes.begin(); it != fantomes.end(); it++){
//        if(it->getPosX() == getPacmanX() && it->getPosY() == getPacmanY())
//            fantomes.erase(it);
//    }
}

int Jeu::getNombreJoueur() const
{
    return nombreJoueur;
}

int Jeu::getVitesse() const
{
    return vitesse;
}

int Jeu::getNbCasesX() const
{
    return largeur;
}

int Jeu::getNbCasesY() const
{
    return hauteur;
}

//int Jeu::getPacmanX() const
//{
//    return posPacmanX;
//}
//
//int Jeu::getPacmanY() const
//{
//    return posPacmanY;
//}

Case Jeu::getCase(int x, int y) const
{
    assert(x>=0 && x<largeur && y>=0 && y<hauteur);
    return terrain[y*largeur+x];
}

bool Jeu::posValide(int x, int y) const
{
    return (x>=0 && x<largeur && y>=0 && y<hauteur && terrain[y*largeur+x]==VIDE);
}

bool Jeu::deplacePacman(Pacman &pac,Direction dir)
{
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};
    int testX, testY;

    testX = pac.getPosX() + depX[dir];
    testY = pac.getPosY() + depY[dir];

    if (posValide(testX, testY))
    {
        pac.posX = testX;
        pac.posY = testY;
        return true;
    }
    else
        return false;
}
