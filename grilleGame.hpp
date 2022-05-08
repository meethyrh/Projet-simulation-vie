#ifndef GRILLEGAME_HPP
#define GRILLEGAME_HPP

#include <array>
#include <iostream>
#include <vector>
#include <cmath>
#include "coord.hpp"
#include "anipop.hpp"

using namespace std;


class Grille{
    array<array<int,TAILLEGRILLE>,TAILLEGRILLE> grille;

    public:
    //création d'une grille vide (avec que des indentifiant = -1)
    /*
    param:
    return: une grille
    */
    Grille();
    

    //Vérifie si une case de coordonnée c est vide ou non
    //si oui renvoie true, si non renvoi false
    /*
    param: coordonnée de  la case à vérifier
    return: bool
    */
    bool caseVide(Coord c)const;

    //renvoi l'indentifiant de la case au coordonnées c
    /*
    param: les coordonnées de la case
    return: l'identifiant 
    */
    int getCase(Coord c)const;

    //vide une case de coordonnée "c" de la grille (transforme l'identifiant en -1)
    /*
    param: coordonnées de la case à vider
    return: void
    */
    void videCase(Coord c);

    //change l'identifiant d'une case de coordonnée connu en un nouvel identifiant id 
    /*
    param: le nouvel identifiant, les coordonnées de l'id à changer
    return: void
    */
    void setCase(int id,Coord c);

};
ostream &operator<<(ostream &out, const Grille grille);

class Game{
    Grille grille;
    Population pop;
    
    public:
    
    Game(int probR,int probL);
    
    Animal getAnimal(Coord c)const;
    void ajouteAnimal(Espece e,Coord c);
    void supprimeAnimal(Coord c);
    void deplaceAnimal(Coord c1,Coord c2);
    Ensemble voisinsVides(Coord c)const;
    Ensemble voisinsEspece(Coord c,Espece e)const;
    bool trouverAmour(Coord c)const;
    void bougeLapin();
    void bougeRenard();
    void verifieGrille()const;
    void afficheDonnee();
    
}; 
ostream &operator<<(ostream &out, const Game g);





#endif
