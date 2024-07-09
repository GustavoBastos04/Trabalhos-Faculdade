#include "arvore_B+.h"

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