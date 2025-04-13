#include <stdio.h>

void calc(int chart[3][3], int sums[6]);
void print(int chart[3][3], int sums[6]);

int main()
{
    int chart[3][3];
    int sums[6];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Please enter value for row %d, col %d: ", i + 1, j + 1);
            scanf("%d", &chart[i][j]);
        }
    }

    calc(chart, sums);
    print(chart, sums);

    return 0;
}

void calc(int chart[3][3], int sums[6])
{
    for (int i = 0; i < 6; i++)
        sums[i] = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sums[i] += chart[i][j];     
            sums[j + 3] += chart[i][j]; 
        }
    }
}

void print(int chart[3][3], int sums[6])
{
    printf("\n==== Chart ====\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%4d", chart[i][j]);
        }
        printf(" | Row Sum: %d\n", sums[i]);
    }

    printf("---------------\n");
    printf("Col Sums: %d %d %d\n", sums[3], sums[4], sums[5]);
}


// TODO:
// Dinamik Boyut
// Ortalama, en küçük, en büyük
// Satır - sütun bazında arama
// CSV formatında kaydetme
// Transpoz