#ifndef ANIPOP_HPP
#define ANIPOP_HPP

#include <array>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "coord.hpp"

using namespace std;

const bool versAge = true;
const bool versReprodEntreEspece = false;
const bool versReprodSexuee = false; 

const int FoodInit = 5;
const int FoodLapin = 5;
const int FoodReprod = 8;
const int MaxFood = 10;
const float ProbBirthRenard = 0.05 ;//+ int(versReprodEntreEspece)*5*0.05+ int(versReprodSexuee)*10*0.05;
const float ProbBirthLapin = 0.3 ;//+ int(versReprodEntreEspece)*5*0.3+ int(versReprodSexuee)*10*0.3;
const int MinFreeBirthLapin = 5;
const int DureeDeVieLapin = 100;
const int DureeDeVieRenard = 200;

enum class Espece{Lapin,Renard,Vide};

class Animal{
    Espece espece;
    Coord coord;
    int ident;
    int nvNourriture;
    int age;
    bool sexe;
    
    public:
    //Construit un animal avec une espèce donnée, ses coordonées et son identifiant
    /*
    param: espece, coord, int
    return Animal
    */
    Animal(Espece e,Coord c ,int id):espece{e},coord{c},ident{id},nvNourriture{FoodInit},age{0},sexe {rand()%100>50}{}

    //Construit un animal corespondant à une case vide (un animal "Vide")
    /*
    param: 
    return Animal "vide"
    */
    Animal():espece{Espece::Vide},coord{0},ident{-1}{}
    
    //Renvoie l'espece d'un animal 
    /*
    param: 
    return Espece de l'animal
    */
    Espece getEspece()const{return espece; }

    //Renvoi les coordonnées d'un animal
    /*
    param: 
    return Coordonee de l'animal
    */
    Coord getCoord()const{return coord; }

    //procédure qui change les coordonnées d'un animal
    /*
    param: coord
    return void
    */
    void setCoord(Coord c){coord = c;}

    //renvoi l'identifiant d'un animal
    /*
    param: 
    return identifiant de l'animal
    */
    int getId()const{return ident;}
    
    // renvoie l'age d'un animal;
    /*
    param:
    return: int, l'age de l'animal
    */ 
    int getAge()const{return age;}
	
    //renvoie le sexe de l'animal
    /*
    param: 
    return: true = un sexe, false l'autre
    */
	bool getSexe()const{return sexe;}

    //renvoie le niveau de nourriture d'un animal (renard)
    /*
    param:
    return: int, son niveau de nourriture
    */
    int getFood() const{return nvNourriture;}

    //Renvoi l'éspcèce à laquelle appartient l'animal
    /*
    param: 
    return l'espece de l'animal en chaine de caractères
    */
    string toString()const;

    //procédure qui diminue le niveau de faim d'un animal; ne pourra plus manger si l'animal n'a pas dutout faim
    /*
    param: int (identifiant de l'animal)
    return void
    */
    void mange();

    // procédure qui augmente le niveau de faim d'un animal; si il a vraiment faim et qu'il jeune, il meurt
    /*
    param: 
    return void
    */
    void jeune();

    //procédure qui supprime l'animal de la population et met à jour la grille
    /*
    param: 
    return void
    */
    bool meurt();

    //Ajoute un animal à la population et met a jour la grille
    /*
    param: 
    return bool True si il s'est reproduit et false sinon
    */
    bool seReproduit();
    
    // augmente l'age d'un animal
    /*
    param: 
    return: void
    */
    void vieilli();
    
    
};  

// surcharge de << pour un animal
ostream &operator<<(ostream &out, const Animal a);

class Population{
    array <Animal, MAXCARD+1> tabPop;
    Ensemble casesVides;
    int nbRenard;
    int nbLapin;
    float sommeDureeLapin;
	float nbMortLapin;
	float sommeDureeRenard;
	float nbMortRenard;
    float maxDureeLapin;
	float maxDureeRenard;
    public:
    //Construit une population vide
    Population();
    
    //Renvoi l'animal d'indentifiant connu id
    /*
    param: id
    return Animal d'identifiant id
    */
    Animal get(int id)const;

    //renvoie le nombre de renard dans une population
    /*
    param:
    return: entier, le nombre de renard
    */
    int getNbRenard()const{return nbRenard;}

    // renvoie le nombre de lapin
    /*
    param:
    return: entier, le nombre de lapin
    */
    int getNbLapin()const{return nbLapin;}

    // renvoie la somme des durrées de vie de tous les Lapins
    /*
    param: 
    return: float
    */
    float getSommeDureeLapin()const{return sommeDureeLapin;}

    // renvoie le nombre de mort de Lapin
    /*
    param: 
    return: float, le nombre de mort des lapins
    */
    float getNbMortLapin()const{return nbMortLapin;}

    //renvoie la somme des durrées de vie de tous les Renards
    /*
    param:
    return: float
    */
    float getSommeDureeRenard()const{return sommeDureeRenard;}

    //renvoie le nombre de mort de renard
    /*
    param:
    return: float
    */
    float getNbMortRenard()const{return nbMortRenard;}

    // renvoie la durée de vie maximale d'un lapin
    /*
    param: 
    return: float
    */
    float getMaxDureeLapin()const{return maxDureeLapin;}

    // renvoie la durée de vie maximale d'un renard
    /*
    param:
    return: float
    */
    float getMaxDureeRenard()const{return maxDureeRenard;}

    //Donne l'ensemble des animaux qui existe ou ne sont pas mort dans la population
    /*
    param: 
    return Ensemble contenant les indentifiant des animaux non vide de la population
    */
    Ensemble getIds()const;

    //reserve un identifiant pas encore pris par un animal et met a jour la liste des casesVides
    /*
    param: 
    return int représentant un identifiant non utilisé par un animal
    */
    int reserve();
    
    //procédure qui ajoute un animal à la population
    /*
    param: Animal a
    return void
    */
    void set(Animal a);

    //procédure qui supprime un animal avec un identifiant id de la population et met à jour les cases vides...
    /*
    param: identifiant id
    return void
    */
    void supprime(int id);
    
};

//surcharde de << pour une population
ostream &operator<<(ostream &out, const Population a);

#endif
