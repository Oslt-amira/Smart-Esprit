#include <gtk/gtk.h>



 



typedef struct{

 char nom[50];

 char pnom[50];

 char  cin[9];

 char  id[50];

 char contact[10];

 char enquette[10];

 char date[30];

 char objet[50];

 char prob[300];





}rec;



void actv(int e,char v[]);

void objpl(int obj1,int obj2,char ob[]);

void ajouter_pl(rec p);

void afficher_rec(GtkWidget *liste,char fname[]);

void supprimer_pl(rec x);

void recherche_pl(char rd[30]);

int service_rec();

void pos_car(char ch[], char c, int *p_oc, int *d_oc);





