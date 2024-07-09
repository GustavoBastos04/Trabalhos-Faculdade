#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILENAME 256

#define VERTICE_INVALIDO NULL
#define AN -1
#define MAXNUMVERTICES 100

typedef int Peso;

typedef struct str_aresta {
    int vdest;
    Peso peso;
    struct str_aresta* prox;
} Aresta;

typedef Aresta* Apontador;

typedef struct {
    Apontador* listaAdj;
    int numVertices;
    int numArestas;
} Grafo;

typedef struct estr {
    int chave;
    struct estr* prox;
} NO;

typedef struct estrutura {
    NO* inicio;
    NO* fim;
} FILA;

/* Funções */
bool inicializaGrafo(Grafo *grafo, int nv);
void liberaGrafo(Grafo* grafo);
int obtemNrVertices(Grafo* grafo);
int obtemNrArestas(Grafo* grafo);
bool verificaValidadeVertice(int vertice, Grafo* grafo);
bool listaAdjVazia(int v, Grafo* grafo);
Apontador proxListaAdj(int v, Grafo* grafo, Apontador atual);
Apontador primeiroListaAdj(int v, Grafo* grafo);
bool existeAresta(int v1, int v2, Grafo* grafo);
bool removeArestaObtendoPeso(int v1, int v2, Peso* peso, Grafo* grafo);
Peso obtemPesoAresta(int v1, int v2, Grafo* grafo);
void insereAresta(int v1, int v2, Peso peso, Grafo* grafo);
bool removeAresta(int v1, int v2,Grafo* grafo);
void imprimeGrafo(Grafo* grafo);
void leGrafo(char* nomearq, Grafo *grafo);
void inicializarFdinam(FILA* f);
void entrarFdinam(int ch, FILA* f);
int sairFdinam(FILA* f);
void imprimeCaminho(int vertice1, int vertice2, int antecessor[]);
int obtemVerticeDestino(Apontador p, Grafo* grafo);