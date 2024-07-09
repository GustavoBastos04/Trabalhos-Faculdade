
#ifdef MATRIZ
#include "grafo_matrizadj.h"
#else
#include "grafo_listaadj.h"
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#define MAX_FILENAME 256

/* OBS: 0 = branco; 1 = cinza; 2 = preto */

/*
==============================
    Busca em Profundidade
==============================
*/

void visitaBP(int vertice, Grafo* g, int* tempo, int* cor, int* tdesc, int* tterm, int* antecessor,int* exploraBP, bool* verticeArticulacao, int prof){
    
    printf("%d ", vertice);

    cor[vertice] = 1;
    tdesc[vertice] = ++(*tempo);

    int filhos = 0;

    //if(!listaAdjVazia(vertice, g))
    //{

        Apontador ap = primeiroListaAdj(vertice, g);

        while(ap != VERTICE_INVALIDO)
        {
        
            int v = obtemVerticeDestino(ap, g);
            
            if(cor[v] == 0)
            {
                filhos++;

                antecessor[v] = vertice;
                
                visitaBP(v, g, tempo, cor, tdesc,tterm, antecessor, exploraBP, verticeArticulacao, prof + 1);

                if(exploraBP[vertice] > exploraBP[v])
                {
                    exploraBP[vertice] = exploraBP[v];
                }
                if(antecessor[vertice] == -1 && filhos > 1)  
                {
                    verticeArticulacao[vertice] = true;
                }

                if(antecessor[vertice] != -1 && (exploraBP[v] >= tdesc[vertice])) 
                {
                    verticeArticulacao[vertice] = true;
                }

                if(antecessor[vertice] != -1 && exploraBP[v] > exploraBP[vertice])
                {
                    verticeArticulacao[vertice] = true;
                }
            }
            else
            {
                if (v != antecessor[vertice])
                {
                    if(exploraBP[vertice] > tdesc[v])
                    {
                        exploraBP[vertice] = tdesc[v];
                    }
                }
            }
            
           ap = proxListaAdj(vertice, g, ap);
        }

        tterm[vertice] = ++(*tempo);
        cor[vertice] = 2;
    //}
}

void buscaProfundidade(Grafo* g, bool* verticeArticulacao){
    
    int tdesc[g->numVertices], tterm[g->numVertices], antecessor[g->numVertices], cor[g->numVertices], exploraBP[g->numVertices];

    int tempo = 0;

    for (int i = 0; i < g->numVertices; i++)
    {
        cor[i] = 0;
        tdesc[i] = 0;
        tterm[i] = 0;
        antecessor[i] = -1;
        exploraBP[i] = i;
        verticeArticulacao[i] = false;
    }
    
    printf("BP:\n");
    for (int j = 0; j < g->numVertices; j++)
    {
        if(cor[j] == 0)
        {
            visitaBP(j,g,&tempo,cor,tdesc,tterm,antecessor, exploraBP, verticeArticulacao, 0);
        }
    }

    printf("\n\n");

    printf("Caminhos BP:");

    int origem = 0;

    for (int x = 0; x < g->numVertices; x++) 
    {  
        imprimeCaminho(origem, x, antecessor);
    }

    printf("\n\n");
    
}

/*
==============================
    Componentes Conectados
==============================
*/
void atribuiVerticeComponenteConectado(int vertice, Grafo* g, int quantidadeComponentes, int* componentesConectados){
    
    componentesConectados[vertice] = quantidadeComponentes;

    Apontador q = primeiroListaAdj(vertice, g);

    while (q != VERTICE_INVALIDO)
    {
        int w = obtemVerticeDestino(q, g);

        if (componentesConectados[w] == 0)
        {
            atribuiVerticeComponenteConectado(w, g, quantidadeComponentes, componentesConectados);
        }

        q = proxListaAdj(vertice, g, q);   
    }
    
}

void componentesConectados(Grafo* g){
    int componenteConectado[g->numVertices];

    for (int i = 0; i < g->numVertices; i++)
    {
        componenteConectado[i] = 0;
    }

    int quantidadeComponentes = 0;

    for (int j = 0; j < g->numVertices; j++)
    {
        if (componenteConectado[j] == 0)
        {
            quantidadeComponentes++;
            atribuiVerticeComponenteConectado(j, g, quantidadeComponentes, componenteConectado);
        }
        
    }
    
    printf("Componentes Conectados: \n");
    
    for (int x = 0; x < quantidadeComponentes; x++)
    {
        printf("C%d: ", (x+1));

        for (int y = 0; y < g->numVertices; y++)
        {
            if(componenteConectado[y] == (x+1))
            {
                printf("%d ", y);
            }
        }
        
        printf("\n");
    }

    printf("\n");
}

/*
==============================
    Busca em Largura
==============================
*/
void imprimeBL(int vertice1, int vertice2, int* antecessor, int* distancia){
    if(vertice1 == vertice2)
    {
        printf("%d ", vertice2);
        return;
    }
    if(distancia[vertice2] == 0) return;

    imprimeBL(vertice1, antecessor[vertice2], antecessor, distancia);
    printf("%d ", vertice2);

}


void visitaLargura(int vertice, Grafo* g, int* cor, int *antecessor, int* distancia){

    cor[vertice] = 1;
    distancia[vertice] = 0;
    FILA F;

    inicializarFdinam(&F);
    entrarFdinam(vertice, &F);

    while (F.inicio != NULL)
    {
        int w = sairFdinam(&F);

        printf("%d ", w);

        Apontador q = primeiroListaAdj(w, g);

        while (q != VERTICE_INVALIDO)
        {
            int v = obtemVerticeDestino(q, g);
            if (cor[v] == 0)
            {
                cor[v] = 1;
                antecessor[v] = w;
                distancia[v] = distancia[w] + 1;
                entrarFdinam(v, &F);
            }
            
            q = proxListaAdj(w, g, q);
        }

        cor[w] = 2;
    }
}

void buscaLargura(Grafo* g){
    int cor[g->numVertices], antecessor[g->numVertices], distancia[g->numVertices];

    for(int i = 0; i < g->numVertices; i++)
    {
        cor[i] = 0;
        antecessor[i] = -1;
        distancia[i] = INT_MAX;
    }

    printf("BL:\n");
    for(int j = 0; j< g->numVertices; j++)
    {
        if(cor[j] == 0) visitaLargura(j, g , cor, antecessor, distancia);
    }   

    printf("\n\n");
    printf("Caminhos BL:\n");

    int origem = 0;

    for (int x = 0; x < g->numVertices; x++)
    {   
        if(distancia[x] == 0)
        {
            origem = x;
        } 
        imprimeBL(origem, x, antecessor, distancia);
        
        printf("\n");
    }    

    printf("\n");
}

/*
==============================
    Vértices de Articulação
==============================
*/

void imprimeVerticesArticulacao(Grafo* g, bool* verticeArticulacao)
{
    printf("Vertices de articulacao:\n");
    for (int i = 0; i < g->numVertices; i++)
    {
        if(verticeArticulacao[i] == true) printf("%d ", i);
    }
    printf("\n");
}


/*
==============================
    Leitura de Grafo
==============================
*/
void leGrafo(char* nomearq, Grafo *grafo){
    FILE *fp;
    int v1, v2;
    Peso peso;
    int numVertices, numArestas;

    fp = fopen(nomearq, "r");
    if(fp==NULL) {
        fprintf(stderr, "ERRO: impossível detectar o arquivo. Verifique se o mesmo existe.\n");
        return ;
    }

    if(fscanf(fp, "%d %d", &numVertices, &numArestas) != 2) {
        fprintf(stderr, "ERRO: leitura de numero de vertices e/ou de arestas incorreta.\n");   
        return ;
    }

    inicializaGrafo(grafo, numVertices);
    
    for (int i = 0; i < numArestas; i++)
    {
            fscanf(fp, "\n%d %d %d\n", &v1, &v2, &peso);
            insereAresta(v1, v2, peso, grafo);
    }

    fclose(fp);
}
/*
==============================
    Arquivo de Saída
==============================
*/
void saidaGrafo(char* nomearq, Grafo* grafo){
    FILE *fp;

    fp = fopen(nomearq, "w");

    if (fp == NULL)
    {
        fprintf(stderr, "Erro com arquivo de saída\n");
        return;
    }
    int fd = fileno(fp), copy = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);


    bool verticeArticulacao[grafo->numVertices];
    
    buscaLargura(grafo);

    buscaProfundidade(grafo, verticeArticulacao);

    componentesConectados(grafo);

    imprimeVerticesArticulacao(grafo, verticeArticulacao);

    fflush(stdout);   
    fclose(fp);
    dup2(copy,STDOUT_FILENO);
}

int main(int argc, char* argv[]){
    
    if (argc != 3) 
    {
        printf("Este programa exige dois argumentos.\n"); 
        exit(1);
    }
    
    Grafo grafo;

    char inputFile[MAX_FILENAME];
    strcpy(inputFile, argv[1]);

    char outputFile[MAX_FILENAME];
    strcpy(outputFile, argv[2]);

    leGrafo(inputFile, &grafo);
    
    saidaGrafo(outputFile, &grafo);
}