#ifndef COORD_HPP
#define COORD_HPP

#include <array>
#include <iostream>

using namespace std;

const int TAILLEGRILLE = 10;
const int MAXCARD = 100;

class Ensemble;
class Coord{
        int ligne;
        int colonne;
    public:
        //constructeurs de l'ensemble coord
        Coord(int lig,int col);
        Coord(int n);
        //renvoie la ligne d'une coord
        int getLigne() const;
        //renvoie la colonne d'une coord
        int getColonne() const;
        // renvoie l'entier correspondant aux coordonnées dans la grille
        int toInt()const;
        // renvoie l'ensemble des cases voisines à la case de coordonnées cord
        Ensemble voisines()const;
};

// affiche une coord
ostream &operator<<(ostream &out, const Coord c);

//operateur egalite entre deux coord
bool operator==(const Coord c1, const Coord c2);

class Ensemble{
        array<int,MAXCARD> t;
        int card;
    public:
        Ensemble():card{0}{t.fill(0);};
        // affichage d'un ensemble
        ostream & operator<<(ostream &out)const;
        //renvoie si l'ensemble est vide ou non
        bool estVide()const;
        //renvoie le cardinal de l'ensemble
        int cardinal()const;
        //ajoute un element à la fin de l'ensemble si c'est possible
        void ajoute(int n);
        /*retire un element d'une case aléatoire de l'ensemble.
        Pour cela on echange l'element de la case tirée aléatoirement avec l'element de la dernière case.
        On enlève ensuite l'element de la dernière case*/
        int tire();

    
};





#endif
