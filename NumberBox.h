#ifndef NUMBERBOX_H
#define NUMBERBOX_H

#include <ncurses.h>
#include <vector>

#define ENTER 10
#define DELETE 

using namespace std;

class NumberBox{

public:
    bool isFocused;

private:
    int posx, posy;
    vector<int> content;
    int width;
    //seters
    void SetPosx(int sPosx);

    void SetPosy(int sPosy);
    
    void SetWidth(int sWidth);
    
    void SetContent(int keyPressed);

    //getters
    int GetPosx();

    int GetPosy();

    int GetWidth();

    int GetContent();

    //display
    void DisplayBox();

};




#endif //NUMBERBOX_H