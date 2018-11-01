/*
 * Author:  Andrej Klocok
 * Login:	xkloco00
 * File:	puzzleGUI.h
 */

#ifndef PUZZLE_H
#define PUZZLE_H

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <string.h>

#include "puzzleGame.h"
#include "puzzleCss.h"

//selectable options
typedef struct {
    int rows;
    int cols;
    int gameType;
    enum Themes theme;
    ThemeImgs *themeImgs;
}GameOptions;

//player moves
typedef struct {
    int moves;
    GtkWidget *label;
} GameMoves;

//main struct that contains nececery informations
typedef struct {
    GtkWidget *mainWindow;
    Board   *board;
    GameOptions *options;
    GameMoves *playerMoves;
} PuzzleGame;

//game info
PuzzleGame *puzzleGame;

void initApplication();                                                     //Initialze whole window of puzzle game
void initTopMenu(GtkWidget *menubar, GtkAccelGroup *accel_group);           //Initialize menubar

void destroy_signal(GtkWidget *widget, gpointer data);                      //Destructor for gtk
gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);   //Sends destroy signal to window

void optionNewGameCB(GtkWidget *widget, gpointer data);                     //On new game button callback
void optionAboutCB(GtkWidget *widget, gpointer data);                       //On about button callback
void optionQuitCB(GtkWidget *widget, gpointer data);                        //OnQuit button callback
void boardFieldCB(GtkWidget *widget, gpointer data);                        //On field of board structure callback
void changeThemeCB(GtkWidget *widget, gpointer data);                       //Change theme callback
void redrawFields();                                                        //Redraw images of fields on board

void moveInc(int val);                                                      //Increase player moves
void showVictory();                                                         //Shows victory dialog
void updateButtonLabel(int value, GtkWidget *button);                       //Function updates button value label
void swapFields(Field *cell, Field *neigh);                                 //Function swaps two fields on board
void freeMemory();                                                          //Function frees allocated memory
void newGame();                                                             //Redraw board

#endif // !PUZZLE_H
