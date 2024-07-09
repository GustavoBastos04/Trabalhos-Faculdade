#include "arvore_B+.h"

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