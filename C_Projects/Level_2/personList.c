#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Person
{
    char fullName[80];
    char phoneNum[15];
    struct Person *next;
} Person;

int menu();
void initPersons(Person **head);
Person *createPerson();
void addPerson(Person **head);
void searchPerson(Person *head);
void listPersons(Person *head);
void deletePerson(Person **head);
void updateFile(Person *head);
void to_lowercase(char *string);
void strip(char *string);

int main()
{
    Person *head = NULL;
    initPersons(&head);

    while (1)
    {
        switch (menu())
        {
            case 1:
                addPerson(&head);
                updateFile(head);
                break;
            case 2:
                searchPerson(head);
                break;
            case 3:
                listPersons(head);
                break;
            case 4:
                deletePerson(&head);
                updateFile(head);
                break;
            case 5:
                printf("\nThank you for using YDK Phone Book");
                exit(0);
            default:
                printf("\nYou have wrong dialed!\n");
        }
    }

    return 0;
}

int menu()
{
    int operation = 0;

    printf("\n\n==== YDKE PHONE BOOK ====\n");
    printf("1. Add Person\n");
    printf("2. Search Person\n");
    printf("3. List Persons\n");
    printf("4. Delete Person\n");
    printf("5. Exit\n");
    printf("Enter function: ");
    scanf("%d", &operation);
    while (getchar() != '\n');

    return operation;
}

void initPersons(Person **head)
{  
    FILE *file = fopen("persons.da", "r");
    if (file == NULL)
    {
        file = fopen("persons.da", "w");
        if (file == NULL)
        {
            perror("\nCouldn't open the file!");
            exit(1);
        }
    } 

    char buffer[120];
    Person *temp1 = *head;

    while (fgets(buffer, sizeof(buffer), file))
    {
        Person *newPerson = malloc(sizeof(Person));

        char *part = strtok(buffer, "|");
        if (part == NULL) continue;
        strcpy(newPerson->fullName, part);

        part = strtok(NULL, "\n");
        if (part == NULL) continue;
        strcpy(newPerson->phoneNum, part);

        newPerson->next = NULL;

        if (temp1 != NULL)
        {
            temp1->next = newPerson;
            temp1 = newPerson;
            continue;
        }

        *head = newPerson;
        temp1 = newPerson; 
    }

    fclose(file);
}

Person * createPerson()
{
    char temp_name[30], temp_surname[50], temp_phoneNum[15], temp_fullName[85], space[] = " ";

    printf("Enter the name: ");
    fgets(temp_name, sizeof(temp_name), stdin);
    strip(temp_name);

    printf("Enter the surname: ");
    fgets(temp_surname, sizeof(temp_surname), stdin);
    strip(temp_surname);

    printf("Enter the phone number: ");
    fgets(temp_phoneNum, sizeof(temp_phoneNum), stdin);
    strip(temp_phoneNum);

    strcpy(temp_fullName, temp_name);
    strcat(temp_fullName, space);
    strcat(temp_fullName, temp_surname);

    Person *newPerson = malloc(sizeof(Person));
    strcpy(newPerson->fullName, temp_fullName);
    strcpy(newPerson->phoneNum, temp_phoneNum);
    newPerson->next = NULL;

    return newPerson;
}

void addPerson(Person **head)
{
    Person *newPerson = createPerson();

    Person *temp1 = *head;
    Person *temp2 = NULL; 

    while (temp1 != NULL)
    {
        int cmp = strcmp(newPerson->fullName, temp1->fullName);
        if (cmp == -1) break;
        temp2 = temp1;
        temp1 = temp1->next;
    }

    if (*head == NULL || temp2 == NULL)
    {
        *head = newPerson;
        newPerson->next = temp1;
        return;
    }

    temp2->next = newPerson;
    newPerson->next = temp1;
}

void searchPerson(Person *head)
{
    char target[85];
    char lowersentence[50];
    int found = 0;

    printf("\nEnter Name: ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = 0;

    to_lowercase(target);

    Person *temp = head;
    while (temp != NULL)
    {
        strcpy(lowersentence, temp->fullName);
        to_lowercase(lowersentence);

        if (strstr(lowersentence, target))
        {
            printf(">> %s -> %s\n", temp->fullName, temp->phoneNum);
            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
    {
        printf("\nNo result!\n");
    }
}

void listPersons(Person *head)
{
    int count = 1;

    printf("\n\n");
    printf("---Persons---\n");

    Person *temp = head;
    while (temp != NULL)
    {
        printf("%d) %s -> %s\n", count, temp->fullName, temp->phoneNum);
        temp = temp->next;
        count++;
    }

}

void deletePerson(Person **head)
{
    int deleteIndex;

    if (*head == NULL)
    {   
        printf("\nThe notebook is empty!\n");
        return;
    }

    listPersons(*head);
    printf("Enter the id: ");
    scanf("%d", &deleteIndex);
    while (getchar() != '\n');

    Person *temp1 = *head;
    Person *temp2 = NULL;

    if (deleteIndex == 1)
    {
        *head = temp1->next;
        free(temp1);
        return;
    }

    deleteIndex--;

    while (temp1 != NULL)
    {
        if (!deleteIndex)
        {
            temp2->next = temp1->next;
            free(temp1);
            return;
        }

        temp2 = temp1;
        temp1 = temp1->next;
        deleteIndex--;
    }
}

void updateFile(Person *head)
{
    FILE *file = fopen("persons.da", "w");
    if (file == NULL)
    {
        perror("\nCouldn't open!");
        exit(1);
    }

    Person *temp = head;
    while (temp != NULL)
    {
        fprintf(file, "%s|%s\n", temp->fullName, temp->phoneNum);
        temp = temp->next;
    }

    fflush(file);
}

void to_lowercase(char *string)
{
    while (*string)
    {
        *string = tolower(*string);
        string++;
    }
}


void strip(char *str)
{
    char *src = str;
    char *dst = str;
    int in_word = 0;

    while (isspace((unsigned char)*src)) src++;

    while (*src) {
        if (isspace((unsigned char)*src)) 
        {
            if (in_word) 
            {
                *dst++ = ' ';
                in_word = 0;
            }
        } 
        
        else 
        {
            *dst++ = *src;
            in_word = 1;
        }

        src++;
    }

    if (dst > str && isspace((unsigned char)*(dst - 1))) {
        dst--;
    }

    *dst = '\0';
}

// TODO:
// Hızlı Erişim -> Son kişi
// Listeyi Json veya csv
// Filtreleme
