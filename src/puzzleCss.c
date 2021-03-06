/*
 * Author:  Andrej Klocok
 * Login:	xkloco00
 * File:	puzzleCss.c
 */
#include "puzzleCss.h"
/**
 * @brief Initialize css properties from CSS file
 * 
 */
void initCSS(){
    GtkCssProvider *cssProvider;
	GdkDisplay *display;
  	GdkScreen *screen;
	char* cssFilePath = "src/puzzle.css";

	cssProvider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
 
    GError *error = 0;
    gtk_css_provider_load_from_file(cssProvider, g_file_new_for_path(cssFilePath), &error);
    g_object_unref (cssProvider);

    GtkSettings *default_settings = gtk_settings_get_default();
    g_object_set(default_settings, "gtk-button-images", TRUE, NULL); 
}
/**
 * @brief Loads pictures from img directory to game structure
 * 
 * @param board     board
 * @param imgs      structure that holds images
 */
void initPictures(Board *board, ThemeImgs *imgs){

    int totalFields = board->cols * board->rows;
    imgs->length = totalFields;
    imgs->images = malloc(sizeof(ImageStruct)*totalFields);
    char name[50];
    memset(name,0,50);

    //load colors
    for(int i=0; i< totalFields; i++){
        sprintf(name, "img/cat%d.jpg",i);
        imgs->images[i].image = gtk_image_new_from_file(name);
        g_object_ref(imgs->images[i].image);
        gtk_widget_show(GTK_WIDGET(imgs->images[i].image));
        memset(name,0,50);
    }
}
/**
 * @brief Function add style to button according to used theme and value that button struct(Field) holds
 * 
 * @param btn       button
 * @param value     Field value
 * @param Themes    used theme
 * @param imgs      loaded images
 */
void addStyleBtn(GtkWidget *btn, int value, enum Themes theme, ThemeImgs *imgs){
    char  buf[5];

	sprintf(buf, "%d", value);
    gtk_button_set_image (GTK_BUTTON (btn), NULL);
            
    switch (theme)
    {
        case RoyalT:
            if(value%2){
                gtk_widget_set_name(btn, "oddR");
                gtk_button_set_label(GTK_BUTTON(btn), buf);
                
            }
            else if(value == 0){
                gtk_widget_set_name(btn, "zero");
                gtk_button_set_label(GTK_BUTTON(btn), "");
            }
            else{
                gtk_widget_set_name(btn, "primeR");
                gtk_button_set_label(GTK_BUTTON(btn), buf);
            }
            break;
        case ClassicT:
            if(value == 0){
                gtk_widget_set_name(btn, "zero");
                gtk_button_set_label(GTK_BUTTON(btn), "");
            }
            else{
                gtk_widget_set_name(btn, "numbC");
                gtk_button_set_label(GTK_BUTTON(btn), buf);
            }
            break;
        default://KittenT
            gtk_widget_set_name(btn, "img");
            gtk_button_set_label(GTK_BUTTON(btn), "");
            gtk_button_set_image (GTK_BUTTON (btn), imgs->images[value].image);
            
            break;
    }
    
}

