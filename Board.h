#ifndef BOARD_H
#define BOARD_H

#include <ncurses.h>

class Board
{
    public:
        Board(); //ctor
        ~Board();//dctor

        void SetDimensions(int sWidth, int sHeight);

        int GetWidth();
        int GetHeight();

        void SetMargin(int sMargin);
        int GetMargin();

        void SetInitialPos(int sZerox, int sZeroy);



        void DisplayBoard();

    protected:

    private:
        int width;
        int height;
        int margin;
        int zerox;
        int zeroy;
};

#endif // BOARD_H