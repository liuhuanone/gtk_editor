#include <gtk/gtk.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>

GtkBuilder *builder ;
GtkTextView *textview1;
GtkColorSelection *colorselection;
GtkFontSelection *fontselection;
GtkColorButton *colorbutton1;
GtkColorButton *colorbutton2;
GtkFontButton *fontbutton1;
gboolean state1 = TRUE;
GtkWidget *window1;
gboolean state2 ;
GdkColor color1;
GdkColor color2;
GdkColor color3;

/*字体颜色*/
void fcSet(GtkWidget *widget, gpointer data)
{
     gtk_color_button_get_color(colorbutton2, &color2);
     gtk_widget_modify_text(GTK_WIDGET(textview1), GTK_STATE_NORMAL, &color2);
}
//void textcolor(GtkWidget *widget, gpointer data)
//{
//     gtk_color_selection_get_current_color(colorselection, &color1);
//     gtk_widget_modify_text(GTK_WIDGET(textview1), GTK_STATE_NORMAL, &color1);
//}

/*背景颜色*/
void bgSet(GtkWidget *widget, gpointer data)
{
     gtk_color_button_get_color(colorbutton1, &color1);
     gtk_widget_modify_bg(GTK_WIDGET(window1), GTK_STATE_NORMAL, &color1);
}

//void bgcolor(GtkWidget *widget, gpointer data)
//{
//     gtk_color_selection_get_current_color(colorselection, &color2);
//     gtk_widget_modify_base(GTK_WIDGET(textview1), GTK_STATE_NORMAL, &color2);
//}

/*获取字体颜色按钮状态*/
//void getstate1(GtkWidget *widget, gpointer data)
//{
//    state1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radionbutton1));
//    if(state1)
//        g_signal_connect(colorselection, "color-changed", G_CALLBACK(textcolor), NULL);
//    else
//        g_signal_handlers_disconnect_by_func(colorselection, G_CALLBACK(textcolor), NULL);
//
//}

/*获取背景颜色按钮状态*/
//void getstate2(GtkWidget *widget, gpointer data)
//{
//    state2 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radionbutton2));
//    if(state2)
//        g_signal_connect(colorselection, "color-changed", G_CALLBACK(bgcolor), NULL);
//    else
//        g_signal_handlers_disconnect_by_func(colorselection, G_CALLBACK(bgcolor), NULL);
//}
/*设置字体*/
void fontSet(GtkWidget *widget, gpointer data)
{
    gchar *font;
    PangoFontDescription *font1;
    font = gtk_font_button_get_font_name(fontbutton1);
    font1 = pango_font_description_from_string(font);
    gtk_widget_modify_font(GTK_WIDGET(textview1), font1);


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
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *entry4;

    /*builder.xml连接创建*/
    gtk_init (&argc, &argv);
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "myapp.glade", NULL);
    gtk_builder_connect_signals (builder, NULL);
    entry2 = GTK_WIDGET (gtk_builder_get_object (builder, "entry2"));
    window1 = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
    textview1 = GTK_TEXT_VIEW (gtk_builder_get_object (builder, "textview1"));
    entry3 = GTK_WIDGET (gtk_builder_get_object (builder, "entry3"));
    entry4= GTK_WIDGET (gtk_builder_get_object (builder, "entry4"));
    colorselection = GTK_COLOR_SELECTION (gtk_builder_get_object(builder, "colorselection1"));
    fontselection = GTK_FONT_SELECTION (gtk_builder_get_object(builder, "fontselection1"));
    colorbutton1 = GTK_COLOR_BUTTON (gtk_builder_get_object(builder, "colorbutton1"));
    colorbutton2 = GTK_COLOR_BUTTON (gtk_builder_get_object(builder, "colorbutton2"));
    fontbutton1 = GTK_FONT_BUTTON (gtk_builder_get_object(builder, "fontbutton1"));
    textbuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview1));
    g_signal_connect(entry2, "activate", G_CALLBACK(saveFile), textview1);
    g_signal_connect(textbuff, "changed", G_CALLBACK(linesize), entry3);
    g_signal_connect(textbuff, "changed", G_CALLBACK(charsize), entry4);
    g_signal_connect(colorbutton1, "color-set", G_CALLBACK(bgSet), NULL);
    g_signal_connect(colorbutton2, "color-set", G_CALLBACK(fcSet), NULL);
    g_signal_connect(fontbutton1, "font-set", G_CALLBACK(fontSet), NULL);


    gtk_window_set_icon(GTK_WINDOW(window1), create_pixbuf("icon.ico"));
    g_object_unref (G_OBJECT (builder));
    gtk_widget_show (window1);
    gtk_main ();
    return 0;
}
