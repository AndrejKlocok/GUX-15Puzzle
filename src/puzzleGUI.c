/*
 * Author:  Andrej Klocok
 * Login :  xkloco00
 */

#include "puzzleGUI.h"

/**
 * @brief Destructor for gtk
 * 
 * @param widget 	GtkWidget *widget
 * @param data 		gpointer data
 */
void destroy_signal(GtkWidget *widget, gpointer data)
{
	freeMemory();
	gtk_main_quit();
}

/**
 * @brief Sends destroy signal to window
 * 
 * @param widget 
 * @param event 
 * @param data 
 * @return gboolean 
 */
gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	return FALSE; 
}

/**
 * @brief OnQuit button callback
 * 
 * @param widget 	GtkWidget *widget
 * @param data 		gpointer data
 */
void optionQuitCB(GtkWidget *widget, gpointer data)
{
	freeMemory();
	gtk_main_quit();
}

/**
 * @brief On new game button callback
 * 
 * @param widget 	GtkWidget *widget
 * @param data 		gpointer data
 */
void optionNewGameCB(GtkWidget *widget, gpointer data){
	//change difficulty
	puzzleGame->options->gameType = GPOINTER_TO_INT (data);
	//init board according to new difficulty
	newGame();
}

/**
 * @brief  On about button callback
 * 
 * @param widget 	GtkWidget *widget
 * @param data 		gpointer data
 */
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

/**
 * @brief Function frees allocated memory
 * 
 */
void freeMemory(){
	free(puzzleGame->board->fields);
	free(puzzleGame->board);
	free(puzzleGame->options);
	free(puzzleGame);
}

/**
 * @brief Function updates button value label
 * 
 * @param value 	value displayed on button(label)
 * @param button 	button
 */
void updateButtonLabel(int value, GtkWidget *button){
	char  buf[5];

	sprintf(buf, "%d", value);
	gtk_button_set_label(GTK_BUTTON(button), buf);
	addStyleBtn(button, value);
}

/**
 * @brief Function swaps two fields on board
 * 
 * @param cell 
 * @param neigh 
 */
void swapFields(Field *cell, Field *neigh){
	//swap fields
	Field temp = *cell;
	cell->value = neigh->value;
	neigh->value = temp.value;
	
	//update labels
	updateButtonLabel(cell->value, cell->button);
	updateButtonLabel(neigh->value, neigh->button);	
}

/**
 * @brief On field of board structure callback
 * 
 * @param widget 	GtkWidget *widget
 * @param data 		gpointer data
 */
void boardFieldCB(GtkWidget *widget, gpointer data){
	Field *cell = (Field*) data;	//clicked field
	Field *neigh;					// neighbor

	//check neighboors
	neigh = gameStep(puzzleGame->board, cell);
	//no empty cell around
	if(neigh == NULL){
		return;
	}
	//swap fields if 0 
	swapFields(cell, neigh);
	//check win state
	if(gameVictory(puzzleGame->board)){
		printf("Victory\n");
		showVictory();
		newGame();
	}
}

/**
 * @brief Shows victory dialog
 * 
 */
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

/**
 * @brief Initialize menubar
 * 
 * @param menubar 
 * @param accel_group 
 */
void initTopMenu(GtkWidget *menubar, GtkAccelGroup *accel_group){
	//options menu and buttons
	GtkWidget *btnQuit, *btnAbout;
	GtkWidget *options, *optionsMenu;
	//new game menu and buttons
	GtkWidget *newGameItem, *newGameMenu;
	GtkWidget *btnRandom, *btnEasy, *btnAdvanced, *btnTest;

	//options menu
	options = gtk_menu_item_new_with_mnemonic("_Options");
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), options);
	optionsMenu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(options), optionsMenu);

	//about button
	btnAbout = gtk_menu_item_new_with_mnemonic("_About");
	gtk_widget_add_accelerator(btnAbout, "activate", accel_group, GDK_KEY_a, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(optionsMenu), btnAbout);
	g_signal_connect(G_OBJECT(btnAbout), "activate", G_CALLBACK(optionAboutCB), NULL);

	//quit button
	btnQuit = gtk_menu_item_new_with_mnemonic("_Quit");
	gtk_widget_add_accelerator(btnQuit, "activate", accel_group,
		GDK_KEY_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(optionsMenu), btnQuit);
	g_signal_connect(G_OBJECT(btnQuit), "activate", G_CALLBACK(optionQuitCB), NULL);

	//new game Menu
	newGameItem = gtk_menu_item_new_with_mnemonic("_NewGame");
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), newGameItem);
	newGameMenu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(newGameItem), newGameMenu);

	//test
	btnTest = gtk_menu_item_new_with_mnemonic("_Test");
	gtk_widget_add_accelerator(btnTest, "activate", accel_group, GDK_KEY_t, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(newGameMenu), btnTest);
	g_signal_connect(G_OBJECT(btnTest), "activate", G_CALLBACK(optionNewGameCB), GINT_TO_POINTER(TEST));

	//easy
	btnEasy = gtk_menu_item_new_with_mnemonic("_Easy");
	gtk_widget_add_accelerator(btnEasy, "activate", accel_group, GDK_KEY_e, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(newGameMenu), btnEasy);
	g_signal_connect(G_OBJECT(btnEasy), "activate", G_CALLBACK(optionNewGameCB), GINT_TO_POINTER(EASY));

	//advanced
	btnAdvanced = gtk_menu_item_new_with_mnemonic("_Advanced");
	gtk_widget_add_accelerator(btnAdvanced, "activate", accel_group, GDK_KEY_a, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(newGameMenu), btnAdvanced);
	g_signal_connect(G_OBJECT(btnAdvanced), "activate", G_CALLBACK(optionNewGameCB), GINT_TO_POINTER(ADVANCED));

	//random
	btnRandom = gtk_menu_item_new_with_mnemonic("_Random");
	gtk_widget_add_accelerator(btnRandom, "activate", accel_group, GDK_KEY_r, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(newGameMenu), btnRandom);
	g_signal_connect(G_OBJECT(btnRandom), "activate", G_CALLBACK(optionNewGameCB), GINT_TO_POINTER(RANDOM));
}

/**
 * @brief Initialze whole window of puzzle game
 * 
 */
void initApplication(){
	GtkWidget *vbox, *content, *boardGrid, *menuGrid;
	GtkWidget *menubar;
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
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

	gtk_container_add(GTK_CONTAINER(puzzleGame->mainWindow), vbox);

	menubar = gtk_menu_bar_new();

	/* content */
	content = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	

	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), content, TRUE, TRUE, 0);

	/* start accelerator group */
	accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(puzzleGame->mainWindow), accel_group);
	
	//create top menu
	initTopMenu(menubar, accel_group);
	
	//init main grid table
	Board *board = puzzleGame->board;
	int numbOfFields = board->rows * board->cols;

	boardGrid = gtk_grid_new();
	gtk_widget_set_size_request(boardGrid, 200, 200);
	menuGrid = gtk_grid_new();
	
	gtk_box_pack_start(GTK_BOX(content), boardGrid, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(content), menuGrid, FALSE, FALSE, 40);

	//init board
	char nameField[10];

	for (int i=0; i< numbOfFields; i++){
		sprintf(nameField, "%d", board->fields[i].value);
		board->fields[i].button = gtk_button_new_with_label(nameField);
		addStyleBtn(board->fields[i].button, board->fields[i].value);
		g_signal_connect(G_OBJECT(board->fields[i].button), "clicked", G_CALLBACK(boardFieldCB), &board->fields[i]);
		gtk_grid_attach(GTK_GRID(boardGrid), board->fields[i].button, i%4, i/4, 1, 1);
		
	}


}
/**
 * @brief Redraw board
 * 
 */
void newGame(){
	//init board
	initBoard(puzzleGame->board, puzzleGame->options->gameType);
	//redraw buttons
	int totalFields = puzzleGame->board->rows * puzzleGame->board->cols;
	for(int i = 0; i < totalFields; i++){
		Field *f = &puzzleGame->board->fields[i];
		updateButtonLabel(f->value, f->button);
	}
}