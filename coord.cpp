#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <exception>
//#include "doctest.h"
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
};

/*
TEST_CASE("tests des méthode de COORD"){
	Coord c {1,3};
	CHECK(c.getLigne() == 1);
	CHECK(c.getColonne() == 3);
}
TEST_CASE("operateur =="){
	CHECK(Coord {3,4} == Coord {3,4} );
	CHECK_FALSE(Coord {3,4} == Coord {4,3} );
	CHECK_FALSE(Coord {1,2} == Coord {4,3} );
}
TEST_CASE("constructeur avec int"){
	CHECK(Coord {3} == Coord {0,3} );
	CHECK(Coord {10} == Coord {1,0} );
	CHECK(Coord {21} == Coord {2,1} );
    CHECK(Coord {9} == Coord {0,9} );
	CHECK(Coord {0} == Coord {0,0} );
	CHECK(Coord {99} == Coord {9,9} );
}
TEST_CASE("test toInt"){
	CHECK(Coord {0,3}.toInt()==3 );
	CHECK(Coord {1,0}.toInt()==10 );
	CHECK(Coord {2,1}.toInt()==21 );
}
TEST_CASE("test voisines"){
	CHECK(Coord {1,1}.voisines().cardinal()== 8);
    CHECK(Coord {0,0}.voisines().cardinal()== 3);
    CHECK(Coord {0,1}.voisines().cardinal()==5);
    CHECK(Coord {TAILLEGRILLE-1,1}.voisines().cardinal()==5);
}*/



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

/*
TEST_CASE("test methode ensemble"){
    srand(time(NULL));
    Ensemble e{};
    CHECK(e.estVide() );
    e.ajoute(5);
    CHECK_FALSE(e.estVide() );
    CHECK(e.cardinal()==1 );
    e.ajoute(6);
    e.ajoute(8);
    int res = e.tire();
	CHECK(e.cardinal()==2 );
	CHECK((res==5 or res==6 or res==8));
}*/

/*void Ensemble::retire(int n){
    for(int i = 0; i < cardinal(); i++){
        if(t[i] == n){
            int tmp = t[cardinal() -1];
            t[cardinal()-1] = t[i];
            t[i] = tmp; 
            card--;
        }
    }
}*/

/*
TEST_CASE("test retire() ensemble"){
    Ensemble e{};
    e.ajoute(1); 
    e.retire(1);
    CHECK(e.estVide());
    e.ajoute(1);e.ajoute(2);e.ajoute(3);
    e.retire(2);
    CHECK(e.cardinal() == 2);
}*/


