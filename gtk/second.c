#include <gtk/gtk.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>

GtkBuilder *builder ;
GtkTextView *textview1;
GtkColorSelection *colorselection;
GtkRadioButton *radionbutton1;
GtkRadioButton *radionbutton2;
gboolean state1 = TRUE;
GtkWidget *window1;
gboolean state2 ;
GdkColor color1;
GdkColor color2;
/*字体颜色*/
void textcolor(GtkWidget *widget, gpointer data)
{
     gtk_color_selection_get_current_color(colorselection, &color1);
     gtk_widget_modify_text(GTK_WIDGET(textview1), GTK_STATE_NORMAL, &color1);
}

/*背景颜色*/
void bgcolor(GtkWidget *widget, gpointer data)
{
     gtk_color_selection_get_current_color(colorselection, &color2);
     gtk_widget_modify_bg(window1, GTK_STATE_NORMAL, &color2);
}

/*获取字体颜色按钮状态*/
void getstate1(GtkWidget *widget, gpointer data)
{
    state1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radionbutton1));
    if(state1)
        g_signal_connect(colorselection, "color-changed", G_CALLBACK(textcolor), NULL);
    else
        g_signal_handlers_disconnect_by_func(colorselection, G_CALLBACK(textcolor), NULL);

}

/*获取背景颜色按钮状态*/
void getstate2(GtkWidget *widget, gpointer data)
{
    state2 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radionbutton2));
    if(state2)
        g_signal_connect(colorselection, "color-changed", G_CALLBACK(bgcolor), NULL);
    else
        g_signal_handlers_disconnect_by_func(colorselection, G_CALLBACK(bgcolor), NULL);
}

/*统计字符数*/
void charsize(GtkWidget *textbuff, GtkWidget *entry4)
{
    int charsize ;
    char ccharsize[4];

    charsize =  gtk_text_buffer_get_char_count (GTK_TEXT_BUFFER(textbuff));
    itoa(charsize, ccharsize, 10);
    gtk_entry_set_text (GTK_ENTRY(entry4), ccharsize);
}
/*统计行数*/
void linesize(GtkWidget *textbuff, GtkWidget *entry3)
{
    int linesize ;
    char clinesize[4];

    linesize =  gtk_text_buffer_get_line_count (GTK_TEXT_BUFFER(textbuff));
    itoa(linesize, clinesize, 10);
    gtk_entry_set_text (GTK_ENTRY(entry3), clinesize);
}
/*打开功能*/
void openFile (GtkObject *object, GtkWidget *dialog1)
{
    gtk_widget_show(dialog1);
}
/*保存功能*/

void saveFile(GtkWidget *entry2, GtkWidget *textview)
{
    FILE *fp;
    gchar *fpath;
    gchar *text;
    GtkTextIter start, end;
    GtkTextBuffer *textbuff;
    gchar *fileName;

    char path[100] = "C:\\Users\\liuxi_001\\Desktop\\";
    fileName= gtk_entry_get_text(GTK_ENTRY(entry2));
    fpath = strcat(path, fileName);
    fp = fopen(fpath, "wb");
    textbuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    gtk_text_buffer_get_bounds(textbuff, &start, &end);
    text = gtk_text_buffer_get_text(textbuff, &start, &end, TRUE);
    fputs(text, fp);

    fclose(fp);
}
/*应用程序图标*/
GdkPixbuf *create_pixbuf(const gchar * filename) {

   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);

   if(!pixbuf) {

      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}

int main (int argc, char *argv[])
{
    GtkTextBuffer *textbuff;
    GtkWidget *dialog1;

    GtkWidget *open;

    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *entry4;

    /*builder.xml连接创建*/
    gtk_init (&argc, &argv);
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "myapp.glade", NULL);
    gtk_builder_connect_signals (builder, NULL);
    dialog1 = GTK_WIDGET (gtk_builder_get_object (builder, "dialog1"));
    entry2 = GTK_WIDGET (gtk_builder_get_object (builder, "entry2"));
    window1 = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
    textview1 = GTK_TEXT_VIEW (gtk_builder_get_object (builder, "textview1"));
    entry3 = GTK_WIDGET (gtk_builder_get_object (builder, "entry3"));
    entry4= GTK_WIDGET (gtk_builder_get_object (builder, "entry4"));
    open = GTK_WIDGET (gtk_builder_get_object (builder, "open"));
    colorselection = GTK_COLOR_SELECTION (gtk_builder_get_object(builder, "colorselection1"));
    radionbutton1 = GTK_RADIO_BUTTON (gtk_builder_get_object(builder, "radiobutton1"));
    radionbutton2 = GTK_RADIO_BUTTON (gtk_builder_get_object(builder, "radiobutton2"));

    textbuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview1));

    g_signal_connect(open, "activate", G_CALLBACK(openFile), dialog1);
    g_signal_connect(entry2, "activate", G_CALLBACK(saveFile), textview1);
    g_signal_connect(textbuff, "changed", G_CALLBACK(linesize), entry3);
    g_signal_connect(textbuff, "changed", G_CALLBACK(charsize), entry4);
    g_signal_connect(radionbutton1, "toggled", G_CALLBACK(getstate1), NULL);
    g_signal_connect(radionbutton2, "toggled", G_CALLBACK(getstate2), NULL);

    gtk_window_set_icon(GTK_WINDOW(window1), create_pixbuf("icon.ico"));
    g_object_unref (G_OBJECT (builder));
    gtk_widget_show (window1);
    gtk_main ();
    return 0;
}
