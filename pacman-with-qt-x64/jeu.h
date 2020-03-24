#ifndef JEU_H
#define JEU_H

#include <list>
using namespace std;

typedef enum {VIDE, MUR} Case;
typedef enum {GAUCHE, DROITE, HAUT, BAS} Direction;

class Jeu;

class Objet
{
    friend class Jeu;

  protected:
    int posX, posY;
    Direction dir;

  public:
    Objet();
    int getPosX() const;
    int getPosY() const;
};

class Fantome: public Objet
{

  public:
    Fantome(){}
};

class Pacman: public Objet
{
  public:
    Pacman(){}
};

class GodFantome: public Objet
{
  public:
    GodFantome(){}
};

class Jeu
{

    protected:
        Case *terrain;
        int largeur, hauteur; // Nombre de cases en largeur et en hauteur
        int posPacmanX, posPacmanY;

    public:
        list<Fantome> fantomes;
        list<GodFantome> godFantomes;

    public:
        Pacman pacmanA;
        Pacman pacmanB;

    protected:
        int nombreJoueur;
        int vitesse;
        int nombreFantome;
        int numeroMode;
    public:
        Jeu();
        Jeu(const Jeu &)=delete;
        ~Jeu();
        Jeu &operator=(const Jeu &)=delete;

//    bool init();
    bool init();
    void evolue();

    // Retourne les dimensions (en nombre de cases)
    int getNbCasesX() const;
    int getNbCasesY() const;

    //Mettre les parametre necessaire
    void setInfoJeu(int, int, int, int);

    //Retourne les parametre pour configurer le jeu
    int getNombreJoueur() const;
    int getVitesse() const;
    int getNombreFantome() const;

//    // Retourne la position du Pacman
//    int getPacmanX() const;
//    int getPacmanY() const;

    // Retourne la case à une position donnée
    Case getCase(int, int) const;

    // Indique si la case à une position donnée existe et est vide
    // (Pacman ou les fantomes peuvent l'occuper)
    bool posValide(int, int) const;

    // Déplace Pacman dans une direction (si la case à atteindre est valide)

    bool deplacePacman(Pacman &, Direction);
};

#endif
