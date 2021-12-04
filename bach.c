#include<stdio.h>
#define N 65
#define LETTERS 26
int main(void)
{
char eingabe[N];
int k,j=0;
fgets(eingabe,N,stdin);
 
 int alphabet [LETTERS];
 
 for (int i=0; i < LETTERS; i++)
 {
       alphabet [i] =0;
 }
 char* c = eingabe;
 
 while (*c != '\0')
 {
       alphabet [*c - 'A'] = alphabet [ *c - 'A'] + 1;
       c++;
 }
  for(k=0;eingabe[k]!='\n';k++)
   {
       if((eingabe[k]='A') || (eingabe[k]='E') || (eingabe[k]='I') || (eingabe[k]='O') || (eingabe[k]='U'))
         {j++;}
         k++;
   }
 for (int i =0; i < LETTERS;i++)
     printf ("%c: %d\n",i+ 'A',alphabet [i]);
     printf("\nDas Wort enthaelt %d Vokale.",j);
 
 
 return 0;
}