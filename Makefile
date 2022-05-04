CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3 -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS=
EXEC_FILES= test jeu
sfmlvar= -lsfml-graphics -lsfml-window -lsfml-system

all: jeu
# Regle generique
%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

jeu: coord.o anipop.o grilleGame.o jeu.o primitives.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(sfmlvar)


test: test.o coord.o anipop.o grilleGame.o 
	$(CXX) -o $@ $^ $(LDFLAGS)
    

coord.o: coord.hpp
anipop.o : anipop.hpp coord.hpp
grilleGame.o: anipop.hpp coord.hpp grilleGame.hpp
primitives.o: primitives.h
jeu.o: anipop.hpp coord.hpp grilleGame.hpp primitives.h

check: test
	./test

clean:
	rm -f *.o $(EXEC_FILES) core.*
