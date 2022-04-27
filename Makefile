CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3
EXEC_FILES= test jeu

all: jeu
# Regle generique
%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

jeu: coord.o anipop.o jeu.o
	$(CXX) -o $@ $^ $(LDFLAGS)


test: test.o coord.o anipop.o 
	$(CXX) -o $@ $^ $(LDFLAGS)
    

coord.o: coord.hpp
anipop.o : anipop.hpp coord.hpp
jeu.o: anipop.hpp coord.hpp

check: test
	./test

clean:
	rm -f *.o $(EXEC_FILES)
