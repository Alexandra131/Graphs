/*--- graf-L.c --- Graf implementat cu liste --*/
#include "graf-L.h"

TGL* AlocG(int nr) /* aloca spatiu pentru descriptor graf si
	                      vector de (n+1) adrese liste arce */
{
  TGL* g = (TGL*)malloc(sizeof(TGL));    /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (AArc*)calloc((nr+1), sizeof(AArc)); /* spatiu vector adr.liste arce */
  if(!g->x) { free(g); return NULL; }
  g->n = nr;
  return g;
}

void DistrG(TGL** ag)
{ 
  int i;
  AArc p, aux;
  for(i = 1; i <= (*ag)->n; i++){ 
    p = (*ag)->x[i];
    while(p)
    { aux = p; p = p->urm;
      free(aux);
    }
  }
  free((*ag)->x);
  free(*ag);
  *ag = NULL;
}



void AfiGrafL(TGL * g)
{
  AArc l;
  int i;

  for(i = 1; i <= g->n; i++){
    l = g->x[i];
    if(!l)
      printf("%d: - \n", i);
    else
      printf("%d: ", i);
    for(; l != NULL; l = l->urm)
      printf(" %d (%d)", l->d, l->c);
    printf("\n");
  }
}


void DFS1 (TGL *g, int vizitat[], int i){
  
  vizitat[i] = 1; //macram nodul in care mergem ca vizitat 
  AArc copie_graf = g->x[i];
  while (copie_graf != NULL) { //pentru nodul respectv incercam sa gsim vecinii
    int j = copie_graf->d;
    if (vizitat[j] == 0) // daca vecinul nu a fost vizitat
      DFS1(g, vizitat, j); //apelam funtia recursiv
    copie_graf = copie_graf->urm; // avansam la urmatorul varf din lsita
  }       
}     

void DFS (TGL *g, int vizitat[], int *componente) { //aflam componentele conexe 
  for (int i = 0; i <g->n; i++) //parcurg pentru fiecare nod in graf
  if(vizitat[i] == 0) { //in cazul in care nu am nodul respectiv vizitat
    DFS1(g, vizitat,i); //parcurg in adancime componenta ce contine nodul i
    (*componente)++;
  }
  *componente = *componente  - 1;
}


int Prim(TGL* g, int* visited) {
    int primul_oras = 0, al_doilea_oras = 0, cost_minim = 0;
    int minim = 0;
    
    for (int i = 1; i < g->n; i++) {
        minim = 10000;

        
        for (int j = 1; j <= g->n; j++) { //parcurg toate nodurile
            if (visited[j]) { //daca intalnesc un nod vizitat
                AArc p = g->x[j];
                while(p) {
                    //daca gasesc un cost mai mic decat minimul si un nod nevizitat
                    if (minim > p->c && visited[p->d] == 0) {
                       //actualizez nodurile si minimul
                        primul_oras = j;
                        al_doilea_oras = p->d;
                        minim = p->c;
                    }
                    p = p->urm;
                }
            }
        }

        
        if (minim != 10000) {
            cost_minim = cost_minim + minim; //calculez costul
            visited[primul_oras] = 1; //marcam  ca vizitate ambele noduri
            visited[al_doilea_oras] = 1;}
        
    }

    return cost_minim; //returam costul minim
}


void CalculeazaCosturiComponenteConexe(TGL* g, int vector_cost[], int  componente, int contor)
{
    int  visited[g->n +1];  // Vector pentru a marca nodurile vizitate
    for (int i = 0; i <= g->n+1; i++) {
      visited[i] = 0;
    }
    int primul_oras = 0, al_doilea_oras = 0, cost_minim = 0;
    for (int i = 1; i <= g->n; i++)
    {
        if (!visited[i])
        {
            // Resetăm valorile la fiecare componentă conexă
            for (int j = 1; j <= g->n; j++)
            {
                visited[j] = 0;
            }

            visited[i] = 1;  // Marchăm nodul inițial ca vizitat
            int cost = Prim(g, visited); //calculez costul
            vector_cost[contor] = cost; //punem costul in vectorul de costuri
            contor++;
           
        }
    }
}


//task2


int DFSt_gasire_drum_Corabie_Insula (TGL *g, int corabie, int insula, int vizitat[]) {
 
  if(corabie == insula) {
    return 1;// avem drum de la corabie la insula
  }
  vizitat[corabie] = 1; //punem pe nodul pe care il vizitam 1
  AArc copie = g->x[corabie];
 
  while (copie) {
    int destinatie = copie->d; //destinatia in care putem merge (nodurile vecine)
    if (!vizitat[destinatie]) {
      if(DFSt_gasire_drum_Corabie_Insula(g, destinatie, insula,vizitat)) {
     
        return 1; //avem nod in care sa trecem
      }
    }
    copie = copie->urm;
  }

  return 0; //nu avem drum de la corabie la insula
}


int drumul_minim( int distanta[], int vect_noduri_fol[], int nr_noduri) { //calculeaza costul pentru distanta minima
  int minim = 10000, contor = 0;
  for (int i = 1; i < nr_noduri; i++) {
    if (vect_noduri_fol[i] == 0 && distanta[i] <= minim) {
      minim = distanta[i]; //salvez valoarea minima
      contor = i; //salvez contorul pentru costul minim
    }
  }
  return contor;
}






int Dijkstra_alg(TGL* g, int minim, int insula, int poz_corabie, int nr_noduri, char vector_noduri[nr_noduri + 1][50],char vector_noduri_adancimi[nr_noduri + 1][50],int  vector_adancimi[100], FILE *fout) {
    char vector_noduri_vizitate[nr_noduri + 1][50]; // vectorul in care punem nodurile pe care le parcurgem
    int dist[nr_noduri + 1], contor_distanta_minima;
    int vec_adancimi_fol[100]; //vectorul in care am adancimile elementelor pe care le folosesc
    for (int i = 0; i < 100; i++) {
      vec_adancimi_fol[i] = 0;
    }
    int dist_minim[nr_noduri + 1]; //vectorul meu in care merchez nodurile in care am fost
    int contor = 1, adancime_min = 0, adancime = 0;
    int cel_mai_bun_drum[nr_noduri + 1]; //punem de fiecare data contorul pesntur cel mai bun drum
    for (int i = 1; i <= nr_noduri; i++) {
        dist[i] = 10000;
        dist_minim[i] = 0;
    }
    dist[insula] = 0;  // distanta de la un nod la el insusi e zero

    for (int j = 1; j <= nr_noduri; j++) {
        contor_distanta_minima = drumul_minim(dist, dist_minim, nr_noduri); //luam valoarea indexului care are costul cel mai mic
        dist_minim[contor_distanta_minima] = 1; //marcam nodul ca vizitat
        AArc copie = g->x[contor_distanta_minima];
        for (; copie != NULL; copie = copie->urm) { //parcurgem pana cand nu mai avem vecini
            int distanta1 = copie->d;
            int cost = copie->c;
            if (!dist_minim[distanta1] && dist[distanta1] > dist[contor_distanta_minima] + cost) {
                dist[distanta1] = dist[contor_distanta_minima] + cost;
                cel_mai_bun_drum[distanta1] = contor_distanta_minima; // punem contorul pentru cel mai scurt drum 
            }
        }
    }
     int contor1 = 1;
    int nod_curent = poz_corabie;
    int numar_noduri_drum = 0;
    while (nod_curent != insula) { //cat timp nu am ajuns la corabie
      char vector[nr_noduri + 1][50];
      strcpy(vector[contor], vector_noduri[nod_curent]); //pun intr-un vector nodurile pe care le.am vizitat
   
        for (int j = 2; j <= nr_noduri-1; j++) {
        if (strstr(vector[contor],vector_noduri_adancimi[j])){ //vreau sa gasesc indexul pentru vectorul_noduri_adan pentru care am aceeasi valoare 
       
        adancime = vector_adancimi[j];
        vec_adancimi_fol[contor1] = adancime;// vectorul in care am adancimile vectorului prin care am trcut
        contor1++;//contorul creste
        }
      } 


      strcpy(vector_noduri_vizitate[contor], vector_noduri[nod_curent]);//pun in vectorul de noduri vizitate nodurile prin care am trecut
      contor++; //contorul creste
      nod_curent = cel_mai_bun_drum[nod_curent]; //luam contorul pentru cel mai bun drum
        
    }
     
    
  for(int i = 0; i< contor1-1; i++) { //ordonez vecotorul de adancimi crescator
    for(int j = 0; j < contor1-i-1; j++ ) {
      if (vec_adancimi_fol[j] > vec_adancimi_fol[j+1]) {
        int aux = vec_adancimi_fol[j];
        vec_adancimi_fol[j] = vec_adancimi_fol[j+1];
        vec_adancimi_fol[j+1] = vec_adancimi_fol[j];
      }
    }
  }

   fprintf(fout,"%s ", vector_noduri[insula]); //afisam insula
   for (int i = contor-1; i >=1; i--){
    fprintf(fout,"%s ", vector_noduri_vizitate[i]); //urmata de nodurile prin care trecem
   }
   fprintf(fout, "\n");
       fprintf(fout,"%d\n", dist[poz_corabie]); //printam costul
  fprintf(fout,"%d\n", vec_adancimi_fol[1]); //adancimea minima
  return vec_adancimi_fol[1];
  
   
}


 