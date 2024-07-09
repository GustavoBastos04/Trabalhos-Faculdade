#include "arvore_B+.h"

bool readFile(char *inputFile, ACTIONS *actions)
{
    char act;
    int key, i = 0, r = 0, p = 0, x = 0;

    FILE *fp = fopen(inputFile, "r");

    if (!fp)
    {
        fprintf(stderr, "Can't read file\n");
        return false;
    }

    while (!feof(fp))
    {

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

bool writeFile(char *outputFile, ACTIONS *actions, BPLUS_TREE *tree)
{
    int i = 0, r = 0, p = 0, x = 0;
    FILE *fp = fopen(outputFile, "w");

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
