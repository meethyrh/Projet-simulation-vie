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
    Grille();
    
    bool caseVide(Coord c)const;
    int getCase(Coord c)const;

    void videCase(Coord c);
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
    bool trouverAmour(Coord c);
    void bougeLapin();
    void bougeRenard();
    void afficheRepartion();
}; 
ostream &operator<<(ostream &out, const Game g);





#endif
