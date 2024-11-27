#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
typedef struct{
    char type; /*d for deposit and w for withdraw*/
    double amount;
}Operation;

typedef struct{
    char name[MAX];
    char email[MAX];
    long Acc_number;
    double  balance;
    int number_of_operation;
    Operation operations[MAX];
}Account;

void menu();
void addAccount(Account account[], int* num_account);
void displayAll(Account accounts[], int size);
int loadAccounts(Account accounts[100]);/*load all data to an array */
void saveAccounts(Account account[], int num_account);
int isAccount(Account accounts[],int num_accounts, int account_number);
void search(Account accounts[], int num_accounts);
void deleteAccount(Account accounts[], int *num_accounts);
void updateAccount(Account accounts[], int num_accounts);
void toUpper();
void deleteHolerAccounts(Account accounts[], int *num_accounts);
//todo 
void printOperation(Account accounts[], int num_accounts);
void addOperation(Account accounts[], int num_accounts);

int main(){
    Account accounts[100];
    int choice, num_of_accounts = loadAccounts(accounts);

    do{ 
        menu();
        scanf("%d",&choice);

        if (choice == 1)
        {
            system("clear");
            addAccount(accounts,&num_of_accounts);
            saveAccounts(accounts,num_of_accounts);
        }
        else if(choice == 2){
            updateAccount(accounts,  num_of_accounts);
            saveAccounts(accounts, num_of_accounts);
        }else if(choice == 3){
            deleteAccount(accounts,&num_of_accounts);
            saveAccounts(accounts,num_of_accounts);
            
        }else if(choice == 4){
            //deleteHolerAccounts(accounts, &num_of_accounts);
            saveAccounts(accounts,num_of_accounts);
        }else if(choice == 5){
            
            system("clear");
            search(accounts,num_of_accounts);
           
        }else if(choice == 6){
            displayAll(accounts,num_of_accounts);
        }else if(choice == 7){           
        addOperation(accounts, num_of_accounts);
        saveAccounts(accounts,num_of_accounts);


            
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
//todo 
void addOperation(Account accounts[], int num_accounts){
    char OP;
    int i ,j;
    long account_number;
    double user_operation;

    system("clear");
    printf("Enter account Number: ");
    scanf("%ld", &account_number);

    for(i = 0; i< num_accounts; i++){
        if(accounts[i].Acc_number == account_number)
            printf("\nHello %s\n",accounts[i].name);
            printf("\nYour Balance: %.3f", accounts[i].balance);
            printf("\nWhat Operation you want?");
            printf("\n -Deposit [D/d]");
            printf("\n -Withdraw[W/w]");
            printf("\n--> ");
            scanf("%s", &OP);
            printf("\nOnly put positive values!");

            //! fix
            if(OP == 100 || OP == 68){/*deposit*/
                printf("\nHow much you want to Deposit: ");
                scanf("%lf",&user_operation);

                if(user_operation > 0){
                        accounts[i].balance += user_operation;
                          /*to put amount ant type of operation at the end*/
                        accounts[i].operations[accounts[i].number_of_operation].amount 
                        = user_operation;
                        accounts[i].operations[accounts[i].number_of_operation].type
                         = 'D';
                        accounts[i].number_of_operation++;
                        printf("\nYour new Balance: %.3lf", accounts[i].balance);
                        return;
                }else{ printf("ERROR, Only positive values!");}

            }else if(OP == 119 || OP == 87){/*withdraw*/
                printf("\nHow much you want to Withdraw: ");
                scanf("%lf",&user_operation);
            if(user_operation > 0){
                        if(accounts[i].balance >= user_operation){
                        accounts[i].balance -= user_operation;
                        /*to put amount ant type of operation at the end*/
                        accounts[i].operations[accounts[i].number_of_operation].amount 
                        = user_operation;
                        accounts[i].operations[accounts[i].number_of_operation].type
                         = 'W';
                        accounts[i].number_of_operation++;
                        printf("\nYour new Balance: %.3lf", accounts[i].balance);
                        return;
                        }
                        printf("\nSorry, you don't have enough Balance.");
                        return;
                }else{ printf("ERROR, Only positive values!");}
            }
    }
}
void updateAccount(Account accounts[], int num_accounts){
    int i,j;
    long account_number;
    char newName[MAX];
    
    system("clear");
    printf("Enter account Number to Update: ");
    scanf("%ld", &account_number);

    for(i = 0; i< num_accounts; i++){
        if(accounts[i].Acc_number == account_number){
            printf("What do you want to change?");
            printf("\n1 -Account Number");
            printf("\n2 -Account Name");
            printf("\n-->");
            scanf("%ld",&account_number);

            if(account_number == 1){
                //change number
                printf("Enter your new Account number: ");
                scanf("%ld", &account_number);
                for(j = 0; j< num_accounts; j++){
                    if(accounts[j].Acc_number == account_number){
                        printf("Sorry, this number already exist!");
                        return;
                    }
                }
                accounts[i].Acc_number = account_number;
                return;


            }else if(account_number == 2){
                //change name
                //todo should convert every name to UPPER before save.
                printf("Enter a new Name for your Account: ");
                scanf("%s",&newName);
                strcpy(accounts[i].name, newName);
                return;
            }else{
                printf("Wrong choice!");
                return;
            }  
            return;
        }
    }printf("Sorry. Account not found!");
}
void deleteAccount(Account accounts[], int *num_accounts){
    int i , j;
    long account_number;
    Account tempAcc;

    system("clear");
    printf("Enter account Number to Delete: ");
    scanf("%ld", &account_number);

    for(i = 0; i<*num_accounts; i++){
        if(accounts[i].Acc_number == account_number){
          
                accounts[i] = accounts[*num_accounts-1];
                printf("Account was deleted!\n");
            
            (*num_accounts)--;
            return;
        }
    }printf("Sorry. Account not found!");
}

void search(Account accounts[], int num_accounts){
    
    int i,j=0;
    long account_number;

    printf("Enter Account Number: ");
    scanf("%ld", &account_number);
    
    for(i = 0; i<num_accounts; i++){ 
        if(accounts[i].Acc_number == account_number){
               
        printf("\nAccount Number: %ld\n",accounts[i].Acc_number);
        printf("Account Name: %s\n",accounts[i].name);
        printf("Account Email: %s\n",accounts[i].email);
        printf("Account Balance: %.3f\n",accounts[i].balance);
        printf("Number of operation: %d\n",accounts[i].number_of_operation);
        printf("Operation Summery:\n");
        for(j = 0; j< accounts[i].number_of_operation ;j++){  
            printf("%d--%c[%.3f]\n",j+1,accounts[i].operations[j].type
            ,accounts[i].operations[j].amount);
            
        }
        return;
        }

    }printf("Account not found..");
    

}
//! no need for it.
int isAccount(Account accounts[],int num_accounts, int account_number){
    /*
    will return 1 if account number is found. else 0.
    need to take input from main 
     */
    int i;
  
    for(i = 0; i< num_accounts; i++){
        if(accounts[i].Acc_number == account_number){
          return 1 ;
        }
    }
    /*will print this when no account was found*/
    // printf("\nSorry, There is no account with this Number");
    return 0 ;

}

//todo
void addAccount(Account accounts[], int* num_account){
    Account newAccount;
    long new_account_number, i;
    //Todo
    /* must put condion for account number 
        todo and email must be like ( xxx@xxx.xxx )
    */ 
    printf("\nEnter your Account number: ");
    scanf("%ld",&new_account_number);

    for(i = 0; i< *num_account; i++){
    if(accounts[i].Acc_number == new_account_number){
        printf("Sorry, this number is not available\n");
        return;
    }}
    newAccount.Acc_number = new_account_number;
    getchar();

    printf("Enter your Name: ");
    scanf("%s",&newAccount.name);

    printf("Enter your Email: ");
    scanf("%s",&newAccount.email);

    printf("Enter your Balance: ");
    scanf("%lf",&newAccount.balance);
    

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
        printf("Account Balance: %.3f\n",accounts[i].balance);
        printf("Number of operation: %d\n\n",accounts[i].number_of_operation);
    }
    

}

void saveAccounts(Account accounts[], int num_account){

      // Open a file in binary write mode
    FILE* file = fopen("Accounts.bin", "wb");
    if (file == NULL) {
        perror("Error while opening file");
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
    printf("data was written to Binary file "
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