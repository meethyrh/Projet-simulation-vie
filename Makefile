CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3 
LDFLAGS= -Wall -std=c++11 -g -O3 -lpdcurses -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -L -lsfml-graphics -lsfml-window -lsfml-system 
EXEC_FILES= test jeu

all: jeu
# Regle generique
%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

jeu: coord.o anipop.o grilleGame.o jeu.o primitives.o 
	$(CXX) -o $@ $^ $(LDFLAGS)


test: test.o coord.o anipop.o grilleGame.o 
	$(CXX) -o $@ $^ $(LDFLAGS)
    

coord.o: coord.hpp
anipop.o : anipop.hpp coord.hpp
grilleGame.o: anipop.hpp coord.hpp grilleGame.hpp
primitives.o : primitives.hpp
jeu.o: anipop.hpp coord.hpp grilleGame.hpp primitives.hpp

check: test
	./test

clean:
	rm -f *.o $(EXEC_FILES) core.*
