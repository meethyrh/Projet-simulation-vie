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
    //Construit une grille d'animaux vide (une grille avec tout les identifiant à -1)
    Grille();
    
    //Verifie si une case est vide
    /*
    param: coordonnées de la case
    return True si la case est vide, false sinon
    */
    bool caseVide(Coord c)const;

    //renvoie l'identifiant de l'animal aux coordonnées "c" dans la grille
    /*
    param: coordonnées "c" de la case
    return entier corresponadnt à l'identifiant
    */
    int getCase(Coord c)const;

    //Vide une case qui était occupée par un animal (ne fait rien si la case était vide)
    //Change l'identifiant à la case de coordonnées c en -1 dans la grille 
    /*
    param: coordonnées "c" de la case
    return void
    */
    void videCase(Coord c);

    //Change l'identifiant aux coordonnées "c" en l'identifiant id pris en paramettre
    /*
    param: le nouvel identifiant, coordonnées "c" de la case
    return void
    */
    void setCase(int id,Coord c);

};

//surcharge de l'oppérateur << pour les grilles
ostream &operator<<(ostream &out, const Grille grille);

class Game{
    Grille grille;
    Population pop;
    
    public:
    
    //Construit le jeu avec une probabilité d'apparition de renard donnée et 
    //une probabilité d'apparition de lapin donnée
    /*
    param: probR (probabilité d'apparition des renard), probL (probabilité d'apparition des lapins)
    */
    Game(int probR,int probL);
    
    //renvoie l'animal auc coordonnées données dans la grille
    /*
    param: coordonnées c de l'animal dans la grille
    return: animal corréspondant aux coordonnées données
    */
    Animal getAnimal(Coord c)const;

    // ajoute Animal d'une espece e donnée à des coordonnées données dans le jeu (population et grille)
    /*
    param: L'espece et les coordonnées de l'animal
    return: void
    */
    void ajouteAnimal(Espece e,Coord c);

    // Supprime l'animal aux coordonnées données du jeu (population et grille)
    /*
    param: coordonnées de l'animal à supprimer
    return:void
    */
    void supprimeAnimal(Coord c);

    // deplace un animal dans la grille;
    /*
    param: coordonnées de départ, coordonnées d'arrivée
    return: void
    */
    void deplaceAnimal(Coord c1,Coord c2);

    //Bouge un lapin sur une des cases vides lui étant voisine dans la grille
    /*
    param: coordonnées du lapin
    return: void
    */
    void bougeLapin(Coord c);
    
}; 

//surcharge de l'opperateur << pour le jeu;
ostream &operator<<(ostream &out, const Game g);





#endif