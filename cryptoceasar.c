// Simple C Program to encrypt and decrypt a string 
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int i , x ;
    char str[100];//str variable wo die zeichenkette gespeichert wird
    printf("\nGeben Sie eine Zeichenkette ein: \t");
    fgets(str,100,stdin);
    printf("\nBitte waehlen Sie eine Option aus:\n");
    printf("1:Encrypt the string.\n");
    printf("2:Decrypt the string.\n : ");
    scanf("%d",&x);
    //using switch case statements 
    switch(x)
    {
        case 1:
        for(i=0;(i<100 && str[i]!='\0');i++)
        str[i]=str[i]+3; // they key for encryption is 3 that is added to ASCII value
        printf("\nEncrypted String: %s \n",str);
        break ;
        case 2:
        for(i=0;(i<100 && str[i]!='\0');i++)
        str[i]=str[i]-3;// they key for encryption is 3 that is substracted to ASCII value 
        printf("\nDecrypted String: %s\n",str);
        break ;
        default:
        printf("\nError\n");
    }
    return 0;
}