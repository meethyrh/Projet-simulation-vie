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
bool Game::trouverAmour(Coord c){
	Animal a = getAnimal(c);
	Animal a2;
	Coord coordVois;
	Espece espA = a.getEspece();
	if(espA==Espece::Vide)throw runtime_error("le vide ne peut pas trouver l'amour");
	Ensemble vois = c.voisines();
	do{
		coordVois= Coord {vois.tire()};	
		a2= getAnimal(coordVois);
		if(a2.getEspece() == espA and a.getSexe() == a2.getSexe())return true;
	}while(not vois.estVide());
	return false;
}


void Game::bougeLapin(){
	Grille CasesVisite;
	Ensemble CasesPourAlea;
	for(int i =0;i<TAILLEGRILLE*TAILLEGRILLE;i++)CasesPourAlea.ajoute(i);
	while(not CasesPourAlea.estVide()){
		Coord c{CasesPourAlea.tire()};
		if(CasesVisite.getCase(c)==-1){
			Animal a = getAnimal(c);
			if(a.getEspece() == Espece::Lapin){
				a.vieilli();
				pop.set(a);
				if(a.meurt()){
					supprimeAnimal(c);
					return;
				}
				Ensemble vois = c.voisines();
				bool reprodPossible = false;
				if(vois.cardinal()>=MinFreeBirthLapin and (trouverAmour(c)or not versReprodSexuee))reprodPossible=true;
				Coord coordVois;
				Animal a2;
				do{
					coordVois= Coord {vois.tire()};
					a2= getAnimal(coordVois);
					
				}while( not grille.caseVide(coordVois) and not vois.estVide());
				//cout<<c << " " <<coordVois<<endl;
				if(not vois.estVide()){
					deplaceAnimal(c,coordVois);
					CasesVisite.setCase(1,coordVois);
					//~ cout <<reprodPossible<<endl;
					if( reprodPossible and rand()%100 < ProbBirthLapin* (10*int(versReprodSexuee))){
						ajouteAnimal(Espece::Lapin,c);
					}
				}
			}
		}
	}

}
void Game::bougeRenard(){
	Grille CasesVisite;
	Ensemble CasesPourAlea;
	for(int i =0;i<TAILLEGRILLE*TAILLEGRILLE;i++)CasesPourAlea.ajoute(i);
	while(not CasesPourAlea.estVide()){
		Coord c{CasesPourAlea.tire()};
		if(CasesVisite.getCase(c)==-1){
			Animal a = getAnimal(c);
			if(a.getEspece() == Espece::Renard){
				a.jeune();
				a.vieilli();
				pop.set(a);
				//~ cout <<a.getFood()<<endl;
				if(a.meurt()){
					supprimeAnimal(c);
					return;
				}
				Ensemble vois = c.voisines();
				bool reprodPossible=false;
				if(trouverAmour(c)or not versReprodSexuee)reprodPossible=true;
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
				}while( not (a2.getEspece()==Espece::Lapin and a.getFood()<=MaxFood  ) and not vois.estVide());
				bool deplacement=false;
				
				if(a2.getEspece()==Espece::Lapin  and a.getFood()<=MaxFood ){
					a.mange();
					pop.set(a);
					supprimeAnimal(coordVois);
					deplaceAnimal(c,coordVois);
					CasesVisite.setCase(1,coordVois);
					deplacement=true;
				}else if(existeVide){
					deplaceAnimal(c,coordVoisVide);
					CasesVisite.setCase(1,coordVoisVide);
					deplacement=true;
				}
				if(deplacement==true and a.seReproduit() and rand()%100 < ProbBirthRenard * (10*int(versReprodSexuee)) and reprodPossible ){
					ajouteAnimal(Espece::Renard,c);
				}
				
				
			}
		}
	}
}
void Game::afficheRepartion(){
	cout<<"nombre de lapin : "<<pop.getNbLapin()<<endl;
    cout<<"nombre de renard : "<<pop.getNbRenard()<<endl;
    cout<<"duree de vie moyenne d'un lapin : "<<pop.getSommeDureeLapin() / pop.getNbMortLapin()<<endl;
    cout<<"duree de vie moyenne d'un renard : "<<pop.getSommeDureeRenard() / pop.getNbMortRenard()<<endl;
    //~ cout<<"1 : "<<pop.getSommeDureeLapin() <<endl;
    //~ cout<<"2 : "<< pop.getNbMortLapin()<<endl;
    //~ cout<<"3 : "<<pop.getSommeDureeRenard()<<endl;
    //~ cout<<"4 : "<< pop.getNbMortRenard()<<endl;
}





