/*
 * Author:  Andrej Klocok
 * Login :  xkloco00
 */

#include "puzzle.h"

/* window destroyed */
void destroy_signal(GtkWidget *widget, gpointer data)
{
	freeMemory();
	gtk_main_quit();
}

/* request for window close from WM */
gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	return FALSE;   	/* send destroy signal */
}


void optionQuitCB(GtkWidget *widget, gpointer data)
{
	g_print("Quit button\n");
	freeMemory();
	gtk_main_quit();
}

void optionNewGameCB(GtkWidget *widget, gpointer data){
	printf("New game\n");
	newGame();
}

void optionAboutCB(GtkWidget *widget, gpointer data)
{
	static const gchar * const author[] = {
		"Andrej Klocok <xkloco00@vutbr.cz>",
		NULL
	};
	gtk_show_about_dialog (GTK_WINDOW(gtk_widget_get_toplevel(widget)),
		"authors", author,
		"program-name", "15 puzzle",
		"title", ("GUX-project2"),
		NULL); 
}

void freeMemory(){
	free(puzzleGame->board->fields);
	free(puzzleGame->board);
	free(puzzleGame->options);
	free(puzzleGame);
}

Field* getFieldFromBoard(int r, int c){
	int pos;
	if(r < 0 || c < 0 || r >= puzzleGame->board->rows || c >= puzzleGame->board->cols ){
		return NULL;
	}
	pos = r * puzzleGame->board->cols + c;

	return &puzzleGame->board->fields[pos];
}

Field* gameStep(Field *cell){
	//check Upper
	Field *n;
	n = getFieldFromBoard(cell->row-1, cell->col);
	if(n != NULL && n->value == 0){
		return n;	
	}
	//check Lower
	n = getFieldFromBoard(cell->row+1, cell->col);
	if(n != NULL && n->value == 0){
		return n;	
	}
	//check left
	n = getFieldFromBoard(cell->row, cell->col-1);
	if(n != NULL && n->value == 0){
		return n;	
	}
	//check right
	n = getFieldFromBoard(cell->row, cell->col+1);
	if(n != NULL && n->value == 0){
		return n;	
	}
	//nothing found
	return NULL;
}

bool gameVictory(){
	Board *board = puzzleGame->board;
	int totalFields = board->cols * board->rows;
	for(int i = 0; i <totalFields-1; i++ ){
		if(board->fields[i].value != i+1){
			return false;
		}
	}
	return true;
}

void updateButtonLabel(int value, GtkWidget *button){
	char  buf[5];
	sprintf(buf, "%d", value);
	gtk_button_set_label(GTK_BUTTON(button), buf);
}

void swapFields(Field *cell, Field *neigh){
	//swap values
	Field temp = *cell;
	cell->value = neigh->value;
	neigh->value = temp.value;
	
	updateButtonLabel(cell->value, cell->button);
	updateButtonLabel(neigh->value, neigh->button);
	
}

void boardFieldCB(GtkWidget *widget, gpointer data){
	Field *cell = (Field*) data;
	Field *neigh;
	//check neighboors
	neigh = gameStep(cell);
	//no empty cell around
	if(neigh == NULL){
		return;
	}
	//swap fields if 0 
	swapFields(cell, neigh);
	//check win state
	if(gameVictory()){
		printf("Victory\n");
		showVictory();
		newGame();
	}
}

void showVictory(){
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(puzzleGame->mainWindow), 
			GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			"%s", "You win");
	gtk_window_set_title(GTK_WINDOW(dialog), "Victory");
	gtk_dialog_run(GTK_DIALOG(dialog));      
	gtk_widget_destroy(dialog);
}

void initApplication(){
	GtkWidget *vbox, *menubar, *scrollw, *boardGrid;
	GtkWidget *options;
	GtkWidget *optionsMenu;
	GtkWidget *btnNewGame, *btnQuit, *btnAbout;
	GtkAccelGroup *accel_group;


	/* create main window */
	puzzleGame->mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(puzzleGame->mainWindow), "15-Puzzle");
	gtk_window_set_default_size(GTK_WINDOW(puzzleGame->mainWindow), 400, 400);
	gtk_window_set_position(GTK_WINDOW(puzzleGame->mainWindow), GTK_WIN_POS_CENTER);

	g_signal_connect(G_OBJECT(puzzleGame->mainWindow), "destroy",
		G_CALLBACK(destroy_signal), NULL);
	g_signal_connect(G_OBJECT(puzzleGame->mainWindow), "delete_event",
		G_CALLBACK(delete_event), NULL);

	/* create main container */
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	gtk_container_add(GTK_CONTAINER(puzzleGame->mainWindow), vbox);

	/* create main parts - menu, scrolled window and status bar */
	menubar = gtk_menu_bar_new();

	/* content */
	scrollw = gtk_scrolled_window_new(NULL, NULL);


	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), scrollw, TRUE, TRUE, 0);

	/* start accelerator group */
	accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(puzzleGame->mainWindow), accel_group);

	//options menu
	options = gtk_menu_item_new_with_mnemonic("_Options");
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), options);
	optionsMenu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(options), optionsMenu);
	
	//new game button
	btnNewGame = gtk_menu_item_new_with_mnemonic("_NewGame");
	gtk_widget_add_accelerator(btnNewGame, "activate", accel_group,
		GDK_KEY_n, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(optionsMenu), btnNewGame);
	g_signal_connect(G_OBJECT(btnNewGame), "activate", G_CALLBACK(optionNewGameCB), NULL);
	
	//about button
	btnAbout = gtk_menu_item_new_with_mnemonic("_About");
	gtk_widget_add_accelerator(btnAbout, "activate", accel_group,
		GDK_KEY_a, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(optionsMenu), btnAbout);
	g_signal_connect(G_OBJECT(btnAbout), "activate", G_CALLBACK(optionAboutCB), NULL);

	//quit button
	btnQuit = gtk_menu_item_new_with_mnemonic("_Quit");
	gtk_widget_add_accelerator(btnQuit, "activate", accel_group,
		GDK_KEY_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(optionsMenu), btnQuit);
	g_signal_connect(G_OBJECT(btnQuit), "activate", G_CALLBACK(optionQuitCB), NULL);

	//init buttons on board
	Board *board = puzzleGame->board;
	int numbOfFields = board->rows * board->cols;

	boardGrid = gtk_grid_new();
	gtk_widget_set_size_request(boardGrid, 200, 200);
	gtk_container_add(GTK_CONTAINER(scrollw), boardGrid);
	
	char nameField[10];
	
	for (int i=0; i< numbOfFields; i++){
		sprintf(nameField, "%d", board->fields[i].value);
		board->fields[i].button = gtk_button_new_with_label(nameField);
		g_signal_connect(G_OBJECT(board->fields[i].button), "clicked", G_CALLBACK(boardFieldCB), &board->fields[i]);
		gtk_grid_attach(GTK_GRID(boardGrid), board->fields[i].button, i%4, i/4, 1, 1);
		
	}
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void initBoard(int rows, int cols){
	Board *board = puzzleGame->board;
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

void newGame(){
	//free fields
	free(puzzleGame->board->fields);
	//init board
	initBoard(puzzleGame->options->rows, puzzleGame->options->cols);
	//redraw buttons
	int totalFields = puzzleGame->board->rows * puzzleGame->board->cols;
	for(int i = 0; i < totalFields; i++){
		Field *f = &puzzleGame->board->fields[i];
		updateButtonLabel(f->value, f->button);
	}
}

int main(int argc, char *argv[])
{
	puzzleGame = malloc(sizeof(PuzzleGame));
	puzzleGame->board = malloc(sizeof(Board));
	puzzleGame->options = malloc(sizeof(GameOptions));
	srand(time(NULL));
	puzzleGame->options->rows = 4;
	puzzleGame->options->cols = 4;
	
	initBoard(4,4);
	gtk_init(&argc, &argv);

	initApplication();
	
	gtk_widget_show_all(puzzleGame->mainWindow);

	gtk_main();
	return 0;
}