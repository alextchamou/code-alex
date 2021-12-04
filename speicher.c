#include <stdio.h>
#include <limits.h>
int main(void)
{
printf("sizeof(char)      = %ld Byte; ([%d ... %d])\n", sizeof(char),
CHAR_MIN , CHAR_MAX);
printf("sizeof(short)     = %ld Byte; ([%d ... %d])\n", sizeof(short),
SHRT_MIN , SHRT_MAX);
printf("sizeof(int)       = %ld Byte; ([%d ... %d])\n", sizeof(int), INT_MIN
, INT_MAX);
printf("sizeof(long)      = %ld Byte; ([%ld ... %ld])\n", sizeof(long),
LONG_MIN , LONG_MAX);
printf("sizeof(long long) = %ld Byte; ([%lld ... %lld])\n", sizeof(long long
), LLONG_MIN , LLONG_MAX);
printf("sizeof(float)     = %ld Byte;\n", sizeof(float));
printf("sizeof(double)    = %ld Byte;\n", sizeof(double));
int a = 46, b = 89;
double c = 5.3, d = 2017.411;
printf("Wert von a: %d, Speicheradresse von a: %p\n", a, &a);
printf("Wert von b: %d, Speicheradresse von b: %p\n", b, &b);
printf("Wert von c: %f, Speicheradresse von c: %p\n", c, &c);
printf("Wert von d: %f, Speicheradresse von d: %p\n", d, &d);
return 0;
}