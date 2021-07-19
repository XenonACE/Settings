#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

GtkWidget *window;
GtkWidget *quitBtn;
GtkBuilder *builder = NULL;
GtkWidget *stack;

// Stack children
GtkWidget *aboutpane;
GtkWidget *themepane;

// Main window buttons
GtkWidget *aboutBtn;
GtkWidget *themeBtn;

static void quitButtonClicked(__attribute__((unused)) GtkWidget *widget,
			      __attribute__((unused)) gpointer data)
{
	g_print("%s called.\n", __FUNCTION__);
	gtk_main_quit();
}

static void aboutButtonClicked(__attribute__((unused)) GtkWidget *widget,
			      __attribute__((unused)) gpointer data)
{
	g_print("%s called.\n", __FUNCTION__);
	gtk_stack_set_visible_child(stack, aboutpane);
}

static void themeButtonClicked(__attribute__((unused)) GtkWidget *widget,
			      __attribute__((unused)) gpointer data)
{
	g_print("%s called.\n", __FUNCTION__);
	gtk_stack_set_visible_child(stack, themepane);
}

gboolean windowDelete(__attribute__((unused)) GtkWidget *widget,
		      __attribute__((unused)) GdkEvent *event,
		      __attribute__((unused)) gpointer data)
{
	g_print("%s called.", __FUNCTION__);
	gtk_main_quit();
	return FALSE;
}

int main(int argc, char **argv) {
	FILE *file;
	char path[1035];

	file = popen("/bin/uname -r", "r");
	if (file == NULL) {
		printf("Error reading /bin/uname");
		exit(1);
	}

	while(fgets(path, sizeof(path), file) != NULL) {
		printf("%s", path);
	}

	pclose(file);

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();

	if (gtk_builder_add_from_file(builder, "layout.glade", NULL) == 0) {
		printf("gtk_builder_add_from_file FAILED\n");
		return(1);
	}

	window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
	quitBtn = GTK_WIDGET(gtk_builder_get_object(builder, "quitBtn"));
	stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack"));

	// Stack children
	aboutpane = GTK_WIDGET(gtk_builder_get_object(builder, "about-pane"));
	themepane = GTK_WIDGET(gtk_builder_get_object(builder, "theme-pane"));

	//
	aboutBtn = GTK_WIDGET(gtk_builder_get_object(builder, "about-btn"));
	themeBtn = GTK_WIDGET(gtk_builder_get_object(builder, "theme-btn"));

	g_signal_connect(quitBtn, "clicked", G_CALLBACK(quitButtonClicked), NULL);
	g_signal_connect(window, "delete_event", G_CALLBACK(windowDelete), NULL);

	// Main window buttons
	g_signal_connect(aboutBtn, "clicked", G_CALLBACK(aboutButtonClicked), NULL);
	g_signal_connect(themeBtn, "clicked", G_CALLBACK(themeButtonClicked), NULL);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
