#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50
typedef struct
{
    char type; /*d for deposit and w for withdraw*/
    double amount;
} Operation;

typedef struct
{
    char name[MAX];
    char email[MAX];
    long Acc_number;
    double balance;
    int number_of_operation;
    Operation operations[MAX];
} Account;

void menu();
void addAccount(Account account[], int *num_account);
void displayAll(Account accounts[], int size);
int loadAccounts(Account accounts[100]); /*load all data to an array */
void saveAccounts(Account account[], int num_account);
int isAccount(Account accounts[], int num_accounts, int account_number);
void search(Account accounts[], int num_accounts);
void deleteAccount(Account accounts[], int *num_accounts, long account_number);
void updateAccount(Account accounts[], int num_accounts);
void toUpper();
void deleteHolerAccounts(Account accounts[], int *num_accounts);
// todo
void printOperation(Account accounts[], int num_accounts);
void addOperation(Account accounts[], int num_accounts);

int emailCheck(char x[]); /* i will use this in addAccount*/
int isAlphabetic(const char *name);
void toUpperCase(char *name);
int isSameString(const char x[], const char y[]);

int main()
{
    Account accounts[100];
    int choice, num_of_accounts = loadAccounts(accounts);

    do
    {
        menu();
        scanf("%d", &choice);

        if (choice == 1)
        {
            system("clear");
            addAccount(accounts, &num_of_accounts);
            saveAccounts(accounts, num_of_accounts);
        }
        else if (choice == 2)
        {
            updateAccount(accounts, num_of_accounts);
            saveAccounts(accounts, num_of_accounts);
        }
        else if (choice == 3)
        {
            int account_number = 0;
            system("clear");
            printf("Enter account Number to Delete: ");
            scanf("%ld", &account_number);
            deleteAccount(accounts, &num_of_accounts, account_number);
            saveAccounts(accounts, num_of_accounts);
        }
        else if (choice == 4)
        {
            deleteHolerAccounts(accounts, &num_of_accounts);
            saveAccounts(accounts, num_of_accounts);
        }
        else if (choice == 5)
        {

            system("clear");
            search(accounts, num_of_accounts);
        }
        else if (choice == 6)
        {
            displayAll(accounts, num_of_accounts);
        }
        else if (choice == 7)
        {
            addOperation(accounts, num_of_accounts);
            saveAccounts(accounts, num_of_accounts);
        }
        else if (choice == 8)
        {
            system("clear");
            printf("==========================================================\n");
            printf("===========Thank you for Banking With BEST BANK===========\n");
            printf("==========================================================\n");
        }
        else
        {
            printf("\nInvalid choice");
        }

        printf("\n\n");
    } while (choice != 8);

    return 0;
}
int isSameString(const char x[], const char y[])
{
    return strcmp(x, y) == 0;
}

void deleteHolerAccounts(Account accounts[], int *num_accounts)
{
    char name[MAX];
    int i = 0, j;
    int prevAccountNumber = *num_accounts; /*to know if there was a delete*/
    printf("Enter Account holder's name to delete all of his Accounts: ");
    getchar();
    fgets(name, MAX, stdin);
    name[strcspn(name, "\n")] = '\0';
    toUpperCase(name);
    if (!isAlphabetic(name))
    {
        printf("Wrong Name format ");
        return;
    }
    for (i = 0; i < *num_accounts; i++)
    {
        if (isSameString(name, accounts[i].name))
        {
            deleteAccount(accounts, num_accounts, accounts[i].Acc_number);
            i--; // Adjust index to re-check the current position
        }
    }
    if (prevAccountNumber == *num_accounts)
    {
        printf("No accounts are found for the given holder name");
        return;
    }
}
int isAlphabetic(const char *name)
{
    int i;
    if (name == NULL || name[0] == '\0')
    {
        return 0; // Invalid input
    }

    for (i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            return 0; // Non-alphabetic character found
        }
    }
    return 1; // All characters are valid
}

void toUpperCase(char *name)
{
    int i;
    for (i = 0; name[i] != '\0'; i++)
    {
        name[i] = toupper(name[i]); // Convert each character to uppercase
    }
}
int emailCheck(char x[])
{
    /*
    this function counts distance between start of email until @
    then until  . until the end
    last it counts the difference between (start , @ , . , end)
    then using if you can control how do you want */
    int start = 0, at = 0, comma = 0;
    char *pemail = x;

    while (*pemail != '@' && *pemail != '\0' && isalnum(*pemail))
    {
        start++;
        pemail++;
    }
    if (*pemail != '@')
    {
        goto wrong;
    }
    pemail++; /*skips @*/

    while (*pemail != '.' && *pemail != '\0' && isalnum(*pemail))
    {

        at++;
        pemail++;
    }
    if (*pemail != '.')
    {
        goto wrong;
    }
    pemail++; /*skips @*/
    while (*pemail != 0 && isalpha(*pemail))
    {
        if (*pemail == '.')
        {
            pemail++;
            continue;
        }
        comma++;
        pemail++;
    }

wrong:
    /*
    to control email checker.

    */
    if (start >= 3 && at >= 3 && comma >= 3)
    {
        return 1;
    }
    else
    {
        printf("\nWrong email\n");
        return 0;
    }
}
// todo
void addOperation(Account accounts[], int num_accounts)
{
    char OP;
    int i;
    long account_number;
    double user_operation = 0;

    system("clear");
    printf("Enter account Number: ");
    scanf("%ld", &account_number);

    for (i = 0; i < num_accounts; i++)
    {
        if (accounts[i].Acc_number == account_number)
        {
            printf("\nHello %s\n", accounts[i].name);
            printf("\nYour Balance: %.3f", accounts[i].balance);
            printf("\nWhat Operation you want?");
            printf("\n -Deposit [D/d]");
            printf("\n -Withdraw [W/w]");
            printf("\n--> ");
            scanf(" %c", &OP);

            printf("\nOnly put positive values!");

            if (OP == 'D' || OP == 'd')
            { /* Deposit*/
                printf("\nHow much you want to Deposit: ");
                scanf("%lf", &user_operation);

                if (user_operation > 0)
                {
                    accounts[i].balance += user_operation;
                    accounts[i].operations[accounts[i].number_of_operation].amount = user_operation;
                    accounts[i].operations[accounts[i].number_of_operation].type = 'D';
                    accounts[i].number_of_operation++;
                    printf("\nYour new Balance: %.3lf", accounts[i].balance);
                    return;
                }
                else
                {
                    printf("ERROR, Only positive values!");
                }
            }
            else if (OP == 'W' || OP == 'w')
            { /*Withdraw*/
                printf("\nHow much you want to Withdraw: ");
                scanf("%lf", &user_operation);

                if (user_operation > 0)
                {
                    if (accounts[i].balance >= user_operation)
                    {
                        accounts[i].balance -= user_operation;
                        accounts[i].operations[accounts[i].number_of_operation].amount = user_operation;
                        accounts[i].operations[accounts[i].number_of_operation].type = 'W';
                        accounts[i].number_of_operation++;
                        printf("\nYour new Balance: %.3lf", accounts[i].balance);
                        return;
                    }
                    printf("\nSorry, you don't have enough Balance.");
                }
                else
                {
                    printf("ERROR, Invalid input.");
                }
            }
            return; /*Exit after processing*/
        }
    }

    printf("\nAccount not found.");
}

void updateAccount(Account accounts[], int num_accounts)
{
    int i, j;
    long account_number, oldNum;
    char newName[MAX], oldName[MAX]; /*to display old name*/

    system("clear");
    printf("Enter account Number to Update: ");
    scanf("%ld", &account_number);

    for (i = 0; i < num_accounts; i++)
    {
        if (accounts[i].Acc_number == account_number)
        {
            printf("What do you want to change?");
            printf("\n1 -Account Number");
            printf("\n2 -Account Name");
            printf("\n-->");
            scanf("%ld", &account_number);

            if (account_number == 1)
            {
                /*change number*/

                printf("Enter your new Account number: ");
                scanf("%ld", &account_number);
                for (j = 0; j < num_accounts; j++)
                {
                    if (accounts[j].Acc_number == account_number)
                    {
                        printf("Sorry, this number already exist!");
                        return;
                    }
                }
                oldNum = accounts[i].Acc_number;
                accounts[i].Acc_number = account_number;
                printf("Account number %ld is updated to %ld\n", oldNum, accounts[i].Acc_number);
                return;
            }
            else if (account_number == 2)
            {
                /*change name*/

                strcpy(oldName, accounts[i].name);
                printf("Enter a new Name for your Account: ");
                scanf("%s", &newName);
                toUpperCase(newName);
                strcpy(accounts[i].name, newName);
                printf("%s was updated to %s", oldName, newName);
                return;
            }
            else
            {
                printf("Wrong choice!");
                return;
            }
            return;
        }
    }
    printf("Sorry. Account not found!");
}
void deleteAccount(Account accounts[], int *num_accounts, long account_number)
{
    int i, j;

    for (i = 0; i < *num_accounts; i++)
    {
        if (accounts[i].Acc_number == account_number)
        {

            printf("Account -%ld- was deleted successfully.\n", accounts[i].Acc_number);
            accounts[i] = accounts[*num_accounts - 1];

            (*num_accounts)--;
            return;
        }
    }
    printf("DELETE ERROR. Account not found!\n");
}

void search(Account accounts[], int num_accounts)
{

    int i, j = 0;
    long account_number;

    printf("Enter Account Number: ");
    scanf("%ld", &account_number);

    for (i = 0; i < num_accounts; i++)
    {
        if (accounts[i].Acc_number == account_number)
        {

            printf("\nAccount Number: %ld\n", accounts[i].Acc_number);
            printf("Account Name: %s\n", accounts[i].name);
            printf("Account Email: %s\n", accounts[i].email);
            printf("Account Balance: %.3f\n", accounts[i].balance);

            if (accounts[i].number_of_operation)
            {
                printf("Operation Summery:\n");
                for (j = 0; j < accounts[i].number_of_operation; j++)
                {
                    printf("%d--%c[%.3f]\n", j + 1, accounts[i].operations[j].type, accounts[i].operations[j].amount);
                }
            }
            else
            {
                printf("No operations found for this account.");
            }
            return;
        }
    }
    printf("Account not found..");
}

void addAccount(Account accounts[], int *num_account)
{
    Account newAccount;
    long new_account_number, i;

    /*
         email must be at least like ( xxx@xxx.xxx )
    */
    printf("\nEnter your Account number: ");
    scanf("%ld", &new_account_number);

    for (i = 0; i < *num_account; i++)
    {
        if (accounts[i].Acc_number == new_account_number)
        {
            printf("Sorry, this number is not available\n");
            return;
        }
    }
    newAccount.Acc_number = new_account_number;
    getchar();

    printf("Enter your Name: ");
    fgets(newAccount.name, MAX, stdin);
    newAccount.name[strcspn(newAccount.name, "\n")] = '\0';

    if (!isAlphabetic(newAccount.name))
    {
        printf("Error: wrong format.\n");
        return;
    }

    toUpperCase(newAccount.name); /*Convert the name to uppercase*/

    printf("Enter your Email: ");
    fgets(newAccount.email, MAX, stdin);
    newAccount.email[strcspn(newAccount.email, "\n")] = '\0';
    if (!emailCheck(newAccount.email))
    {
        return;
    }

    printf("Enter your Balance: ");
    scanf("%lf", &newAccount.balance);

    newAccount.number_of_operation = 0;
    accounts[*num_account] = newAccount;
    (*num_account)++;
}
void displayAll(Account accounts[], int size)
{
    int i;
    system("clear");

    if (!size)
    {
        printf("There is no accounts.\n");
        return;
    }
    for (i = 0; i < size; i++)
    {
        printf("\n==================================");
        printf("\nAccount Number: %ld\n", accounts[i].Acc_number);
        printf("Account Name: %s\n", accounts[i].name);
        printf("Account Email: %s\n", accounts[i].email);
        printf("Account Balance: %.3f\n", accounts[i].balance);
        printf("Number of operation: %d\n", accounts[i].number_of_operation);
        printf("==================================\n\n");
    }
}

void saveAccounts(Account accounts[], int num_account)
{
    /*Open a file in binary write mode*/
    FILE *file = fopen("Accounts.bin", "wb");
    if (file == NULL)
    {
        perror("Error while opening file");
        return;
    }

    /*Write the number of accounts first*/
    if (fwrite(&num_account, sizeof(int), 1, file) != 1)
    {
        perror("Error writing account count");
        fclose(file);
        return;
    }

    /*Write the accounts array*/
    if (fwrite(accounts, sizeof(Account), num_account, file) != (size_t)num_account)
    {
        perror("Error writing accounts");
        fclose(file);
        return;
    }

    fclose(file);
    printf("\nData was written to Binary file successfully.\n");
}

int loadAccounts(Account accounts[])
{
    /*Open a file in binary read mode*/
    FILE *file = fopen("Accounts.bin", "rb");
    if (file == NULL)
    {
        printf("No previous account data found. Starting with an empty list.\n");
        return 0; /*No accounts loaded*/
    }

    /* Check if the file is empty*/
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == 0)
    {
        printf("The file is empty. Starting with an empty list of accounts.\n");
        fclose(file);
        return 0; /* No accounts loaded*/
    }
    rewind(file);

    int num_account = 0;

    /*Read the number of accounts*/
    if (fread(&num_account, sizeof(int), 1, file) != 1)
    {
        perror("Error reading account count");
        fclose(file);
        return 0;
    }

    /*Read the accounts array*/
    if (fread(accounts, sizeof(Account), num_account, file) != (size_t)num_account)
    {
        perror("Error reading accounts");
        fclose(file);
        return 0;
    }

    fclose(file);
    printf("%d accounts loaded successfully.\n", num_account);
    return num_account;
}

void menu()
{

    printf("====Hello to BEST BANK====\n");
    printf("1 -Add Account\n");
    printf("2 -Update Account\n");
    printf("3 -Delete Account\n");
    printf("4 -Delete Holder Accounts\n");
    printf("5 -Search Account\n");
    printf("6 -Display All Accounts\n");
    printf("7 -Add Operation\n");
    printf("8 -Exit\n");
}