#ifndef GRILLEJEU_HPP
#define GRILLEJEU_HPP

#include <array>
#include <iostream>
#include <vector>
#include <cmath>
#include "coord.hpp"
#include "anipop.hpp"

using namespace std;


class Grille{
    array<array<int,TAILLEGRILLE>,TAILLEGRILLE> grille;

    public:
    bool caseVide()const;
    int getCase(Coord c)const;

    void videCase(Coord c);
    void setCase(int id,Coord c);

}







#endif