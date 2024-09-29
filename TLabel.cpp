#include "TLabel.h"
#include "conio.h"  // Asegúrate de incluir tu implementación de conio.h

TLabel::TLabel()
{
    //ctor
    width = 20;
    height = 1;
    alignVertical = TEXT_LEFT;
    alignHorizontal = TEXT_CENTER;
    memset(text, 0, 256);
    length = 0;
}

TLabel::~TLabel()
{
    //dtor
}

void TLabel::SetText(const char* str)
{
    memset(text, 0, 256);
    length = 0;

    length = strlen(str);
    if(length > width)
        length = width;

    strncpy(text, str, length);

    ShowText();
}

void TLabel::SetHorAlignment(enum TEXT_ALIGN aAlign)
{
    alignHorizontal = aAlign;

    if(length)
        ShowText();
}

void TLabel::SetVerAlignment(enum TEXT_ALIGN aAlign)
{
    alignVertical = aAlign;

    if(length)
        ShowText();
}

void TLabel::ShowText()
{
    int x, y;
    char strWidth[12];

    textcolor(GetTxtColor());  // Usamos las funciones de conio.h para color
    textbackground(GetBackColor());

    x = 0;
    if(alignHorizontal == TEXT_RIGHT)
        x = width - length;
    if(alignHorizontal == TEXT_CENTER)
        x = (width - length) / 2;

    y = this->height / 2;
    if(alignVertical == TEXT_TOP)
        y = 0;
    if(alignVertical == TEXT_BOTTOM)
        y = height - 1;

    sprintf(strWidth, "%%%ds", width);
    for(int j = 0; j < height; j++) {
        gotoxy(posx, posy + j); // Mueve el cursor usando gotoxy de conio.h
        cprintf(strWidth, " "); // Borra la línea con espacios

        if(j == y) {
            gotoxy(posx + x, posy + j);
            for(int i = 0; i < length; i++) {
                cprintf("%c", text[i]); // Imprime el texto usando cprintf de conio.h
            }
        }
    }
}


