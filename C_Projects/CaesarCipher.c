#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypter(char *sentence, int key);
void decrypter(char *sentence, int key);
void handle_file();
int menu();

int main()
{
    handle_file();

    return 0;
}

void encrypter(char *sentence, int key)
{
    while (*sentence)
    {
        if (isalpha(*sentence) && isupper(*sentence))
        {
            *sentence = (*sentence - 'A' + key) % 26 + 'A';
        }

        else if (isalpha(*sentence) && islower(*sentence))
        {
            *sentence = (*sentence - 'a' + key) % 26 + 'a';
        }

        sentence++;
    }
}

void decrypter(char *sentence, int key)
{
    while (*sentence)
    {
        if (isalpha(*sentence) && isupper(*sentence))
        {
            *sentence = (*sentence - 'A' - key + 26) % 26 + 'A';
        }

        else if (isalpha(*sentence) && islower(*sentence))
        {
            *sentence = (*sentence - 'a' - key + 26) % 26 + 'a';
        }

        sentence++;
    } 
}

void handle_file()
{
    switch (menu())
    {
        case 1: 
        {
            char file_name[50];
            int key = 0;

            printf("Please enter the name of the file without ext: ");
            fgets(file_name, sizeof(file_name), stdin);
            file_name[strcspn(file_name, "\n")] = 0;
            strcat(file_name, ".txt");

            printf("Please enter the key: ");
            scanf("%d", &key);
            while (getchar() != '\n');

            FILE *file_r = fopen(file_name, "r");
            FILE *file_a = fopen(file_name, "a");

            fprintf(file_a, "\n\nEncrypted:\n");

            char buffer[1000];
            while (fgets(buffer, sizeof(buffer), file_r))
            {
                encrypter(buffer, key);   
                fprintf(file_a, "%s", buffer);    
            }

            fclose(file_r);
            fclose(file_a);
            break;
        }

        case 2:
        {
            char file_name[50];
            int key = 0;

            printf("Please enter the name of the file without ext: ");
            fgets(file_name, sizeof(file_name), stdin);
            file_name[strcspn(file_name, "\n")] = 0;
            strcat(file_name, ".txt");

            printf("Please enter the key: ");
            scanf("%d", &key);
            while (getchar() != '\n');

            FILE *file_r = fopen(file_name, "r");
            FILE *file_a = fopen(file_name, "a");

            fprintf(file_a, "\n\nDecrypted:\n");

            char buffer[1000];
            while (fgets(buffer, sizeof(buffer), file_r))
            {
               decrypter(buffer, key);   
                fprintf(file_a, "%s", buffer);    
            }

            fclose(file_r);
            fclose(file_a);
            break;
        }
    }
}


int menu()
{
    int operation = 0;

    printf("\n\n==== CaesarCipher Encryption ====\n");
    printf("1. Encrypt a file\n");
    printf("2. Decrypt a file\n");
    printf("Enter a value: ");
    scanf("%d", &operation);
    while (getchar() != '\n');

    return operation;
}

// TODO:
// B. Komut Satırı Parametresi ile Çalışma (Advanced)