#include<stdio.h>
#define MAX 61
int main()
{
char eingabe[MAX];
int n=0,i;
fgets(eingabe,MAX,stdin);
for(i=0;eingabe[i]!='\0';i++)
n+=1;
printf("Der String \"%s\" ist %d Zeichen lang.",eingabe,n);
}