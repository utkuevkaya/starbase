#include <stdio.h>
#include <stdbool.h>

typedef struct Stack 
{
    int data[10];
    int top;
    bool isEmpty;
} Stack;

int menu();
void show(Stack *stack);
void push(Stack *stack);
int pop(Stack *stack);
void checkEmpty(Stack *stack);

int main()
{
    Stack stack;
    stack.top = -1;
    Stack *stack_ptr = &stack;

    while (1)
    {
        switch (menu())
        {
            case 1:
                push(stack_ptr);
                break;
            case 2:
                checkEmpty(stack_ptr);

                if (stack.isEmpty)
                {
                    printf("The Stack is empty!");
                    break;
                }
                
                else 
                {
                    printf("Popped: %d", pop(stack_ptr));
                    break;
                }
            case 3:
                show(stack_ptr);
                break;
            case 4: 
                printf("\nThank you for using Stack :)\n");
                return 0;
            default:
                printf("You have wrong dialed!\n");
        }
    }

    return 0;
}

int menu()
{
    int operation = 0;

    printf("\n\n=== Stack ===\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Show\n");
    printf("4. Exit\n");

    printf("Enter your function: ");
    scanf("%d", &operation);
    while (getchar() != '\n');

    return operation;
}

void push(Stack *stack)
{
    if (stack->top == 9)
    {
        printf("\nThe stack is full!");
        return;
    }

    int num;

    printf("\nEnter the number you would like to push: ");
    scanf("%d", &num);
    while (getchar() != '\n');

    stack->top++;
    stack->data[stack->top] = num;
}

int pop(Stack *stack)
{
    int num; 

    num = stack->data[stack->top];
    stack->top--;

    return num;
}

void show(Stack *stack)
{
    for (int i = 0; i < stack->top+1; i++)
    {
        printf("%d -> ", stack->data[i]);
    }

    printf("END\n");
}

void checkEmpty(Stack *stack)
{
    if (stack->top > -1 && stack->top < 10)
    {
        stack->isEmpty = false;
    }

    if (stack->top == -1)
    {
        stack->isEmpty = true;
    }
}

// TODO:
// Stack'i struct ve pointer ile yazmak 
// Dinamik Stack yapmak 
// Parantez dengeleme ya da undo / redo konuları 
// peek -> En üstteki elemanı göster ama çıkarma 
// Clear fonksiyonu 
// Char stack yaparak parantez dengeleme algoritması yaz 
// Ters yazdırma