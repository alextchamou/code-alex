#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct user user;
struct user {
    char phone[50];
    char ac[50];
    char password[50];
    float balance;
};
 int main()
{
 user usr,usr1; 
 FILE *fp;
 char filename[50],phone[50],pword[50];
 char cont='y';
 int opt,choice;
 float amount ;
 printf("\n\nwhat do you want to do ?");
 printf("\n\n1. Register an account");
 printf("\n2. Login to account");
 printf("\n\n Your choice : \t");
 scanf("%d",&opt);
 if (opt==1)
 {
     system("clear");
     printf("Enter your account number: \t");
     scanf("%s",usr.ac);
     printf("Enter your phone number: \t");
     scanf("%s",usr.phone);
     printf("Enter your password:\t");
     scanf("%s",usr.password);
    usr.balance=0;
    strcpy(filename,usr.phone);
    fp=fopen(strcat(filename,".dat"),"w");
    fwrite(&usr,sizeof(user),1,fp);
    if(&fwrite != 0)
        printf("\n\nAccount succesfully registred");
    else
    printf("something went wrong please try again");
    fclose(fp);
 }
 if(opt== 2){
     system("clear");
     printf("phone number: ");
     scanf("%s",phone);
     printf("Password: \t");
     scanf("%s",pword);
     strcpy(filename,phone);
     fp=fopen(strcat(filename,".dat"),"r");
     if(fp==NULL)// si le pointeur est null cela voudrait dire qu il ne trouve aucun fichier correspondant a ce nom
     printf("\nAccount number not registrered");
     else{
     fread(&usr,sizeof(user),1,fp);
     fclose(fp);
     if(!strcmp(pword,usr.password))
     //strcmp renvoi 0 si les chaines sont equal la negation! c est pour que ca soit vrai
     {
     printf("\n\twelcome %s",usr.phone);
        while(cont=='y')
     {
         system("clear");
         printf("\n\nPress 1 for balance inquiry");
         printf("\nPress 2 for depositing cash");
         printf("\nPress 3 for cash withdraw");
         printf("\nPress 4 for online transfer  ");
         printf("\nPress 5 for password change");
         printf("\nYour choice: \t");
         scanf("%d",&choice);
         switch(choice)
         {
             case 1: 
             printf("\nYour current balance is %.2f Euro",usr.balance);
             break ;
             case 2:
             printf("\nEnter the amount: \t");
             scanf("%f",&amount);
             usr.balance+= amount ;
             fp=fopen(filename,"w");
             fwrite(&usr,sizeof(user),1,fp);
             if(&fwrite != NULL)
             printf("\nsuccesfully deposited.");
             fclose(fp);
             break;
             case 3:
             printf("\nEnter the amount: \t");
             scanf("%f",&amount);
             usr.balance -= amount ;
             fp=fopen(filename,"w");
             fwrite(&usr,sizeof(user),1,fp);
             if(&fwrite != NULL)
             printf("\nyou have withdrawn %.2f Euro",amount);
             fclose(fp);
             break;
             case 4:
             printf("\nPlease Enter the phone number to transfer the balance : \t");
             scanf("%s",phone);
             printf("\nPlease enter the amount to tranfer: \t");
             scanf("%f",&amount);
             strcpy(filename,phone);
             if(amount>usr.balance)
             printf("\nInsufficient balance");
             else{
                 
                 fp=fopen(strcat(filename,".dat"),"w"); 
                 if(fp==NULL)
                 printf("\nAccount  number not registred");
                 else{
                 fread(&usr1,sizeof(user),1,fp);
                 fclose(fp);
                 fp=fopen(filename,"w");
                 usr1.balance += amount;
                 fwrite(&usr1,sizeof(user),1,fp);
                 fclose(fp);
                 if(&fwrite!=NULL)
                 printf("\nYou have succesfully transfered %.2f Euro to %s",amount,phone);
                 strcpy(filename,usr.phone);
                 fp=fopen(strcat(filename,".dat"),"w");
                 usr.balance -= amount;
                 fwrite(&usr,sizeof(user),1,fp);
                 fclose(fp);
                 }
                 
             }
             break;
             case 5:
             printf("\nPlease enter a new password:\t");
             scanf("%s",pword);
             fp=fopen(filename,"w");
             strcpy(usr.password,pword);
             fwrite(&usr,sizeof(user),1,fp);
             if(&fwrite!=NULL)
             printf("\nPassword succesfully changed");
             break;
             default:
             printf("\nInvalid option");

         }
        printf("\nDo you want to continue the transaction [y/n] ");
        scanf("%s",&cont);

     }
    
     
    
     }
     }
return 0;
 }
}
