#include <iostream>
#include <vector>
#include "grilleGame.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"


using namespace std;

int main(){
//     Grille g;
    
//     g.setCase(5454,0);
//     cout<< g;
    Game g{10,10};
    // Population p;
    // for(int i = 0;i<10;i++){
    //     Animal a = {Espece::Lapin, {1,0}, p.reserve()};
    //     p.set(a);
    // }
    // cout<<p;
    
//     cout << a.toString() << endl;
//     array<int, 6> n;
//     for(int i = 0;i<6;i++)cout<<n[i];
    
    for(int i =0;i<5;i++){
        for(int c =0;c<TAILLEGRILLE*TAILLEGRILLE;c++){
            g.bougeLapin(c);
        }
        //cout<<g<<endl;
    }
    
    
    return 0;
}