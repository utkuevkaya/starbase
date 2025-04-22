#include <stdio.h>

#define LEN 10

int max(int *array);
float mean(int *array);
void print(int *array);
void timesTwo(int *array);

int main()
{
    int array[LEN];

    for (int i = 0; i < LEN; i++)
    {
        printf("Enter the %d. value: ", i+1);
        scanf("%d", array+i);
    }

    int max_value = max(array);
    float mean_value = mean(array);

    printf("%d\n", max_value);
    printf("%f\n", mean_value);
    print(array);
    printf("\n");
    timesTwo(array);

    return 0;
}

int max(int *array)
{
    int max = *array;

    for (int i = 0; i < LEN; i++)
    {
        if (*(array+i) > max)
        {
            max = *(array+i);
        }
    }

    return max;
}

float mean(int *array)
{
    float mean = 0;
    
    for (int i = 0; i < LEN; i++)
    {
        mean += *(array+i);
    }

    mean /= LEN;

    return mean;
}

void print(int *array)
{
    for (int i = 0; i < LEN; i++) 
    {
        printf("%d ", *(array+i));
    }
}

void timesTwo(int *array)
{
    for (int i = 0; i < LEN; i++) 
    {
        printf("%d ", 2 * *(array+i));
    }
}

// TODO
// Minimum Bulma
// Toplamı döndüren fonksiyon
// Ters yazdırma 