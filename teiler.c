#include <stdio.h>
int main(void)
{
int zahl = 0;
int i = 2;
// Einlesen der Eingabe
scanf("%d", &zahl);
while (i <= zahl)
{
// Der Operator % berechnet den
//Rest bei ganzzahliger Division;
// z.B. ergibt 37 % 5 den Wert 2.
if (zahl % i == 0)
{
printf("%i ", i);
// Der Operator / berechnet den
//ganzzahligen Quotienten bei der
//Division;
// z.B. ergibt 37 % 5 den Wert
zahl = zahl / i;
}
else
{
i++;
}
}
printf("\n");
return 0;
}
