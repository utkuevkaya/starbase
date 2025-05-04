#include <stdio.h>
#include <stdlib.h>

int show_menu();
void create_array();
void sort_array();
void print_array();

int *array = NULL;
int array_length;

int main()
{
    while (1)
    {
        switch(show_menu())
        {
            case 1:
                create_array();
                sort_array();
                print_array();
                break;
            case 2:
                printf("\nThank you for using SORTER!");
                exit(0);
                break;
            default:
                printf("\nYou have wrong number entered!\n");
        }
    }

    return 0;
}

int show_menu()
{
    int operation = 0;

    printf("\n\n==== SORTER ====\n");
    printf("1. Sort\n");
    printf("2. Exit\n");
    printf("Please enter the value of operation you would like to do: ");
    scanf("%d", &operation);

    return operation;
}

void create_array()
{
    printf("\nEnter the number of values you would like to enter: ");
    scanf("%d", &array_length);

    array = malloc(array_length * sizeof(int));

    for (int i = 0; i < array_length; i++)
    {
        int temp = 0;
        printf("Please enter the %d. value: ", i+1);
        scanf("%d", &temp);
        array[i] = temp;
    }
}

void sort_array()
{
    for (int i = 0; i < array_length-1; i++) 
    {
        for (int j = 0; j < array_length-1; j++)
        {
            int temp = 0; 
            if (array[j] > array[j+1]) {
                temp = array[j+1];
                array[j+1] = array[j];
                array[j] = temp;
            } 
        }
    }
}

void print_array()
{
    for (int i = 0; i < array_length; i++)
    {
        printf("%d ", array[i]);
    }
}

// TODO:
// Hem küçükten büyüğe hem de büyükten küçüğe sıralama 
// Selection Sort ve Insertion Sort ve Quick Sort algoritmaları ekle bunların sürelerini yaz.