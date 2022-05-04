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

//surcharge de << pour la grille
ostream &operator<<(ostream &out, const Grille grille);

class Game{
    Grille grille;
    Population pop;
    
    public:
    
    //crée une population et une grille initiale. (avec déjà des lapins et des renards 
    //en fonction de leur probabilité d'apparition)
    /*
    param: probaR (probabilité d'apparition de renard), probaL (Probabilité d'apparition des lapins)
    return: Game
    */
    Game(int probR,int probL);
    
    //Prend un animal dans le jeu ayant des coordonnées "c" dans la grille
    /*
    param: coordonées de l'animal dans la grille
    return: l'animal
    */
    Animal getAnimal(Coord c)const;

    //ajoute un animal au jeu (dans la grille et la population)
    /*
    param: l'espece de l'animal et ses coordonnées
    return: void
    */
    void ajouteAnimal(Espece e,Coord c);

    //supprime un animal au jeu (dans la grille et la population)
    /*
    param: ses coordonnées
    return: void
    */
    void supprimeAnimal(Coord c);

    //déplace un animale d'une coordonnée à une autre 
    /*
    param: coordonnées de départ, coordonnées d'arrivé
    return: void
    */
    void deplaceAnimal(Coord c1,Coord c2);

    //Bouge un lapin
    /*
    param: coordonnée de lapin à bouger
    return: void
    */
    void bougeLapin(Coord c);

    //Bouge un renard en fonction de si il mange ou non
    /*
    param: coordonnées du renard à bouger
    return: void
    */
    void bougeRenard(Coord c);
    
}; 

//surecharge de << pour le jeu
ostream &operator<<(ostream &out, const Game g);



#endif