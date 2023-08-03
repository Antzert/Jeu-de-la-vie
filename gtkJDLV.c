#include <stdlib.h>
#include <gtk-2.0/gtk/gtk.h>

/*
gcc gtkJDLV.c -o prog `pkg-config --cflags --libs gtk+-2.0`
*/

int main(int argc, char** argv)
{
	GtkWidget* window = NULL;
	GtkWidget* label = NULL;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window), "Jeu de la vie launcher");
	gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	label = gtk_label_new("<span size=\"xx-large\">Launcher du jeu de la vie</span>");
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	gtk_container_add(GTK_CONTAINER(window), label);

	gtk_widget_show_all(window);

	gtk_main();
	return EXIT_SUCCESS;
}