#include <stdio.h>
#include <stdlib.h>



typedef struct Node {
    int data;
    struct Node *next;
} Node;



Node* createNode(int data) {
    Node* newNode = (Node* )malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}



void insertAtBeginning(Node** head, int data) {                 // Node** head -> Bir Node'un adresinin adresini taşır. 
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}



void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}



void insertAtPosition(Node** head, int data, int position) {
    Node* newNode = createNode(data);

    if (position == 1) {
        newNode->next = *head;
        *head = newNode;
        return; 
    }


    Node* temp = *head;
    int current_pos = 1;

    while(temp != NULL) {

        if (current_pos+1 == position) {
            newNode->next = temp->next;
            temp->next = newNode;
            return;
        }

        temp = temp->next;
        current_pos++;
    } 

    printf("\nPosition out of bounds!\n");
    free(newNode);
    return;
}



void deleteFromBeginning(Node** head) {

    if (*head == NULL) {
        return; 
    }

    Node* temp = *head;
    *head = temp->next;
    free(temp);
}



void deleteFromEnd(Node** head) {

    if (*head == NULL) {
        return; 
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    

    Node* temp_one = *head; 
    Node* temp_two = temp_one->next;

    while (temp_two->next != NULL) {
        temp_one = temp_two;
        temp_two = temp_two->next;
    }

    temp_one->next = NULL;
    free(temp_two);
}



void deleteFromPosition(Node** head, int position) {

    if (position == 1) {
        deleteFromBeginning(head);
        return;
    }

    
    Node* tempOne = *head;
    Node* tempTwo = tempOne->next;
    int tempTwo_pos = 2;

    while (tempTwo != NULL) {

        if (tempTwo_pos == position) {
            tempOne->next = tempTwo->next;
            free(tempTwo);
            return;
        }

        tempOne = tempTwo;
        tempTwo = tempTwo->next;
        tempTwo_pos++;
    }
}



Node* search(Node** head, int data) {
    Node* temp = *head;

    while (temp != NULL) {
        
        if (temp->data == data) {
            return temp;
        }

        temp = temp->next; 
    }
    return 0;
}


void printList(Node* head) {
    Node* temp = head; 

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


int main() {

    Node *head = NULL;
    insertAtBeginning(&head, 10); // [10]
    insertAtBeginning(&head, 20); // [20 -> 10]
    insertAtBeginning(&head, 40); // [40 -> 20 -> 10]
    insertAtEnd(&head, 15);       // [40 -> 20 -> 10 -> 15]
    insertAtPosition(&head, 90, 3); // [40 -> 20 -> 90 -> 10 -> 15]
    insertAtPosition(&head, 34, 4); // [40 -> 20 -> 90 -> 34 -> 10 -> 15]
    deleteFromBeginning(&head);   // [20 -> 90 -> 34 -> 10 -> 15]
    deleteFromEnd(&head);         // [20 -> 90 -> 34 -> 10]
    deleteFromPosition(&head, 2); // [20 -> 34 -> 10]
    insertAtEnd(&head, 5);        // [20 -> 34 -> 10 -> 5]
    insertAtPosition(&head, 13, 2); // [20 -> 13 -> 34 -> 10 -> 5]
    Node *ptr = search(&head, 13);
    printList(head);
    
    if (ptr == NULL) {
        printf("\nCouldn't Find!");
    } 

    else {
        printf("\n%d: %p", *ptr, ptr);
    }

    return 0;
}