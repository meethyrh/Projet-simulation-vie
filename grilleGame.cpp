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
    if(e == Espece::Vide)throw runtime_error("impossible ajoue animal vide (action inutile)");
    int id = pop.reserve();
    Animal a{e,c,id};
    pop.set(a);
    grille.setCase(id,c);
    

}

void Game::supprimeAnimal(Coord c){
    int id = grille.getCase(c);
    pop.supprime(id);
    grille.videCase(c);
}

void Game::deplaceAnimal(Coord c1,Coord c2){
    //cout <<grille<<endl;
    Animal a = getAnimal(c1);
    int id = a.getId();
    grille.setCase(id,c2);
    grille.videCase(c1);
    a.setCoord(c2);
    pop.set(a);
    //cout <<grille<<endl;

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
    Animal a = getAnimal(c);
    if(a.getEspece() == Espece::Lapin){
        Ensemble vois = c.voisines();
        Coord coordVois;
        do{
            coordVois= Coord {vois.tire()};
        }while( not grille.caseVide(coordVois) and not vois.estVide());
        //cout<<c << " " <<coordVois<<endl;
        if(not vois.estVide()){
            deplaceAnimal(c,coordVois);
        }
    }

}
void Game::bougeRenard(Coord c){
    Animal a = getAnimal(c);
    
    if(a.getEspece() == Espece::Renard){
        a.jeune();
        if(a.meurt()){
            supprimeAnimal(c);
            return;
        }
        Ensemble vois = c.voisines();
        Coord coordVois;
        Coord coordVoisVide;
        bool existeVide = false;
        Animal a2;
        do{
            coordVois= Coord {vois.tire()};
            if(grille.caseVide(coordVois)){
                existeVide = true;
                coordVoisVide = coordVois;
            }
            a2= getAnimal(coordVois);
        }while( not (a2.getEspece()==Espece::Lapin and a.getFood()<MaxFood ) and not vois.estVide());
        if(a2.getEspece()==Espece::Lapin  and a.getFood()<MaxFood ){
            supprimeAnimal(coordVois);
            deplaceAnimal(c,coordVois);
            a.mange();
        }else if(existeVide){
            deplaceAnimal(c,coordVoisVide);
        }
        
        pop.set(a);
    }
}