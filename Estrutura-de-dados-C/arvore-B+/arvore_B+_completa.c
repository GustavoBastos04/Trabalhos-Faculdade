/*
==============================================================================================================
Nome: Gustavo Bastos de Souza
Número USP: 14576642
==============================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_FILENAME 256
#define MAX_KEYS 100

#define PARAMETER 3
#define MAXIMUM_KEYS 2 * PARAMETER - 1
#define MINIMUM_KEYS PARAMETER - 1
#define MAXIMUM_CHILD 2 * PARAMETER
#define MINIMUM_CHILD PARAMETER

typedef struct actions {
    int addKeys[MAX_KEYS];
    int removeKeys[MAX_KEYS];
    int printInstant[MAX_KEYS];
    int end;
    char operation[MAX_KEYS];
    int numOfOperations;
} ACTIONS;

typedef int KeyType;

// OBS: Trata o caso em que, se é folha, childNodes[MAXIMUM_CHILD] aponta para o próximo e o resto NULL
typedef struct str_node
{
    KeyType keyList[MAXIMUM_KEYS];
    struct str_node *childNodes[MAXIMUM_CHILD];
    int numOfKeys;
    bool leaf;
} NODE;

typedef struct
{
    NODE *root;
} BPLUS_TREE;

NODE *newNodeCreation()
{

    NODE *newNode = (NODE *)malloc(sizeof(NODE));

    newNode->leaf = true;

    newNode->numOfKeys = 0;

    for (int i = 0; i < MAXIMUM_CHILD; i++)
    {
        newNode->childNodes[i] = NULL;
    }

    return newNode;
}

/*
=============================================================================================================
    Insertion Area
=============================================================================================================
*/

void splitChild(NODE *nonFullNode, int i, NODE *fullNode)
{

    NODE *newNode = newNodeCreation();
    newNode->leaf = fullNode->leaf;

    if (newNode->leaf == true)
    {
        newNode->numOfKeys = MINIMUM_KEYS + 1;

        for (int l = 0; l < MINIMUM_KEYS + 1; l++)
        {
            newNode->keyList[l] = fullNode->keyList[l + MINIMUM_KEYS];
        }

        fullNode->childNodes[MAXIMUM_CHILD] = newNode;
    }
    else
    {
        newNode->numOfKeys = MINIMUM_KEYS;

        for (int j = 0; j < MINIMUM_KEYS; j++)
        {
            newNode->keyList[j] = fullNode->keyList[j + MINIMUM_KEYS + 1];
        }

        for (int k = 0; k < MINIMUM_CHILD; k++)
        {
            newNode->childNodes[k] = fullNode->childNodes[k + MINIMUM_CHILD];
            fullNode->childNodes[k + MINIMUM_CHILD] = NULL;
        }
    }

    fullNode->numOfKeys = MINIMUM_KEYS;

    for (int l = nonFullNode->numOfKeys; l >= i; l--)
    {
        nonFullNode->childNodes[l + 1] = nonFullNode->childNodes[l];
        nonFullNode->keyList[l] = nonFullNode->keyList[l - 1];
    }

    nonFullNode->childNodes[i] = newNode;
    nonFullNode->keyList[i - 1] = fullNode->keyList[MINIMUM_KEYS];
    nonFullNode->numOfKeys += 1;
}

bool insertNonFullInternalNode(NODE *currentNode, int keyToInsert)
{

    int i = currentNode->numOfKeys - 1;

    if (currentNode->leaf == true)
    {
        while (i >= 0 && currentNode->keyList[i] > keyToInsert)
        {
            currentNode->keyList[i + 1] = currentNode->keyList[i];
            i--;
        }
        currentNode->keyList[i + 1] = keyToInsert;
        currentNode->numOfKeys++;
    }
    else
    {
        while (i >= 0 && currentNode->keyList[i] > keyToInsert)
            i--;

        i++;
        if (currentNode->childNodes[i]->numOfKeys == MAXIMUM_KEYS)
        {
            splitChild(currentNode, i + 1, currentNode->childNodes[i]);
            if (currentNode->keyList[i] < keyToInsert)
                i++;
        }
        insertNonFullInternalNode(currentNode->childNodes[i], keyToInsert);
    }
}

void BPlusInsertion(BPLUS_TREE *T, int keyToInsert)
{

    if (T->root->numOfKeys == MAXIMUM_KEYS)
    {

        NODE *newNode = newNodeCreation();
        newNode->leaf = false;

        newNode->childNodes[0] = T->root;
        splitChild(newNode, 1, T->root);
        insertNonFullInternalNode(newNode, keyToInsert);
        T->root = newNode;
    }
    else
        insertNonFullInternalNode(T->root, keyToInsert);
}

/*
=============================================================================================================
    Delete Area
=============================================================================================================
*/

NODE *BPlusSearch(NODE *node, int key)
{
    if (node == NULL)
        return NULL;

    int index = 0;

    while ((index < node->numOfKeys) && (key > node->keyList[index]))
        index++;

    if ((index < node->numOfKeys) && (key == node->keyList[index]))
        return node;

    return BPlusSearch(node->childNodes[index], key);
}

// Given "key" is inside "NODE x"
int findKeyIndex(NODE *x, int key)
{

    for (int i = 0; i < x->numOfKeys; i++)
    {
        if (x->keyList[i] == key)
            return i;
    }
}
void removeFromLeafWithInsufficientKeys(NODE *parent, NODE *x, int targetKey)
{

    int XIndex = 0;
    while (parent->childNodes[XIndex] != x)
    {
        if (parent->childNodes[XIndex] == x)
            break;

        XIndex++;
    }
    // 3a case
    if (parent->childNodes[XIndex - 1] && (parent->childNodes[XIndex - 1]->numOfKeys > MINIMUM_KEYS))
    {

        int keyIdx = findKeyIndex(x, targetKey);

        for (int i = keyIdx; i > 0; i--)
        {
            x->keyList[i] = x->keyList[i - 1];
        }

        parent->keyList[XIndex - 1] = parent->childNodes[XIndex - 1]->keyList[parent->childNodes[XIndex - 1]->numOfKeys - 1];
        x->keyList[0] = parent->keyList[XIndex - 1];
        parent->childNodes[XIndex - 1]->numOfKeys -= 1;
    }
    else
    {
        // 3a case ptII Note: this conditional has to be tested
        if (parent->childNodes[XIndex + 1] && parent->childNodes[XIndex + 1]->numOfKeys > MINIMUM_KEYS)
        {
            int keyIdx = findKeyIndex(x, targetKey);

            for (int i = keyIdx; i < x->numOfKeys - 1; i++)
            {
                x->keyList[i] = x->keyList[i + 1];
            }

            x->keyList[x->numOfKeys - 1] = parent->keyList[XIndex]; // first parent key

            parent->keyList[XIndex] = parent->childNodes[XIndex + 1]->keyList[1]; // B+ Tree properties

            for (int i = 0; i < parent->childNodes[XIndex + 1]->numOfKeys - 1; i++)
            {
                parent->childNodes[XIndex + 1]->keyList[i] = parent->childNodes[XIndex + 1]->keyList[i + 1];
            }
            parent->childNodes[XIndex + 1]->numOfKeys -= 1;
        }
        // 3b case (preference for the left)
        else
        {
            int keyIdx = findKeyIndex(x, targetKey);
            // Left Brother
            if (parent->childNodes[XIndex - 1])
            {

                for (int i = 0; i < x->numOfKeys; i++)
                {
                    if (x->keyList[i] != targetKey)
                    {
                        parent->childNodes[XIndex - 1]->keyList[parent->childNodes[XIndex - 1]->numOfKeys] = x->keyList[i];
                        parent->childNodes[XIndex - 1]->numOfKeys += 1;
                    }
                }

                for (int i = XIndex - 1; i < parent->numOfKeys; i++)
                {
                    parent->keyList[i] = parent->keyList[i + 1];
                }

                parent->numOfKeys -= 1;

                while (parent->childNodes[XIndex + 1] != NULL)
                {

                    parent->childNodes[XIndex] = parent->childNodes[XIndex + 1];
                    XIndex += 1;
                }
                NODE *aux = parent->childNodes[XIndex + 1];
                parent->childNodes[XIndex + 1] = NULL;
                free(aux);
                free(x);
            }
        }
    }
}

void removeFromLeafWithEnoughKeys(NODE *x, int targetKey)
{
    for (int i = 0; i < x->numOfKeys; i++)
    {
        if (x->keyList[i] == targetKey)
        {
            for (int j = i; j < x->numOfKeys - 1; j++)
            {
                x->keyList[j] = x->keyList[j + 1];
            }
            x->keyList[x->numOfKeys - 1] = 0;
            x->numOfKeys -= 1;
            return;
        }
    }
}

// 2 case
void removeFromInternalNode(NODE *x, int targetKey)
{

    int keyIdx = findKeyIndex(x, targetKey);

    // 2B case
    if (x->childNodes[keyIdx + 1]->numOfKeys > MINIMUM_KEYS)
    {
        x->keyList[keyIdx] = x->childNodes[keyIdx + 1]->keyList[1];

        for (int i = 0; i < x->childNodes[keyIdx + 1]->numOfKeys - 1; i++)
        {
            x->childNodes[keyIdx + 1]->keyList[i] = x->childNodes[keyIdx + 1]->keyList[i + 1];
        }
        x->childNodes[keyIdx + 1]->numOfKeys -= 1;
    }
    else
    {
        // 2A case
        if (x->childNodes[keyIdx]->numOfKeys > MINIMUM_KEYS)
        {
            x->keyList[keyIdx] = x->childNodes[keyIdx]->keyList[x->childNodes[keyIdx]->numOfKeys - 1];
            x->childNodes[keyIdx + 1]->keyList[0] = x->keyList[keyIdx];
            x->childNodes[keyIdx]->numOfKeys -= 1;
        }
        // 2C case
        else
        {
            for (int i = 1; i < x->childNodes[keyIdx + 1]->numOfKeys; i++)
            {
                x->childNodes[keyIdx]->keyList[x->childNodes[keyIdx]->numOfKeys] = x->childNodes[keyIdx + 1]->keyList[i];

                x->childNodes[keyIdx]->numOfKeys += 1;
            }

            for (int i = keyIdx; i < x->numOfKeys - 1; i++)
            {
                x->keyList[i] = x->keyList[i + 1];
            }
            x->numOfKeys -= 1;

            while (x->childNodes[keyIdx + 2] != NULL)
            {
                x->childNodes[keyIdx + 1] = x->childNodes[keyIdx + 2];
                keyIdx += 1;
            }
            free(x->childNodes[keyIdx + 2]);
        }
    }
}

void BPlusRemoval(BPLUS_TREE *tree, int keyToRemove)
{

    NODE *x = BPlusSearch(tree->root, keyToRemove);

    if (x != NULL)
    {

        if (x->childNodes[0])
        {
            removeFromInternalNode(x, keyToRemove);
        }
        else
        {

            if (x->numOfKeys > MINIMUM_KEYS)
            {
                removeFromLeafWithEnoughKeys(x, keyToRemove);
            }

            else
            {

                NODE *XParent = BPlusSearch(tree->root, x->keyList[0]);

                removeFromLeafWithInsufficientKeys(XParent, x, keyToRemove);

                // Busca o índice de x como filho de XParent
            }
        }
    }
}

/*
=============================================================================================================
    Print Area
=============================================================================================================
*/
void showTree(NODE *node, int level)
{
    int i;

    if (node != NULL)
    {
        if (node->numOfKeys == 0)
        {
            printf("Vazia");
            return;
        }

        int i;
        printf("(");

        for (i = 0; i < node->numOfKeys; i++)
        {

            showTree(node->childNodes[i], level + 1);
            if (node->childNodes[0])
                printf(" ");
            else if (i != 0)
                printf(" ");
                
            printf("%d", node->keyList[i]);

            if (node->childNodes[0])
                printf(" ");
        }
        showTree(node->childNodes[i], level + 1);
        printf(")");
    }
}

/*
=============================================================================================================
    I/O files
=============================================================================================================
*/
bool readFile(char* inputFile, ACTIONS* actions){
    char act;
    int key, i = 0, r = 0, p = 0, x = 0;

    FILE* fp = fopen(inputFile, "r");

    if(!fp) {
        fprintf(stderr, "Can't read file\n");
        return false;
    }  

    
    while (!feof(fp)){

        fscanf(fp, "%c %d\n", &act, &key);
        switch (act)
        {
        case 'i':
            actions->addKeys[i] = key;
            i++;
            actions->operation[x] = 'i';
            actions->numOfOperations++;
            break;

        case 'r':
            actions->removeKeys[r] = key;
            r++;
            actions->operation[x] = 'r';
            actions->numOfOperations++;
            break;

        case 'p':
            actions->printInstant[p] = x;
            p++;
            actions->operation[x] = 'p';
            actions->numOfOperations++;
            break;
        case 'f':
            actions->end = x;
            actions->operation[x] = 'x';
            actions->numOfOperations += 1;
            break;
        default:
            break;
        }
        x++;
    }

    fclose(fp);
    
    return true;

}

bool writeFile(char* outputFile, ACTIONS* actions, BPLUS_TREE* tree){
    int i = 0, r = 0, p = 0, x = 0;
    FILE* fp = fopen(outputFile, "w");
    
    if (fp == NULL)
    {
        fprintf(stderr, "Erro com arquivo de saída\n");
        return false;
    }
    int fd = fileno(fp), copy = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);


    for (int a = 0; a < actions->numOfOperations; a++)
    {   
        switch (actions->operation[a])
        {
        case 'i':
            BPlusInsertion(tree, actions->addKeys[i]);
            i++;
            break;
        
        case 'p':
            showTree(tree->root, 0);
            printf("\n");
            p++;
            break;
        
        case 'r':
            BPlusRemoval(tree, actions->removeKeys[r]);
            r++;
            break;

        case 'f':
            return true;
            break;

        default:
            break;
        }
    }
    

    fflush(stdout);
    fclose(fp);
    dup2(copy, STDOUT_FILENO);
}

/*
=============================================================================================================
    Main
=============================================================================================================
*/

int main(int argc, char* argv[]){

    if(argc != 3){
        printf("Program requires two arguments\n");
        exit(1);
    }

    char inputFile[MAX_FILENAME];
    strcpy(inputFile, argv[1]);

    char outputFile[MAX_FILENAME];
    strcpy(outputFile, argv[2]);

    ACTIONS fileActions;
    
    readFile(inputFile, &fileActions);

    BPLUS_TREE *tree = (BPLUS_TREE *)malloc(sizeof(BPLUS_TREE));
    tree->root = newNodeCreation();

    writeFile(outputFile, &fileActions, tree);

}