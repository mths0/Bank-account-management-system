#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char type;
    double amount;
}Operation;

typedef struct{
    char name[50];
    char email[50];
    long Acc_number;
    double  balance;
    int number_of_operation;
    Operation operations[50];
}Account;

void menu();
int main(){

    Account user1 = {"Mohannad", "mhn@f.com",11241,2000};

    printf("%s ,%s, %ld, %.2f",user1.name,user1.email,user1.Acc_number,user1.balance);
   
    return 0;
}
void menu(){
    printf("\n====Hello to BEST BANK====\n");
    printf("1 -Add Account\n");
    printf("2 -Update Account\n");
    printf("3 -Delete Account\n");
    printf("4 -Delete Holder Accounts\n");
    printf("5 -Search Account\n");
    printf("6 -Display All Accounts\n");
    printf("7 -Add Operation\n");
}