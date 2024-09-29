/*! \mainpage Ejercicio Titulo
 * \date 01/01/2023
 * \author Nombre
 * \section genDesc Descripcion general
 * [Complete aqui con su descripcion]
 *
 * \section desarrollos Observaciones generales
 * [Complete aqui con sus observaciones]
 *
 * \section changelog Registro de cambios
 *
 * |   Fecha    | Descripcion                                    |
 * |:----------:|:-----------------------------------------------|
 * | 01/01/2023 | Creacion del documento                         |
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <cstring>
#include <time.h>
#include <stdlib.h>

#include "TObject.h"
#include "TLabel.h"
#include "TEdit.h"
#include "TTimer.h"
/* END Includes --------------------------------------------------------------*/

using namespace std;

/* typedef -------------------------------------------------------------------*/
typedef struct{
    int x;
    int y;
    char c;
}_sSnakePart;

#define TAB             9
#define ESC             27
#define ARRIBA          1072
#define ABAJO           1080
#define IZQUIERDA       1075
#define DERECHA         1077

#define MOVINGUP        0
#define MOVINGDOWN      1
#define MOVINGLEFT      2
#define MOVINGRIGHT     3
/* END typedef ---------------------------------------------------------------*/


/* define --------------------------------------------------------------------*/

/* END define ----------------------------------------------------------------*/


/* Function prototypes -------------------------------------------------------*/
void OnTimer1TimeReady(void *arg);
//void OnTimer2TimeReady(void *arg);
short OnEdit1KeyPressed(TEdit *ed, short opt);
/* END Function prototypes ---------------------------------------------------*/


/* Global variables ----------------------------------------------------------*/
TEdit edit1;
TTimer timer1;
TTimer timer2;

int direcction, lastDirecction;
int timerMs;

_sSnakePart auxSnake;
vector<_sSnakePart>snake;
bool putNextPiece;
int nextX, nextY;
/* END Global variables ------------------------------------------------------*/


/* Function prototypes user code ----------------------------------------------*/
void OnTimer2TimeReady(void *arg){
    int i;

    nextX = (rand()%80) + 1;
    nextY = (rand()%40) + 2;

    for(i=0; i<snake.size(); i++){
        if(nextX==snake.at(i).x && nextY==snake.at(i).y)
            break;
    }
    if(i==snake.size()){
        gotoxy(nextX, nextY);
        printf("%c", snake.front().c + 1);
        return;
    }

    timer2.StartTimer(20, TTimer::TIMER_ONE_SHOT);
}


void OnTimer1TimeReady(void *arg){

    gotoxy(snake.front().x, snake.front().y);
    printf(" ");

    auxSnake = snake.back();
    if(direcction == MOVINGRIGHT){
        auxSnake.x++;
        if(auxSnake.x == 81)
            auxSnake.x = 1;
    }
    if(direcction == MOVINGLEFT){
        auxSnake.x--;
        if(auxSnake.x == 0)
            auxSnake.x = 80;
    }
    if(direcction == MOVINGUP){
        auxSnake.y--;
        if(auxSnake.y == 1)
            auxSnake.y = 41;
    }
    if(direcction == MOVINGDOWN){
        auxSnake.y++;
        if(auxSnake.y == 41)
            auxSnake.y = 2;
    }
    lastDirecction = direcction;

    for(int i=1; i<snake.size(); i++){
        snake.at(i).c++;
        snake.at(i-1) = snake.at(i);
        gotoxy(snake.at(i-1).x, snake.at(i-1).y);
        printf("%c", snake.at(i).c);
    }

    gotoxy(auxSnake.x, auxSnake.y);
    printf("%c", auxSnake.c);

    if(auxSnake.x==nextX && auxSnake.y==nextY){
        for(int i=0; i<snake.size(); i++)
            snake.at(i).c++;
        snake.push_back(auxSnake);
        timer2.StartTimer(((rand()%2201)+300), TTimer::TIMER_ONE_SHOT);
    }
    snake.back() = auxSnake;


//    gotoxy(nextX, nextY);
//    printf(" ");
//    if(direcction == MOVINGRIGHT){
//        nextX++;
//        if(nextX == 81)
//            nextX = 1;
//    }
//    if(direcction == MOVINGLEFT){
//        nextX--;
//        if(nextX == 0)
//            nextX = 80;
//    }
//    if(direcction == MOVINGUP){
//        nextY--;
//        if(nextY == 1)
//            nextY = 41;
//    }
//    if(direcction == MOVINGDOWN){
//        nextY++;
//        if(nextY == 41)
//            nextY = 2;
//    }
//    lastDirecction = direcction;
//
//    gotoxy(nextX, nextY);
//    printf("A");
}

short OnEdit1KeyPressed(TEdit *ed, short opt){
    int aux;

    if((opt<'0' || opt>'9') && !iscntrl(opt))
        return 0;

    if(opt == 13){
        aux = atoi(edit1.GetText());
        if(aux < 20)
            aux = timerMs;
        timerMs = aux;
        timer1.StartTimer(timerMs, TTimer::TIMER_PERIODIC);
    }
    return opt;
}

/* END Function prototypes user code ------------------------------------------*/


int main()
{
/* Local variables -----------------------------------------------------------*/
    TLabel label1;
    TLabel label2;


    short opt;
/* END Local variables -------------------------------------------------------*/


/* User code -----------------------------------------------------------------*/
    srand(time(0));

    //textmode(C4350);

    label1.SetPosx(1);
    label1.SetPosy(1);
    label1.SetWidth(80);
    label1.SetHorAlignment(TLabel::TEXT_CENTER);
    label1.SetTxtColor(BLACK);
    label1.SetBackColor(LIGHTGRAY);

    label1.SetText("CHARACTER MOVING");

    label2.SetPosx(60);
    label2.SetPosy(42);
    label2.SetWidth(20);
    label2.SetHorAlignment(TLabel::TEXT_CENTER);
    label2.SetTxtColor(BLACK);
    label2.SetBackColor(LIGHTGRAY);

    label2.SetText("DERECHA");

    edit1.SetPosx(1);
    edit1.SetPosy(42);
    edit1.SetWidth(40);
    edit1.SetFocused(true);
    edit1.SetTxtColor(WHITE);
    edit1.SetBackColor(BROWN);
    edit1.SetText("100");
    edit1.AttachOnKeyPressed(OnEdit1KeyPressed);


    timerMs = 100;
    timer1.AttachOnTimerReady(OnTimer1TimeReady, nullptr);
    timer1.StartTimer(timerMs, TTimer::TIMER_PERIODIC);

    timer2.AttachOnTimerReady(OnTimer2TimeReady, nullptr);
    timer2.StartTimer(3000, TTimer::TIMER_ONE_SHOT);

    auxSnake.x = 1;
    auxSnake.y = 2;
    auxSnake.c = 'A';
    snake.push_back(auxSnake);
    nextX = 1;
    nextY = 2;
    direcction = MOVINGRIGHT;
    lastDirecction = MOVINGRIGHT;

    while(1){
        opt = 0;
        if(kbhit()){
            if((opt = getch()) == 0)
                opt = 1000 + getch();

        }

        if(opt == ESC) //ESC
            break;

        switch(opt){
        case ARRIBA:
            if(lastDirecction != MOVINGDOWN){
                direcction = MOVINGUP;
                label2.SetText("ARRIBA");
            }
            break;
        case ABAJO:
            if(lastDirecction != MOVINGUP){
                direcction = MOVINGDOWN;
                label2.SetText("ABAJO");
            }
            break;
        case DERECHA:
            if(lastDirecction != MOVINGLEFT){
                direcction = MOVINGRIGHT;
                label2.SetText("DERECHA");
            }
            break;
        case IZQUIERDA:
            if(lastDirecction != MOVINGRIGHT){
                direcction = MOVINGLEFT;
                label2.SetText("IZQUIERDA");
            }
            break;
        }

        edit1.Task(opt);

        timer1.TimerTask();
        timer2.TimerTask();

    }


/* END User code -------------------------------------------------------------*/

    return 0;
}
