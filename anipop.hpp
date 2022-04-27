#ifndef ANIPOP_HPP
#define ANIPOP_HPP

#include <array>
#include <iostream>
#include <vector>
#include "coord.hpp"

using namespace std;

enum class Espece{Lapin,Renard,Vide};

class Animal{
    Espece espece;
    Coord coord;
    int ident;
    
    public:
    Animal(Espece e,Coord c ,int id):espece{e},coord{c},ident{id}{}
    Animal():espece{Espece::Vide},coord{0},ident{-1}{}
    
    Espece getEspece()const{return espece; }
    Coord getCoord()const{return coord; }
    void setCoord(Coord c){coord = c;}
    int getId()const{return ident;}
    string toString()const;
    void mange(int n);
    void jeune();
    void meurt();
    bool seReproduit();
    
    
};  

ostream &operator<<(ostream &out, const Animal a);

class Population{
    array <Animal, MAXCARD> tabPop;
    Ensemble casesVides;
    
    
    public:
    Population();
    
    Animal get(int id)const;
    Ensemble getIds()const;
    int reserve();
    void set(Animal a);
    void supprime(int id);
    
};

ostream &operator<<(ostream &out, const Population a);

#endif
