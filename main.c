#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ACCOUNT_NUM 1000
#define NAME_LEN 15
#define ACCOUNT_NUM_LEN 7
#define FILE_LEN 20

struct bank_account
{
    char owner_first_name[NAME_LEN], owner_last_name[NAME_LEN], account_num[ACCOUNT_NUM_LEN];
    int  balance;

};
typedef struct bank_account Account;


void searchAccount(Account account_reg[],char account_num[], int *nrOfAccounts);


void sortBalance(Account agentesArr[], int *nrOfAccounts);
void sortAccounts(Account agentesArr[], int *nrOfAccounts);
void readFromFile(Account account_reg[],int *nrOfAccounts, char accountFile[]);
void makeFile(Account account_reg[],int *nrOfAccounts, char accountFile[]);
void reg_new_acc(Account account_reg[], int *nrOfAccounts);
Account create_user(char owner_first_name[], char owner_last_name[], char account_num[]);
void accountManagement(Account account_reg[],int *nrOfAccounts);
void print_account(Account account_reg[], int *pNrOfAccounts);
int checkAccountNum(Account account_reg[],char account_num[], int *nrOfAccounts);
void sortLastNames(Account agentesArr[], int *nrOfAccounts);
void increaseBalance(Account account_reg[], char accountNum[],int  amount, int *nrOfAccounts);
void decreaseBalance(Account account_reg[], char accountNum[], int  amount, int *nrOfAccounts);
void moveBalance(Account account_reg[],char account_num[],char account_num2[],int balance,int *nrOfAccounts);

//void sub_menu(Account account_reg[],  int nrOfAccounts);
//void sort(char *string[], int nrOfAccounts, int str_len);
//void swap(Account xp,Account yp);
//void bubbleSort_desc(Account account_reg[], int nrOfAccounts);

int main(void)
{
    Account account_reg[MAX_ACCOUNT_NUM];
    int nrOfAccounts = 0;
    char accountFile[FILE_LEN];
    //readFromFile(account_reg, &nrOfAccounts, accountFile);
    accountManagement(account_reg, &nrOfAccounts);


    return 0;
}

void readFromFile(Account account_reg[],int *nrOfAccounts, char accountFile[])
{   int i;
    printf("Add file: ");
    scanf("%s%*c", accountFile);
    FILE *fp;
    fp=fopen(accountFile,"r");
    if(fp!=NULL)
    {
        fscanf(fp,"%d\n", nrOfAccounts);

        for(i = 0; i < (*nrOfAccounts); i++)
        {

            fscanf(fp,"%s", account_reg[i].owner_first_name);
            fscanf(fp,"%s", account_reg[i].owner_last_name);
            fscanf(fp,"%s", account_reg[i].account_num);
            fscanf(fp,"%d", &account_reg[i].balance);
        }
        fclose(fp);
    } else { printf("Kunde inte oppna filen!\n"); }

}

void makeFile(Account account_reg[],int *nrOfAccounts, char accountFile[])
{
    FILE *fp;
    fp=fopen(accountFile,"w");
    if(fp!=NULL)
    {
        fprintf(fp,"%d\n", (*nrOfAccounts));    //NECCESSARY???

        for(int i = 0; i < (*nrOfAccounts); i++)
        {

            fprintf(fp,"%s", account_reg[i].owner_first_name);
            fprintf(fp,"%s", account_reg[i].owner_last_name);
            fprintf(fp,"%s", account_reg[i].account_num);
            fprintf(fp,"%d", account_reg[i].balance);
        }
        fclose(fp);
    } else { printf("Kunde inte oppna filen!\n"); }
}


void accountManagement(Account account_reg[],int *nrOfAccounts)
{
    int choice = 0;

    do
    {
        printf("(1) Register New User\n(2) Print All Users\n(3) Sort Using ID \n(4) Sort Using Last Names\n");
        printf("(5) Sort Using Balance\n(6) Increase Balance\n(7) Deposit \n(8) Move Balance \n(9) Quit");
        printf("\n\nEnter Number: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:

                reg_new_acc(account_reg, nrOfAccounts);
                break;

            case 2:
                print_account(account_reg, nrOfAccounts);
                break;
            case 3:
                //bubbleSort_desc(account_reg[], nrOfAccounts);
                sortAccounts(account_reg,nrOfAccounts);
                break;

            case 4:
                printf("Sorting Using Last Names:\n");
                sortLastNames(account_reg,nrOfAccounts);
                break;

            case 5:

                printf("Sorting Balance\n");
                sortBalance(account_reg,nrOfAccounts);
                break;

            case 6:

                printf("Please Enter the Account Number:\n");
                char accountNumber21[ACCOUNT_NUM_LEN];
                scanf("%s", accountNumber21);

                printf("Please Enter the Amount:\n");
                int amount=0;
                scanf("%d", &amount);
                increaseBalance(account_reg, accountNumber21,amount, nrOfAccounts);
                break;

            case 7:

                printf("Please Enter the Account Number:\n");
                char accountNumber22[ACCOUNT_NUM_LEN];
                scanf("%126s", accountNumber22);

                printf("Please Enter the Amount:\n");
                int amount1=0;
                scanf("%d", &amount1);
                decreaseBalance(account_reg, accountNumber22,amount1, nrOfAccounts);
                break;

            case 8:

                printf("Please Enter the First Account Number:\n");
                char accountNumber25[ACCOUNT_NUM_LEN];
                scanf("%s", accountNumber25);

                printf("Please Enter the Second Account Number:\n");
                char accountNumber26[ACCOUNT_NUM_LEN];
                scanf("%s", accountNumber26);

                printf("Please Enter the Amount:\n");
                int amount5=0;
                scanf("%d", &amount5);
                moveBalance(account_reg, accountNumber25, accountNumber26, amount5, nrOfAccounts);
                break;

            case 9:
                printf("Goodbye!\n");
                break;

        }

    } while ( choice != 9);
}

void reg_new_acc(Account account_reg[], int *nrOfAccounts)
{

    char owner_first_name[NAME_LEN], owner_last_name[NAME_LEN], account_num[ACCOUNT_NUM_LEN];

    while (*nrOfAccounts < MAX_ACCOUNT_NUM)
    {

        printf("\nRegistering User ...\n");
        printf("Please Enter (6-dig) ID (q for for quitting): ");
        scanf("%s%*c", account_num);
        account_num[6]='\0';

        if (strcmp(account_num, "q") == 0)
        {
            printf("Avslutar\n");
            return ;
        }

        while(checkAccountNum(account_reg, account_num, nrOfAccounts)==0)
        {



            printf("Kontonummer finns redan\n");
            printf("Please Enter Again: ");
            scanf("%s%*c", account_num);
            account_num[6]='\0';

        }

        printf("Enter Full Name: ");
        scanf(" %s",owner_first_name);
        scanf(" %s", owner_last_name);


        account_reg[*nrOfAccounts] = create_user(owner_first_name, owner_last_name, account_num);
        (*nrOfAccounts)++;



    }

}

int checkAccountNum(Account account_reg[],char account_num[], int *nrOfAccounts)
{

    if(strcmp(account_num, "q") == 0)
    {

        accountManagement(account_reg , nrOfAccounts);

    }

    for(int i = 0; i < *nrOfAccounts; i++)
    {
        if(strcmp(account_num,account_reg[i].account_num) == 0)
        {
            return 0;
        }
    }

    return 1;
}

void searchAccount(Account account_reg[],char account_num[], int *nrOfAccounts)
{
    for(int i = 0; i < *nrOfAccounts; i++)
    {
        if(strcmp(account_num,account_reg[i].account_num) == 0)
        {
            printf("%s\t\t%s\t%s\t\t%d\n\n", account_reg[i].account_num, account_reg[i].owner_first_name, account_reg[i].owner_last_name, account_reg[i].balance);
        }
    }
}

void moveBalance(Account account_reg[],char account_num[],char account_num2[],int balance,int *nrOfAccounts)
{
            decreaseBalance(account_reg, account_num, balance, nrOfAccounts);
            increaseBalance(account_reg, account_num2, balance, nrOfAccounts);

}
void increaseBalance(Account account_reg[], char accountNum[], int  amount, int *nrOfAccounts)
{


    for(int i = 0; i < *nrOfAccounts; i++)
    {
        if(strcmp(accountNum,account_reg[i].account_num) == 0)
        {

            account_reg[i].balance+=amount;
        }
    }


}



void decreaseBalance(Account account_reg[], char accountNum[], int  amount, int *nrOfAccounts)
{

    for(int i = 0; i < *nrOfAccounts; i++)
    {
        if(strcmp(accountNum,account_reg[i].account_num) == 0)
        {
            if(account_reg[i].balance-amount>=0){

                account_reg[i].balance-=amount;
            } else{
                printf("Can't Deposit\n");
            }
        }
    }

}




Account create_user(char owner_first_name[], char owner_last_name[], char account_num[])
{
    Account account;
    strcpy(account.account_num, account_num);
    strcpy(account.owner_first_name, owner_first_name);
    strcpy(account.owner_last_name, owner_last_name);
    account.balance=0;
    return account;
}

void print_account(Account account_reg[], int *pNrOfAccounts)
{
    int i;
    printf("\nAll Accounts\n");
    printf("ID\tFull-Name\t\tBalance\n");
    printf("____________________________________________\n");
    for(i = 0; i < *pNrOfAccounts; i++)
    {
        printf("%s\t\t%s\t%s\t\t%d\n\n", account_reg[i].account_num, account_reg[i].owner_first_name, account_reg[i].owner_last_name, account_reg[i].balance);
    }
}


void sortAccounts(Account agentesArr[], int *nrOfAccounts) {
    Account temp;

    for(int i = 0; i < *nrOfAccounts ; i++) {
        for(int j=0; j < *nrOfAccounts-i-1 ; j++){
            int comp = strcmp(agentesArr[j].account_num, agentesArr[j+1].account_num);
            printf("%d\t",comp);
            if(comp > 0) {


                temp = agentesArr[j];
                agentesArr[j] = agentesArr[j+1];
                agentesArr[j+1] = temp;
            }
        }
    }

}

void sortLastNames(Account agentesArr[], int *nrOfAccounts) {
    Account temp;

    for(int i = 0; i < *nrOfAccounts ; i++) {
        for(int j=0; j < *nrOfAccounts-i-1 ; j++){
            int comp = strcmp(agentesArr[j].owner_last_name, agentesArr[j+1].owner_last_name);
            printf("%d\t",comp);
            if(comp > 0) {


                temp = agentesArr[j];
                agentesArr[j] = agentesArr[j+1];
                agentesArr[j+1] = temp;
            }
        }
    }

}



void sortBalance(Account agentesArr[], int *nrOfAccounts) {
    Account temp;
    printf("In Accouny");
    for(int i = 0; i < *nrOfAccounts ; i++) {
        for(int j=0; j < *nrOfAccounts-i-1 ; j++){
            if(agentesArr[j].balance < agentesArr[j+1].balance){

                temp = agentesArr[j];
                agentesArr[j] = agentesArr[j+1];
                agentesArr[j+1] = temp;;

            }
        }
    }

}







