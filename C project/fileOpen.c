#include <stdio.h>
/*this */
int main(){


    FILE* ptrf;

    ptrf = fopen("newfile.txt","r");

    char text[10000];
    if(ptrf != NULL){
        
        while(fgets(text,1000,ptrf)){

            printf("%s",text);
        }
    }

    
    fclose(ptrf);
    return 0;
}