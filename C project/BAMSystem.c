#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char type; /*d for deposit and w for withdraw*/
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
void addAccount(Account account[], int* num_account);
void displayAll(Account accounts[], int size);
int loadAccounts(Account accounts[100]);/*load all data to an array */
void saveAccounts(Account account[], int num_account);


int main(){
    Account accounts[100];
    int choice, num_of_accounts = loadAccounts(accounts);

    do{ 
        menu();
        scanf("%d",&choice);

        if (choice == 1)
        {
            addAccount(accounts,&num_of_accounts);
            saveAccounts(accounts,num_of_accounts);
        }
        else if(choice == 2){
            displayAll(accounts,num_of_accounts);
        }else if(choice == 3){
            displayAll(accounts,num_of_accounts);
        }else if(choice == 4){
            displayAll(accounts,num_of_accounts);
        }else if(choice == 5){
            displayAll(accounts,num_of_accounts);
        }else if(choice == 6){
            displayAll(accounts,num_of_accounts);
        }else if(choice == 7){
            displayAll(accounts,num_of_accounts);
            
        }else if(choice == 8){
            system("clear");
            printf("==========================================================\n");
            printf("===========Thank you for Banking With BEST BANK===========\n");
            printf("==========================================================\n");

            
        }else{
            printf("\nInvalid choice");

        }
        

    printf("\n\n");
    }while(choice != 8);


    return 0;
}
void addAccount(Account accounts[], int* num_account){

    Account newAccount;

    printf("\nEnter your Account number: ");
    scanf("%d",&newAccount.Acc_number);
    getchar();

    printf("\nEnter your Name: ");
    scanf("%s",&newAccount.name);

    printf("\nEnter your Email: ");
    scanf("%s",&newAccount.email);

    printf("\nEnter your Balance: ");
    scanf("%f",&newAccount.balance);

    newAccount.number_of_operation= 0;
    accounts[*num_account] = newAccount;
    (*num_account)++;

}
void displayAll(Account accounts[], int size){
    system("clear");
    int i;
    
    if(!size){
        printf("There is no accounts.\n");
        return;
    }
    for(i = 0; i<size; i++){
        printf("\nAccount Number: %ld\n",accounts[i].Acc_number);
        printf("Account Name: %s\n",accounts[i].name);
        printf("Account Email: %s\n",accounts[i].email);
        printf("Account Balance: %ld\n",accounts[i].balance);
    }
    

}

void saveAccounts(Account accounts[], int num_account){

      // Open a file in binary write mode
    FILE* file = fopen("Accounts.bin", "wb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    // Write the data to the file
    size_t num_written
        = fwrite(&accounts, sizeof(Account), 1, file);
    if (num_written != 1) {
        perror("Error writing to file");
        fclose(file);
        return;
    }
    // Close the file
    fclose(file);
    printf("Struct data written to Binary file "
           "successfully.\n");
}

int loadAccounts(Account accounts[]){

 FILE* file = fopen("Accounts.bin","rb");
    if(file == NULL){
        perror("Error opening file");
        return 1;
    }
    int count = fread(&accounts , sizeof(Account), 1, file);
    return count; /*number of accounts loaded.*/
    fclose(file);

}
   
void menu(){
    // system("clear");
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