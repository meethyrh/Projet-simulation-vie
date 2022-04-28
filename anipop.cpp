#include <array>
#include <iostream>
#include <vector>
#include <exception>
#include "anipop.hpp"
#include "doctest.h"

using namespace std;

string Animal::toString()const{
    switch(espece){
        case Espece::Renard: return "Renard";    
        case Espece::Lapin: return "Lapin";
        default: return "Animal indéfini";
    } 
}

TEST_CASE("to string function"){

}

ostream & operator<<(ostream &out,const Animal a){
    out << a.toString()<<" "<<a.getCoord()<<" "<<a.getId();
    return out;
}

Population::Population(){
    tabPop.fill(Animal{});
    for(int i = 0;i<MAXCARD-1;i++){
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
    if(casesVides.cardinal()==MAXCARD)throw runtime_error("impossible de supprimer un animal d'une population vide");
    Animal a{};
    tabPop[id]=a;
    casesVides.ajoute(id);
}

Animal Population::get(int id)const{
    if(id>=MAXCARD)throw invalid_argument("identifiant non existant");
    return tabPop[id];
}
Ensemble Population::getIds() const{
    Ensemble e;
    for(int i = 0;i<MAXCARD-1;i++){
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
