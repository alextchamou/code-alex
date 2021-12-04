#include <stdio.h>
#include <string.h>
#define MAX 61
int main()
{
   char string[MAX];
   int c = 0, count[26] = {0}, x;
   int k;
   int a=0,e=0,i=0,o=0,u=0;
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
   if(string[k]=='A')
   a+=1;
   else if(string[k]=='E')
   e+=1;
   else if(string[k]=='I')
   i+=1;
   else if(string[k]=='O')
   o+=1;
   else if (string[k]=='U')
   u+=1;
   
}
   for (c = 0; c < 26; c++)
         printf("%c : %d\n " , c + 'A', count[c]);
         printf("\nDas Wort enthaelt %d Vokale.",a+e+i+o+u);

   return 0;
}