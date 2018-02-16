/*
Pelin Radu-Cristian
Grupa: 314 AB
Tema 1 - Criptare

Pentru verificare: nume fisier baza: baza.txt;
                   nume fisier mesaj1: mesaj 1.txt;
                   nume fisier mesaj2: mesaj 2.txt;
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct baza
{
    int valoare;                                                //structura: lista pentru baza de numeratie;
    struct baza *urmatorul;
}BAZA;

typedef struct mesaj
{
    int valoare;                                                //structura: sitva pentru codurile mesajelor si rezultatul final;
    struct mesaj *anteriorul;
}MESAJ;

typedef struct cuvant
{
    char cuv[30];                                               //structura: lista pentru cuvintele din mesaje si baze;
    struct cuvant *urmatorul;
}CUVANT;

void citire_fisier(FILE **f, char nume[30])                     //functia ce permite deschiderea unui fisier dupa nume;
{
    char *fisier;

    fisier=(char*)malloc(sizeof(char)*10);                      //se aloca dinamic spatiu pentru numele fisierului;

    if(fisier==NULL)
      {
         printf("1.Nu se poate aloca memorie dinamic");         //se verifica daca exista spatiu de alocare;
         exit(1);
      }

    printf("Dati numele fisierului ce contine %s:", nume);
    fflush(stdin);
    gets(fisier);

    if((*f=fopen(fisier,"rt"))==NULL)
    {
        printf("Nu se poate deschide fisierul %s !", fisier);   //se deschide fisierul si se verifica daca aceasta exista pe disc;
        exit(1);
    }

    free(fisier);                                               //se elibereaza memoria alocata dinamic;
}

void creare_baza(FILE **f, BAZA **cap_baza, int *nr_elemente)   //functie ce creaza baza de numeratie criptata sub forma
{                                                               //de lista preluand informatii din fisierul baza.txt;

    BAZA *nod_1, *nod_i;
    int i;

    fscanf(*f,"%d", nr_elemente);                               //se citesc cate elemente sunt in baza;

    nod_1=(BAZA*)malloc(sizeof(BAZA));                          //se aloca dinamic spatiu pentru un element al listei;

    if(nod_1==NULL)
      {
         printf("2.Nu se poate aloca memorie dinamic");         //se verifica daca exista spatiu de alocare;
         exit(1);
      }

    nod_1->valoare=0;
                                                                //se da valoarea primului element;
    nod_1->urmatorul=NULL;

    *cap_baza=nod_1;                                            //capul listei devine primul element;

    for(i=1; i<*nr_elemente; i++)
      {
         nod_i=(BAZA*)malloc(sizeof(BAZA));                     //se aloca dinamic spatiu pentru urmatorul element al listei;
         if(nod_i==NULL)                                        //pana la nr_elemente-2;
           {
             printf("3.Nu se poate aloca memorie dinamic");     //se verifica daca exista spatiu de alocare;
             exit(1);
           }
         nod_i->valoare=i;                                      //se dau valoarea pentru urmatorul element al listei;
         nod_i->urmatorul=NULL;                                 //pana la nr_elemente-2;
         nod_1->urmatorul=nod_i;
         nod_1=nod_i;                                           //se fac legaturile in lista;
      }
}

void creare_mesaj(int i, MESAJ **varf)                         //functie ce creaza stiva mesaj cu informatia criptata;
  {                                                            //adaugand element cu element;
     MESAJ *nod=NULL;

     nod=(MESAJ*)malloc(sizeof(MESAJ));                        //se aloca dinamic spatiu pentru un element al stivei;

     if(nod==NULL)
       {
         printf("4.Nu se poate aloca memorie dinamic");        //se verifica daca exista spatiu de alocare;
         exit(1);
       }

     nod->valoare=i;                                           //se da valoarea pentru elementul adaugat in stiva;

     nod->anteriorul=*varf;                                    //se fac legaturile in stiva;

     *varf=nod;                                                //varful stivei devine ultimul element citit;
   }

int mesaj_text(FILE **f, CUVANT **cap)                         //functie ce creaza listele de cuvinte din cele 3 fisiere;
{                                                              //folosite ulterior pentru compararea cu baza si crearea;
                                                               //stivelor mesaj;
    CUVANT *nod_1, *nod_i;
    int i=1;
    char cuvant[30];

    fscanf(*f,"%s",cuvant);                                    //se citeste primul cuvant din fisier;

    nod_1=(CUVANT*)malloc(sizeof(CUVANT));                     //se aloca dinamic spatiu pentru un element al listei;

    if(nod_1==NULL)
       {
         printf("5.Nu se poate aloca memorie dinamic");
         exit(1);
       }

    strcpy(nod_1->cuv,cuvant);
                                                              //se da valoarea primului element din lista;
    nod_1->urmatorul=NULL;

    *cap=nod_1;                                               //capul listei devine primul element;

    while(!feof(*f))
      {
        fscanf(*f,"%s",cuvant);                               //se citeste urmatorul cuvant din fisier;
        nod_i=(CUVANT*)malloc(sizeof(CUVANT));                //se aloca dinamic spatiu pentru urmatorul elemente ale listei;
        if(nod_i==NULL)
          {
            printf("6.Nu se poate aloca memorie dinamic");    //se verifica daca exista spatiu de alocare;
            exit(1);
          }
        strcpy(nod_i->cuv,cuvant);
        nod_1->urmatorul=NULL;                                //se da valoarea urmatorului element din lista;
        nod_i->urmatorul=NULL;
        nod_1->urmatorul=nod_i;                               //se fac legaturile in lista;
        nod_1=nod_i;
        i++;                                                  //creste numarul de elemente la fiecare citire;
      }

    fclose(*f);                                               //inchide definit fisierul;

return i-1;                                                   //returneaza numarul de elemente citite;
}

void eliberare_lista(CUVANT **cap)                            //functie ce elibereaza spatiu alocat dinamic;
{
    CUVANT *aux, *copiator;

    for(aux=*cap; aux!=NULL; aux=copiator)
       {
            copiator=aux->urmatorul;                          //se elibereaza memoria element cu element si se schimba legaturile;
            free(aux);
       }
}

void mesaje(FILE **f, FILE *g, FILE *h, MESAJ **varf_1, MESAJ **varf_2, CUVANT **cap)//functie ce creaza mesajele 1 si 2 criptate;
  {                                                                                  //sub forma de stive preluand informatii din;
       CUVANT *cap1=NULL, *cap2=NULL, *aux_1=NULL, *aux_2=NULL;                      //fisierele baza.txt, mesaj1.txt si mesaj2.txt;
       int n,m,l,i,j;

       m=mesaj_text(&*f,&*cap);
                                                              //se preia numarul de cuvinte din fiecare fisier si se creaza;
       n=mesaj_text(&g,&cap1);
                                                              //listele de cuvinte corespunzatoare fiecarui fisier;
       l=mesaj_text(&h,&cap2);

       for(aux_1=cap1, i=0; i<n; aux_1=aux_1->urmatorul, i++) //se parcurge lista mesajului 1 si lista bazei;
         for(aux_2=*cap, j=0; j<m; aux_2=aux_2->urmatorul, j++)
           if(strcmp(aux_2->cuv,aux_1->cuv)==0)               //se verifica carei pozitii ii corespund in baza cuvantul;
              creare_mesaj(j,&(*varf_1));                     // se adauga pozitia in stiva cu mesajul 1 codificat;

       for(aux_1=cap2, i=0; i<l; aux_1=aux_1->urmatorul, i++) //analog;
           for(aux_2=*cap, j=0; j<m; aux_2=aux_2->urmatorul, j++)                                                                     //analog;
             if(strcmp(aux_1->cuv,aux_2->cuv)==0)
                creare_mesaj(j,&(*varf_2));


       eliberare_lista(&cap1);
                                                              //se elibereaza memoria inutila;
       eliberare_lista(&cap2);
}

int citire_element(MESAJ **varf)                             //functie ce citeste din mesaju intial si rezultatul final criptat;
{                                                            // element cu element;
       int i;
       MESAJ *aux=NULL;
                                                             //se preia un element din stiva;
       i=(*varf)->valoare;
                                                             //se schimba legaturile;
       aux=(*varf)->anteriorul;
                                                             //se elibereaza memoria pentru elementul preluat;
       free(*varf);
                                                             //varful stivei devine elementul anterior din stiva;
       *varf=aux;
                                                             //returneaza elementul sters;
       return i;
}

int stergere_baza(BAZA **cap, int contor, int *nr_elemente)  //functia ce sterge din baza un element de pe o pozitie data;
{                                                            //si returneaza valoarea elementului de pe pozitie;
 int val_ret, i;
 BAZA *aux, *copiator;
 if(contor==0)
      {
        val_ret=(*cap)->valoare;
        copiator=(*cap)->urmatorul;                           //<-1.daca elementul de sters este capul listei;
        free(*cap);
        *cap=copiator;
      }
  else
    for(aux=*cap, i=0; aux!=NULL; aux=aux->urmatorul, i++)    //se parcurge baza pana se ajunge cu o pozitie in in fata
          if(i+1==contor)                                     //elementului dorit;
        {
         val_ret=aux->urmatorul->valoare;
         copiator=aux->urmatorul;
         aux->urmatorul=copiator->urmatorul;                  //<-2.daca elementul de sters este oricare alt element;
         free(copiator);
        }

     *nr_elemente=*nr_elemente-1;                             //numarul de elementele ale bazei scade cu o unitate;

      return val_ret;                                         //returneaza valoarea stearsa din lista;
}

void creare_fisier(FILE **f, MESAJ **varf, CUVANT **cap)
{
    char *fisier;
    CUVANT *aux=NULL;
    int i, x;

    fisier=(char*)malloc(sizeof(char)*15);                   //se aloca dinamic spatiu pentru numele fisierului;

    if(fisier==NULL)
      {
         printf("7.Nu se poate aloca memorie dinamic");      //se verifica daca exista spatiu de alocare;
         exit(1);
      }

    printf("Dati numele fisierului ce contine rezultatul:");

    fflush(stdin);

    gets(fisier);

    if((*f=fopen(fisier,"wt"))==NULL)
    {
        printf("Nu se poate deschide fisierul %s !", fisier); //se deschide fisierul si se verifica daca aceasta exista pe disc;
        exit(1);
    }

    while(*varf)
     {
        x=citire_element(&*varf);                             //se citeste element cu element din stiva rezultat
        for(aux=*cap, i=0; aux!=NULL; aux=aux->urmatorul, i++)
           if(i==x) fprintf(*f,"%s ",aux->cuv);               //daca elementul corespunde pozitiei din lista de cuvinte;
     }                                                        //acesta se scrie in fisierul rezultat.txt;

        free(fisier);

        eliberare_lista(&*cap);                               //se elibereaza memoria pentru lista de cuvinte a bazei;

        fclose(*f);                                           //inchide definitiv fisierul;
}

MESAJ* rezultat(CUVANT **cap_text)                            //functia ce returneaza varful stivei rezultat;
{
     int i, nr, aux_1, mesaj_1, mesaj_2, transport=0, suma, ok1=0, ok2=0;
     BAZA *aux, *copiator, *cap_baza=NULL;
     FILE *f, *g, *h;
     MESAJ *vf_msg_1=NULL, *vf_msg_2=NULL, *vf_rez=NULL;;

     citire_fisier(&f,"baza");                                //se citeste din fisierul baza.txt

     citire_fisier(&g,"primul mesaj");                        //se citeste din fisierul mesaj 1.txt

     citire_fisier(&h,"al doilea mesaj");                     //se citeste din fisierul mesaj 2.txt

     creare_baza(&f,&cap_baza,&aux_1);                        //se creaza baza de numeratie;

     mesaje(&f,g,h,&vf_msg_1,&vf_msg_2,&*cap_text);           //se creaza stivele mesajelor;

     while(vf_msg_1 || vf_msg_2)                              //cat timp una din stive are elemente:
     {
        if(!vf_msg_1) mesaj_1=0;
         else mesaj_1=citire_element(&vf_msg_1);              //<-1. daca se ajunge la capatul uneia dintre stive valoarea se;
        if(!vf_msg_2) mesaj_2=0;                              //se va egala cu zero, altfel valoare va fi cea citita din stiva;
         else mesaj_2=citire_element(&vf_msg_2);
        while(ok1==0 && ok2==0)
        {
            for(aux=cap_baza; aux!=NULL; aux=aux->urmatorul)
            {
            if(mesaj_1==aux->valoare) ok1=1;                  //<-2. daca valoare citita din stiva nu se mai gaseste in baza se;
                                                              //incrementeaza cu cate un element pana de gaseste in baza;
            if(mesaj_2==aux->valoare) ok2=1;
            }
            if(ok1==0) mesaj_1++;
            if(ok2==0) mesaj_2++;
            }
        for(aux=cap_baza, i=0; aux!=NULL; aux=aux->urmatorul, i++)
            if(aux->valoare==mesaj_1) mesaj_1=i;
            else                                             //<-3. se atribuie fiecarei valori, pozitia din baza de numeratie;
            if(aux->valoare==mesaj_2) mesaj_2=i;
        suma=(transport+mesaj_1+mesaj_2)%aux_1;              //<-4. se face suma intre pozitii si se preia restul impartirii
                                                             //sumei la numarul de elemente din baza;
        transport=1;                                         //<-5.transportul devine 1;

        creare_mesaj(stergere_baza(&cap_baza,suma,&aux_1),&vf_rez); //<-6 se elimina din baza restul preluat la 4 si se adauga;
      }                                                             //la stiva rezultat;

     creare_mesaj(stergere_baza(&cap_baza,transport,&aux_1),&vf_rez);//<-7. la final se adauga in stiva rezultat si valoarea de pe
                                                                     //pozitia transportului;
     for(aux=cap_baza; aux!=NULL; aux=copiator)
        {
            copiator=aux->urmatorul;                          //se elibereaza memoria element cu element din baza de numeratie
            free(aux);                                        //si se schimba legaturile;

        }

     return vf_rez;                                           //returneaza varful stivei rezultat;
}

int main(void)
{
    CUVANT *cap_text=NULL;
    MESAJ *rez=NULL;
    FILE *f;
    rez=rezultat(&cap_text);
    creare_fisier(&f,&rez,&cap_text);
}
