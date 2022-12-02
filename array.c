#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct data
{
    int priority;
    char *c;
} data;

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

data *makeNode(void)
{
    data *n = malloc(sizeof(data));
    n->priority = rand() % 1000;
    n->c = generateRandomString();
    return n;
}

data **makeArray(int arraySize)
{
    data **array = (data **)malloc(sizeof(data *) * arraySize);
    return array;
}

void insertNodeToArray(data **array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        array[i] = makeNode();
    }
}

void selectionSort(data **array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = i + 1; j < arraySize; j++)
        {
            if (array[i]->priority < array[j]->priority)
            {
                // 바꾸기
                data *tempData = array[i];
                array[i] = array[j];
                array[j] = tempData;
            }
        }
    }
}

void popBiggestPriority(data **array, int arraySize)
{
    selectionSort(array, arraySize);

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
    insertNodeToArray(array, arraySize);
    end = clock();

    insertTime = (double)(end - start);
    printf("\nArray - Insert에 소요 시간: %.0lfms", insertTime);
    start = clock();
    popBiggestPriority(array, arraySize);
    end = clock();
    popTime = (double)(end - start);
    printf("\nArray - Pop에 소요 시간: %.0lfms", popTime);
    totalTime = insertTime + popTime;
    printf("\nArray - 전체 소요 시간!: %.0lfms", totalTime);
}

int main(void)
{
    int arraySize;
    printf("Insert the number of inputs: ");
    scanf("%d", &arraySize);
    arrayExecution(arraySize);
    return 0;
}