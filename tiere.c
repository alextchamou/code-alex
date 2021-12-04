#include <stdio.h>
int main(void)
{
  int a, b;
  int c, d;
  int x, y;

  printf("Anzahl Beine von Tier 1: ");
  scanf("%d", &a);
  printf("\nAnzahl Beine von Tier 2: ");
  scanf("%d", &b);
  printf("\nGesamtzahl aller Beine: ");
  scanf("%d", &c);
  printf("\nGesamtzahl aller Köpfe: ");
  scanf("%d", &d);

  x = d- (c-a*d)/(b-a); // TODO
  y = (c-a*d)/(b-a); // TODO

  printf("\n%d %d-Beiner und %d %d-Beiner haben zusammen %d Köpfe und %d Beine\n",
         x, a,
         y, b,
         d, c);

  return 0;
}