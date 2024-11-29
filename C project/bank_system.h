#ifndef Bank_SYSTEM_h
#define Bank_SYSTEM_h

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

void menu(void);
void addAccount(Account account[], int *num_account);
void displayAll(Account accounts[], int size);
int loadAccounts(Account accounts[100]); /*load all data to an array */
void saveAccounts(Account account[], int num_account);
int isAccount(Account accounts[], int num_accounts, int account_number);
void search(Account accounts[], int num_accounts);
void deleteAccount(Account accounts[], int *num_accounts, long account_number);
void updateAccount(Account accounts[], int num_accounts);
void deleteHolerAccounts(Account accounts[], int *num_accounts);
void printOperation(Account accounts[], int num_accounts);
void addOperation(Account accounts[], int num_accounts);
int emailCheck(char x[]); /* i will use this in addAccount*/
int isAlphabetic(const char *name);
void toUpperCase(char *name);
int isSameString(const char x[], const char y[]);

#endif 