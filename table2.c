#include<stdio.h>
int main ()
{
    int lv=1 ;
    printf("die ersten zehn Quadratzahlen sind :");
    while(lv<=10)
    {
        printf("%d ",lv*lv);
        lv=lv+1 ;
    }
    return 0;
}