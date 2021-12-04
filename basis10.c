#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX 20
int main (void)
{
    char eingabe[MAX+1];
    fgets(eingabe,21,stdin);
    
    int i,s, j,n;
    int sum=0;
    s=strlen(eingabe)-1;
    for(i=0,j=s-1;i<s;i++,j--)
    {
        if(eingabe[i]=='Z')
            n=2 ;
            else if(eingabe[i]=='Y')
                n=1;
                else if(eingabe[i]=='X')
                n=0;
        sum+=n*pow(3,j);
    }
    printf("In Basis 10: %d",sum);
    return 0;
}