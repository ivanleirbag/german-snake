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
    int i, j;

    for (i=0-margin; i < height+margin; i++){
        for (j=0-margin; j < width+margin; j++){ 
            if(i < 0 || i >= height || j < 0 || j >= width){
                move((zeroy+i), (zerox+j));
                printw("+");
            }
        }
    }
}