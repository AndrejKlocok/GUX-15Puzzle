/*
 * Author:  Andrej Klocok
 * Login:	xkloco00
 * File:	puzzleCss.h
 */
#ifndef PUZZLECSS_H
#define PUZZLECSS_H

#include <gtk/gtk.h>
#include <string.h>

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

void initCSS();                                                                     //Initialize css properties from CSS file
void addStyleBtn(GtkWidget *btn, int value, enum Themes theme, ThemeImgs *imgs);    //Function add style to button according to used theme
void initPictures(Board *board, ThemeImgs *imgs);                                   //Loads pictures from img directory to game structure

#endif // !PUZZLECSS_H
