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
	puzzleGame->options->gameType = EASY;
	puzzleGame->options->theme = RoyalT;
	puzzleGame->options->themeImgs = malloc(sizeof(ThemeImgs));

	createBoard(puzzleGame->board, 4, 4);
	initBoard(puzzleGame->board, puzzleGame->options->gameType);
	gtk_init(&argc, &argv);

	initApplication();
	initCSS();
	initPictures(puzzleGame->board, puzzleGame->options->themeImgs);

	gtk_widget_show_all(puzzleGame->mainWindow);

	gtk_main();
	return 0;
}