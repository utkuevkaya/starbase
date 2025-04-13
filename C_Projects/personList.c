#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu();
void addPerson();
void showList();
void searchName(); 

typedef struct Person
{
    char *name;
    char *surname;
    char *phone;
} Person;

Person *persons; 
int count = 0;

int main()
{
    int capacity = 10;
    persons = malloc(capacity * sizeof(Person));

    while (1)
    {
        switch (menu())
        {
            case 1:
                if (count >= capacity)
                {
                    printf("Kapa arttı lan!");
                    capacity *= 2;
                    persons = realloc(persons, capacity * sizeof(Person));
                }
                addPerson();
                count += 1;
                break;
            case 2:
                showList();
                break;
            case 3:
                searchName();
                break;
            case 4:
                for (int i = 0; i < count; i++)
                {
                    free(persons[i].name);
                    free(persons[i].surname);
                    free(persons[i].phone);
                }
                free(persons);
                return 0;
            default:
                printf("\nYou have wrong entered!\n");
        }
        
    }
    return 0;
}

int menu()
{
    int operation = 0; 

    printf("\n\n=== Romulus Person List ===\n");
    printf("1. Add Person\n");
    printf("2. Show List\n");
    printf("3. Search for Name\n");
    printf("4. Exit\n");
    printf("Enter a value: ");
    scanf("%d", &operation);

    while (getchar() != '\n');

    return operation;
}

void addPerson()
{
    char name_temp[100];
    char surname_temp[100];
    char phone_temp[100];

    printf("\nName: ");
    fgets(name_temp, sizeof(name_temp), stdin);
    name_temp[strcspn(name_temp, "\n")] = 0;

    persons[count].name = malloc(strlen(name_temp) +  1);
    strcpy(persons[count].name, name_temp);


    printf("Surname: ");
    fgets(surname_temp, sizeof(surname_temp), stdin);
    surname_temp[strcspn(surname_temp, "\n")] = 0;

    persons[count].surname = malloc(strlen(surname_temp) + 1);
    strcpy(persons[count].surname, surname_temp);

    
    printf("Phone: ");
    fgets(phone_temp, sizeof(phone_temp), stdin);
    phone_temp[strcspn(phone_temp, "\n")] = 0;
    
    persons[count].phone = malloc(strlen(phone_temp) + 1);
    strcpy(persons[count].phone, phone_temp);


    printf("Person added!\n");
}

void showList()
{
    printf("\n---Person List---\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s %s - %s\n", i+1, persons[i].name, persons[i].surname, persons[i].phone);
    }
}

void searchName()
{
    char target[100];
    int is_found = 0;

    printf("\nEnter a name: ");
    fgets(target, 100, stdin);
    target[strcspn(target, "\n")] = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(persons[i].name, target) == 0)
        {
            printf(">> %s %s - %s\n", persons[i].name, persons[i].surname, persons[i].phone);
            is_found = 1;
        }
    }

    if (!is_found)
        printf("No name has found!");
}

// Dosyaya yazma 
// Kişi silme ve güncelleme
// Soyada göre sıralama
// Telefon numarasını doğrula