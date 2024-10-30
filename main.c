#include "graf-L.h"
#include <string.h>
#define c1 "cerinta1"
#define c2 "cerinta2"
int main(int argc, char *argv[])
{
  FILE *fin = fopen("tema3.in", "rt");
  FILE *fout = fopen("tema3.out", "wt");
  char cerinta[10];
  strcpy(cerinta, argv[1]);
  if (strstr(cerinta, "1"))
  {
    TGL *graf = NULL;
    AArc *p, aux;
    char primul_oras[30];
    char al_doilea_oras[30];
    int cost = 0, componente = 0;
    int nr_obiective = 0, nr_drumuri = 0;
    fscanf(fin, "%i", &nr_obiective); //citire noduri
    fscanf(fin, "%i", &nr_drumuri); //citire muchii
    char vector[nr_obiective + 1][50];
    graf = AlocG(nr_obiective);
    if (!graf)
      return 0;
    int contor = 1, contor_curent1 = -1, contor_curent2 = -1;
    int variabila0 = 0, variabila1 = 0;
    while (fscanf(fin, "%s%s%i", primul_oras, al_doilea_oras, &cost) == 3) //citire primului nod, al doilea si costul
    {

      for (int i = 1; i <= contor; i++)
      {
        if (strcmp(primul_oras, vector[i]) == 0) //daca avem primul nod citit  in vector
        {
          variabila0 = 1;
        }
      }

      for (int i = 1; i <= contor; i++)
      {
        if (strcmp(al_doilea_oras, vector[i]) == 0) // daca avem al doilea nod citit in vector
        {
          variabila1 = 1;
        }
      }
      if (variabila0 == 0) //in cazul in care nu il avem adaugam primul oras
      {
        strcpy(vector[contor], primul_oras);
        contor++;
      }

      if (variabila1 == 0) // in cazul in care nu il avem adaugam al doilea oras
      {
        strcpy(vector[contor], al_doilea_oras);
        contor++;
      }

      for (int i = 1; i <= contor; i++)
      {
        if (strstr(vector[i], primul_oras)) //luam contorul din vector pentru primul nod citit
        {
          contor_curent1 = i;
        }
      }
      for (int i = 1; i <= contor; i++)
      {
        if (strstr(vector[i], al_doilea_oras)) //luam contorul din vector pentru al doileaa nod
        {
          contor_curent2 = i;
        }
      }
      //creare lista
      variabila0 = 0;
      variabila1 = 0;
      p = graf->x + contor_curent1; 
      while (*p && (*p)->d < contor_curent2)
        p = &(*p)->urm;
      aux = (TCelArc *)calloc(sizeof(TCelArc), 1);
      if (!aux)
      {
        DistrG(&graf);
        return 0;
      }
      aux->urm = *p;
      *p = aux;
      aux->d = contor_curent2;
      aux->c = cost;

      p = graf->x + contor_curent2;
      while (*p && (*p)->d < contor_curent1)
        p = &(*p)->urm;
      aux = (TCelArc *)calloc(sizeof(TCelArc), 1);
      if (!aux)
      {
        DistrG(&graf);
        return 0;
      }
      aux->urm = *p;
      *p = aux;
      aux->d = contor_curent1;
      aux->c = cost;
    }

    int vizitat[graf->n]; // vectorul de vizitati pe care il folosesc pt a afla nr de comp conexe
    int vector_cost[70];  // vectorul in care pun costul pentru componenetele conexe
    for (int i = 0; i <= graf->n; i++) //initializam vectorul de vizitati cu zero
    {
      vizitat[i] = 0;
    }

    DFS(graf, vizitat, &componente); // calculam numarul de componente conexe
    fprintf(fout, "%d\n", componente); //printez numarul de componente

    int visited[graf->n + 1]; //vectorul de vizitati pe crae il folosesc pentru a afla costul fiecarie componente
    for (int i = 1; i <= graf->n + 1; i++) //initializez vectorul
    {
      visited[i] = 0;
    }
    visited[1] = 1;
    int contor2 = 0;

    CalculeazaCosturiComponenteConexe(graf, vector_cost, componente, contor2);

    for (int i = 0; i < componente - 1; i++) //ordonez elementele crescator din vectr_cost
      for (int j = 0; j < componente - i - 1; j++)
        if (vector_cost[j] > vector_cost[j + 1])
        {
          int aux = vector_cost[j];
          vector_cost[j] = vector_cost[j + 1];
          vector_cost[j + 1] = aux;
        }
    for (int i = 0; i < componente; i++)
    {
      fprintf(fout, "%d\n", vector_cost[i]); //printez costul
    }
    DistrG(&graf);
  }

  // cerinta 2

  if (strstr(cerinta, "2"))
  {
    TGL *graf = NULL;
    AArc *p, aux;
    int nr_noduri = 0, nr_muchi = 0, cost = 0;
    fscanf(fin, "%i", &nr_noduri); //citim nodurile
    fscanf(fin, "%i", &nr_muchi); //citim muchiile
    char vector_noduri[nr_noduri + 1][50];
    char primul_nod[30], al_doilea_nod[30];
    graf = AlocG(nr_noduri);
    if (!graf)
      return 0;
    int poz_cor_vector = 0; // pozitia corabiei in vector;
    int contor = 1, contor_curent1 = -1, contor_curent2 = -1;
    int variabila0 = 0, variabila1 = 0;
    while (fscanf(fin, "%s%s%i", primul_nod, al_doilea_nod, &cost) == 3) //citim primul nod, al doilea, si costul
    {
      for (int i = 1; i <= contor; i++)
      {
        if (strcmp(primul_nod, vector_noduri[i]) == 0) //avem primul nod in vector
        {
          variabila0 = 1;
        }
      }

      for (int i = 1; i <= contor; i++)
      {
        if (strcmp(al_doilea_nod, vector_noduri[i]) == 0) //avem al doilea nod in vector
        {
          variabila1 = 1;
        }
      }
      if (variabila0 == 0) //daca nu avem primul nod in vector
      {
        strcpy(vector_noduri[contor], primul_nod); //punem nodul in vector
        if (strstr(primul_nod, "Corabie"))
        {
          poz_cor_vector = contor; //pozitia corabiei in vector
        }

        contor++;
      }

      if (variabila1 == 0) //daca nu avem al doilea nod in vector
      {
        strcpy(vector_noduri[contor], al_doilea_nod); //punem al doilea nod in vector
        if (strstr(al_doilea_nod, "Corabie"))
        {
          poz_cor_vector = contor; //poz corabiei in vector
        }

        contor++;
      }

     

      for (int i = 1; i <= contor; i++)
      {
        if (strstr(vector_noduri[i], primul_nod)) //contorul din vector  pentru primul oras
        {
          contor_curent1 = i;
        }
      }
      for (int i = 1; i <= contor; i++)
      {
        if (strstr(vector_noduri[i], al_doilea_nod)) //contorul din vector pentru al doilea oras
        {
          contor_curent2 = i;
        }
      }
      //creare graf
      variabila0 = 0;
      variabila1 = 0;
      p = graf->x + contor_curent1;
      while (*p && (*p)->d < contor_curent2)
        p = &(*p)->urm;
      aux = (TCelArc *)calloc(sizeof(TCelArc), 1);
      if (!aux)
      {
        DistrG(&graf);
        return 0;
      }
      aux->urm = *p;
      *p = aux;
      aux->d = contor_curent2;
      aux->c = cost;
    }
    AfiGrafL(graf);
    int adancime = 0;
    char nume_nod[30];
    strcpy(nume_nod, "");
    int contor1 = 1;

    char vector_noduri_adancimi[nr_noduri + 1][50]; // vectorul in care pun numele fiecarui nod in ordine
    int vector_adancimi[100];                       // vector in care pun adancimea fiecarui nod
    strcpy(vector_noduri_adancimi[0], "Insula"); //punem pe prima poz din vectorul de adancimi Insula
    vector_adancimi[0] = 1; //adancimea insulei este egala cu 1
    while (fscanf(fin, "%s%i", nume_nod, &adancime) == 2) //citim nodul care este urmat de cost
    {

      vector_adancimi[contor1] = adancime; //punem adancimea in vector 
      strcpy(vector_noduri_adancimi[contor1], nume_nod); //punem nodul in vectorul de noduri pt Adancimi

      contor1++;
    }

    int greutate_comoara = 0;          // greutatea comorii
    greutate_comoara = atoi(nume_nod); // pentru ca ultima valoare citita se pune in nume-nod

    int vec_viz_corabie_insula[graf->n]; // vector in care verificam daca avem drum corabie insula
    for (int i = 1; i <= graf->n; i++)
    {
      vec_viz_corabie_insula[i] = 0;
    }

    int drum1 = 1000; //cazul in care nu avem drum de la insula la corabie
    drum1 = DFSt_gasire_drum_Corabie_Insula(graf, 1, poz_cor_vector, vec_viz_corabie_insula);
    if (drum1 == 0)
    {
      fprintf(fout, "Echipajul nu poate transporta comoara inapoi la corabie");
      return 0;
    }
    for (int i = 1; i <= graf->n; i++)
    {
      vec_viz_corabie_insula[i] = 0;
    }

    int drum = 0;
    //cazul in care nu avem drum de corabie la insula
    drum = DFSt_gasire_drum_Corabie_Insula(graf, poz_cor_vector, 1, vec_viz_corabie_insula);

    if (drum == 0)
    {
      fprintf(fout, "Echipajul nu poate ajunge la insula");
      return 0;
    }

    int adanicme_min;
    int minim = 10000;
     //prelucrare si printare informati
    adanicme_min = Dijkstra_alg(graf, minim, 1, poz_cor_vector, nr_noduri, vector_noduri, vector_noduri_adancimi, vector_adancimi, fout);
    float nr_drumuri;
    nr_drumuri = greutate_comoara / adanicme_min;
    fprintf(fout, "%0.f", nr_drumuri);
    DistrG(&graf);
  }
  return 0;
}
