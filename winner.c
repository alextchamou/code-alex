#include<stdio.h>
#define MAX 61
int main()
{
int i,j=0,k=0;
char eingabe[MAX];
fgets(eingabe,MAX,stdin);
   for(i=0;eingabe[i]!='\0';i++)
   {
       if(eingabe[i]=='a')
       j+=1;
       else if(eingabe[i]=='b')
       k+=1;
       
   }
   if(j>k)
       printf("Alice");
       else if(j<k)
       printf("Bob");
       else if(j==k)
       printf("Gleichstand");
   
}