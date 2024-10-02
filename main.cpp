#include <iostream>
#include <string>
#include <ncurses.h>
#include <vector>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <functional>
#include <chrono>
#include <thread>

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
#define MARGIN 2
#define WALLS 2
#define SNAKE 1
#define FRUIT 3
#define LOSE 4
#define WIN 5
 //g++ ./main.cpp ./TTimer.cpp ./Board.cpp ./Entity.cpp ./Snake.cpp -o main -lncurses

using namespace std;

int key, timerMs;
bool menu = true;
bool running = false;

//Objetos Init
Board board;

Snake snake(20, 15,
    WIDTH, HEIGHT,
    ZERO_X,
    ZERO_Y);
Snake *snakePtr = &snake;

Entity fruit(23, 25, '"');
Entity *enttPtr = &fruit;
Entity head(999, 999, 'x');

TTimer timer;
TTimer drawTimer;

void RenderGame(void *arg);

void CallSnakeMovement(Entity *entity);


int main(){
    srand(time(0));
    initscr();
    start_color();
    init_pair(SNAKE, COLOR_BLACK, COLOR_GREEN);
    init_pair(WALLS, COLOR_BLUE, COLOR_BLUE);
    init_pair(FRUIT, COLOR_GREEN, COLOR_RED);
    init_pair(LOSE, COLOR_BLACK, COLOR_RED);
    init_pair(WIN, COLOR_BLACK, COLOR_GREEN);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

   
    board.SetDimensions(WIDTH, HEIGHT);
    board.SetInitialPos(ZERO_X, ZERO_Y);
    board.SetMargin(MARGIN);


    Entity *fruitPtr = &fruit;
    fruit.SetBoundaries(WIDTH,      HEIGHT,
                        (ZERO_X), 
                        (ZERO_Y));
    
    timerMs = 200;
    timer.AttachOnTimerEnttReady(CallSnakeMovement, enttPtr);
    timer.StartTimer(70000, TTimer::TIMER_PERIODIC);

    drawTimer.AttachOnTimerReady(RenderGame, nullptr);
    drawTimer.StartTimer(timerMs, TTimer::TIMER_PERIODIC);

while (menu){

        snake.ResetSnake();
    
        attroff(A_REVERSE);
        curs_set(0);
        erase();
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
            

            //Input
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

            //Render de la pantalla y movimientos
            timer.TimerTask();
            drawTimer.TimerTask();
            attron(COLOR_PAIR(FRUIT));
            fruit.draw(nullptr);
            attroff(COLOR_PAIR(FRUIT));

            //Come la fruta?
            head = snake.GetHead();
            if (fruit.collidesWith(head)){
                snake.Grow();
                int newX = ZERO_X + (rand()%WIDTH);
                int newY = ZERO_Y + (rand()%HEIGHT);
                fruit.SetPosx(newX);
                fruit.SetPosy(newY);
            }
            
            //Pantalla de muerte
            if(snake.isDead){
                timer.StopTimer();
                drawTimer.StopTimer();
                move((ZERO_Y+(HEIGHT/2)-1), (ZERO_X+(WIDTH/2)-4));
                attron(COLOR_PAIR(LOSE));
                printw("Perdiste!");
                refresh();

                for (int i=0-MARGIN; i < (HEIGHT+MARGIN)/2; i++){
                    for (int j=0-MARGIN; j < WIDTH+MARGIN+1; j++){ 
                        move((ZERO_Y+i), (ZERO_X+j));
                        printw(" ");
                        move((ZERO_Y+HEIGHT-i), (ZERO_X+WIDTH-j));
                        printw(" ");
                        refresh();
                        this_thread::sleep_for(chrono::milliseconds(5));  
                    }
                }
                attroff(COLOR_PAIR(LOSE));
                running = false;
            }
            //
            if(snake.GetBody().size() > 54){
                timer.StopTimer();
                drawTimer.StopTimer();
                move((ZERO_Y+(HEIGHT/2)-1), (ZERO_X+(WIDTH/2)-4));
                attron(COLOR_PAIR(WIN));
                printw("Ganaste!");
                refresh();
                for (int i=0-MARGIN; i < (HEIGHT+MARGIN)/2; i++){
                    for (int j=0-MARGIN; j < WIDTH+MARGIN+1; j++){ 
                        move((ZERO_Y+i), (ZERO_X+j));
                        printw(" ");
                        move((ZERO_Y+HEIGHT-i), (ZERO_X+WIDTH-j));
                        printw(" ");
                        refresh();
                        this_thread::sleep_for(chrono::milliseconds(5));  
                    }
                }
                attroff(COLOR_PAIR(WIN));
                running = false;
            }
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

void RenderGame(void *arg){
    erase();
    int x, y;
    attron(COLOR_PAIR(SNAKE));
    vector<Entity> body = snake.GetBody();
    for(int i = 0; i < body.size(); i++){
        body.at(i).draw(nullptr);
    }
    attroff(COLOR_PAIR(SNAKE));
    attron(COLOR_PAIR(WALLS));
    board.DisplayBoard();
    attroff(COLOR_PAIR(WALLS));
    refresh();
}