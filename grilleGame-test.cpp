#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "coord.hpp"
#include "anipop.hpp"
#include "grilleGame.hpp"

TEST_CASE("Grille()"){
    Grille g{};
    int taille = TAILLEGRILLE *TAILLEGRILLE;
    for(int i = 0; i < taille; i++){
        CHECK(g.getCase(i) == -1);
    }
}

TEST_CASE("Case vide, set case, get case, vide case"){
    Grille g{};
    CHECK(g.caseVide(10));
    g.setCase(1, 10);
    CHECK_FALSE(g.caseVide(10));
    CHECK(g.getCase(10)==1);
    g.videCase(10);
    CHECK(g.caseVide(10));

    CHECK(g.caseVide(6));
    g.setCase(1, 6);
    CHECK_FALSE(g.caseVide(6));
    CHECK(g.getCase(6)==1);
    g.videCase(6);
    CHECK(g.caseVide(6));

    CHECK(g.caseVide(105));
    g.setCase(1, 105);
    CHECK_FALSE(g.caseVide(105));
    CHECK(g.getCase(105)==1);
    g.videCase(105);
    CHECK(g.caseVide(105));
}


TEST_CASE("constructeur Game"){
    int sommeLapin = 0;
    int sommeRenard = 0;
    for(int i = 0; i < 100; i++){
        Game g{7,20};;
        int nbLapin = 0;
        int nbRenard = 0;
        for(int i = 0; i < TAILLEGRILLE*TAILLEGRILLE; i++){
            if(g.getAnimal(i).getEspece() == Espece::Lapin){
                nbLapin++;
            } else if (g.getAnimal(i).getEspece() == Espece::Renard){
                nbRenard++;
            }
        } 
        sommeLapin += nbLapin;
        sommeRenard += nbRenard;
    } 
    bool test = round(sommeLapin/(TAILLEGRILLE*TAILLEGRILLE)) <= 21 and round(sommeLapin/(TAILLEGRILLE*TAILLEGRILLE)) >= 19;
    CHECK(test);
    bool test2 = round(sommeRenard/(TAILLEGRILLE*TAILLEGRILLE)) <= 8 and round(sommeRenard/(TAILLEGRILLE*TAILLEGRILLE)) >= 6;
    CHECK(test2);

}

TEST_CASE("get animal, ajoute animal, supprime"){
    Game g{0,0};
    g.ajouteAnimal(Espece::Lapin, 10);
    Animal a = g.getAnimal(10);
    CHECK(a.getEspece() == Espece::Lapin);
    CHECK(a.getCoord() == 10);
    CHECK(g.getCaseGame(10) != -1);

    g.ajouteAnimal(Espece::Renard, 20);
    Animal b = g.getAnimal(20);
    CHECK(b.getEspece() == Espece::Renard);
    CHECK(b.getCoord() == 20);
    CHECK(g.getCaseGame(20) != -1);

    g.supprimeAnimal(10);
    CHECK(g.getCaseGame(10) == -1);

    g.supprimeAnimal(20);
    CHECK(g.getCaseGame(20) == -1);

}

TEST_CASE("voisin vide"){
    Game g{0,0};
    g.ajouteAnimal(Espece::Lapin, {2,2});
    Ensemble v = g.voisinsVides({2,2});
    CHECK_FALSE(v.estVide());
    CHECK(v.cardinal() == 8);

    g.ajouteAnimal(Espece::Lapin, {2,3});
    v = g.voisinsVides({2,2});
    CHECK(v.cardinal() == 7);

    g.ajouteAnimal(Espece::Lapin, {2,1});
    v = g.voisinsVides({2,2});
    CHECK(v.cardinal() == 6);

    g.ajouteAnimal(Espece::Lapin, {1,2});
    v = g.voisinsVides({2,2});
    CHECK(v.cardinal() == 5);
}


TEST_CASE("voisin Espece"){
    Game g{0,0};
    g.ajouteAnimal(Espece::Lapin, {2,2});
    Ensemble v = g.voisinsEspece({2,2}, Espece::Lapin);
    CHECK(v.estVide());

    g.ajouteAnimal(Espece::Lapin, {2,3});
    v = g.voisinsEspece({2,2}, Espece::Lapin);
    CHECK(v.cardinal() == 1);

    g.ajouteAnimal(Espece::Renard, {2,1});
    v = g.voisinsEspece({2,2}, Espece::Renard);
    CHECK(v.cardinal() == 1);

    g.ajouteAnimal(Espece::Lapin, {1,2});
    v = g.voisinsEspece({2,2}, Espece::Lapin);
    CHECK(v.cardinal() == 2);

    g.ajouteAnimal(Espece::Renard, {3,2});
    v = g.voisinsEspece({2,2}, Espece::Renard);
    CHECK(v.cardinal() == 2);
}

TEST_CASE("trouver ammour"){
    Game g{0,0};

    g.ajouteAnimal(Espece::Lapin, {2,2});
    Animal a = g.getAnimal({2,2});

    g.ajouteAnimal(Espece::Lapin, {2,3});
    Animal b = g.getAnimal({2,3});

    bool pareil = (a.getSexe() == b.getSexe());
    bool amour = g.trouverAmour({2,2});
    if(versReprodSexuee){
        CHECK(pareil == amour);
    } else{
        CHECK(amour);
    }


    g.ajouteAnimal(Espece::Lapin, {4,4});
    g.ajouteAnimal(Espece::Renard, {4,5});
    if(versReprodSexuee or versReprodEntreEspece){
        CHECK_FALSE(g.trouverAmour({4,4}));
    } else {
        CHECK(g.trouverAmour({4,4}));
    }
    
}

TEST_CASE("Deplacement Animal"){
    Game g{0,0};
    g.ajouteAnimal(Espece::Lapin, {3,4});
    g.deplaceAnimal({3,4}, {3,5});
    CHECK(g.getCaseGame({3,4}) == -1);
    CHECK(g.getCaseGame({3,5}) == g.getAnimal({3,5}).getId());
}

TEST_CASE(" Bouge lapin"){
    Game g{0,0};
    g.ajouteAnimal(Espece::Lapin, {5,9});
    g.ajouteAnimal(Espece::Lapin, {3,4});
    g.bougeLapin();
    CHECK(g.getCaseGame({5,9}) == -1);
    CHECK(g.getCaseGame({3,4}) == -1);
}

TEST_CASE(" Bouge renard"){
    Game g{0,0};
    g.ajouteAnimal(Espece::Renard, {5,9});
    g.ajouteAnimal(Espece::Renard, {3,4});
    g.ajouteAnimal(Espece::Lapin, {3,5});
    g.bougeRenard();
    CHECK(g.getCaseGame({5,9}) == -1);
    CHECK(g.getCaseGame({3,4}) == -1);
    CHECK(g.getAnimal({3,5}).getEspece() == Espece::Renard);
}


int main(int argc, const char **argv) {
	doctest::Context context(argc, argv);
	int test_result = context.run();
	if (context.shouldExit()) return test_result;
}