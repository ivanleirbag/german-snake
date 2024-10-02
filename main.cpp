#include <iostream>
#include <string>
#include <ncurses.h>
#include <vector>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <functional>
#include <unistd.h>

#include "TTimer.h"
#include "Board.h"
#include "Entity.h"
#include "Snake.h"

#define ESC 27
#define ENTER 10
#define HEIGHT 30
#define WIDTH 40
#define ZERO_X 4
#define ZERO_Y 2
 //g++ ./main.cpp ./TTimer.cpp ./Board.cpp ./Entity.cpp ./Snake.cpp -o main -lncurses


int key, timerMs;
bool menu = true;
bool running = false;

//Objetos Init
Board board;

Snake snake(20, 10,
    WIDTH-1, HEIGHT-1,
    ZERO_X,
    ZERO_Y);
Snake *snakePtr = &snake;

Entity entity(23, 25, '*');
Entity *enttPtr = &entity;

TTimer timer;
TTimer drawTimer;


void DrawSnake(void *arg);

void CallSnakeMovement(Entity *entity);


int main(){
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

   
    board.SetDimensions(WIDTH, HEIGHT);
    board.SetInitialPos(ZERO_X, ZERO_Y);


    Entity *entityPtr = &entity;
    entity.SetBoundaries(WIDTH-1,      HEIGHT-1, //-1 magico
                        (ZERO_X), 
                        (ZERO_Y));
    
    timerMs = 200;
    timer.AttachOnTimerEnttReady(CallSnakeMovement, enttPtr);
    timer.StartTimer(70000, TTimer::TIMER_PERIODIC);

    drawTimer.AttachOnTimerReady(DrawSnake, nullptr);
    drawTimer.StartTimer(timerMs, TTimer::TIMER_PERIODIC);

while (menu){
        attroff(A_REVERSE);
        curs_set(0);
        clear();
        printw("> Presiona [ENTER] para iniciar el programa.\n\n");
        printw("> Presiona [ESC] para cerrar el programa.");
        refresh();

        switch (key = getch()){
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
            key = getch();
            
            switch (key){
            case ESC:
                timer.StopTimer();
                drawTimer.StopTimer();
                clear();
                endwin();
                running = false;
                menu = false;
                break;
            case ENTER:
                break;
            case KEY_UP:
                snake.SetDirection(Snake::UP);
                break;
            case KEY_LEFT:
                snake.SetDirection(Snake::LEFT);
                break;
            case KEY_DOWN:
                snake.SetDirection(Snake::DOWN);
                break;
            case KEY_RIGHT:
                snake.SetDirection(Snake::RIGHT);
                break;
            default:
                break;
            }
            erase();
            timer.TimerTask();
            board.DisplayBoard();
            drawTimer.TimerTask();
            entity.draw(nullptr);
            


            move(30, 30);
            printw("%d %d %d %ld",
             snake.GetDirection(),
             snake.GetPosx(),
             snake.GetPosy(),
             (snake.GetBody().size()));


            refresh();
        }
    }
    clear();
    endwin();
    return 0;
}


void CallSnakeMovement(Entity *entity){
    snake.MovingTo(entity);
}

void DrawSnake(void *arg){
    int x, y;
    vector<Entity> body = snake.GetBody();
    for(int i = 0; i < body.size(); i++){
        body.at(i).draw(nullptr);
    }
}