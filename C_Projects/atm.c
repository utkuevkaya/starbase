#include <stdio.h>
#include <stdlib.h>

int balance = 1000;
const int password = 1923;
int operation;

void check_entrance();
void show_menu();
void show_balance();
void deposit();
void withdraw();

int main()
{
    
    check_entrance();

    while (1) 
    {
        show_menu();

        // Selecting Operations
        switch (operation)
        {
            case 1:
                show_balance();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                printf("\nThank you for using KLM ATM\nSee you later!\n");
                exit(1);
            default:
                printf("\nPlease enter a valid number!\n");
        }
    }

    return 0;
}


void check_entrance()
{
    int tried_password;
    int remaining_tries = 3;

    printf("\nWelcome to the KLM ATM\n");

    do 
    {
        printf("Please enter your Password!\n");
        printf("Password: ");
        scanf("%d", &tried_password);

        if (--remaining_tries == 0 && tried_password != password)
        {
            printf("\nWrong password. Account has blocked!");
            exit(0);
        }

        if (tried_password != password) 
        {
            printf("\nWRONG PASSWORD!\n");
        }

        
    } while (remaining_tries != 0 && tried_password != password);
}


void show_menu()
{
    printf("\n\n\n=== KLM ATM MENU ===\n");
    printf("1. Show Balance\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Exit\n");

    printf("Please enter a value: ");
    scanf("%d", &operation);
}

void show_balance()
{
    printf("\nYour current balance is: %d\n", balance);
}

void deposit()
{
    int deposit = 0;
    printf("\nPlease enter the amount of money you would like to deposit: ");
    scanf("%d", &deposit);

    balance += deposit;

    show_balance();
}

void withdraw()
{
    int withdraw = 0;

    show_balance();
    
    do 
    {
        
        printf("\nPlease enter the amount of money you would like to withdraw: ");
        scanf("%d", &withdraw);

        if (withdraw > balance) 
        {
            printf("\nYou can not withdraw money more than %d\n", balance);
        }
    } while (withdraw > balance);

    balance -= withdraw;

    show_balance();
}


// TODO: 
// Her işlemden sonra işlem fişi
// Para çekiminde 10'un katları kuralı 
// Çoklu kullanıcı (kullanıcı adı + şifre) (struct + dosya)