#ifndef PUZZLE_H
#define PUZZLE_H


#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
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

typedef struct {
    int rows;
    int cols;
}GameOptions;

typedef struct {
    GtkWidget *mainWindow;
    Board   *board;
    GameOptions *options;
} PuzzleGame;

static PuzzleGame *puzzleGame;

//initialize application
void initApplication();

//ititialize board fields
void initBoard(int rows, int cols);
Field* gameStep(Field *cell);
void swap(int *a, int *b);
bool gameVictory();
void freeMemory();
void newGame();

// window callback prototypes
void destroy_signal(GtkWidget *widget, gpointer data);
gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);


//options menu
void optionNewGameCB(GtkWidget *widget, gpointer data);
void optionAboutCB(GtkWidget *widget, gpointer data);
void optionQuitCB(GtkWidget *widget, gpointer data);

//field buttons CB
void boardFieldCB(GtkWidget *widget, gpointer data);
void showVictory();
#endif // !PUZZLE_H
