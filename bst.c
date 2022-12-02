#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct bstNode *bstPointer;

typedef struct data
{
    int priority;
    char *c;
} data;

typedef struct bstNode
{
    data data;
    bstPointer leftChild;
    bstPointer rightChild;
} bstNode;

char *generateRandomString(void)
{
    char *s = (char *)malloc(100);
    for (int i = 0; i < 100; i++)
    {
        s[i] = rand() % 26 + 'a';
    }
    s[99] = '\0';
    return s;
}

data *makeRandomData(void)
{
    data *d = (data *)malloc(sizeof(data));

    d->priority = rand() % 1000;
    d->c = generateRandomString();

    return d;
}

bstPointer makeTreeNode(void)
{
    bstPointer treePointerPointer = (bstPointer)malloc(sizeof(bstNode));

    treePointerPointer->data = *makeRandomData();
    treePointerPointer->leftChild = NULL;
    treePointerPointer->rightChild = NULL;

    return treePointerPointer;
}

int insertNodeToBST(bstPointer *root, bstPointer insertedNode)
{
    if (*root == NULL)
    {
        *root = insertedNode;
    }
    else
    {
        if (insertedNode->data.priority >= (*root)->data.priority)
        {
            insertNodeToBST(&(*root)->rightChild, insertedNode);
        }
        else
        {
            insertNodeToBST(&(*root)->leftChild, insertedNode);
        }
    }
    return insertedNode->data.priority;
}

void popBiggestPriorityFromBST(bstPointer *root)
{
    // 오른 자식이 없으면 루트가 가장 큰거임.
    if ((*root)->rightChild == NULL)
    {
        int result = (*root)->data.priority;
        bstPointer temp = *root;
        *root = (*root)->leftChild;
        // printf("%d ", result);
    }
    // 오른 자식이 있는 경우 그 오른자식을 재귀적으로 계속 타고가서 없앰
    else
    {
        popBiggestPriorityFromBST(&((*root)->rightChild));
    }
}

void bstExecution(int arraySize)
{
    srand(time(NULL));
    double insertTime, popTime, totalTime;

    clock_t start, end;
    bstPointer root = NULL;

    int arraySize;
    scanf("%d", &arraySize);

    // insert
    start = clock();
    ////
    for (int i = 0; i < arraySize; i++)
    {
        insertNodeToBST(&root, makeTreeNode());
        // printf("%d ", insertTreeNode(&root, makeTreeNode()));
    }
    end = clock();

    insertTime = (double)(end - start);
    printf("\nBinary Search Tree - Insert에 소요 시간: %.0lfms", insertTime);

    // pop
    start = clock();
    for (int i = 0; i < arraySize; i++)
    {
        popBiggestPriorityFromBST(&root);
    }
    end = clock();
    popTime = (double)(end - start);
    printf("\nBinary Search Tree - Pop에 소요 시간: %.0lfms", popTime);

    // total
    totalTime = insertTime + popTime;
    printf("\nBinary Search Tree - 전체 소요 시간: %.0lfms", totalTime);
}

int main(void)
{

    return 0;
}
