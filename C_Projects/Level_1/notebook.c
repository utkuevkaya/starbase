#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define filepath "C:/Yazilim/utkuevkaya/C_Projects/notebook.txt"
FILE *file;
char sentence[1000];

int menu();
void write_note();
void find_word();
void to_lowercase(char *str);

int main()
{
    file = fopen(filepath, "a+");
    if (file == NULL)
    {
        perror("File couldn't opened!");
        return 1;
    }

    while (1) 
    {
        switch(menu())
        {
            case 1:
                write_note();
                break;

            case 2:
                find_word();
                break;

            case 3:
                printf("\nThank you for using Mini Notebook");
                fclose(file);
                return 0;
                break;

            default:
                printf("\nYou have wrong dialed!\n");
        }
    }

    return 0;
}

int menu()
{
    int operation = 0;

    printf("\n\n=== Mini Notebook ===\n");
    printf("1. Enter Note\n");
    printf("2. Find Word\n");
    printf("3. Exit\n");

    printf("\nPlease enter the value of a function: ");
    scanf("%d", &operation);
    while (getchar() != '\n');

    return operation;
}

void write_note()
{
    printf("\nEnter a sentence: ");
    fgets(sentence, 1000, stdin);
    sentence[strcspn(sentence, "\n")] = 0;

    fprintf(file, "%s\n", sentence);
    fflush(file);
}

void find_word()
{
    char target[1024];
    char lower_sentence[1000];
    int found = 0;
    
    printf("\nEnter a word: ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = 0;
    
    to_lowercase(target);
    
    fseek(file, 0, SEEK_SET);

    printf("\n\n---- Search Results ----\n\n");
    while (fgets(sentence, sizeof(sentence), file))
    {
        strcpy(lower_sentence, sentence);
        to_lowercase(lower_sentence);

        if (strstr(lower_sentence, target)) 
        {
            printf(">> %s", sentence);
            found = 1; 
        }
    }

    if (!found)
    {
        printf("\nNo results!\n");
    }

}

void to_lowercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// TODO:
// kelime sayma / silme / düzenleme
// Sonuç sayısı gösterme
// Aynı anda birden fazla kelime 
// Notlara tarih ekle
// Farklı kullanıcılar için farklı dosyalar