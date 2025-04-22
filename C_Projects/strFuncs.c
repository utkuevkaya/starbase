#include <stdio.h>

int my_strlen(char *str);
void my_strcpy(char *dest, char *src);
int my_strcmp(char *str1, char *str2);
void my_strcat(char *dest, char *src);

int main()
{
    char str1[10] = "Merhaba";
    char str2[10];
    char str3[20] = "Selamlar";

    int len = my_strlen(str1);
    printf("%d\n", len); 

    my_strcpy(str2, str1);
    printf("%s\n", str2);

    printf("%d\n", my_strcmp(str1, str3));
    printf("%d\n", my_strcmp(str1, str2));

    my_strcat(str3, str2);
    printf("%s", str3);

    return 0;
}

int my_strlen(char *str)
{
    int len = 0;

    while (*str)
    {
        len++;
        str++;
    }

    return len;
}

void my_strcpy(char *dest, char *src)
{
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';
}

int my_strcmp(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
        {
            return *str1 - *str2;
        }

        str1++;
        str2++;
    }

    return *str1 - *str2;
}

void my_strcat(char *dest, char *src)
{
    while (*dest)
    { 
        dest++; 
    }

    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';
}

// TODO
// Büyük küçük harf farkını kaldıran my_stricmp()
// Bu fonksiyonları bir main.c dosyası içinde çağır. 
// dinamik bellek 
// stringi ters çevir
// karakter arayan fonksiyon