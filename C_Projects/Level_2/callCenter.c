#include <stdio.h>
#include <stdlib.h>

typedef struct Person {
    int operationTime;
    struct Person *next;
} Person;

typedef struct {
    Person *head;
    Person *tail;
} Queue;

float calcStatistics(int opTime);
Queue *createQueue();
Person *createPerson(int opTime);
int isEmpty(Queue *q);
void enqueue(Queue *q, int opTime);
int dequeue(Queue *q);
void printQueue(Queue *q);
void clearQueue(Queue *q);
int menu();

int main() {
    Queue *q = createQueue();

    while (1) {
        switch (menu()) {
            case 1: {
                int opTime;
                printf("Enter operation time (in minutes): ");
                scanf("%d", &opTime);
                enqueue(q, opTime);
                printf("Person added to queue.\n");
                break;
            }

            case 2: {
                int opTime = dequeue(q);
                if (opTime != -1) {
                    printf("Processing person... Operation time: %d min\n", opTime);
                    float avg = calcStatistics(opTime);
                    printf("Average operation time: %.2f minutes\n", avg);
                }
                break;
            }

            case 3:
                printQueue(q);
                break;

            case 4:
                clearQueue(q);
                printf("Thank you for using X Bank.\n");
                exit(0);
        }
    }

    return 0;
}

int menu() {
    int choice;
    printf("\n--- X BANK QUEUE SYSTEM ---\n");
    printf("1. Add Person to Queue\n");
    printf("2. Process Next Person\n");
    printf("3. View Queue\n");
    printf("4. Show Statistics\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);
    return choice;
}

Queue *createQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->head = q->tail = NULL;
    return q;
}

Person *createPerson(int opTime) {
    Person *p = (Person *)malloc(sizeof(Person));
    p->operationTime = opTime;
    p->next = NULL;
    return p;
}

int isEmpty(Queue *q) {
    return q->head == NULL;
}

void enqueue(Queue *q, int opTime) {
    Person *p = createPerson(opTime);
    if (isEmpty(q)) {
        q->head = q->tail = p;
    } else {
        q->tail->next = p;
        q->tail = p;
    }
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return -1;
    }

    Person *temp = q->head;
    int time = temp->operationTime;
    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = NULL;
    free(temp);
    return time;
}

void printQueue(Queue *q) {
    printf("\nQueue: ");
    Person *p = q->head;
    if (!p) {
        printf("Empty\n");
        return;
    }

    while (p != NULL) {
        printf("[%d min] -> ", p->operationTime);
        p = p->next;
    }
    printf("NULL\n");
}

float calcStatistics(int opTime) {
    static int totalTime = 0;
    static int count = 0;
    totalTime += opTime;
    count++;
    return (float)totalTime / count;
}

void clearQueue(Queue *q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
    free(q);
}
