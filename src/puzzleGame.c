/*
 * Author:  Andrej Klocok
 * Login :  xkloco00
 */

#include "puzzleGame.h"

/**
 * @brief Get the Field From Board function returns desired field from 1-dim arr
 * 
 * @param board 	board struct containing fields
 * @param r 		desired row
 * @param c 		desired col
 * @return Field* 	pointer to structure field
 */
Field* getFieldFromBoard(Board *board, int r, int c){
	//check boundaries
	if(r < 0 || c < 0 || r >= board->rows || c >= board->cols ){
		return NULL;
	}
	return &board->fields[r * board->cols + c];
}
/**
 * @brief Function performs one step and returns neighbor
 * 
 * @param board 	board struct
 * @param cell 		field to which we want to find neighbor
 * @return Field*  	pointer to neighbor
 */
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

/**
 * @brief Function checks victory condition
 * 
 * @param board 	board struct
 * @return true 	victory
 * @return false 	some fields are wrong
 */
bool gameVictory(Board *board){
	int totalFields = board->cols * board->rows;
	//check victory condition
	for(int i = 0; i <totalFields-1; i++ ){
		if(board->fields[i].value != i+1){
			return false;
		}
	}
	return true;
}

/**
 * @brief Function swaps two integers
 * 
 * @param a 	int pointer
 * @param b 	int pointer
 */
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief Create a Board function creates board and allocate memory for fields
 * 
 * @param board 	board struct
 * @param rows 		rows of board
 * @param cols 		collumns of board
 */
void createBoard(Board *board, int rows, int cols){
	board->rows = rows;
	board->cols = cols;
	board->fields = malloc(sizeof(Field)*(rows*cols));
}
/**
 * @brief Shuffle intitial arr of numbers
 * 
 * @param board 		board structure
 * @param numbArr 		initial array of integers
 * @param base 			guaranteed numb of shuffles
 * @param randChance 	maximum of random aditional shuffles
 */
void shuffleBoard(Board *board, int *numbArr, int base, int randChance){
	int randTimes, randDirecion;	// random generated ints
	int r,c;						// row, col when looping over 1-dim array
	int indexDirection;				// index to 1-dim arr
	int totalFields = board->rows*board->cols;	// length of arr

	//generate numb of shuffles
	randTimes = base + rand() % randChance;	
	//for every shuffle
	for(int t = 0; t < randTimes; t++){	
		r=0;
		c=0;
		//for every int in arr
		for(int x = 0; x < totalFields; x++){
			//find blank (0)
			if(numbArr[x] == 0){
				//generate direction
				randDirecion = rand() %4;
				
				//direction
				switch (randDirecion)
				{	
					//up
					case UP:
						//get index to 1-dim
						indexDirection = (r-1)* (board->cols) + c;
						//check boundaries
						if(indexDirection > 0 && indexDirection < totalFields-1){
							swap(&numbArr[x], &numbArr[indexDirection]);
						}
						else{
							//try again
							t--;
						}
						break;
					//down
					case DOWN:
						//get index to 1-dim
						indexDirection = (r+1)*board->cols + c;
						//check boundaries
						if(indexDirection > 0 && indexDirection < totalFields-1){
							swap(&numbArr[x], &numbArr[indexDirection]);
						}
						else{
							//try again
							t--;
						}
						break;
					//left
					case LEFT:
						//get index to 1-dim
						indexDirection = r*board->cols + (c-1);
						//check boundaries
						if(indexDirection > 0 && indexDirection < totalFields-1){
							swap(&numbArr[x], &numbArr[indexDirection]);
						}
						else{
							//try again
							t--;
						}
						break;
					//right
					default:
						//get index to 1-dim
						indexDirection = r*board->cols + (c+1);
						//check boundaries
						if(indexDirection > 0 && indexDirection < totalFields-1){
							swap(&numbArr[x], &numbArr[indexDirection]);
						}
						else{
							//try again
							t--;
						}
						break;
				}
			}
			c++;
			//we have 4 collumns indexed from 0
			if(c>3){
				c = 0;
				r++;
			}
		}
	}
}

/**
 * @brief Function initialize board with fields
 * 
 * @param board 		board struct
 * @param shuffleType 	type of shuffle (int constant)
 */
void initBoard(Board *board, int shuffleType){
	int r, c;					//row and collumn in loop
	int totalFields = board->rows*board->cols;	//total length of array
	int numbArr[totalFields];	//initialized array of integers
	int randVal;				// random value

	//init "table" of values
	for(int i=0; i< totalFields-1; i++){
		numbArr[i]=i+1;
	}
	numbArr[totalFields-1] = 0;

	//perform shuffle type according to chosen difficulty
	switch (shuffleType)
	{
		case TEST:
			//we will make it to be one step to win
			swap(&numbArr[totalFields-1], &numbArr[totalFields-2]);

			break;
		case EASY:
			//few shuffles
			shuffleBoard(board, numbArr, 5, 10);
			break;

		case ADVANCED:
			//many shuffles - but still there is sulution
			shuffleBoard(board, numbArr, 10, 15);
			break;
		//case RANDOM:
		default:
			//random shuffle - there could not be a solutions
			for(int i=totalFields-1; i>0;i--){
				randVal = rand() % (i+1);
				swap(&numbArr[i], &numbArr[randVal]);

			}
			break;
	}
	//reset row, col index
	r=0;
	c=0;
	//init fields
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
