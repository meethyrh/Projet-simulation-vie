#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "primitives.h"
#include "grilleGame.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

using namespace sf;
using namespace std;


int main(){
    string mode = "sfml";
    Game g{10,10};

    
    if(mode == "sfml"){
        int TailleCase = 60;
        int TailleFenetre = TailleCase * TAILLEGRILLE;
        RenderWindow window(VideoMode(TailleFenetre, TailleFenetre), "FoxWar");
        bool tourLapin = true;
        while (window.isOpen()){
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
            sf::Event event;
            while (window.pollEvent(event)){
                // évènement "fermeture demandée" : on ferme la fenêtre
                if (event.type == sf::Event::Closed)
                    window.close();
            }
       
            window.clear(Color::White);
            if(tourLapin){
                for(int c =0;c<TAILLEGRILLE*TAILLEGRILLE;c++){
                    g.bougeLapin(c);
                }
                
            }else{
                for(int c =0;c<TAILLEGRILLE*TAILLEGRILLE;c++){
                    g.bougeRenard(c);
                }
            }
            tourLapin = not tourLapin;
            for(int i =0;i<TAILLEGRILLE;i++){
                for(int j =0;j<TAILLEGRILLE;j++){
                    Animal a = g.getAnimal({i,j});
                    if(a.getEspece() == Espece::Lapin){
                        draw_filled_rectangle(window, {i* TailleCase,j*TailleCase}, TailleCase, TailleCase, Color::Green);
                    }
                    if(a.getEspece() == Espece::Renard){
                        draw_filled_rectangle(window, {i* TailleCase,j*TailleCase}, TailleCase, TailleCase, Color::Red);
                    }
                }
            }
            window.display();
            sleep(seconds(10));
        }
    }
    else{
        for(int i =0;i<5;i++){
            for(int c =0;c<TAILLEGRILLE*TAILLEGRILLE;c++){
                g.bougeLapin(c);
            }
            for(int c =0;c<TAILLEGRILLE*TAILLEGRILLE;c++){
                g.bougeRenard(c);
            }
            cout<<g<<endl;
        }  
    }
    return 0;
}