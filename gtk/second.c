#include <gtk/gtk.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>

GtkBuilder *builder ;
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
    GtkWidget *window1;
    GtkWidget *open;
    GtkWidget *textview1;
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
    textview1 = GTK_WIDGET (gtk_builder_get_object (builder, "textview1"));
    entry3 = GTK_WIDGET (gtk_builder_get_object (builder, "entry3"));
    entry4= GTK_WIDGET (gtk_builder_get_object (builder, "entry4"));
    open = GTK_WIDGET (gtk_builder_get_object (builder, "open"));

    textbuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview1));

    g_signal_connect(open, "activate", G_CALLBACK(openFile), dialog1);
    g_signal_connect(entry2, "activate", G_CALLBACK(saveFile), textview1);
    g_signal_connect(textbuff, "changed", G_CALLBACK(linesize), entry3);
    g_signal_connect(textbuff, "changed", G_CALLBACK(charsize), entry4);

    gtk_window_set_icon(GTK_WINDOW(window1), create_pixbuf("icon.ico"));
    g_object_unref (G_OBJECT (builder));
    gtk_widget_show (window1);
    gtk_main ();
    return 0;
}
