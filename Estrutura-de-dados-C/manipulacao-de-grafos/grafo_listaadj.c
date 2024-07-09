#include "grafo_listaadj.h"

bool inicializaGrafo(Grafo *grafo, int nv){

    if (grafo == NULL){ 
        fprintf(stderr, "ERRO na chamada de inicializaGrafo: grafo == NULL. \n");
        return false;
    }

    if(nv <= 0) {
        fprintf(stderr, "ERRO na chamada de inicializaGrafo: Numero de vertices deve ser positivo. \n");
        return false;
    }

    grafo->numVertices = nv;
    if(!(grafo->listaAdj = (Apontador*) calloc(nv, sizeof(Apontador)))){
        fprintf(stderr, "ERRO: falha na alocacao de memoria na funcao inicializaGrafo.\n");
        return false;
    }
    grafo->numArestas = 0;
    // calloc já inicializa com zeros... nao precisa inicializar grafo->listaAdj[i]
    return true;
}

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

/* Verificação se a lista de adjacência de um vértice v é vazia */
bool listaAdjVazia(int v, Grafo* grafo){
    if(!verificaValidadeVertice(v, grafo)) return false;
    return (grafo->listaAdj[v] == NULL);
    }

/* Retorna o proximo vertice adjacente a v, partindo do vertice "atual" adjacente a v*/
Apontador proxListaAdj(int v, Grafo* grafo, Apontador atual){
    if(atual == NULL){
        fprintf(stderr, "atual == NULL\n");
        return VERTICE_INVALIDO;
    }
    return atual->prox;
}

/* Endereco do primeiro vertice adjacente a v */
Apontador primeiroListaAdj(int v, Grafo* grafo){

    return grafo->listaAdj[v];
} 

bool existeAresta(int v1, int v2, Grafo* grafo){
    Apontador q;

    if( !(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo))){ 
        fprintf(stderr, "ERRO: um dos vertices nao e valido;");
        return false;
    }
    q = grafo->listaAdj[v1];
    while ( (q != NULL) && (q->vdest != v2)) q = q->prox;
    
    if(q != NULL) return true;
    return false;
}

int obtemNrVertices(Grafo* grafo){
    return grafo->numVertices;
}

int obtemNrArestas(Grafo* grafo){
    return grafo->numArestas;
}

/* Retorna o peso da aresta (v1, v2) se ela existir e AN caso contrário */
Peso obtemPesoAresta(int v1, int v2, Grafo* grafo){
    if( !(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2,grafo))) return AN;

    Apontador q = grafo->listaAdj[v1];
    while ( (q!=NULL) && (q->vdest != v2)) q = q->prox;

    if(q != NULL) return q->peso;
    return AN;
}

void insereAresta(int v1, int v2, Peso peso, Grafo* grafo){
    Apontador p;
    Apontador q;

    if(!(verificaValidadeVertice(v1,grafo) && verificaValidadeVertice(v2, grafo))){
        fprintf(stderr, "ERRO: um dos vertices nao e valido.\n");
        return;
    }
    if(!(p = (Apontador) calloc(1, sizeof(Aresta))) || !(q = (Apontador) calloc(1,sizeof(Aresta)))){
        fprintf(stderr, "ERRO: Falha na alocacao de memoria na funcao insereAresta\n");
        return;
    }

    p->vdest = v2;
    p->peso = peso;

    
    p->prox = grafo->listaAdj[v1]; /* Insere no início! */
    grafo->listaAdj[v1] = p;
    grafo->numArestas++;
    

    if (v1 != v2)
    {
        q->vdest = v1;
        q->peso = peso;

        q->prox = grafo->listaAdj[v2]; /* Insere no início! */
        grafo->listaAdj[v2] = q;
        grafo->numArestas++;

    }
}

bool removeAresta(int v1, int v2, Grafo* grafo){
    Apontador q, p, ant, ant2;

    if(!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo))) return false;

    q = grafo->listaAdj[v1];
    p = grafo->listaAdj[v2];

    while ((q != NULL) && (q->vdest != v2))
    {
        ant = q;
        q = q->prox;
    }
    
    while ((p != NULL) && (p->vdest != v2))
    {
        ant2 = p;
        p = p->prox;
    }

    // aresta existe 
    if (q != NULL && p != NULL)
    {
        if (grafo->listaAdj[v1] == q) grafo->listaAdj[v1] = q->prox;
        else ant->prox = q->prox;
        q->prox = NULL;
        free(q);
        q = NULL;

        if (grafo->listaAdj[v2] == p) grafo->listaAdj[v2] = p->prox;
        else ant2->prox = p->prox;
        p->prox = NULL;
        free(p);
        p = NULL;
        return true;
    }
    // aresta não existe
    return false;
}

bool removeArestaObtendoPeso(int v1, int v2, Peso* peso, Grafo* grafo){
    Apontador q, ant;

    if(!(verificaValidadeVertice(v1,grafo) && verificaValidadeVertice(v2, grafo))) return false;
    
    q = grafo->listaAdj[v1];
    while ((q != NULL) && (q->vdest != v2)){
        ant = q;
        q = q->prox;
    }

    // aresta existe
    if (q != NULL){
        if (grafo->listaAdj[v1] == q)
            grafo->listaAdj[v1] = q->prox;
        else ant->prox = q->prox;
        *peso = q->peso;
        q->prox = NULL;
        free(q);
        q = NULL;
        return true;
    }
    // aresta não existe
    return false;
}

int obtemVerticeDestino(Apontador p, Grafo* grafo){
    if(p) return p->vdest;
    else return -1;
}

void imprimeGrafo(Grafo* grafo){
    Apontador q;
    for (int i = 0; i < grafo->numVertices; i++)
    {
        q = grafo->listaAdj[i];
        printf("%d: ", i);
        
        while (q!=NULL)
        {
            printf("(%d, %d); ", q->vdest, q->peso);
            q = q->prox;
        }
        printf("\n");
        
    }
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

// Caminho mais curto de busca em largura
void imprimeCaminho(int vertice1, int vertice2, int antecessor[]){
    /*
    if (vertice1 == vertice2)
    {    
        printf("%d ", vertice1);
        return;
    }
    */
    if(vertice2 == -1){
        printf("\n");
        return;
    } 
        
    imprimeCaminho(vertice1, antecessor[vertice2], antecessor);
    
    printf("%d ", vertice2);
}


