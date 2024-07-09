#include "arvore_B+.h"

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