#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 10000000
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct data
{
    int priority;
    char *c;
} data;

data heap[MAX_ELEMENTS];

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

void push(data d, int *nodeIndex)
{
    int i;

    i = ++(*nodeIndex);

    while ((i != 1) && (d.priority > heap[i / 2].priority))
    {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = d;
}

data *popHeap(int *nodeIndex)
{
    int parent, child;
    data item, temp;

    item = heap[1];
    temp = heap[(*nodeIndex)--];

    parent = 1;
    child = 2;

    while (child <= *nodeIndex)
    {
        if ((child < *nodeIndex) && (heap[child].priority < heap[child + 1].priority))
        {
            child++;
        }
        if (temp.priority >= heap[child].priority)
        {
            break;
        }
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return &item;
}

int main(void)
{
    srand(time(NULL));
    int n = 0;
    data *d;

    double insertTime, popTime, totalTime;

    clock_t start, end;
    
    int arraySize;
    scanf("%d", &arraySize);

    // insert
    start = clock();
    ////
    printf("insert:  ");
    for (int i = 0; i < arraySize; i++)
    {
        d = makeRandomData();
        // printf("%d ", d->priority);
        push(*d, &n);
    }
    end = clock();

    insertTime = (double)(end - start);
    printf("\nInsert에 소요 시간: %lfms\n", insertTime);

    // pop
    printf("\npop: ");

    start = clock();
    for (int i = 0; i < arraySize; i++)
    {
        d = popHeap(&n);
        // printf("%d ", d->priority);
    }
    end = clock();
    popTime = (double)(end - start);
    printf("\nPop에 소요 시간: %lfms", popTime);

    // total
    totalTime = insertTime + popTime;
    printf("\n\n전체 소요 시간: %lfms", totalTime);

    return 0;
}
