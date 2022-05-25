#include <iostream>
#include <vector>
#include <ncurses.h>
#include <string>

#include "grilleGame.hpp"

//#define DOCTEST_CONFIG_IMPLEMENT
//#include "doctest.h"

using namespace std;


void dessine(WINDOW *win, Game g){

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    //init_pair(3, COLOR_GREEN, COLOR_GREEN);
    wprintw(win, "\n");
    for(int i = 0; i<TAILLEGRILLE;i++){
        wprintw(win, "   ");
        wrefresh(win);
        for(int j = 0; j<TAILLEGRILLE;j++){
            if(g.getAnimal({i,j}).getEspece() == Espece::Lapin){
                string animal = g.getAnimal({i,j}).toString();

                wattron(win,COLOR_PAIR(2)); wattron(win,A_BOLD);
                wprintw(win, animal.c_str());wprintw(win, " ");
                wattroff(win, COLOR_PAIR(2)); wattroff(win,A_BOLD);

                wrefresh(win);
            }
            else if(g.getAnimal({i,j}).getEspece() == Espece::Renard){
                string animal = g.getAnimal({i,j}).toString();

                wattron(win, A_BOLD);
                wattron(win, COLOR_PAIR(1));
                wprintw(win, animal.c_str());wprintw(win, " ");
                wattroff(win, COLOR_PAIR(1));
                wattroff(win, A_BOLD);

                wrefresh(win);
            } else {
                string animal = g.getAnimal({i,j}).toString();
                wattron(win, A_INVIS);
                wprintw(win, animal.c_str());wprintw(win, " ");
                wattroff(win, A_INVIS);
                wrefresh(win);
            }
        }
        wprintw(win,""); wprintw(win,"\n");
        wrefresh(win);
    }
}

int main(){


    // if(not has_colors()){
    //     printw("Your terminal doesn't support colors...");
    //     getch();
    //     return -1;
    // }

    initscr();

    start_color();
    init_pair(4,COLOR_GREEN, COLOR_BLACK);

    noecho();
    curs_set(0);

    int height = 22;
    int width = 47; 
    int y = 0;
    int x = 5;

    Game g{5,20};
    bool tourLapin = true;

    move(0,0);
    printw("début du jeu, appuyez sur une touche... \n");
    printw("note: à chaque fois que vous passez une étape, appuyez sur une touche \n");
    refresh();
    getch();
    clear();

    //création de la fenêtre de jeu
    WINDOW * win = newwin(height, width, y, x);
    refresh();

    //création de la fenêtre des données
    WINDOW * data = newwin(height, width, y, x+width+1);
    refresh();

    curs_set(0);

    wrefresh(win);
    wrefresh(data);
    refresh();

    wattron(data,COLOR_PAIR(4));
    wprintw(data, g.afficheDonnee().c_str());
    wattroff(data,COLOR_PAIR(4));
    dessine(win, g);
    box(win,0,0);
    wrefresh(win);
    wrefresh(data);

    while(true){
        if(tourLapin){
            g.bougeLapin();
            dessine(win, g);
            box(win,0,0);
            wattron(data,COLOR_PAIR(4));
            wprintw(data, g.afficheDonnee().c_str());
            wrefresh(win);
            wattroff(data,COLOR_PAIR(4));
            wrefresh(data);
        } else {
            g.bougeRenard();
            dessine(win, g);
            box(win,0,0);
            wattron(data,COLOR_PAIR(4));
            wprintw(data, g.afficheDonnee().c_str());
            wrefresh(win);
            wattroff(data,COLOR_PAIR(4));
            wrefresh(data);
            
        } 
        tourLapin = not tourLapin;
        wclear(win);
        wclear(data);

        //pour eviter que le terminal aille trop vite
        if(tourLapin){
            napms(200);
        }
    }
    return 0;
}