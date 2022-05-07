#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <cstdlib>
#include <ctime>
#include <curses.h>
#include <SFML/Graphics.hpp>

#include "primitives.hpp"
#include "grilleGame.hpp"

//~ #define DOCTEST_CONFIG_IMPLEMENT
//~ #include "doctest.h"

using namespace sf;
using namespace std;
void draw_filled_rectangle(SDL_Renderer  *window_renderer,SDL_Rect &rect,float x,float y,float taille,int r,int g,int b){
	
	rect.x = x;
	rect.y = y;
	rect.w = taille;
	rect.h = taille;

	SDL_SetRenderDrawColor(window_renderer, r, g, b, 255);
	SDL_RenderFillRect(window_renderer, &rect);
	SDL_RenderDrawRect(window_renderer, &rect);
	SDL_SetRenderDrawColor(window_renderer, 255,255, 255, 255);
}
int main( int argc, char* args[]){
	srand(time(NULL));
    string mode = "sdl";
    Game g{7,20};
    //~ Game g{0,0};
	//~ g.ajouteAnimal(Espece::Lapin,{3,3});
    
    if(mode == "sfml"){
        float TailleFenetre = 600;
        float TailleCase = TailleFenetre / TAILLEGRILLE;
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
                g.bougeLapin();
            }else{
                g.bougeRenard();
            }
            tourLapin = not tourLapin;
            for(int i =0;i<TAILLEGRILLE;i++){
                for(int j =0;j<TAILLEGRILLE;j++){
                    Animal a = g.getAnimal({i,j});
                    if(a.getEspece() == Espece::Lapin){
                        draw_filled_rectangle(window, Point{i* TailleCase,j*TailleCase}, TailleCase, TailleCase, Color::Green);
                    }
                    else if(a.getEspece() == Espece::Renard){
                        draw_filled_rectangle(window, Point{i* TailleCase,j*TailleCase}, TailleCase, TailleCase, Color::Red);
                    }
                }
            }
            window.display();
            sleep(seconds(0.5));
        }
    }
    else if(mode == "sdl"){
		SDL_Window     *window;
		SDL_Renderer  *window_renderer;
		SDL_Rect rect;
		SDL_Init(SDL_INIT_VIDEO);
		initscr();	
		TTF_Init();
		float TailleFenetre = 600;
        float TailleCase = TailleFenetre / TAILLEGRILLE;
		SDL_CreateWindowAndRenderer(TailleFenetre, TailleFenetre, SDL_WINDOW_SHOWN, &window, &window_renderer);
		TTF_Font* font;
		font = TTF_OpenFont("arial_narrow_7.ttf",200);//"arial_narrow_7.ttf"
		if ( !font ) {
			cout << "Failed to load font: " << TTF_GetError() << endl;
		}
		SDL_Event events;
		bool isOpen = true;
		
        bool tourLapin = true;
		while (isOpen){
			//~ cout <<rand()%100<<endl;
			while (SDL_PollEvent(&events)){
				switch (events.type){
					case SDL_QUIT:
						isOpen = false;
						TTF_CloseFont(font);
						SDL_DestroyRenderer( window_renderer );
						SDL_DestroyWindow( window );
						window  = NULL;
						window_renderer = NULL;
						TTF_Quit();
						SDL_Quit(); 
						break;
				}
			}
			SDL_RenderClear(window_renderer);
			if(tourLapin){
                g.bougeLapin();
            }else{
                g.bougeRenard();
            }
            tourLapin = not tourLapin;
            for(int i =0;i<TAILLEGRILLE;i++){
                for(int j =0;j<TAILLEGRILLE;j++){
                    Animal a = g.getAnimal({i,j});
                    if(a.getEspece() == Espece::Lapin){
						if(a.getSexe() and versReprodSexuee)draw_filled_rectangle(window_renderer,rect, i* TailleCase,j*TailleCase, TailleCase, 165,255,0);
                        else draw_filled_rectangle(window_renderer,rect, i* TailleCase,j*TailleCase, TailleCase, 0,255,0);
                    }
                    else if(a.getEspece() == Espece::Renard){
						if(a.getSexe() and versReprodSexuee)draw_filled_rectangle(window_renderer,rect, i* TailleCase,j*TailleCase, TailleCase, 255,192,203);
                        else draw_filled_rectangle(window_renderer,rect, i* TailleCase,j*TailleCase, TailleCase, 255,0,0);
                    }
                }
            }
            SDL_RenderPresent(window_renderer);
            refresh();
            g.afficheRepartion();
		}
		
	}
    else{
        for(int i =0;i<5;i++){
			g.bougeLapin();
			g.bougeRenard();
            cout<<g<<endl;
        }  
    }
    return 0;
}
