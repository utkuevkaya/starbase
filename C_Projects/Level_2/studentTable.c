#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define NAME_LEN 50

typedef struct Student {
    int stuNo;
    char name[NAME_LEN];
    struct Student* next;
} Student;

int hash(int stuNo);
Student *createStudent(int stuNo, const char *name);
void addStudent(int stuNo, const char *name);
void searchStudent(int stuNo);
void deleteStudent(int stuNo);
void listStudents();
void clean();

Student *hashTable[TABLE_SIZE];

int main() {
    int operation, no;
    char name[NAME_LEN];

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Delete Student\n");
        printf("4. List Students\n");
        printf("0. Exit\n");
        printf("Enter a function: ");
        scanf("%d", &operation);
        while (getchar() != '\n');

        switch (operation) {
            case 1:
                printf("\nName: ");
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = 0;

                printf("Student No: ");
                scanf("%d", &no);
                while (getchar() != '\n');

                addStudent(no, name);
                break;

            case 2:
                printf("Student No: ");
                scanf("%d", &no);
                searchStudent(no);
                break;

            case 3:
                printf("Student No: ");
                scanf("%d", &no);
                deleteStudent(no);
                break;

            case 4:
                listStudents();
                break;

            case 0:
                clean();
                printf("\nThank you for using SMS!");
                return 0;

            default:
                printf("\nWrong dialed!\n");
        }
    }
}

int hash(int stuNo)
{
    return stuNo % TABLE_SIZE;
}

Student *createStudent(int stuNo, const char *name)
{
    Student *newStudent = malloc(sizeof(Student));

    strcpy(newStudent->name, name);
    newStudent->stuNo = stuNo;
    newStudent->next = NULL;

    return newStudent;
}

void addStudent(int stuNo, const char *name)
{
    int index = hash(stuNo);
    Student *newStudent = createStudent(stuNo, name);

    newStudent->next = hashTable[index];
    hashTable[index] = newStudent;
}

void searchStudent(int stuNo)
{
    int index = hash(stuNo);
    Student *temp = hashTable[index];

    while (temp != NULL)
    {
        if (temp->stuNo == stuNo)
        {
            printf("\n---Student---\n");
            printf("Name: %s\n", temp->name);
            printf("Student No: %d\n", temp->stuNo);
            return;
        }

        temp = temp->next;
    }

    printf("The Student couldn't be found!\n");
}

void deleteStudent(int stuNo)
{
    int index = hash(stuNo);
    Student *temp1 = hashTable[index];
    Student *temp2 = NULL;
    
    while (temp1 != NULL)
    {
        if (temp1->stuNo == stuNo)
        {
            if (temp2 == NULL)
            {
                hashTable[index] = temp1->next;
            }

            else
            {
                temp2->next = temp1->next;
            }

            free(temp1);
            printf("Student has been deleted!\n");
            return;
        }

        temp2 = temp1;
        temp1 = temp1->next;
    }

    printf("The Student couldn't be found!\n");
}

void listStudents()
{
    printf("\n\n___All Students___:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Student *temp = hashTable[i];

        if (temp == NULL) continue;
        
        printf("\n%d. Index:\n", i);
        while (temp != NULL)
        {
            printf(">> %s - %d\n", temp->name, temp->stuNo);
            temp = temp->next;
        }
    }
}

void clean()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Student *iter = hashTable[i];

        while (iter != NULL)
        {
            Student *temp = iter;
            iter = iter->next;
            free(temp);
        }
    }
}

// TODO:
// Aynı numara engelleme
// Dinamik hashtablosu
// Dosya kaydetme
// Alfabetik sıralama
// Kullanıcı dostu arayüz
// Öğrencilere notlar struct içinde struct
