#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "coord.hpp"

TEST_CASE("tests des méthode de COORD"){
	Coord c {1,3};
	CHECK(c.getLigne() == 1);
	CHECK(c.getColonne() == 3);
}
TEST_CASE("operateur =="){
	CHECK(Coord {3,4} == Coord {3,4} );
	CHECK_FALSE(Coord {3,4} == Coord {4,3} );
	CHECK_FALSE(Coord {1,2} == Coord {4,3} );
}
TEST_CASE("constructeur avec int"){
	CHECK(Coord {3} == Coord {0,3} );
	CHECK(Coord {10} == Coord {0,10} );
    CHECK(Coord {205} == Coord {2,5} );
    CHECK(Coord {125} == Coord {1,25} );
}
TEST_CASE("test toInt"){
	CHECK(Coord {0,3}.toInt()==3 );
	CHECK(Coord {1,0}.toInt()==100 );
	CHECK(Coord {2,1}.toInt()==201 );
    CHECK(Coord {3,21}.toInt()==321 );
}
TEST_CASE("test voisines"){
	CHECK(Coord {1,1}.voisines().cardinal()== 8);
    CHECK(Coord {0,0}.voisines().cardinal()== 3);
    CHECK(Coord {0,1}.voisines().cardinal()==5);
    CHECK(Coord {TAILLEGRILLE-1,1}.voisines().cardinal()==5);
}


//***********************ENSEMBLE************************

TEST_CASE("test methode ensemble"){
    srand(time(NULL));
    Ensemble e{};
    CHECK(e.estVide() );
    e.ajoute(5);
    CHECK_FALSE(e.estVide() );
    CHECK(e.cardinal()==1 );
    e.ajoute(6);
    e.ajoute(8);
    int res = e.tire();
	CHECK(e.cardinal()==2 );
	CHECK((res==5 or res==6 or res==8));
}


int main(int argc, const char **argv) {
	doctest::Context context(argc, argv);
	int test_result = context.run();
	if (context.shouldExit()) return test_result;
}
