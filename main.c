#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define Max(x, y) (((x) > (y)) ? (x) : (y))

typedef struct Node {
    int source;
    struct Node* lf;
    struct Node* rt;
} MyTreeNode;

MyTreeNode* insNode(MyTreeNode* bin, int source)
{
    MyTreeNode* current = bin;
    MyTreeNode* parent = bin;
    MyTreeNode* newNode = (MyTreeNode*)malloc(sizeof(MyTreeNode));
    if (newNode == NULL)
        return NULL;
    newNode->source = source;
    newNode->lf = NULL;
    newNode->rt = NULL;
    if (bin == NULL) {
        bin = newNode;
        return bin;
    }
    while (current->source != source) {
        parent = current;
        if (current->source >= source) {
            current = current->lf;
            if (current == NULL) {
                parent->lf = newNode;
                return bin;
            }
        }
        else {
            current = current->rt;
            if (current == NULL) {
                parent->rt = newNode;
                return bin;
            }
        }
    }
    return bin;
}

int treeGrow(MyTreeNode* bin)
{
    if (bin == NULL)
        return 0;

    int lfGrow = treeGrow(bin->lf);
    int rtGrow = treeGrow(bin->rt);
    int currGrow = Max(lfGrow, rtGrow) + 1;

    return currGrow;
}

int balTree(MyTreeNode* bin)
{
    if (bin == NULL)
        return 1;

    int lfGrow = treeGrow(bin->lf);
    int rtGrow = treeGrow(bin->rt);

    int growTreeDiffer = abs(lfGrow - rtGrow);
    if (growTreeDiffer > 1)
        return 0;

    return balTree(bin->lf) && balTree(bin->rt);
}

void prinTree(MyTreeNode* bin)
{
    if (bin != NULL) {
        printf("%d", bin->source);
    }
    else {
        printf("NULL");
        return;
    }
    if (bin->lf != NULL || bin->rt != NULL) {
        printf("(");
        prinTree(bin->lf);
        printf(",");
        prinTree(bin->rt);
        printf(")");
    }
}

void freeTree(MyTreeNode* bin)
{
    if (bin == NULL)
        return;
    if (bin->lf != NULL) {
        freeTree(bin->lf);
    }
    if (bin->rt != NULL) {
        freeTree(bin->rt);
    }
    free(bin);
}

int main()
{
    const int TREES = 50;
    const int NODES = 10000;
    MyTreeNode* tree[TREES];
    int balTrees = 0;

    srand((unsigned)time(NULL));

    for (int i = 0; i < TREES; i++) {
        tree[i] = NULL;
        tree[i] = insNode(tree[i], rand());
        for (int j = 0; j < NODES; j++) {
            insNode(tree[i], rand());
        }
        balTrees += balTree(tree[i]);
        freeTree(tree[i]);
    }
    prinTree(tree);
    printf("% Trees are balanced\n", (float)balTrees / TREES * 100);

    return 0;
}
