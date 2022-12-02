#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 10000000
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct bstNode *bstPointer;

typedef struct data
{
    int priority;
    char *c;
} data;

typedef struct linkedNode
{
    data *data;
    struct linkedNode *next;
} linkedNode;

typedef struct bstNode
{
    data data;
    bstPointer leftChild;
    bstPointer rightChild;
} bstNode;

data maxHeap[MAX_ELEMENTS];

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
    data *n = malloc(sizeof(data));
    n->priority = rand() % 1000000;
    n->c = generateRandomString();
    return n;
}

data **makeArray(int arraySize)
{
    data **array = (data **)malloc(sizeof(data *) * arraySize);
    return array;
}

void pushNodeToArray(data **array, int arraySize)
{
    array[0] = makeRandomData();
    for (int i = 1; i < arraySize; i++)
    {
        array[i] = makeRandomData();
        for (int j = 0; j < i; j++)
        {
            if (array[i]->priority > array[j]->priority)
            {
                data *temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

void popBiggestPriorityFromArray(data **array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        array[i] = NULL;
    }
}

void arrayExecution(int arraySize)
{
    srand(time(NULL));
    double insertTime, popTime, totalTime;
    clock_t start, end;

    data **array = makeArray(arraySize);
    start = clock();
    pushNodeToArray(array, arraySize);
    end = clock();

    insertTime = (double)(end - start);
    printf("\nArray - Insert에 소요 시간: %.0lfms", insertTime);
    start = clock();
    popBiggestPriorityFromArray(array, arraySize);
    end = clock();
    popTime = (double)(end - start);
    printf("\nArray - Pop에 소요 시간: %.0lfms", popTime);
    totalTime = insertTime + popTime;
    printf("\nArray - 전체 소요 시간!: %.0lfms", totalTime);
}

linkedNode *makeLinkedNode(void)
{
    linkedNode *linkedNodePointer = (linkedNode *)malloc(sizeof(linkedNode));

    linkedNodePointer->data = makeRandomData();
    linkedNodePointer->next = NULL;

    return linkedNodePointer;
}

void pushNodeToLinkedList(linkedNode **headPointer)
{
    linkedNode *newNode = makeLinkedNode();
    linkedNode *temp = *headPointer;

    if (*headPointer == NULL)
    {
        *headPointer = newNode;
    }
    else
    {
        *headPointer = newNode;
        newNode->next = temp;
    }
}

void popBiggestPriorityFromLinkedList(linkedNode **headPointer)
{
    linkedNode *temp = *headPointer;
    linkedNode *temp2 = *headPointer;
    linkedNode *tempMax = *headPointer;

    if (*headPointer == NULL)
    {
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->data->priority > tempMax->data->priority)
            {
                tempMax = temp;
            }
            temp = temp->next;
        }
        if (tempMax == *headPointer)
        {
            *headPointer = (*headPointer)->next;
        }
        else
        {
            while (temp2->next != tempMax)
            {
                temp2 = temp2->next;
            }
            temp2->next = tempMax->next;
        }
    }
}

void linkedListExecution(int arraySize)
{
    double insertTime, popTime, totalTime;

    clock_t start, end;
    linkedNode *head = NULL;

    // insert
    start = clock();
    for (int i = 0; i < arraySize; i++)
    {
        pushNodeToLinkedList(&head);
    }
    end = clock();

    insertTime = (double)(end - start);
    printf("\nLinked List - Insert에 소요 시간: %.0lfms", insertTime);

    start = clock();
    for (int i = 0; i < arraySize; i++)
    {
        popBiggestPriorityFromLinkedList(&head);
    }
    end = clock();
    popTime = (double)(end - start);
    printf("\nLinked List - Pop에 소요 시간: %.0lfms", popTime);

    // total
    totalTime = insertTime + popTime;
    printf("\nLinked List - 전체 소요 시간: %.0lfms", totalTime);
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

void insertNodeToMaxHeap(data d, int *nodeIndex)
{
    int i;

    i = ++(*nodeIndex);
    // printf("%d ", d.priority);

    while ((i != 1) && (d.priority > maxHeap[i / 2].priority))
    {
        maxHeap[i] = maxHeap[i / 2];
        i /= 2;
    }
    maxHeap[i] = d;
}

data *popBiggestNodeFromHeap(int *nodeIndex)
{
    int parent, child;
    data item, temp;

    item = maxHeap[1];
    temp = maxHeap[(*nodeIndex)--];

    parent = 1;
    child = 2;

    while (child <= *nodeIndex)
    {
        if ((child < *nodeIndex) && (maxHeap[child].priority < maxHeap[child + 1].priority))
        {
            child++;
        }
        if (temp.priority >= maxHeap[child].priority)
        {
            break;
        }
        maxHeap[parent] = maxHeap[child];
        parent = child;
        child *= 2;
    }
    maxHeap[parent] = temp;
    // printf("%d ", item.priority);
    return &item;
}

void heapExecution(int arraySize)
{
    srand(time(NULL));
    int n = 0;
    data *d;

    double insertTime, popTime, totalTime;

    clock_t start, end;

    // insert
    start = clock();
    ////
    for (int i = 0; i < arraySize; i++)
    {
        d = makeRandomData();
        // printf("%d ", d->priority);
        insertNodeToMaxHeap(*d, &n);
    }
    end = clock();

    insertTime = (double)(end - start);
    printf("\nMax Heap - Insert에 소요 시간: %.0lfms", insertTime);

    // pop

    start = clock();
    for (int i = 0; i < arraySize; i++)
    {
        d = popBiggestNodeFromHeap(&n);
        // printf("%d ", d->priority);
    }
    end = clock();
    popTime = (double)(end - start);
    printf("\nMax Heap - Pop에 소요 시간: %.0lfms", popTime);

    // total
    totalTime = insertTime + popTime;
    printf("\nMax Heap - 전체 소요 시간: %.0lfms", totalTime);
}

int main(void)
{
    int inputSize;
    printf("Insert the number of inputs: ");
    scanf("%d", &inputSize);
    // printf("----------------------------------------");
    // arrayExecution(arraySize);
    // printf("----------------------------------------");
    // linkedListExecution(arraySize);
    // printf("----------------------------------------");
    // heapExecution(arraySize);
    printf("----------------------------------------");
    bstExecution(inputSize);

    return 0;
}
