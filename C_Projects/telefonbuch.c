#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char *name;
    char *telNo;
    struct Person *next;
} Person;

Person* createPerson(const char* name, const char* telNo) {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    newPerson->name = (char*)malloc(strlen(name) + 1);
    strcpy(newPerson->name, name);
    newPerson->telNo = (char*)malloc(strlen(telNo) + 1);
    strcpy(newPerson->telNo, telNo);
    newPerson->next = NULL;
    return newPerson;
}

void addPerson(Person** head, const char* name, const char* telNo) {
    Person* newPerson = createPerson(name, telNo);

    if (*head == NULL) {
        *head = newPerson;
        return;
    }    

    Person* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newPerson;
}

void printList(Person* head) {
    Person* temp = head;
    size_t personCount = 1;

    while (temp != NULL) {
        int length;
        int space_length = 20; 

        length = strlen(temp->name);
        space_length = 20 - length;

        printf("%zu) %s", personCount, temp->name);
        for (size_t i = 0; i < space_length; i++) {
            printf(" ");
        }
        printf("| %s", temp->telNo);
        printf("\n");
        temp = temp->next;
        personCount++;
    }
}

void deletePerson(Person** head, const char* name){
    Person* temp1 = *head;
    Person* temp2 = NULL;

    if (temp1 != NULL && strcmp(temp1->name, name) == 0) {
        *head = temp1->next;
        free(temp1->name);
        free(temp1->telNo);
        free(temp1);
        return;
    }

    while (temp1 != NULL && temp1->next != NULL) {
        temp2 = temp1->next;
        if (strcmp(temp2->name, name) == 0) {
            temp1->next = temp2->next;
            free(temp2->name);
            free(temp2->telNo);
            free(temp2);
            return;
        }
        temp1 = temp1->next;
    }
}

void freeList(Person* head) {
    Person* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp->telNo);
        free(temp);
    }
}

int main() {
    Person* head = NULL;

    addPerson(&head, "Mustafa Senturk", "05321374920");
    addPerson(&head, "Isa", "05321374921");
    addPerson(&head, "Kadriye", "05321374922");
    addPerson(&head, "Nursen", "05321374920");
    deletePerson(&head, "Mustafa Senturk");
    printList(head);

    freeList(head);

    return 0;
}
