/*--- graf-L.h --- Graf reprezentat cu liste --*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


#ifndef _GRAF_L_
#define _GRAF_L_

typedef struct celarc 
{ int d;           /* destinatie arc */
  int c;            /* cost arc */
  struct celarc *urm; /* adresa urmatorul adiacent */
} TCelArc, *AArc;

typedef struct 
{ int n;     /* numar noduri */
  AArc* x;    /* vector adrese liste arce */
} TGL;
TGL* AlocG(int nr);
int Dijkstra_alg(TGL* g, int minim, int insula, int poz_corabie, int nr_noduri, char vector_noduri[nr_noduri + 1][50],char vector_noduri_adancimi[nr_noduri + 1][50],int  vector_adancimi[100], FILE *fout);
int DFSt_gasire_drum_Corabie_Insula (TGL *g, int corabie, int insula, int vizitat[]);
int Prim(TGL* g, int* visited);
void DFS (TGL *g, int vizitat[], int *componente);
void DFS1 (TGL *g, int vizitat[], int i);
void AfiGrafL(TGL *); /* afisare liste de adiacente */
void DistrG(TGL** ag);
void CalculeazaCosturiComponenteConexe(TGL* g, int vector_cost[], int  componente, int contor);
#endif
