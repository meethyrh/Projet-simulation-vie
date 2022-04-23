#include <iostream>
#include <array>
#include <stdlib.h>
#include <time.h>
#include "Ensemble.hpp"
#include "doctest.h"
using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"


//Constructeurs
Ensemble::Ensemble(): card{0}{
    tab.fill(0);
}

TEST_CASE("Constructeur vide"){
    CHECK(Ensemble().estVide());
}

//methodes
bool Ensemble::estVide() const{
    return (card==0);
}

TEST_CASE("ensemble vide"){
    CHECK(Ensemble().estVide());
    Ensemble e = Ensemble();
    e.ajoute(1);
    CHECK_FALSE(e.estVide());
}

int Ensemble::cardinal() const{
    return card;
}

TEST_CASE("cardinal"){
    CHECK(Ensemble().cardinal() == 0);
    Ensemble e = Ensemble();
    e.ajoute(1);
    CHECK(e.cardinal() == 1);
    e.ajoute(1);
    CHECK(e.cardinal() == 2);
    e.ajoute(1);
    CHECK(e.cardinal() == 3);
}

void Ensemble::ajoute(int a){
    if (card == MAXCARD){
        __throw_runtime_error("Ensemble plein");
    } else {
        tab[card] = a;
        card++;
    }
}

TEST_CASE("ajoute"){
    Ensemble e = Ensemble();
    e.ajoute(0);
    CHECK(e.tab[0] == 0);
    e.ajoute(1);
    CHECK(e.tab[1] == 1);
    e.ajoute(2);
    CHECK(e.tab[2] == 2);

    Ensemble f = Ensemble();
    f.card = MAXCARD;
    CHECK_THROWS_AS(f.ajoute(1), runtime_error);
}

int Ensemble::tire(){
    if (card == 0){
        __throw_runtime_error("Ensemble vide");
    }
    srand(time(NULL));
    int rdn = rand() % card;
    int val = tab[rdn];
    swap(tab[rdn], tab[card-1]);
    card--;
    return val;
}

TEST_CASE("tire"){
    Ensemble e = Ensemble();
    e.ajoute(0);
    e.ajoute(1);
    e.ajoute(2);
    CHECK(e.card == 3);
    e.tire();
    CHECK(e.card == 2);
    e.tire();
    CHECK(e.card == 1);
    e.tire();
    CHECK(e.card == 0);

    Ensemble f = Ensemble();
    CHECK_THROWS_AS(f.tire(), runtime_error);
}

//fonctions
ostream& operator<<(ostream &out, Ensemble e){
    for(int i = 0; i < e.card; i++){
        out << e.tab[i] << " ";
    } return out;
}

void swap(int &a, int &b){
    int c = a;
    a = b;
    b = c;
}

int main(int argc, const char** argv){
    doctest::Context context(argc, argv);
    int test_result = context.run();
    if (context.shouldExit()) return test_result;

    
    return 0;
}