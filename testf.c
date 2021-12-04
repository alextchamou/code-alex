#include<stdio.h>
#include<stdlib.h>
int main (int argc,char *argv [])
{
    FILE* fichier= NULL ;
    int caractereActuel = 0;
    fichier=fopen("test.txt","r+");
    if (fichier != NULL)
    {
        do{
            //Boucle de lecture de caractere un a un
            caractereActuel = fgetc(fichier);//lecture de caractere
            printf("%c",caractereActuel);//affichage a l ecran 
        }while(caractereActuel !=EOF);
        printf("\nfile open succesfully!!");
    }
    
    else
    {
    printf("impossible d ouvrir le fichier ");
    fputc('A',fichier);
    fputs("\nsalut les nazes comment allez vous ?",fichier);
    fprintf(fichier,"\nassez interessant comme initiative ");
    }
    fclose(fichier);
    return 0;
    }