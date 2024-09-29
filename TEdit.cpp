#include "TEdit.h"
#include "conio.h"  // Incluir la implementación de conio.h

#define ELIMINAR        1083
#define BACKSPACE       8
#define IZQUIERDA       1075
#define DERECHA         1077

TEdit::TEdit()
{
    // Constructor
    width = 20;
    height = 1;
    memset(text, 0, TEXTLENGTH);
    length = 0;
    curPosDisplay = 0;
    curPosText = 0;
    tabStop = true;
    doTask = true;
    onKeyPressed = nullptr;

    lastTime = clock();
}

TEdit::~TEdit()
{
    // Destructor
}

void TEdit::SetText(const char* str)
{
    int i, flag = 0;

    length = strlen(str);
    if(length > TEXTLENGTH)
        length = TEXTLENGTH;

    int j = 0;
    for(i = 0; str[i]; i++) {
        if(!iscntrl(str[i]))  // Ignorar caracteres de control
            text[j++] = str[i];
    }
    text[j] = '\0';

    text[TEXTLENGTH-1] = '\0';
    text[length] = '\0';
    length = strlen(text);

    // Posiciona el cursor en la consola y ajusta los colores
    gotoxy(posx, posy);
    textcolor(GetTxtColor());
    textbackground(GetBackColor());

    curPosDisplay = length;
    if(length > width) {
        i = length - width;
        curPosDisplay = width-1;
    } else {
        i = 0;
    }

    // Mostrar el texto o espacios vacíos si es necesario
    for(; i < width; i++) {
        if(text[i] && !flag)
            cprintf("%c", text[i]);  // Usar cprintf de conio.h
        else {
            flag = 1;
            cprintf(" ");
        }
    }
    curPosText = length;
}

char* TEdit::GetText()
{
    return text;
}

short TEdit::Task(short opt)
{
    int i, j;

    if(!isFocused)
        return 0;

    // Intermitencia del cursor
    if((clock() - lastTime) >= 250) {
        lastTime = clock();
        showCursor = !showCursor;
    }

    // Ajuste de colores
    textcolor(GetTxtColor());
    textbackground(GetBackColor());

    if(opt == 0) {
        // Muestra el cursor en la posición actual
        gotoxy(posx + curPosDisplay, posy);
        if(showCursor) {
            cprintf("%c", 178);  // Símbolo para cursor
        } else {
            cprintf("%c", text[curPosText]);
        }

        return 0;
    } else {
        // Manejo de teclas personalizadas
        if(onKeyPressed != nullptr) {
            opt = onKeyPressed(this, opt);
            if(opt == 0)
                return 0;
        }
    }

    // Manejo de las teclas IZQUIERDA, DERECHA, ELIMINAR y BACKSPACE
    switch(opt) {
        case IZQUIERDA:
            curPosText--;
            if(curPosText < 0)
                curPosText = 0;
            curPosDisplay--;
            if(curPosDisplay < 0)
                curPosDisplay = 0;
            break;
        case DERECHA:
            curPosText++;
            if(curPosText > length)
                curPosText = length;
            curPosDisplay++;
            if(curPosDisplay > (width-1))
                curPosDisplay = width - 1;
            if(curPosDisplay > length)
                curPosDisplay = length;
            break;
        case ELIMINAR:
            if(curPosText == length || length == 0)
                break;
            memcpy(&text[curPosText], &text[curPosText+1], TEXTLENGTH-curPosText);
            text[TEXTLENGTH-1] = '\0';
            length--;
            text[length] = '\0';
            break;
        case BACKSPACE:
            if(curPosText == 0 || length == 0)
                break;
            memcpy(&text[curPosText-1], &text[curPosText], TEXTLENGTH-curPosText);
            text[TEXTLENGTH-1] = '\0';
            length--;
            text[length] = '\0';
            curPosText--;
            curPosDisplay--;
            if(curPosDisplay < 0)
                curPosDisplay = 0;
            break;
        default:
            if(opt > 1000 || iscntrl(opt) || length >= TEXTLENGTH || opt == 0)
                break;

            // Inserta un carácter en la posición actual del cursor
            for(i = TEXTLENGTH-2; i >= curPosText; i--)
                text[i+1] = text[i];
            text[curPosText] = opt;
            curPosText++;
            curPosDisplay++;
            if(curPosDisplay == width)
                curPosDisplay = width - 1;
            length++;
    }

    // Actualiza el texto en la consola después de modificarlo
    i = curPosText - curPosDisplay;
    gotoxy(posx, posy);
    if(i < 0)
        i = 0;

    for(j = 0; j < width; j++) {
        if(j >= length)
            cprintf(" ");  // Rellena con espacios
        else
            cprintf("%c", text[i++]);  // Imprime el texto
    }

    // Posiciona el cursor en la nueva posición
    gotoxy(posx + curPosDisplay, posy);

    return 0;
}

void TEdit::AttachOnKeyPressed(short (*aOnKeyPressed)(TEdit *ed, short key))
{
    onKeyPressed = aOnKeyPressed;
}

int TEdit::DoTask(void *arg)
{
    return Task(*((short *)arg));
}
