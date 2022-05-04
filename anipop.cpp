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
    return nvNourriture <= 0;
}

void Animal::jeune(){
    nvNourriture --;
}
void Animal::mange(){
    nvNourriture = nvNourriture +FoodLapin;
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
}

int Population::reserve(){
    if(casesVides.estVide())throw runtime_error("nombre maximum d'animaux atteint");
    return casesVides.tire();
}
void Population::set(Animal a){
    tabPop[a.getId()]=a;
}
void Population::supprime(int id){
    if(casesVides.cardinal()==MAXCARD+1)throw runtime_error("impossible de supprimer un animal d'une population vide");
    if(id == -1)throw runtime_error("impossible de supprimer un animal vide");
    Animal a{};
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
