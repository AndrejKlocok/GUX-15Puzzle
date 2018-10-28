/*
 * Author:  Andrej Klocok
 * Login :  xkloco00
 */

#include "puzzleGame.h"

Field* getFieldFromBoard(Board *board, int r, int c){
	if(r < 0 || c < 0 || r >= board->rows || c >= board->cols ){
		return NULL;
	}
	return &board->fields[r * board->cols + c];
}

Field* gameStep(Board* board, Field *cell){
	//check Upper
	Field *n;
	n = getFieldFromBoard(board, cell->row-1, cell->col);
	if(n != NULL && n->value == 0){
		return n;	
	}
	//check Lower
	n = getFieldFromBoard(board, cell->row+1, cell->col);
	if(n != NULL && n->value == 0){
		return n;	
	}
	//check left
	n = getFieldFromBoard(board, cell->row, cell->col-1);
	if(n != NULL && n->value == 0){
		return n;	
	}
	//check right
	n = getFieldFromBoard(board, cell->row, cell->col+1);
	if(n != NULL && n->value == 0){
		return n;	
	}
	//nothing found
	return NULL;
}

bool gameVictory(Board *board){
	int totalFields = board->cols * board->rows;
	for(int i = 0; i <totalFields-1; i++ ){
		if(board->fields[i].value != i+1){
			return false;
		}
	}
	return true;
}


void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void initBoard(Board *board, int rows, int cols){
	int r = 0;
	int c = 0;
	int totalFields = rows*cols;
	int numbArr[totalFields];// = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,0,15};
	int randVal;

	board->rows = rows;
	board->cols = cols;
	board->fields = malloc(sizeof(Field)*totalFields);
	
	//init "table" of values
	for(int i=0; i< totalFields; i++){
		numbArr[i]=i;
	}

	//random array
	for(int i=totalFields-1; i>0;i--){
		randVal = rand() % (i+1);
		swap(&numbArr[i], &numbArr[randVal]);

	}
	
	//init values
	for(int i = 0; i < totalFields; i++){
		board->fields[i].value = numbArr[i];
		board->fields[i].row = r;
		board->fields[i].col = c;
		c++;
		//we have 4 collumns indexed from 0
		if(c>3){
			c = 0;
			r++;
		}
	}
}
