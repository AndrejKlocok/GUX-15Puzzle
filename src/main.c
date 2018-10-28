/*
 * Author:  Andrej Klocok
 * Login :  xkloco00
 */

#include "puzzleGUI.h"


int main(int argc, char *argv[])
{	
	

	puzzleGame = malloc(sizeof(PuzzleGame));
	puzzleGame->board = malloc(sizeof(Board));
	puzzleGame->options = malloc(sizeof(GameOptions));
	srand(time(NULL));
	puzzleGame->options->rows = 4;
	puzzleGame->options->cols = 4;
	
	initBoard(puzzleGame->board, 4, 4);
	gtk_init(&argc, &argv);

	initApplication();
	initCSS();
	gtk_widget_show_all(puzzleGame->mainWindow);

	gtk_main();
	return 0;
}