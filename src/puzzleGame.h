/*
 * Author:  Andrej Klocok
 * Login :  xkloco00
 */

#ifndef GAME_H
#define GAME_H

#include <gtk/gtk.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int value;
    int row;
    int col;
    GtkWidget *button;
} Field;

typedef struct {
    int rows;
    int cols;
    Field *fields;
} Board;

Field* getFieldFromBoard(Board *board, int r, int c);
Field* gameStep(Board *board, Field *cell);
bool gameVictory();
void swap(int *a, int *b);
void initBoard(Board *board, int rows, int cols);


#endif // !GAME_H
