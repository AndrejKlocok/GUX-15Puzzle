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

//game dificulty
#define TEST		0
#define EASY 		1
#define ADVANCED 	2
#define RANDOM		3

//directions
#define UP          0
#define DOWN        1
#define RIGHT       2
#define LEFT        3

//field structure, cell from board
typedef struct{
    int value;
    int row;
    int col;
    GtkWidget *button;
} Field;

//board structure
typedef struct {
    int rows;
    int cols;
    Field *fields;
} Board;

Field* getFieldFromBoard(Board *board, int r, int c);                   // Get the Field From Board function returns desired field from 1-dim arr
Field* gameStep(Board *board, Field *cell);                             // Function performs one step and returns neighbor
bool gameVictory();                                                     // Function checks victory condition
void swap(int *a, int *b);                                              // Function swaps two integers
void initBoard(Board *board, int shuffleType);                          // Function initialize board with fields
void createBoard(Board *board, int rows, int cols);                     // Create a Board function creates board and allocate memory for fields
void shuffleBoard(Board *board, int *numbArr, int base, int randChance);// Shuffle intitial arr of numbers

#endif // !GAME_H
