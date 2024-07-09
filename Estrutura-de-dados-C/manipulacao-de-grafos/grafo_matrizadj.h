#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILENAME 256

#define MAXNUMVERTICES 100
#define AN -1
#define VERTICE_INVALIDO -1

typedef int Peso;
typedef struct {
    Peso matriz[MAXNUMVERTICES+1][MAXNUMVERTICES+1];
    int numVertices;
    int numArestas;
} Grafo;
typedef int Apontador;

typedef struct estr {
    int chave;
    struct estr* prox;
} NO;

typedef struct estrutura {
    NO* inicio;
    NO* fim;
} FILA;


// Funções
bool inicializaGrafo(Grafo *grafo, int nv);
int obtemNrVertices(Grafo* grafo);
int obtemNrArestas(Grafo* grafo);
bool verificaValidadeVertice(int vertice, Grafo* grafo);
bool listaAdjVazia(int v, Grafo* grafo);
Apontador proxListaAdj(int v, Grafo* grafo, Apontador atual);
Apontador primeiroListaAdj(int v, Grafo* grafo);
bool existeAresta(int v1, int v2, Grafo* grafo);
Peso obtemPesoAresta(int v1, int v2, Grafo* grafo);
void insereAresta(int v1, int v2, Peso peso, Grafo* grafo);
bool removeAresta(int v1, int v2,Grafo* grafo);
bool removeArestaObtendoPeso(int v1, int v2, Peso* peso, Grafo* grafo);
void imprimeGrafo(Grafo* grafo);
void liberaGrafo(Grafo* grafo);
void leGrafo(char* nomearq, Grafo *grafo);
void inicializarFdinam(FILA* f);
void entrarFdinam(int ch, FILA* f);
int sairFdinam(FILA* f);
void imprimeCaminho(int vertice1, int vertice2, int antecessor[]);
int obtemVerticeDestino(Apontador p, Grafo* grafo);