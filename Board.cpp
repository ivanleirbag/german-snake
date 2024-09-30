#include "Board.h"

Board::Board(){
    width = 20;
    height = 10;
    margin = 2;
    zeroy = 1;
    zerox = 1;
}

Board::~Board(){
}

void Board::SetDimensions(int sWidth, int sHeight){
    width = sWidth;
    height = sHeight;
}

int Board::GetWidth(){
    return width;
}

int Board::GetHeight(){
    return height;
}

void Board::SetMargin(int sMargin){
    margin = sMargin;
}

int Board::GetMargin(){
    return margin;
}

void Board:: SetInitialPos(int sZerox, int sZeroy){
    zerox = sZerox;
    zeroy = sZeroy;
}

void Board::DisplayBoard(){
    int posx = 0;
    int posy = 0;
    int i, j;

    for (i=0; i < height+margin; i++){
        for (j=0; j < width+margin; j++){
            move((posy+zeroy+i), (posx+zerox+j));
            if(i < margin || i >= height || j < margin || j >= width){
                printw("+");
            }else{
                printw(" ");
            }
        }
    }
}