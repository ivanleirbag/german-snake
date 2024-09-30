#include <iostream>
#include <string>
#include <ncurses.h>
#include <vector>
#include <cstring>
#include <time.h>
#include <stdlib.h>

#include "TTimer.h"
#include "Board.h"

#define ESC 27
#define ENTER 10
#define HEIGHT 30
#define WIDTH 60
#define ZERO_X 4
#define ZERO_Y 2


int key;
bool menu = true;
bool running = false;




int main(){
    initscr();
    keypad(stdscr, TRUE);


    Board board;
    board.SetDimensions(WIDTH, HEIGHT);
    board.SetInitialPos(ZERO_X, ZERO_Y);


while (menu){
        attroff(A_REVERSE);
        curs_set(0);
        clear();
        printw("> Presiona [ENTER] para iniciar el programa.\n\n");
        printw("> Presiona [ESC] para cerrar el programa.");
        refresh();

        key = getch();
        switch (key){
        case ESC:
            endwin();
            menu = false;
            break;
        case ENTER:
            running = true;
            clear();
            break;
        default:
            break;
        }
        while (running){
            clear();
            refresh();
            board.DisplayBoard();
            key = getch();
            switch (key){
            case ESC:
                running = false;
                menu = false;
                endwin();
                break;
            case ENTER:
                break;
            default:
                break;
            }
        }
    }

    return 0;
}
