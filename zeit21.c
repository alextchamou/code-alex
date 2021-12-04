#include<stdio.h>
#include<time.h>
int main(void){
    time_t sekunden;
    struct tm *ortszeit ;
    char *tag[7]={"Sonntag","Montag","Dienstag","Mittwoch","Donnerstag","Freitag","Samstag"};
    time(&sekunden); /*sekundenzahl beim Programnmstart*/
    printf("Stunden : Minuten : Sekunden \n");
    printf("%02d: %02d: %02d\n\n",ortszeit->tm_hour,ortszeit->tm_min,ortszeit->tm_sec);
    printf("Wochentag: \t %s \n",tag[ortszeit->tm_wday]);

}