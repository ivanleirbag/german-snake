#include "NumberBox.h"


NumberBox::NumberBox(int cPosx, int cPosy, int cWidth){
    posx = cPosx;
    posy = cPosy;
    width = cWidth;
    useColor = false;
    isFocused = false;
}

NumberBox::~NumberBox(){

}

void NumberBox::SetPosx(int sPosx){
    posx = sPosx;
}

void NumberBox::SetPosy(int sPosy){
    posy = sPosy;
}
    
void NumberBox::SetWidth(int sWidth){
    width = sWidth;
}

void  NumberBox::SetColors(int setColorPair){
    colorPair = setColorPair;
}

void NumberBox::Focus(){
    isFocused = !isFocused;
}

void  NumberBox::UseColors(){
    useColor = true;
}

void NumberBox::SetContent(int keyPressed){
    int tempRelx = relX;
    if(isFocused){
        switch(keyPressed){
            case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
                if(content.size() < width){
                    content.insert((content.begin()+relX), (keyPressed-48));
                }
                break;
            case KEY_LEFT:
                tempRelx++;
                if(tempRelx <= content.size()-1){
                    relX = tempRelx;
                }
                break;
            case KEY_RIGHT:
                tempRelx--;
                if(tempRelx >= 0){
                    relX = tempRelx;
                }
                break;
            case KEY_BACKSPACE:
                if(content.size() > 0){
                    content.erase(content.begin()+relX);
                }
                break;
            default:
                break;
        }
    }
}


//getters
int NumberBox::GetPosx(){
    return posx;
}

int NumberBox::GetPosy(){
    return posy;
}

int NumberBox::GetWidth(){
    return posx;
}

int NumberBox::GetContent(){
    int intContent = 0;
    if(content.size() == 0){
        return 0;
    }
    for (int i = 0; i < content.size(); i++){
        intContent += (content.at(i))*pow(10, i);
    }
    return intContent;
}

//display
void NumberBox::DisplayBox(){
    if(useColor && isFocused){
        attron(COLOR_PAIR(colorPair));
    }

    for (int i = 0; i < width+2; i++){
        if(i == width-relX && isFocused){
            attron(A_REVERSE);
        }
        move(posy, posx+i);
        if(i>0 && i < width+2 && width-i < content.size()){
            printw("%d", content.at(width-i));
        }else{
            attroff(A_REVERSE);
            printw(" ");
        }
        attroff(A_REVERSE);
    }
    if(useColor){
        attroff(COLOR_PAIR(colorPair));
    }
}