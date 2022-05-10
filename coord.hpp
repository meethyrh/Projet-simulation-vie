#ifndef COORD_HPP
#define COORD_HPP

#include <array>
#include <iostream>

using namespace std;

const int TAILLEGRILLE = 100;
const int MAXCARD = TAILLEGRILLE * TAILLEGRILLE;

class Ensemble;
class Coord{
        int ligne;
        int colonne;
    public:
        //constructeurs de l'ensemble coord
        Coord();
        Coord(int lig,int col);
        Coord(int n);

        //renvoie la ligne d'une coord
        /*
        param:
        return: int
        */
        int getLigne() const;

        //renvoie la colonne d'une coord
        /*
        param:
        return: int
        */
        int getColonne() const;

        // renvoie l'entier correspondant aux coordonnées dans la grille
        /*
        param:
        return: int
        */
        int toInt()const;

        // renvoie l'ensemble des cases voisines à la case de coordonnées cord
        /*
        param:
        return: Ensemble
        */
        Ensemble voisines()const;
};

// affiche une coord
ostream &operator<<(ostream &out, const Coord c);

//operateur egalite entre deux coord
bool operator==(const Coord c1, const Coord c2);

class Ensemble{
        array<int,MAXCARD+1> t;
        int card;
    public:
        Ensemble():card{0}{t.fill(0);};
        
        //renvoie si l'ensemble est vide ou non
        /*
        param:
        return: bool
        */
        bool estVide()const;

        //renvoie le cardinal de l'ensemble
        /*
        param:
        return: int
        */
        int cardinal()const;

        //ajoute un element à la fin de l'ensemble si c'est possible
        /*
        param:
        return: void
        */
        void ajoute(int n);

        /*retire un element d'une case aléatoire de l'ensemble.
        Pour cela on echange l'element de la case tirée aléatoirement avec l'element de la dernière case.
        On enlève ensuite l'element de la dernière case*/
        /*
        param:
        return: int
        */
        int tire();
};
// affichage d'un ensemble
ostream & operator<<(ostream &out,const Ensemble e);




#endif
