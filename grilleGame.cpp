#include <array>
#include <iostream>
#include <vector>
#include <exception>
#include "grilleGame.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;

Grille::Grille(){
   for(int c = 0; c<TAILLEGRILLE *TAILLEGRILLE;c++){
       videCase(c);
   }
}


bool Grille::caseVide(Coord c)const{
    return grille[c.getLigne()][c.getColonne()]==-1;
}
int Grille::getCase(Coord c)const{
    return grille[c.getLigne()][c.getColonne()];
}
void Grille::videCase(Coord c){
    grille[c.getLigne()][c.getColonne()]=-1;
}
void Grille::setCase(int id,Coord c){
    if(not caseVide(c))throw runtime_error("impossible d'ajouter un animal dans une case pleine");
    grille[c.getLigne()][c.getColonne()]=id;
}

ostream &operator<<(ostream &out, const Grille grille) {
    for(int i = 0; i<TAILLEGRILLE;i++){
        for(int j = 0; j<TAILLEGRILLE;j++){
            out << grille.getCase({i,j}) << " ";
        }
        out << endl;
    }
    return out;
}



void Game::ajouteAnimal(Espece e,Coord c){
    int id = pop.reserve();
    grille.setCase(id,c);
    Animal a{e,c,id};
    pop.set(a);

}

void Game::supprimeAnimal(Coord c){
    int id = grille.getCase(c);
    pop.supprime(id);
}

void Game::deplaceAnimal(Coord c1,Coord c2){
    Animal a = getAnimal(c1);
    int id = a.getId();
    grille.setCase(id,c2);
    grille.videCase(c1);
    a.setCoord(c2);
    pop.set(a);

}

Game::Game(int probR,int probL):grille{},pop{}{
    srand(time(NULL));
    for(int c= 0;c<TAILLEGRILLE * TAILLEGRILLE;c++){
        int alea = rand()%100;
        if(alea>=0 and alea<probR){
            ajouteAnimal(Espece::Renard,c);
        }
        else if(alea>=probR and alea<probR+probL){
            ajouteAnimal(Espece::Lapin,c);
        }
        else{
            ajouteAnimal(Espece::Vide,c);
        }
    }
}

ostream &operator<<(ostream &out, const Game g){
    for(int i = 0; i<TAILLEGRILLE;i++){
        for(int j = 0; j<TAILLEGRILLE;j++){
            out << g.getAnimal({i,j}).toString() <<" ";
        }
        out << endl;
    }
    return out;
}

Animal Game::getAnimal(Coord c)const{
    int id = grille.getCase(c);
    return pop.get(id);
}
void Game::bougeLapin(Coord c){
    if(getAnimal(c).getEspece() == Espece::Lapin){
        Ensemble vois = c.voisines();
        Coord coordVois;
        do{
            coordVois= Coord {vois.tire()};
        }while(not grille.caseVide(coordVois) and not vois.estVide());
        cout<<c << " " <<coordVois<<endl;
        if(not vois.estVide()){
            deplaceAnimal(c,coordVois);
        }
    }

}
