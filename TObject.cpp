#include "TObject.h"

TObject::TObject(int x, int y)
{
    //ctor

    posx = x;
    posy = y;
    tabStop = false;
    isFocused = false;
    doTask = false;
}

TObject::~TObject()
{
    //dtor
}

void TObject::SetPosx(int aPosx)
{
    posx = aPosx;
}

void TObject::SetPosy(int aPosy)
{
    posy = aPosy;
}

void TObject::SetWidth(int aWidth)
{
    width = aWidth;
}

void TObject::SetHeight(int aHeight)
{
    height = aHeight;
}

void TObject::SetTxtColor(int aTxtColor)
{
    txtColor = aTxtColor;
}

void TObject::SetBackColor(int aBackColor)
{
    backColor = aBackColor;
}

void TObject::SetFocused(bool type)
{
    isFocused = type;
}

int TObject::DoTask(void* arg)
{
    return 0;
}


