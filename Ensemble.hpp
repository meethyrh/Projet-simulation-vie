#ifndef ENSEMBLE_HPP
#define ENSEMBLE_HPP

#include <iostream>
#include <array>
using namespace std;

int const MAXCARD  = 10;

struct Ensemble{
    //ATTRIBUTS*********************************************************
    array<int, MAXCARD> tab;
    int card;

    //METHODES *********************************************************

    //renvoie true si le tableau est vide et false sinon
    bool estVide() const;

    //Renvoie le nombre d'élement d'un tableau (différent de la taille du tableau)
    int cardinal() const;

    //ajoute un élément à l'ensemble 
    void ajoute(int a);
    
    //renvoie un élement pris au hasard dans l'ensemble et le suprime
    int tire();

    

    //CONSTRUCTEURS ****************************************************
    Ensemble();

};

//surcharge de << pour un ensemble
ostream& operator<<(ostream &out, Ensemble e);

void swap(int &a, int &b);

#endif