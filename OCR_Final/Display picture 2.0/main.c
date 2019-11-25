#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "Greyscal.h"
#include "pixel.h"
#include "character.h"
#include "matrix.h"



int LaunchOCR(/*int *argc, char *argv[]*/);
void loadfile(gpointer window);
//Nom DU fichier stocke
char *nameofthefile;
void openhelp();
GtkTextBuffer *buffer;
int advancedmode=0;
void openhelp1();

//image quon voit sur le programme qui est affiche
GtkImage *imageoriginal=NULL;
void switch_active(GtkSwitch *myswitch);




int main(int argc, char *argv[])
{
    /* Variables */
    GtkWidget * window1 = NULL;
    GtkBuilder *builder;
    GtkWidget *closeButton=NULL;
    GtkWidget *openfileButton=NULL;
    GtkWidget *helpbutton=NULL;
    GtkWidget *launchbutton=NULL;
    GtkWidget *Textview=NULL;
    GtkWidget *advance=NULL;
    GtkWidget *helpbutton1=NULL;

    /* Initialisation de GTK+ */
    gtk_init(&argc, &argv);

    /* Creation des widgets de l'interface a partir du fichier XML de Glade, grace au builder GTK */
    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file (builder, "mainui.glade", NULL) == 0) {
      fprintf (stderr, "Erreur: ouverture du fichier GLADE\n") ;
      exit(EXIT_FAILURE);
    }

    /* Recuperation du widget de la fenetre principale */
    window1 = GTK_WIDGET (gtk_builder_get_object (builder, "MainWindow"));
    imageoriginal= GTK_IMAGE(gtk_builder_get_object(builder,"original_image"));
    closeButton= GTK_WIDGET (gtk_builder_get_object(builder, "button_close"));
    openfileButton= GTK_WIDGET(gtk_builder_get_object(builder, "button_charger"));
    helpbutton=GTK_WIDGET(gtk_builder_get_object(builder, "help_button"));
    launchbutton=GTK_WIDGET(gtk_builder_get_object(builder,"launch_ocr"));
    Textview=GTK_WIDGET(gtk_builder_get_object(builder,"zone_de_texte"));
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (Textview));
    advance=GTK_WIDGET(gtk_builder_get_object(builder,"advanced_mode"));
    helpbutton1= GTK_WIDGET(gtk_builder_get_object(builder,"help_button1"));
    

    /* Connection des fonctions de rappel avec les signaux de l'interface */
    gtk_builder_connect_signals (builder, NULL);
    g_signal_connect(G_OBJECT(window1), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    //Bouton Close
    g_signal_connect(G_OBJECT(closeButton), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    //Bouton Open
    g_signal_connect(G_OBJECT(openfileButton),"clicked", G_CALLBACK(loadfile),window1);
    //Bouton Help
    g_signal_connect(G_OBJECT(helpbutton),"clicked",G_CALLBACK(openhelp),NULL);
    //Bouton Launch OCR
    g_signal_connect(G_OBJECT(launchbutton),"clicked",G_CALLBACK(LaunchOCR),NULL);
    //Switch advance
    g_signal_connect(G_OBJECT(advance),"notify::active",G_CALLBACK(switch_active),GTK_SWITCH(advance));
    //Boutton Help
    g_signal_connect(G_OBJECT(helpbutton1),"clicked", G_CALLBACK(openhelp1),NULL);
    

    /* Changement de la fenetre principale a l'etat visible */
    gtk_widget_show (window1);

    /* Lancement de l'execution de la boucle GTK */
    gtk_main ();
    g_object_unref (G_OBJECT (builder));
    /* Fermeture de GTK+ */


    return EXIT_SUCCESS;

}







void loadfile(gpointer window)
{
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  dialog = gtk_file_chooser_dialog_new ("Open File",GTK_WINDOW(window),action,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);

  gtk_widget_show_all(dialog);
  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),"/");
  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_OK)
    {
      GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
      nameofthefile = gtk_file_chooser_get_filename (chooser);
    }
  gtk_widget_destroy (dialog);
  gtk_image_set_from_file(imageoriginal,nameofthefile);
  
}


void openhelp1()
{
    GtkWidget* Fenetre = NULL;

    GtkWidget* Label = NULL;

    gchar* TexteConverti = NULL;

    Fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);  // Définition de la fenêtre

    gtk_window_set_title(GTK_WINDOW(Fenetre), "Instructions"); // Titre de la fenêtre

    gtk_window_set_default_size(GTK_WINDOW(Fenetre), 300, 100); // Taille de la fenêtre

    TexteConverti = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#000000\" size=\"xx-large\"><b>Instructions:</b></span>\n <span face=\"Verdana\" foreground=\"#000000\" size=\"x-large\">1.Open a file \n 2.Switch ON if you want to run in Advanced Mode \n 3.Click on \"Launch OCR\"</span>\n", -1, NULL, NULL, NULL);  //Convertion du texte avec les balises

    Label=gtk_label_new(TexteConverti); // Application de la convertion à notre label

    g_free(TexteConverti); // Libération de la mémoire


    gtk_label_set_use_markup(GTK_LABEL(Label), TRUE); // On dit que l'on utilise les balises pango


    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER); // On centre notre texte


    gtk_container_add(GTK_CONTAINER(Fenetre), Label);  // On ajoute le label a l'interieur de 'Fenetre'


    gtk_widget_show_all(Fenetre); // On affiche 'Fenetre' et tout ce qu'il contient


    
}




void openhelp()
{
    GtkWidget* Fenetre = NULL;

    GtkWidget* Label = NULL;

    gchar* TexteConverti = NULL;

    Fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);  // Définition de la fenêtre

    gtk_window_set_title(GTK_WINDOW(Fenetre), "Credits"); // Titre de la fenêtre

    gtk_window_set_default_size(GTK_WINDOW(Fenetre), 300, 100); // Taille de la fenêtre

    TexteConverti = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#73b5ff\" size=\"xx-large\"><b>Made By JORP Escorp</b></span>\n <span face=\"Verdana\" foreground=\"#39b500\" size=\"x-large\">The OCR Project</span>\n", -1, NULL, NULL, NULL);  //Convertion du texte avec les balises

    Label=gtk_label_new(TexteConverti); // Application de la convertion à notre label

    g_free(TexteConverti); // Libération de la mémoire


    gtk_label_set_use_markup(GTK_LABEL(Label), TRUE); // On dit que l'on utilise les balises pango


    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER); // On centre notre texte


    gtk_container_add(GTK_CONTAINER(Fenetre), Label);  // On ajoute le label a l'interieur de 'Fenetre'


    gtk_widget_show_all(Fenetre); // On affiche 'Fenetre' et tout ce qu'il contient


    
}

void switch_active (GtkSwitch *myswitch)
{
    if (gtk_switch_get_active (myswitch))
      {
      advancedmode=1;
    }else{
      advancedmode=0;
    }
}




int LaunchOCR(/*int argc, char *argv[]*/)
{
  memset(str, 0, sizeof(str));
  if(advancedmode)
    {
      SDL_Window *window = NULL;
      SDL_Renderer *renderer = NULL;
      //SDL_Texture *texture = NULL;
      SDL_Surface *surface = NULL;
      SDL_Surface *tmp = NULL;
      //int statut = EXIT_FAILURE;

      tmp = SDL_LoadBMP(nameofthefile);

      SDL_CreateWindowAndRenderer(1600, 960, SDL_WINDOW_SHOWN, &window,&renderer);

      // surface = SDL_CreateRGBSurface(0, 300, 200, 32, 0, 0, 0, 0);
      // texture = SDL_CreateTextureFromSurface(renderer, surface);
      // texture = SDL_CreateTextureFromSurface(renderer, tmp);
      // SDL_FreeSurface(surface);
      // SDL_FreeSurface(tmp);
      surface = SDL_GetWindowSurface(window);
      SDL_BlitSurface(tmp, NULL, surface, NULL);
      SDL_RenderPresent(renderer);
      SDL_UpdateWindowSurface(window);

      SDL_BlitSurface(tmp, NULL, surface, NULL);
   
      SDL_LockSurface(tmp);
      makeitgrey(tmp, tmp->w, tmp->h);
      SDL_UnlockSurface(tmp);
      SDL_BlitSurface(tmp, NULL, surface, NULL);
      SDL_RenderPresent(renderer);
      SDL_UpdateWindowSurface(window);
    

      SDL_LockSurface(tmp);
      makeitblackandwhite(tmp, tmp->w, tmp->h);
      SDL_UnlockSurface(tmp);
      SDL_BlitSurface(tmp, NULL, surface, NULL);
      SDL_RenderPresent(renderer);
      SDL_UpdateWindowSurface(window);
      SDL_Delay(2000);

    
      LinesAllWhiteInRed(tmp);

  
      /*SDL_BlitSurface(tmp, NULL, surface, NULL);
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);*/
      SDL_LockSurface(tmp);/*Here we lock the surface*/
      SDL_UnlockSurface(surface); /*Here we unlock the surface, it can be used*/
   
      BlockOfCharacter(tmp, surface);
      SDL_UnlockSurface(tmp);
   	  
    
      SDL_BlitSurface(tmp, NULL, surface, NULL);
      SDL_RenderPresent(renderer);
      SDL_UpdateWindowSurface(window);

      SDL_FreeSurface(surface);
      SDL_FreeSurface(tmp);
      SDL_DestroyRenderer(renderer);

      //afficher le text
      gtk_text_buffer_set_text (buffer,str, -1);
    
    
      // statut = EXIT_SUCCESS;
      SDL_Delay(5000);

    

      //Quit
      if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
      if(NULL != window)
        SDL_DestroyWindow(window);
      SDL_Quit();
    
      return 0;
    }
 
      
  else
    {
      SDL_Renderer *renderer = NULL;
      //SDL_Texture *texture = NULL;
      SDL_Surface *surface = NULL;
      SDL_Surface *tmp = NULL;
      //int statut = EXIT_FAILURE;

      tmp = SDL_LoadBMP(nameofthefile);

      surface = SDL_CreateRGBSurface(0, 1920, 1060, 32, 0, 0, 0, 0);
      // texture = SDL_CreateTextureFromSurface(renderer, surface);
      // texture = SDL_CreateTextureFromSurface(renderer, tmp);
      // SDL_FreeSurface(surface);
      // SDL_FreeSurface(tmp);
      //surface = SDL_GetWindowSurface(window);
      SDL_BlitSurface(tmp, NULL, surface, NULL);
      SDL_RenderPresent(renderer);

      SDL_BlitSurface(tmp, NULL, surface, NULL);
   
      SDL_LockSurface(tmp);
      makeitgrey(tmp, tmp->w, tmp->h);
      SDL_UnlockSurface(tmp);
      SDL_BlitSurface(tmp, NULL, surface, NULL);
      SDL_RenderPresent(renderer);
    

      SDL_LockSurface(tmp);
      makeitblackandwhite(tmp, tmp->w, tmp->h);
      SDL_UnlockSurface(tmp);
      SDL_BlitSurface(tmp, NULL, surface, NULL);
      SDL_RenderPresent(renderer);

    
      LinesAllWhiteInRed(tmp);

  
      /*SDL_BlitSurface(tmp, NULL, surface, NULL);
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);*/
      SDL_LockSurface(tmp);/*Here we lock the surface*/
      SDL_UnlockSurface(surface); /*Here we unlock the surface, it can be used*/
   
      BlockOfCharacter(tmp, surface);
      SDL_UnlockSurface(tmp);
   	  
    
      SDL_BlitSurface(tmp, NULL, surface, NULL);
      SDL_RenderPresent(renderer);

      SDL_FreeSurface(surface);
      SDL_FreeSurface(tmp);
      SDL_DestroyRenderer(renderer);

      //afficher le text
      gtk_text_buffer_set_text (buffer,str, -1);
    
      // statut = EXIT_SUCCESS;    

      //Quit
      if(NULL != renderer){
	
        SDL_DestroyRenderer(renderer);
      }
      SDL_Quit();
    
      return 0;
    }
}
