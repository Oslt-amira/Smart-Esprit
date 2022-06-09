#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <string.h>
#include "reclamation.h"

int c=0;
int E=0;
int obj1=0;
int obj2=0;
int M=1;
rec del;

void
on_aobutton_dep_clicked                  (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *B;
GtkWidget *C;
C=lookup_widget(button,"aowindow_menu");
gtk_widget_hide(C);
B=create_aowindow_formulaire();
gtk_widget_show(B);

}


void
on_aobutton_consult_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aowindow_menu ;
GtkWidget *aowindow_consult;
GtkWidget *aotreeview_rec;

aowindow_menu =lookup_widget(objet,"aowindow_menu ");

gtk_widget_destroy(aowindow_menu );
aowindow_consult=lookup_widget(objet,"aowindow_consult");
aowindow_consult=create_aowindow_consult();

gtk_widget_show(aowindow_consult);

aotreeview_rec=lookup_widget(aowindow_consult,"aotreeview_rec");
afficher_rec(aotreeview_rec,"reclm.txt");

}


void
on_aoradiobutton_oui_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
  c=1;
}


void
on_aoradiobutton_non_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
  c=0;
}


void
on_aocheckbutton_ouieq_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
char mail[250]="(  Vous recevrez un e-mail sur l'adresse avec laquelle voue êtes connecté(e)   )";
 GtkWidget*msg ;
 
 if (gtk_toggle_button_get_active(togglebutton))
  {
   msg= lookup_widget(togglebutton, "label_oui") ;
   gtk_label_set_text(GTK_LABEL(msg),mail);
  E=1;
 
  }
}


void
on_aocheckbutton_noneq_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(togglebutton))
  E=0;
}


void
on_aocheckbuttonr_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(togglebutton))
 obj1=1;
}


void
on_aocheckbuttonh_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(togglebutton))
 obj2=1;
}


void
on_aobutton_dep_pl_clicked               (GtkWidget       *button,
                                        gpointer         user_data)
{

rec r;
int j,m,a;
char dj[3];
char dm[4];
char da[5];
char ct[10];
char eq[10];
char objj[]="";
char text[50]="veuillez compléter tous les champs requis";
char text_cin[50]="CIN invalide ";

GtkWidget *A;
GtkWidget *B;

GtkWidget *aoentrynom;
GtkWidget *aoentrypnom;
GtkWidget *aoentrycin;
GtkWidget *aoentryid;
GtkWidget *aospinbutton_jr;
GtkWidget *aospinbutton_ms;
GtkWidget *aospinbutton_an;
GtkWidget *aoentryprob;
GtkWidget *aolabel_complete;
GtkWidget *aolabel_error_cin;


aoentrynom=lookup_widget(button,"aoentrynom");
aoentrypnom=lookup_widget(button,"aoentrypnom");
aoentrycin=lookup_widget(button,"aoentrycin");
aoentryid=lookup_widget(button,"aoentryid");

aospinbutton_jr=lookup_widget(button, "aospinbutton_jr");
aospinbutton_ms=lookup_widget(button, "aospinbutton_ms");
aospinbutton_an=lookup_widget(button, "aospinbutton_an");
aoentryprob=lookup_widget(button,"aoentryprob");
strcpy(r.nom,gtk_entry_get_text(GTK_ENTRY(aoentrynom)));
strcpy(r.pnom,gtk_entry_get_text(GTK_ENTRY(aoentrypnom)));
strcpy(r.cin,gtk_entry_get_text(GTK_ENTRY(aoentrycin)));
strcpy(r.id,gtk_entry_get_text(GTK_ENTRY(aoentryid)));
actv(c,ct);
strcpy(r.contact,ct);
actv(E,eq);
strcpy(r.enquette,eq);
j=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aospinbutton_jr));
m=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aospinbutton_ms));
a=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aospinbutton_an));
sprintf(dj, "%d",j );
sprintf(dm, "%d",m );
sprintf(da, "%d",a );
strcpy(r.date,dj);
strcat(r.date,"/");
strcat(r.date,dm);
strcat(r.date,"/");
strcat(r.date,da);
objpl(obj1,obj2,objj);
strcpy(r.objet,objj);
strcpy(r.prob,gtk_entry_get_text(GTK_ENTRY(aoentryprob)));
if ((strlen(r.cin)!=8))
{
aolabel_error_cin= lookup_widget(button, "aolabel_error_cin") ;
gtk_label_set_text(GTK_LABEL(aolabel_error_cin),text_cin);
}
else
if((strlen(r.nom)==0)||(strlen(r.pnom)==0)||(strlen(r.cin)==0)||(strlen(r.id)==0)||(strlen(r.contact)==0)||(strlen(r.enquette)==0)||(strlen(r.date)==0)||(strlen(r.objet)==0)||(strlen(r.prob)==0))
{
aolabel_complete= lookup_widget(button, "aolabel_complete") ;
gtk_label_set_text(GTK_LABEL(aolabel_complete),text);
}
else
{
ajouter_pl(r);
B=create_aowindow_dep_succ();
gtk_widget_show(B);
A=lookup_widget(button,"aowindow_formulaire");
gtk_widget_hide(A);

}
}


void
on_aobutton_annuler_pl_clicked           (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *A;
GtkWidget *B;
A=lookup_widget(button,"aowindow_formulaire");
gtk_widget_hide(A);
B=create_aowindow_menu ();
gtk_widget_show(B);
}


void
on_aotreeview_rec_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter   iter;
gchar *nom;
gchar *pnom;
gchar *cin;
gchar *id;
gchar *contact;
gchar *enquette;
gchar *date;
gchar *objet;
gchar *prob;
rec r;


GtkTreeModel *model = gtk_tree_view_get_model(treeview);

if (gtk_tree_model_get_iter(model, &iter, path))
{
gtk_tree_model_get (GTK_LIST_STORE(model),&iter,0,&nom,1,&pnom,2,&cin,3,&id,4,&contact,5,&enquette,6,&date,7,&objet,8,&prob,-1);
strcpy(r.nom,nom);
strcpy(r.pnom,pnom);
strcpy(r.cin,cin);
strcpy(r.id,id);
strcpy(r.contact,contact);
strcpy(r.enquette,enquette);
strcpy(r.date,date);
strcpy(r.objet,objet);
strcpy(r.prob,prob);
strcpy(del.nom,nom);
strcpy(del.pnom,pnom);
strcpy(del.cin,cin);
strcpy(del.id,id);
strcpy(del.contact,contact);
strcpy(del.enquette,enquette);
strcpy(del.date,date);
strcpy(del.objet,objet);
strcpy(del.prob,prob);
afficher_rec(treeview,"reclm.txt");
}

}


void
on_aobutton_acc_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aowindow_consult,*wz;
GtkWidget *aotreeview_rec;

wz=lookup_widget(objet,"aowindow_consult");
aowindow_consult=create_aowindow_consult();
gtk_widget_show(aowindow_consult);
gtk_widget_hide(wz);
aotreeview_rec=lookup_widget(aowindow_consult,"aotreeview_rec");

afficher_rec(aotreeview_rec,"reclm.txt");



}


void
on_aobutton_modifier_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{

GtkWidget *B;
B=create_aowindow_modif();
gtk_widget_show(B);

}


void
on_aobutton_supprimer_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
   GtkWidget *B;
B=create_aowindow_c_supp();
gtk_widget_show(B);
 
}


void
on_aobutton_oui_supp_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *A;
A=lookup_widget(objet,"aowindow_c_supp");
gtk_widget_hide(A);
GtkWidget *B;
B=create_aowindow_cs();
gtk_widget_show(B);
supprimer_pl(del);

}


void
on_aobutton_non_supp_clicked             (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *A;
A=lookup_widget(button,"aowindow_c_supp");
gtk_widget_hide(A);
}


void
on_aobutton_rech_pl_clicked              (GtkButton       *objet,
                                        gpointer         user_data)
{GtkWidget *aotreeview_rec;
GtkWidget *aowindow_consult ,*wz;
GtkWidget *aocombobox_rech; 
GtkWidget *aoentry_rech;
char rech[30]; 
char mode_rech[30];


aocombobox_rech=lookup_widget(objet,"aocombobox_rech");

wz=lookup_widget(objet,"aowindow_consult");
aowindow_consult=create_aowindow_consult();
gtk_widget_show(aowindow_consult);
gtk_widget_hide(wz);
aotreeview_rec=lookup_widget(aowindow_consult,"aotreeview_rec");

if (strcmp("Nom",gtk_combo_box_get_active_text(GTK_COMBO_BOX(aocombobox_rech)))==0)
strcpy(mode_rech,"Nom");
if (strcmp("Prénom",gtk_combo_box_get_active_text(GTK_COMBO_BOX(aocombobox_rech)))==0)
strcpy(mode_rech,"Prénom");
if 
(strcmp("CIN",gtk_combo_box_get_active_text(GTK_COMBO_BOX(aocombobox_rech)))==0)
strcpy(mode_rech,"CIN");
if
(strcmp("ID",gtk_combo_box_get_active_text(GTK_COMBO_BOX(aocombobox_rech)))==0)
strcpy(mode_rech,"ID");
if
(strcmp("Date",gtk_combo_box_get_active_text(GTK_COMBO_BOX(aocombobox_rech)))==0)
strcpy(mode_rech,"Date");

aoentry_rech=lookup_widget(objet,"aoentry_rech");
strcpy(rech,gtk_entry_get_text(GTK_ENTRY(aoentry_rech)));
recherche_pl(rech,mode_rech);
afficher_rec(aotreeview_rec,"drec.txt");

}





void
on_aobutton_retour_pl_clicked            (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *aowindow_dep_succ;
GtkWidget *B;
aowindow_dep_succ=lookup_widget(objet,"aowindow_dep_succ");
gtk_widget_destroy(aowindow_dep_succ);

B=create_aowindow_menu ();
gtk_widget_show(B);
}


void
on_aobutton_retour_menu_p_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}



void
on_aoentry_mod_nom_grab_focus          (GtkWidget       *widget,
                                        gpointer         user_data)
{
GtkWidget* modif_n;
GtkWidget* modif_pn;
GtkWidget* modif_cin;
GtkWidget* modif_id;
GtkWidget* modif_prob;
GtkWidget* rb_oui;
GtkWidget* cb_eqt_oui;
GtkWidget* cb_eqt_non;
GtkWidget* d_j;
GtkWidget* d_m;
GtkWidget* d_a;
GtkWidget* cb_obj_h;
GtkWidget* cb_obj_r;



modif_n=lookup_widget(widget, "aoentry_mod_nom");
modif_pn=lookup_widget(widget, "aoentry_mod_pnom");
modif_cin=lookup_widget(widget, "aoentry_mod_cin");
modif_id=lookup_widget(widget, "aoentry_mod_id");
modif_prob=lookup_widget(widget, "aoentry_mod_prob");

gtk_entry_set_text(GTK_ENTRY(modif_n),del.nom);
gtk_entry_set_text(GTK_ENTRY(modif_pn),del.pnom);
gtk_entry_set_text(GTK_ENTRY(modif_cin),del.cin);
gtk_entry_set_text(GTK_ENTRY(modif_id),del.id);
gtk_entry_set_text(GTK_ENTRY(modif_prob),del.prob);

rb_oui=lookup_widget(widget, "aoradiobutton_modif_c_oui");


if(strcmp(del.contact,"oui")==0) gtk_toggle_button_set_active(GTK_RADIO_BUTTON(rb_oui),TRUE);

cb_eqt_oui=lookup_widget(widget, "aocheckbutton_meqt_oui");
if(strcmp(del.enquette,"Oui")==0) gtk_toggle_button_set_active(GTK_RADIO_BUTTON(cb_eqt_oui),TRUE);
else 
{
cb_eqt_non=lookup_widget(widget, "aocheckbutton_meqt_non");
gtk_toggle_button_set_active(GTK_RADIO_BUTTON(cb_eqt_non),TRUE);
}



int p_oc=-1,d_oc=0;
pos_car(del.date,'/',&p_oc,&d_oc);
int i;
char j [3];
for(i=0;i<p_oc;i++) j[i]=del.date[i];
j[p_oc]='\0';
int ij=0;
ij=atoi(j);
d_j=lookup_widget(widget, "aospinbutton_md_j");
gtk_spin_button_set_value(d_j,ij);
char m [3];
for(i=p_oc+1;i<d_oc;i++) m[i-p_oc-1]=del.date[i];
m[d_oc-p_oc-1]='\0';
int im=0;
im=atoi(m);
d_m=lookup_widget(widget, "aospinbutton_md_ms");
gtk_spin_button_set_value(d_m,im);
char a [5];
for(i=d_oc+1;i<strlen(del.date);i++) a[i-d_oc-1]=del.date[i];
a[strlen(del.date)-d_oc-1]='\0';
int ia=0;
ia=atoi(a);
d_a=lookup_widget(widget, "aospinbutton_md_an");
gtk_spin_button_set_value(d_a,ia);


if (strlen(del.objet)==13)
{
cb_obj_h=lookup_widget(widget, "aocheckb_obj_h");
gtk_toggle_button_set_active(GTK_RADIO_BUTTON(cb_obj_h),TRUE);
}
else
if (strlen(del.objet)==14)
{
cb_obj_r=lookup_widget(widget, "aocheckb_obj_r");
gtk_toggle_button_set_active(GTK_RADIO_BUTTON(cb_obj_r),TRUE);
}
else
{
cb_obj_h=lookup_widget(widget, "aocheckb_obj_h");
gtk_toggle_button_set_active(GTK_RADIO_BUTTON(cb_obj_h),TRUE);    
cb_obj_r=lookup_widget(widget, "aocheckb_obj_r");
gtk_toggle_button_set_active(GTK_RADIO_BUTTON(cb_obj_r),TRUE);
}

}


void
on_aoradiobutton_modif_c_non_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
  c=0;
}


void
on_aoradiobutton_modif_c_oui_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
  c=1;
}


void
on_aocheckbutton_meqt_non_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))) E=0;
}


void
on_aocheckb_obj_h_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
 obj2=1;
}



void
on_aocheckbutton_meqt_oui_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))) E=1;
}


void
on_aocheckb_obj_r_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(togglebutton))
 obj1=1;
}


void
on_aobutton_modif_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
supprimer_pl(del);
rec r;
int j,m,a;
char dj[3];
char dm[4];
char da[5];
char ct[10];
char eq[10];
char objj[]="";
char text[50]="veuillez compléter tous les champs requis";
char text_cin[50]="CIN invalide ";

GtkWidget *aoentry_mod_nom;
GtkWidget *aoentry_mod_pnom;
GtkWidget *aoentry_mod_cin;
GtkWidget *aoentry_mod_id;
GtkWidget *aospinbutton_md_j;
GtkWidget *aospinbutton_md_ms;
GtkWidget *aospinbutton_md_an;
GtkWidget *aoentry_mod_prob;
GtkWidget *aolabel_complete;
GtkWidget *aolabel_error_cin;


aoentry_mod_nom=lookup_widget(button,"aoentry_mod_nom");
aoentry_mod_pnom=lookup_widget(button,"aoentry_mod_pnom");
aoentry_mod_cin=lookup_widget(button,"aoentry_mod_cin");
aoentry_mod_id=lookup_widget(button,"aoentry_mod_id");

aospinbutton_md_j=lookup_widget(button, "aospinbutton_md_j");
aospinbutton_md_ms=lookup_widget(button, "aospinbutton_md_ms");
aospinbutton_md_an=lookup_widget(button, "aospinbutton_md_an");
aoentry_mod_prob=lookup_widget(button,"aoentry_mod_prob");
strcpy(r.nom,gtk_entry_get_text(GTK_ENTRY(aoentry_mod_nom)));
strcpy(r.pnom,gtk_entry_get_text(GTK_ENTRY(aoentry_mod_pnom)));
strcpy(r.cin,gtk_entry_get_text(GTK_ENTRY(aoentry_mod_cin)));
strcpy(r.id,gtk_entry_get_text(GTK_ENTRY(aoentry_mod_id)));
actv(c,ct);
strcpy(r.contact,ct);
actv(E,eq);
strcpy(r.enquette,eq);
j=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aospinbutton_md_j));
m=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aospinbutton_md_ms));
a=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aospinbutton_md_an));
sprintf(dj, "%d",j );
sprintf(dm, "%d",m );
sprintf(da, "%d",a );
strcpy(r.date,dj);
strcat(r.date,"/");
strcat(r.date,dm);
strcat(r.date,"/");
strcat(r.date,da);
objpl(obj1,obj2,objj);
strcpy(r.objet,objj);
strcpy(r.prob,gtk_entry_get_text(GTK_ENTRY(aoentry_mod_prob)));
if ((strlen(r.cin)!=8))
{
aolabel_error_cin= lookup_widget(button, "aolabel_error_cin") ;
gtk_label_set_text(GTK_LABEL(aolabel_error_cin),text_cin);
}
else
if((strlen(r.nom)==0)||(strlen(r.pnom)==0)||(strlen(r.cin)==0)||(strlen(r.id)==0)||(strlen(r.contact)==0)||(strlen(r.enquette)==0)||(strlen(r.date)==0)||(strlen(r.objet)==0)||(strlen(r.prob)==0))
{
aolabel_complete= lookup_widget(button, "aolabel_complete") ;
gtk_label_set_text(GTK_LABEL(aolabel_complete),text);
}
else
{
ajouter_pl(r);

GtkWidget *aowindow_modif;
GtkWidget *B;
aowindow_modif=lookup_widget(button,"aowindow_modif");
gtk_widget_destroy(aowindow_modif);
B=create_aowindow_modif_val();
gtk_widget_show(B);
}
}



void
on_aobutton_service_rec_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *B;
B=create_aowindow_spr();
gtk_widget_show(B);

}

int h=0;
int rr=0;
void
on_aobutton_service_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

char text_h[250]="le service le plus réclamé est Hebergement";
char text_r[250]="le service le plus réclamé est Restauration";

GtkWidget *aolabel_service_rrcc ;    
rec r;
FILE *f=NULL;
f=fopen("reclm.txt","r");

  while (fscanf(f,"%s %s %s %s %s %s %s %s %s \n",r.nom,r.pnom,r.cin,r.id,r.contact,r.enquette,r.date,r.objet,r.prob)!=EOF)
      {
         if ((strlen(r.objet))==13)
         h+=1;
         if ((strlen(r.objet))==14)
         rr+=1;

      }
     fclose(f);

if (h>rr)
{
aolabel_service_rrcc= lookup_widget(button, "aolabel_service_rrcc") ;
gtk_label_set_text(GTK_LABEL(aolabel_service_rrcc),text_h);
}
if (h<rr)
{
aolabel_service_rrcc= lookup_widget(button, "aolabel_service_rrcc") ;
gtk_label_set_text(GTK_LABEL(aolabel_service_rrcc),text_r);
}
}


int fe=0;
int fc=0;
void
on_aocheckb_eo_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
 fe=1;
}


void
on_aocheckb_en_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
 fe=2;

}


void
on_aocheckb_co_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
 fc=1;

}


void
on_aocheckb_cn_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
 fc=2;
}

int fo=0;
void
on_aocheckb_or_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
 fo=1;
}


void
on_aocheckb_oh_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
 fo=2;
}


void
on_aobutton_filtrer_clicked            (GtkButton       *widget,
                                        gpointer         user_data)
{

GtkWidget *aowindow_consult,*wz;
GtkWidget *aotreeview_rec;

wz=lookup_widget(widget,"aowindow_consult");
aowindow_consult=create_aowindow_consult();
gtk_widget_show(aowindow_consult);
gtk_widget_hide(wz);
aotreeview_rec=lookup_widget(aowindow_consult,"aotreeview_rec");

filtrer(fe,fc,fo);
afficher_rec(aotreeview_rec,"filtrer.txt");
remove("filtrer.txt");

}


void
on_aobutton_rei_clicked                (GtkButton       *widget,
                                        gpointer         user_data)
{
GtkWidget* aocheckb_eo;
aocheckb_eo=lookup_widget(widget, "aocheckb_eo");
gtk_toggle_button_set_active(GTK_RADIO_BUTTON(aocheckb_eo),FALSE);  

GtkWidget* aocheckb_en;
aocheckb_en=lookup_widget(widget, "aocheckb_en");
gtk_toggle_button_set_active(GTK_RADIO_BUTTON(aocheckb_en),FALSE);    

GtkWidget* aocheckb_co;
aocheckb_co=lookup_widget(widget, "aocheckb_co");
gtk_toggle_button_set_active(GTK_RADIO_BUTTON(aocheckb_co),FALSE);    

GtkWidget* aocheckb_cn;
aocheckb_cn=lookup_widget(widget, "aocheckb_cn");
gtk_toggle_button_set_active(GTK_RADIO_BUTTON(aocheckb_cn),FALSE);    

GtkWidget* aocheckb_oh;
aocheckb_oh=lookup_widget(widget, "aocheckb_oh");
gtk_toggle_button_set_active(GTK_RADIO_BUTTON(aocheckb_oh),FALSE);    

GtkWidget* aocheckb_or;
aocheckb_or=lookup_widget(widget, "aocheckb_or");
gtk_toggle_button_set_active(GTK_RADIO_BUTTON(aocheckb_or),FALSE);    


GtkWidget *aowindow_consult;
GtkWidget *aotreeview_rec;

aowindow_consult=lookup_widget(widget,"aowindow_consult");
aotreeview_rec=lookup_widget(aowindow_consult,"aotreeview_rec");

afficher_rec(aotreeview_rec,"reclm.txt");


}
