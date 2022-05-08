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

Ensemble Game::voisinsVides(Coord c)const{
	Ensemble ens= c.voisines();
	Ensemble ensVide;
	while(not ens.estVide()){
		int coordVois = ens.tire();
		if(grille.getCase(coordVois) == -1){
			ensVide.ajoute(coordVois);
		}
	}
	return ensVide;
}


Ensemble Game::voisinsEspece(Coord c,Espece e)const{
	if(e==Espece::Vide)throw runtime_error("veuillez utiliser la méthode voisinsVide pour chercher des cases vides");
	Ensemble ens= c.voisines();
	Ensemble ensEspece;
	while(not ens.estVide()){
		int coordVois = ens.tire();
		int id = grille.getCase(coordVois);
		if(id != -1){
			Animal a = pop.get(id);
			if(a.getEspece() == e){
				ensEspece.ajoute(coordVois);
			}
		}
	}
	return ensEspece;
}


Animal Game::getAnimal(Coord c)const{
    int id = grille.getCase(c);
    return pop.get(id);
}
bool Game::trouverAmour(Coord c){
	if(not (versReprodEntreEspece) and not (versReprodSexuee))return true;
	Animal a = getAnimal(c);
	Espece espA = a.getEspece();
	if(espA==Espece::Vide)throw runtime_error("le vide ne peut pas trouver l'amour");
	Ensemble voisEsp = voisinsEspece(c, espA);
	if(not(voisEsp.estVide())and versReprodEntreEspece)return true;
	Animal a2;
	Coord coordVois;
	while(not voisEsp.estVide()){
		coordVois= Coord {voisEsp.tire()};
		a2= getAnimal(coordVois);
		if( a.getSexe() == a2.getSexe() and versReprodSexuee)return true;
	}
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
				Ensemble voisVides = voisinsVides(c);
				if(a.meurt()){
					supprimeAnimal(c);
				}else{
					bool reprodPossible = false;
					if(voisVides.cardinal()>=MinFreeBirthLapin and trouverAmour(c))reprodPossible=true;
					
					if(not voisVides.estVide()){
						Coord coordVois = Coord {voisVides.tire()};
						deplaceAnimal(c,coordVois);
						CasesVisite.setCase(1,coordVois);
						//~ cout <<reprodPossible<<endl;
						if( reprodPossible and rand()%100 < ProbBirthLapin*100){
							ajouteAnimal(Espece::Lapin,c);
						}
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
				}else{
					Ensemble voisVides = voisinsVides(c);
					
					Ensemble voisLapin = voisinsEspece(c,Espece::Lapin);
					bool reprodPossible=false;
					if(trouverAmour(c))reprodPossible=true;
					Coord coordVois;
					
					bool deplacement=false;
					if(not (voisLapin.estVide())  and a.getFood()<=MaxFood -FoodLapin){
						coordVois= Coord {voisLapin.tire()};
						a.mange();
						pop.set(a);
						supprimeAnimal(coordVois);
						deplaceAnimal(c,coordVois);
						CasesVisite.setCase(1,coordVois);
						deplacement=true;
					}else if(not (voisVides.estVide())){
						coordVois= Coord {voisVides.tire()};
						deplaceAnimal(c,coordVois);
						CasesVisite.setCase(1,coordVois);
						deplacement=true;
						
					}
					if(deplacement==true and a.seReproduit() and rand()%100 < ProbBirthRenard*100 and reprodPossible ){
						ajouteAnimal(Espece::Renard,c);
					}
				}
			}
		}
	}
}
void Game::verifieGrille()const{
	for(int id= 0;id<TAILLEGRILLE * TAILLEGRILLE;id++){
		Animal a = pop.get(id);
		if( a.getEspece()!=Espece::Vide){
			if(a.getId() != id)throw runtime_error("probleme d'assignation d'id des animaux");
			Coord c = a.getCoord();
			int idAnimGrille = grille.getCase(c);
			if(idAnimGrille != id)throw runtime_error("probleme de localisation des animaux");
		}
	}
	cout<<"aucune dectection de probleme  avec verifieGrille";
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

void Game::afficheDonnee(){
	cout<<"nombre de lapin : "<<pop.getNbLapin()<<endl;
    cout<<"nombre de renard : "<<pop.getNbRenard()<<endl;
    cout<<"duree de vie moyenne d'un lapin : "<<pop.getSommeDureeLapin() / pop.getNbMortLapin()<<endl;
    cout<<"duree de vie moyenne d'un renard : "<<pop.getSommeDureeRenard() / pop.getNbMortRenard()<<endl;
    cout<<"duree de vie max atteinte par un lapin : "<<pop.getMaxDureeLapin()<<endl;
    cout<<"duree de vie max atteinte par un renard : "<<pop.getMaxDureeRenard()<<endl;
    verifieGrille();
    //~ cout<<grille;
    //~ cout<<"1 : "<<pop.getSommeDureeLapin() <<endl;
    //~ cout<<"2 : "<< pop.getNbMortLapin()<<endl;
    //~ cout<<"3 : "<<pop.getSommeDureeRenard()<<endl;
    //~ cout<<"4 : "<< pop.getNbMortRenard()<<endl;
}





