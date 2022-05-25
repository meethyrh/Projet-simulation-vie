#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <exception>
#include "coord.hpp"

using namespace std;
Coord::Coord(){}
Coord::Coord(int lig,int col):ligne{lig},colonne{col}{
	if(lig<0 or col<0 or lig>TAILLEGRILLE or col>TAILLEGRILLE){
		throw invalid_argument("coordonnées en dehord de la grille");
	}
}

Coord::Coord(int n): ligne {n/TAILLEGRILLE}, colonne {n%TAILLEGRILLE}{}

int Coord::getLigne()const{return ligne;}

int Coord::getColonne()const{return colonne;}
 
int Coord::toInt()const{
    return ligne*TAILLEGRILLE + colonne;
}

ostream &operator<<(ostream &out, const Coord c) {
    out << "(" <<c.getLigne()<< ", " << c.getColonne() << ")";
    return out;
}


bool operator==(const Coord c1, const Coord c2) {
    return c1.getLigne() == c2.getLigne() and c1.getColonne() == c2.getColonne();
}

Ensemble Coord::voisines()const{
    Ensemble e{};
    for (int i = max(ligne - 1, 0);i<=min(ligne + 1, TAILLEGRILLE - 1);i++){
        for (int j = max(colonne - 1, 0);j<=min(colonne + 1, TAILLEGRILLE - 1);j++){
            if( not ((*this) == Coord{i,j})){
                e.ajoute(Coord{i, j}.toInt());
            }
        }
    }
    return e;
}

ostream & operator<<(ostream &out,const Ensemble e) { 
    out<<"{";
    int ca = e.cardinal();
    Ensemble e2= e;
    for(int i = 0;i<ca;i++){
		out << e2.tire() << " "; 
	}
	out<<"}";
	return out;
}

bool Ensemble::estVide()const{
    return card==0;
};

int Ensemble::cardinal()const{
    return card;
};

void Ensemble::ajoute(int n){
    if(card>=MAXCARD){
        throw runtime_error("ne peux pas ajouter car card>=MAXCARD");
    }
    t[card]= n ;
    card++;
}
int Ensemble::tire(){
    if(card <1){
        throw runtime_error("ne peux pas tirer d'ensemble d'un ensemble vide");
    }
    int alea = rand()%card;
    ///echange de alea et de la dernière case
    int tmp;
    tmp = t[alea];
    t[alea] = t[card - 1];
    card--;
    return tmp;
};



