#include "grafo_matrizadj.h"

/*
    inicializaGrafo(Grafo* grafo, int nv); inicializa um grafo com nv vértices.
    Vértices vão de 1 a nv.
    Preenche as células com AN (representando ausência de arestas)
    Retorna true se inicializou com sucesso e false caso contrário.
*/

bool verificaValidadeVertice(int vertice, Grafo* grafo){
    if((vertice >= grafo->numVertices)){
        fprintf(stderr, "Numero do vertice %d maior ou igual que o numero total de vertices %d.\n", vertice, grafo->numVertices);
        return false;
    } 
    if(vertice < 0) {
        fprintf(stderr, "Numero de vertices nao pode ser negativo, como %d.\n", vertice);
        return false;
    }
    else return true;
}

bool inicializaGrafo(Grafo* grafo, int nv){
    int i, j;
    if(nv > MAXNUMVERTICES){
        fprintf(stderr, "ERRO na chamada de inicializaGrafo: Numero de vertices maior que o máximo permitido de %d.\n", MAXNUMVERTICES);
        return false;
    }
    if(nv <= 0){
        fprintf(stderr, "ERRO na chamada de inicializaGrafo: Numero de vertices deve ser positivo.\n");
    }
    grafo->numVertices = nv;
    grafo->numArestas = 0;
    for(i = 0; i<grafo->numVertices; i++){
        for(j = 0; j<grafo->numVertices; j++)
            grafo->matriz[i][j] = AN;
    }
    return true;
}

bool listaAdjVazia(int v, Grafo* grafo){
    if(!verificaValidadeVertice(v, grafo)) return true;

    int i;
    for (i=0; i<grafo->numVertices; i++){
        if( grafo->matriz[v][i] != AN) return false;
    }
    return true;
}


Apontador proxListaAdj(int v, Grafo* grafo, int atual){
    if(!verificaValidadeVertice(v, grafo) || !verificaValidadeVertice(atual, grafo)) return VERTICE_INVALIDO;
    
    for (int i = (atual+1); i < grafo->numVertices; i++)
    {
            if(grafo->matriz[v][i] != AN)
            {
                return i;
            }
    }
    return VERTICE_INVALIDO;
}


Apontador primeiroListaAdj(int v, Grafo* grafo){

    if (!(verificaValidadeVertice(v, grafo))) 
    {
        return VERTICE_INVALIDO;
    }

    for (int i = 0; i < grafo->numVertices; i++) 
    {
        if (grafo->matriz[v][i] != AN) 
        {
            return i;
        }
    }
    return VERTICE_INVALIDO;
}

void imprimeGrafo(Grafo* grafo){
    int i, j;
    for (i = 0; i < grafo->numVertices+1; i++)
    {   
        for (j = 0; j < grafo->numVertices; j++)
        {
            if(i == 0)
            {
                if(j == 0) printf("     %d | ", j);
                else printf(" %d | ", j);
            }
            else
            {
                if(grafo->matriz[i-1][j] == -1) printf("%d | ", grafo->matriz[i-1][j]);
                else printf(" %d | ", grafo->matriz[i-1][j]);
            };
        }
        printf("\n");
        if(i != grafo->numVertices) printf("%d | ", i);
    }
    printf("\n");   
}


int obtemVerticeDestino(Apontador p, Grafo* grafo){
    return p;
}

bool existeAresta(int v1, int v2, Grafo* grafo){
    if(!(verificaValidadeVertice(v1, grafo)) || !(verificaValidadeVertice(v2, grafo))) {
        fprintf(stderr, "Vértices inválidos.\n");
        return false;
    }
    if(grafo->matriz[v1][v2] == AN || grafo->matriz[v2][v1] == AN) return false;
    return true;
}

void insereAresta(int v1, int v2, Peso peso ,Grafo* grafo){
    if( existeAresta(v1, v2, grafo) || !verificaValidadeVertice(v1, grafo) || !verificaValidadeVertice(v2, grafo)) return ;
    grafo->matriz[v1][v2] = peso;
    grafo->matriz[v2][v1] = peso;
    grafo->numArestas++;
    
}

Peso obtemPesoAresta(int v1, int v2, Grafo* grafo){
    if( !verificaValidadeVertice(v1, grafo) || !verificaValidadeVertice(v2, grafo)){ 
        fprintf(stderr, "Vértices não são válidos, retornando -1...\n");
        return -1;
    }
    return grafo->matriz[v1][v2];
}

bool removeAresta(int v1, int v2, Grafo* grafo){
    if( !verificaValidadeVertice(v1, grafo) || !verificaValidadeVertice(v2, grafo)) return false;

    /* Se aresta existe */
    if(grafo->matriz[v1][v2] != AN) {
        grafo->matriz[v1][v2] = AN;
        grafo->numArestas--;
        return true;
    }

    /* Aresta não existe */
    return false;
}


/* Além de remover a aresta, retorna em (Peso* peso)*/
bool removeArestaObtendoPeso(int v1, int v2, Peso* peso, Grafo* grafo){
    if( !verificaValidadeVertice(v1, grafo) || !verificaValidadeVertice(v2, grafo)) return false;

    /* Se aresta existe */
    if(grafo->matriz[v1][v2] != AN) {
        *peso = grafo->matriz[v1][v2];
        grafo->matriz[v1][v2] = AN;
        grafo->matriz[v2][v1] = AN;
        grafo->numArestas--;
        return true;
    }

    /* Aresta não existe */
    return false;
}

/* Não precisa fazer nada para liberar matrizes de adjacencia */
void liberaGrafo(Grafo* grafo){}

// Caminho mais curto de busca em largura
void imprimeCaminho(int vertice1, int vertice2, int antecessor[]){
    
    /*
    if (vertice1 == vertice2)
    {    
        printf("%d ", vertice1);
        return;
    }
    */
    if(vertice2 == -1) 
    {
        printf("\n");
        return;
    }
        
    imprimeCaminho(vertice1, antecessor[vertice2], antecessor);
    
    printf("%d ", vertice2);
}


// Inicialização da fila dinamica
void inicializarFdinam(FILA* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// inserir item ao final da fila dinamica
void entrarFdinam(int ch, FILA* f) {
    NO* novo;
    novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->prox = NULL;
    if(f->fim) f->fim->prox = novo; // fila não é vazia
    else f->inicio = novo; // 1a. inserção em fila vazia
    f->fim = novo;
}

// retirar a chave da frente ou -1
int sairFdinam(FILA* f){
    NO* aux;
    int ch;
    
    if(!f->inicio) return(-1);
    
    ch = f->inicio->chave;
    aux = f->inicio;
    f->inicio = f->inicio->prox;
    free(aux);
    
    if(!f->inicio) f->fim = NULL; // fila ficou vazia
    
    return(ch);
}

int obtemNrVertices(Grafo* grafo){
    return grafo->numVertices;
}
int obtemNrArestas(Grafo* grafo){
    return grafo->numArestas;
}


/* OBS: NESSA FUNÇÃO OS PESOS SÃO LIDOS EM INT. MUDAR A ESTRUTURA EM CASO DE IMPLEMENTAÇÃO */
