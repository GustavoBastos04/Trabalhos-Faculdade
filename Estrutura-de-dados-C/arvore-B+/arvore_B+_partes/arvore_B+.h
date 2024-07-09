#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILENAME 256
#define MAX_ACTIONS 100

#define PARAMETER 3
#define MAXIMUM_KEYS 2*PARAMETER-1
#define MINIMUM_KEYS PARAMETER-1
#define MAXIMUM_CHILD 2*PARAMETER
#define MINIMUM_CHILD PARAMETER

// Struct to save input file operations 

typedef struct actions
{
    int addKeys[MAX_ACTIONS];
    int removeKeys[MAX_ACTIONS];
    int printInstant[MAX_ACTIONS];
    int end;
    char operation[MAX_ACTIONS];
    int numOfOperations;
} ACTIONS;

typedef int KeyType;

// If leaf node, childNodes[0] points to the adjacent leaf and childNodes[1] to childNodes[MAXIMUM_CHILD] to NULL
typedef struct str_node {
    KeyType keyList[MAXIMUM_KEYS];
    struct str_node* childNodes[MAXIMUM_CHILD];     
    int numOfKeys;
    bool leaf;
} NODE;

typedef struct {
    NODE* root;
} BPLUS_TREE;

// All functions

NODE *newNodeCreation();
void splitChild(NODE *nonFullNode, int i, NODE *fullNode);
bool insertNonFullInternalNode(NODE *currentNode, int keyToInsert);
void BPlusInsertion(BPLUS_TREE *T, int keyToInsert);
NODE *BPlusSearch(NODE *node, int key);
int findKeyIndex(NODE *x, int key);
void removeFromLeafWithInsufficientKeys(NODE *parent, NODE *x, int targetKey);
void removeFromLeafWithEnoughKeys(NODE *x, int targetKey);
void removeFromInternalNode(NODE *x, int targetKey);
void BPlusRemoval(BPLUS_TREE *tree, int keyToRemove);
void showTree(NODE *node, int level);
bool readFile(char *inputFile, ACTIONS *actions);
bool writeFile(char *outputFile, ACTIONS *actions, BPLUS_TREE *tree);