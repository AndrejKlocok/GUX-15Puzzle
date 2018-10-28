#include "puzzleCss.h"

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
}

void addStyleBtn(GtkWidget *btn, int value){
    if(value%2){
        gtk_widget_set_name(btn, "odd");
    }
    else if(value == 0){
        gtk_widget_set_name(btn, "zero");
        gtk_button_set_label(GTK_BUTTON(btn), "");
    }
    else{
        gtk_widget_set_name(btn, "prime");
    }
}

