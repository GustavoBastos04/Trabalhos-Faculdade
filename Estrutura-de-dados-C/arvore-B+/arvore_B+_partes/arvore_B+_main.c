#include "arvore_B+.h"

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