#include<stdio.h>
int main (void)
{
    int x, y, z, m ;
    scanf("%d",&x);
    scanf("%d",&y);
    scanf("%d",&z);
    if (x>y)
       m=x;
       else
       m=y;
       if(z>m)
       m=z;
       printf("%d\n",m);
       return 0;
}