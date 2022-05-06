#include <array>
#include <iostream>
#include <vector>
#include <exception>
#include "anipop.hpp"

using namespace std;

string Animal::toString()const{
    switch(espece){
        case Espece::Renard: return "R";    
        case Espece::Lapin: return "L";
        default: return ".";
    } 
}

bool Animal::meurt(){
    if(nvNourriture <= 0 )return true;
    if(versAge){
		if(espece==Espece::Lapin and age >= DureeDeVieLapin){
			return true;
		}
		if(espece==Espece::Renard and age >= DureeDeVieRenard){
			return true;
		}
	}
	return false;
	
}

void Animal::jeune(){
    nvNourriture --;
}
void Animal::mange(){
    nvNourriture = nvNourriture +FoodLapin;
}

bool Animal::seReproduit(){
	return nvNourriture>=FoodReprod;
}

void Animal::vieilli(){
	age++;
}
ostream & operator<<(ostream &out,const Animal a){
    out << a.toString()<<" "<<a.getCoord()<<" "<<a.getId();
    return out;
}

Population::Population(){
    tabPop.fill(Animal{});
    for(int i = 0;i<MAXCARD;i++){
        casesVides.ajoute(i);
    }
    nbLapin=0;
    nbRenard=0;
    sommeDureeLapin = 0;
	nbMortLapin = 0;
	sommeDureeRenard = 0 ;
	nbMortRenard=0;
}

int Population::reserve(){
    if(casesVides.estVide())throw runtime_error("nombre maximum d'animaux atteint");
    return casesVides.tire();
}
void Population::set(Animal a){
	if(a.getEspece()==Espece::Vide)throw runtime_error("impossible d'ajouter un animal vide a la pop");
	else if(tabPop[a.getId()].getEspece()==Espece::Vide){
		if(a.getEspece()==Espece::Lapin)nbLapin++;
		if(a.getEspece()==Espece::Renard)nbRenard++;
	}
	else if(a.getEspece()!=tabPop[a.getId()].getEspece())throw runtime_error("impossible de modifier l'espece");
    tabPop[a.getId()]=a;
}
void Population::supprime(int id){
    if(casesVides.cardinal()==MAXCARD+1)throw runtime_error("impossible de supprimer un animal d'une population vide");
    if(id == -1)throw runtime_error("impossible de supprimer un animal vide");
    Animal a{};
    if(tabPop[id].getEspece()==Espece::Lapin){
		nbLapin--;
		nbMortLapin++;
		sommeDureeLapin = sommeDureeLapin + tabPop[id].getAge();
	}
	if(tabPop[id].getEspece()==Espece::Renard){
		nbRenard--;
		nbMortRenard++;
		sommeDureeRenard = sommeDureeRenard + tabPop[id].getAge();
	}
    tabPop[id]=a;
    casesVides.ajoute(id);
}

Animal Population::get(int id)const{
    if(id>=MAXCARD+1)throw invalid_argument("identifiant non existant");
    if(id>-1)return tabPop[id];
    else return Animal{};
}
Ensemble Population::getIds() const{
    Ensemble e;
    for(int i = 0;i<MAXCARD;i++){
        if(tabPop[i].getEspece()!=Espece::Vide){
            e.ajoute(i);
        }
    }
    return e;
}
ostream &operator<<(ostream &out, const Population p){
    Ensemble e = p.getIds();
    while(not e.estVide()){
        out << p.get(e.tire())<<endl;
    }
    return out;
}
