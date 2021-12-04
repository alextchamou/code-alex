#include<stdio.h>
int main(void)
{
    int gesamt=0;
    int st,rest,min,sec =0;
//st :stunden, rest ,min: minuten ,sec: sekunden 
st=gesamt%3600;
rest=gesamt-(st*3600);
min=rest%60 ;
st=rest-(min*60);
if(sec>=0 && min<=59)
printf("%d Stunde(n) %d Minute(n) %d Sekunde(n)",st,min,sec);
return 0;
}