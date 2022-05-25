#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "anipop.hpp"
#include "coord.hpp"
#include <string>


TEST_CASE("constructeur animal et des méthode get..."){
    Animal a{};
    CHECK(a.getEspece() == Espece::Vide);

    Animal b{Espece::Lapin, 10, 10};
    CHECK(b.getEspece() == Espece::Lapin);
    CHECK(b.getCoord() == 10);
    CHECK( b.getId() == 10);
    CHECK( b.getFood() == FoodInit );
    CHECK(b.getAge() == 0 );
    //CHECK(b.getSexe() or not b.getSexe());

    Animal c{Espece::Renard, 9, 9};
    CHECK(c.getEspece() == Espece::Renard );
    CHECK( c.getCoord() == 9 );
    CHECK( c.getId() == 9);
    CHECK( c.getFood() == FoodInit );
    CHECK( c.getAge() == 0 );
   //CHECK( (c.getSexe() or not c.getSexe()));
    
}

TEST_CASE("set coord"){
    Animal d{Espece::Lapin, 10, 10};
    CHECK(d.getCoord() == 10);
    d.setCoord(11);
    CHECK(d.getCoord() == 11);
    d.setCoord(315);
    CHECK(d.getCoord() == 315);
}

TEST_CASE("mange, jeune"){
    Animal e{Espece::Renard, 10, 10};
    CHECK(e.getFood() == FoodInit);
    e.mange();
    CHECK(e.getFood() == 10);
    e.jeune();
    CHECK(e.getFood() == 9);
    e.mange();
    CHECK(e.getFood() == 14);
    e.jeune();
    CHECK(e.getFood() == 13);
}

TEST_CASE("reproduction"){
    Animal f{Espece::Renard, 2,3};
    CHECK_FALSE(f.seReproduit());
    f.mange();
    CHECK(f.seReproduit());
    f.jeune();
    f.mange();
    CHECK(f.seReproduit());
}

TEST_CASE("vieilli"){
    Animal g{Espece::Lapin, 1,2};
    CHECK(g.getAge() == 0);
    g.vieilli();
    CHECK(g.getAge() == 1);
    g.vieilli();
    CHECK(g.getAge() == 2);
    g.vieilli();
    CHECK(g.getAge() == 3);
}

TEST_CASE("To string"){
    Animal h{};
    CHECK(h.toString() == ".");
    Animal i{Espece::Lapin, 1,2};
    CHECK(i.toString() == "L");
    Animal j{Espece::Renard, 1,2};
    CHECK(j.toString() == "R");
}


//******************************************************************************

TEST_CASE("constructeur popultation"){
    Population p{};
    CHECK(p.getNbLapin()==0);
    CHECK(p.getNbRenard()==0);
    CHECK(p.getSommeDureeLapin()==0);
    CHECK(p.getSommeDureeRenard()==0);
	CHECK(p.getNbMortLapin()==0);
    CHECK(p.getNbMortRenard()==0);
	CHECK(p.getMaxDureeLapin()==0);
    CHECK(p.getMaxDureeRenard()==0);
    CHECK(p.getIds().estVide());
}


TEST_CASE("reserve"){
    Population p{};
    int id = p.reserve();
    CHECK(p.get(id).getEspece() == Espece::Vide);
    int id2 = p.reserve();
    CHECK(p.get(id2).getEspece() == Espece::Vide);
    int id3 = p.reserve();
    CHECK(p.get(id3).getEspece() == Espece::Vide);
}

TEST_CASE("set"){
    Population p{};
    int id = p.reserve();
    Animal a{Espece::Lapin, 0, id};
    p.set(a);
    CHECK(p.get(id).getEspece() == Espece::Lapin);
    CHECK(p.get(id).getCoord() == 0);

    int id2 = p.reserve();
    Animal a2{Espece::Renard, 10, id2};
    p.set(a2);
    CHECK(p.get(id2).getEspece() == Espece::Renard);
    CHECK(p.get(id2).getCoord() == 10);


}

TEST_CASE("Supprime"){
    Population p{};
    int id = p.reserve();
    Animal a{Espece::Lapin, 0, id};
    p.set(a);
    p.supprime(id);
    CHECK(p.get(id).getEspece() == Espece::Vide);

    int id2 = p.reserve();
    Animal a2{Espece::Renard, 10, id2};
    p.set(a2);
    p.supprime(id2);
    CHECK(p.get(id).getEspece() == Espece::Vide);

    CHECK(p.getNbLapin() == 0);
    CHECK(p.getNbRenard() == 0);
    
}

TEST_CASE("get id"){
    Population p{};
    int id = p.reserve();
    Animal a{Espece::Lapin, 0, id};
    p.set(a);

    int id2 = p.reserve();
    Animal a2{Espece::Renard, 10, id2};
    p.set(a2);
    Ensemble e = p.getIds();
    CHECK(e.cardinal() == 2);
    int s = e.tire();
    bool test = ((s == id) or (s == id2));
    CHECK(test);

    int m = e.tire();
    test = ((m == id) or (m == id2));
    CHECK(test);

}


int main(int argc, const char **argv) {
	doctest::Context context(argc, argv);
	int test_result = context.run();
	if (context.shouldExit()) return test_result;
}