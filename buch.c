#include <stdio.h>
#include <string.h>
#define MAX 61
int main()
{
   char string[MAX];
   int c = 0, count[26] = {0}, x,j=0;
   int k;
   fgets(string,MAX,stdin);

   while (string[c] != '\0') {

      if (string[c] >= 'A' && string[c] <= 'Z') {
         x = string[c] - 'A';
         count[x]++;
         
      }

      c++;
   }
   for(k=0;string[k]!='\n';k++)
   {
       if((string[k]='A') || (string[k]='E') || (string[k]='I') || (string[k]='O') || (string[k]='U'))
         {j++;}
         k++;
   }

   for (c = 0; c < 26; c++)
         printf("%c : %d\n " , c + 'A', count[c]);
         printf("\nDas Wort enthaelt %d Vokale.",j);

   return 0;
}