#include<stdio.h>
#include<time.h>
int main(int argc, char* argv[])
{
    long sekunden;
    scanf("%ld",&sekunden);
    struct tm * ortszeit ;
    char *tag [7]= {"Sonntag","Montag","Dienstag","Mittwoch","Donnerstag","Freitag","Samstag"};
    char*monat [12]={"Dezember","Januar","Februar","Maerz","April","Mai","Juni","Juli","August","September","Oktober","November",};
    ortszeit = gmtime(&sekunden);
    printf("%s, %d. %s %d, %02d:%02d",tag[ortszeit->tm_wday],ortszeit->tm_mday,monat[ortszeit->tm_mon+1],ortszeit->tm_year+1900,ortszeit->tm_hour,ortszeit->tm_min);
    return 0;
}