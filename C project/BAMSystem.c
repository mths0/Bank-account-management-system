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
int loadAccounts(Account accounts[100]);/*load all data to an array */
int addAccounts(Account account, int num_account);


int main(){
    Account accounts[100];
    int num_of_accounts = loadAccounts(accounts);

    Account user1 = {"Mohannad", "mhn@f.com",11241,2000};

  

    
   


           
    return 0;
}

int addAccounts(Account account, int num_account){

      // Open a file in binary write mode
    FILE* file = fopen("Accounts.bin", "wb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write the data to the file
    size_t num_written
        = fwrite(&account, sizeof(Account), 1, file);
    if (num_written != 1) {
        perror("Error writing to file");
        fclose(file);
        return 1;
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
    printf("\n====Hello to BEST BANK====\n");
    printf("1 -Add Account\n");
    printf("2 -Update Account\n");
    printf("3 -Delete Account\n");
    printf("4 -Delete Holder Accounts\n");
    printf("5 -Search Account\n");
    printf("6 -Display All Accounts\n");
    printf("7 -Add Operation\n");
}