CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3
LDFLAGS= -Wall -std=c++11 -g -O3
EXEC_FILES= jeu testCoord testAnipop testGG

all: jeu
# Regle generique
%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

jeu: coord.o anipop.o grilleGame.o jeu.o  
	$(CXX) -o $@ $^ $(LDFLAGS)
    
testCoord: coord-test.o coord.o  
	$(CXX) -o $@ $^ $(LDFLAGS)

testAnipop: anipop-test.o anipop.o coord.o
	$(CXX) -o $@ $^ $(LDFLAGS)

testGG: grilleGame-test.o grilleGame.o anipop.o coord.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

coord.o: coord.hpp
anipop.o : anipop.hpp coord.hpp
grilleGame.o: anipop.hpp coord.hpp grilleGame.hpp
jeu.o: anipop.hpp coord.hpp grilleGame.hpp 

check: 
	make checkCoord && make checkAnipop && make checkGG

checkCoord: testCoord
	./testCoord

checkAnipop: testAnipop
	./testAnipop

checkGG: testGG
	./testGG

cleanLinux:
	rm -f *.o $(EXEC_FILES) core.*

cleanWindows:
	del *.exe *.o  core.*
