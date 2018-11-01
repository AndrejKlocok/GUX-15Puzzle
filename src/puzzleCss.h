#ifndef PUZZLECSS_H
#define PUZZLECSS_H

#include <gtk/gtk.h>
#include "puzzleGame.h"

enum Themes
{
    RoyalT, ClassicT, KittenT
};

typedef struct{
    GtkWidget *image;
} ImageStruct;

typedef struct{
    ImageStruct *images;
    int length;
} ThemeImgs;

void initCSS();
void addStyleBtn(GtkWidget *btn, int value, enum Themes theme, ThemeImgs *imgs);
void initPictures(Board *board, ThemeImgs *imgs);

#endif // !PUZZLECSS_H
