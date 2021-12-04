#include<stdio.h>
int main ()
{
    int a,b ;
    scanf("%d %d",&a,&b);
    while (a!=b)
    {
        if (a<b)
    b=b-a ;
        else
    a=a-b ;
    }
    printf(" %d \n",a);   
return 0;
} 