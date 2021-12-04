#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

// La fonction PGCD en s'appuyant sur l'algorithme d'EUCLIDE
void PGCD (mpz_t r, mpz_t a , mpz_t b) ;

// La fonction Genere_nbPremier retourne les deux entiers P et Q
// aleatoires et  premiers
void Genere_nbPremier( mpz_t p, mpz_t q, int n, gmp_randstate_t state ) ;

// la fonction genere_PK()  permet de créer la clé public  e
void Genere_publicKey( mpz_t e ,mpz_t p , mpz_t q ,gmp_randstate_t state  );

// La fonction genere_privateKey permet de determiner la clé public
// algorithme euclide etendu
void Genere_privateKey (mpz_t d , mpz_t e , mpz_t phi) ;

// la fonction  initializeRandom permet d,initialiser le generateur de nombre aleatoire
void InitializeRandom(gmp_randstate_t r_state );

// le nextprime permet de calculer le nombre premier suivant
void nextprime (mpz_ptr p, mpz_srcptr t) ;

//la fonction puissances calcule  a exponsant e (mod n) pour de grandes valeurs de l'exposant e
void puissance (mpz_t resultat ,mpz_t a, mpz_t e, mpz_t n) ;

//La test_primalite verifie si un nombre est premier,c'est une application
void  test_primalite ( mpz_t resultat , mpz_t n);

// calculer different parametre de la clé
void Calcul_CRT(mpz_t ip ,mpz_t dp ,mpz_t dq , mpz_t e,mpz_t  p,mpz_t q);

// fonction de chiffrement de message
void  chiffre_Msg( mpz_t chiffre, mpz_t message ,  mpz_t e, mpz_t n);

// fonction dechiffrement de message
void  dechiffre_Msg( mpz_t message2, mpz_t chiffre ,  mpz_t d, mpz_t n);

//dechiffrement en mode CRT
void  dechiffre_MsgCRT(mpz_t message2,  mpz_t cipher , mpz_t dp, mpz_t p, mpz_t dq, mpz_t q, mpz_t ip) ;

// la fonction principal du rsa en mode Standard
void crypter();

// la fonction principal du rsa en mode CRT
void crypterCRT() ;

// La fonction qui permet de signer un message m
void  signer_Msg(mpz_t msg_signe, mpz_t message , mpz_t d, mpz_t n);

// La fonction qui permet de signer un message m au mode CRT
void  signer_MsgCRT(mpz_t msg_signe, mpz_t message , mpz_t dp, mpz_t p, mpz_t dq,  mpz_t q , mpz_t ip) ;

// fonction verifier_sign  verifier si le message a ete altere ou modifie
void  verifier_sign( mpz_t signature_msg , mpz_t message, mpz_t e, mpz_t n) ;

 la classe rsa_gmp.c *******************************************


#include "rsa_gmp.h"

#define BITSTRENGTH  1024               /* size of modulus (n) in bits */
#define PRIMESIZE    (BITSTRENGTH / 2)  /* size of the primes p and q  */
#include "rsa_gmp.h"

/* la fonction PGCD calcule le PGCD de deux entiers a et b
   en s'appuyant sur l'algorithme d'Euclide

/


void PGCD ( mpz_t resultat,  mpz_t a , mpz_t b )
{
   mpz_t r , r1 ,r2;

//intialiser les variables
   mpz_init( r );
   mpz_init( r1 );
   mpz_init( r2 );

// affectation
   mpz_set (r , a ) ;
   mpz_set (r1 , b) ;

   while ( mpz_cmp_ui ( r1, 0) != 0)
   {
       mpz_mod ( r2, r, r1);
       mpz_set (r , r1 ) ;
       mpz_set (r1 , r2) ;
   }

    mpz_set (resultat , r) ;
// liberer l'espace de variable
  mpz_clear( r );
  mpz_clear( r1 );
  mpz_clear( r2 );

}
// le nextprime permet de calculer le nombre premier suivant
void nextprime (mpz_ptr p, mpz_srcptr t)
{
  mpz_t test ;
  mpz_init( test );
  mpz_add_ui (p, t, 13);

  test_primalite ( test , p);
  while (mpz_cmp_ui( test , 0)!= 1 )
  {
    mpz_add_ui (p, p, 13);
    test_primalite ( test , p);
  }

}
/*
la fonction puissances calcule  a exponsant e (mod n) pour de grandes valeurs de l'exposant e

/


void puissance (mpz_t resultat ,mpz_t a, mpz_t e, mpz_t n)
{
    mpz_t temp,t,a_bis,e_bis ;
    // initialise la variable local
    mpz_init( temp );
    mpz_init( t );

    mpz_init( a_bis );
    mpz_set( a_bis , a );

    mpz_init( e_bis );
    mpz_set( e_bis , e );

    mpz_set_ui (temp , 1);

    while ( mpz_cmp_ui ( e_bis,0 )> 0)
    {
        mpz_mod_ui( t , e_bis , 2);
        if( mpz_cmp_ui( t , 0 ) != 0)
         {
            mpz_mul( temp , temp , a_bis);
            mpz_mod( temp , temp ,n );
          }
        mpz_mul(a_bis , a_bis, a_bis);
        mpz_mod ( a_bis, a_bis, n);

        mpz_tdiv_q_ui(e_bis,e_bis,2);
    }

    mpz_set( resultat , temp );
    // liberer l'espace utilisé
    mpz_clear( temp );mpz_clear(t);
    mpz_clear(a_bis );mpz_clear(e_bis );

}

/*
 La test_primalite verifie si un nombre est premier,c'est une application
 de Miller_Rabin
 @ param long a, n( mod n)
 @return 1 ou 0

/

void  test_primalite ( mpz_t resultat , mpz_t n)
{
    mpz_t  var ,p, e, m , i , k ,temp ;
    // initialiser les variables locals
    mpz_init(var) ;mpz_init(p) ;mpz_init(e) ;mpz_init( temp ) ;
    mpz_init( m)  ;mpz_init( i) ;mpz_init( k) ;

    mpz_sub_ui ( m , n , 1);
    mpz_sub_ui ( e , n , 1);
    mpz_set_ui( var , 10 );

    mpz_set_ui ( k , 0 );
    mpz_mod_ui ( temp , e , 2);

    while ( mpz_cmp_ui ( temp , 0 )== 0)
    {
        mpz_tdiv_q_ui( e , e , 2);
        mpz_add_ui ( k , k , 1);
        mpz_mod_ui ( temp , e , 2);
    }

    puissance( p ,var , e , n );

    if( mpz_cmp_ui ( p , 1) == 0)
       {
         mpz_set_ui( resultat , 1);
        return;
       }

    mpz_set_ui( i , 0);

    while( mpz_cmp ( i , k ) < 0)
    {
        if( mpz_cmp( p , m )== 0)
        {
            mpz_set_ui( resultat , 1);
            break ;
        }

        if( mpz_cmp_ui( p , 1 )== 0)
        {
            mpz_set_ui( resultat , 0);
            break ;
        }

        mpz_mul( p, p , p );
        mpz_mod( p , p , n) ;

        mpz_add_ui (i, i , 1);
    }

    // liberer l'espace utilisé par les variables locals
    mpz_init(var) ;mpz_init(p) ; mpz_init(e) ;mpz_init(temp) ;
    mpz_init( m)  ;mpz_init( i) ;mpz_init( k) ;
}

// la fonction  initializeRandom permet d,initialiser le generateur de nombre aleatoire
void InitializeRandom(gmp_randstate_t r_state )
{
    /* Initialisation de nombre aleatoire*/
    unsigned long int  seed;
    seed = time(0);

    gmp_randinit_default (r_state);
    gmp_randseed_ui(r_state, seed);
}

/*
 La fonction Genere_nbPremier retourne les deux entiers P et Q
 aleatoires et  premiers

/


void Genere_nbPremier( mpz_t p, mpz_t q, int n, gmp_randstate_t state )
{
    //création de varaiable locale
    mpz_t rand, nb_aleatoire, max , min , varp , varq;

    // initialiser les variables
    mpz_init( rand ); mpz_init( nb_aleatoire ); mpz_init( max );
    mpz_init( min );mpz_init( varp );mpz_init( varq );

    // calcule du Borne Superieur
    mpz_ui_pow_ui( max, 2, n+1 );
    // calcule du borne inferieur
    mpz_ui_pow_ui( min, 2, n );

    // Génère un nombre compris entre 0 et max et le stocke dans rand. state initialise le générateur aléatoire.
    do
    {
        mpz_urandomm( rand, state, max );

    }while( mpz_cmp( rand, min) > 0 );
    // Vérifie que rand est supérieur à la borne inférieure
    nextprime ( p , rand );

    // Génère un nombre  Q compris entre 0 et max et le stocke dans rand. state initialise le générateur aléatoire.
    do
    {
        mpz_urandomm( nb_aleatoire, state, max );

    }while(( mpz_cmp( nb_aleatoire, min) > 0 )|| ( mpz_cmp ( p , q ) == 0));
    // Vérifie que rand est supérieur à la borne inférieure
     nextprime( q , nb_aleatoire );

    // clear l'espace utilisé
    mpz_clear( nb_aleatoire );mpz_clear( rand );mpz_clear( max );
    mpz_clear( min );mpz_clear( varq );mpz_clear( varp );

}

// la fonction genere_PK()  permet de créer la clé public  e

void Genere_publicKey( mpz_t e ,mpz_t p , mpz_t q ,gmp_randstate_t state  )
{
    mpz_t a , b , c, r , y ,rand_Num;

    // initialiser les avriable locale
    mpz_init( a );
    mpz_init( b );
    mpz_init( c );
    mpz_init( y );
    mpz_init( r );
    mpz_init( rand_Num );

    mpz_sub_ui( a, p, 1 );
    mpz_sub_ui( b, q, 1 );

    mpz_mul( y, a, b );

    //Définition d'une valeur max de E.
    mpz_t max;
    mpz_init( max );
    mpz_set_str ( max , "97" ,0);

    mpz_urandomm( rand_Num, state, max );
    mpz_add_ui ( rand_Num , rand_Num , 3);
    mpz_mod(c,rand_Num,y);
    PGCD( r , c, y);

 while (( mpz_cmp_ui( r,1 )!= 0) ||mpz_cmp( c ,max )>0 ||mpz_cmp_ui( c ,0) ==0 )
   {
       mpz_urandomm( rand_Num, state, max );
       mpz_add_ui ( rand_Num , rand_Num , 3);
       mpz_mod(c,rand_Num,y);
       PGCD( r , c, y);
   }
    mpz_set( e ,c ) ;
    // effacer les espaces utilisées par les variables
    mpz_clear( a );mpz_clear( b );mpz_clear( y );mpz_clear( r );
    mpz_clear( rand_Num );mpz_clear( max );mpz_clear( c );

}

// La fonction genere_privateKey permet de determiner la clé public
// algorithme euclide etendu
void Genere_privateKey (mpz_t d , mpz_t e , mpz_t phi)
{
   mpz_t e0,t0 , t , q, r, n0, temp ,temp2;

   // initialiser les variables
   mpz_init ( e0);mpz_init ( t0 );mpz_init ( t );mpz_init ( q );
   mpz_init ( r );mpz_init ( n0 );mpz_init ( temp );mpz_init ( temp2 );

   mpz_set_ui( t , 1) ;
   mpz_set ( n0 , phi );
   mpz_set ( e0 , e );
   mpz_tdiv_q( q , n0 , e0);
   mpz_mod ( r ,n0 , e0) ;

   while( mpz_cmp_ui ( r, 0) > 0)
   {
       mpz_mul( temp , q, t);
       mpz_sub( temp , t0, temp );

       if( mpz_cmp_ui ( temp , 0) >= 0)
       {
           mpz_mod ( temp , temp ,phi);
       }
       else
       {
           mpz_mod( temp , temp , phi);
       }

       mpz_set( t0 , t);
       mpz_set( t , temp);
       mpz_set( n0, e0);
       mpz_set( e0, r);
       mpz_tdiv_q( q , n0 , e0);
       mpz_mod ( r ,n0 , e0) ;

   }
   mpz_set ( d , t);
   // liberer l'espaces des variables
   mpz_clear( e0 );mpz_clear( t0 );mpz_clear( t );mpz_clear( q );
   mpz_clear( r );mpz_clear(  n0 );mpz_clear( temp );mpz_clear( temp2 );
}

// fonction de chiffrement de message
void  chiffre_Msg( mpz_t chiffre, mpz_t message ,  mpz_t e, mpz_t n)
{
    mpz_t cipher;
	mpz_t i;
    mpz_t temp;

	mpz_init(cipher);
	mpz_init(i);
	mpz_init(temp);
	mpz_set_si(cipher,1);

    puissance (cipher ,message, e, n);
    mpz_set(chiffre,cipher);

    mpz_clear(cipher);
	mpz_clear(temp);
}

// fonction dechiffrement de message
void  dechiffre_Msg( mpz_t message2, mpz_t chiffre ,  mpz_t d, mpz_t n)
{
    mpz_t message;
	mpz_t i;
    mpz_t temp;

	mpz_init(message);
	mpz_init(i);
	mpz_init(temp);
	mpz_set(temp,chiffre);

    puissance ( message,temp , d, n);
    mpz_set(message2,message);

    mpz_clear(message);
	mpz_clear(temp);
}

//dechiffrement en mode CRT
void  dechiffre_MsgCRT(mpz_t message2,  mpz_t cipher , mpz_t dp, mpz_t p, mpz_t dq, mpz_t q, mpz_t ip)
{
    // variables locaux
    mpz_t message,mp,mq ,n;
    mpz_t temp , pq , var;

    // initialisation des variables
	mpz_init(mp); mpz_init(mq);mpz_init( n );
	mpz_init(message); mpz_init(temp);
	mpz_init( pq );mpz_init( var );

	mpz_set_ui(message,1);
	mpz_mul ( n , p , q);

    dechiffre_Msg(mp, cipher , dp, p);
    dechiffre_Msg(mq, cipher , dq, q);

	mpz_sub(pq,mq,mp);
	mpz_mul(temp,pq,ip);
	mpz_mod(var,temp,q);
	mpz_mul( message,var,p);
	mpz_add(message,message,mp);
	mpz_mod( message , message , n);

    mpz_set(message2,message);

	mpz_clear(mp);mpz_clear( n );
	mpz_clear(mq);mpz_clear( var );
    mpz_clear(message);mpz_clear(pq);
	mpz_clear(temp);
}

// La fonction qui permet de signer un message m au mode STANDARD
void  signer_Msg(mpz_t msg_signe, mpz_t message , mpz_t d, mpz_t n)
{

    //calcul le haché du message
    dechiffre_Msg (msg_signe, message ,d ,n);

}
// La fonction qui permet de signer un message m au mode CRT
void  signer_MsgCRT(mpz_t msg_signe, mpz_t message , mpz_t dp, mpz_t p, mpz_t dq,  mpz_t q , mpz_t ip)
{

    //calcul le haché du message
    dechiffre_MsgCRT(msg_signe, message , dp,  p,  dq,  q,  ip);

}
// fonction verifier_sign  verifier si le message a ete altere ou modifie
void  verifier_sign( mpz_t signature_msg , mpz_t message, mpz_t e, mpz_t n)
{
    mpz_t msg_hache;
	mpz_init(msg_hache);

    // On calcule la signature exposnt e modulo  n
    chiffre_Msg(msg_hache,signature_msg, e , n);

    // on compare avec la signature du message
    if(mpz_cmp (message,msg_hache)==0)
    {
        printf("\n\n \t Resultat du verificateur : Message correct\n\n\n\n ");
    }
    else
    {
        printf("\n\n \t Resultat du verificateur : Message corrompu \n\n\n\n");
    }
    mpz_clear(msg_hache);
}

// la fonction principal du rsa en mode Standard
void crypter()
{
    // Variable locales
    mpz_t p , q ,cipher ,e,d , n , phi , message,msg_chiffre ,sign ;

    //initialiser les variables locales

    mpz_init(msg_chiffre); mpz_init(cipher);
    mpz_init(e); mpz_init(n); mpz_init(p);
    mpz_init(q); mpz_init(d); mpz_init(phi);
    mpz_init(sign);mpz_init( message);

    // initialisationn du generateur
    gmp_randstate_t state;
    InitializeRandom(state);
    Genere_nbPremier( p,q ,512, state);

    // la valeur de N
    mpz_mul ( n , p , q);

    // les variablesP et Q
    gmp_printf ("\n\n \t P  \t: \t%Zd \n", p );
    gmp_printf ("\n\n \t Q  \t: \t%Zd \n", q );

    // Generer la clé public
    Genere_publicKey( e, p ,q , state);
    gmp_printf("\n\n \t clef pubic : \t%Zd \n",e);
/*
    // Calculer la valeur de phi
    mpz_sub_ui( p , p , 1);
    mpz_sub_ui( q , q , 1);
    mpz_mul( phi , p , q) ;

    // genere la cle privee
    Genere_privateKey ( d , e , phi );
    gmp_printf("\n\n \t clef prive : \t%Zd \n",d);

    // le message a chiffre // le message a chiffre
    printf("\n\n\n\t Entrez le message a crypter: ");
    gmp_scanf("%Zd",&message);

    //chiffre le message
	chiffre_Msg(  msg_chiffre, message,  e, n);
	gmp_printf("\n\n\t Le message chiffre : \t%Zd\n",msg_chiffre);

	// Signer le message
	//gmp_printf("\n\n\t Le message \t ,%Zd ,%Zd,%Zd\n",message ,d,n);
    signer_Msg( sign , message ,d, n );
    gmp_printf("\n\n \t Voici la signature du message :  %ld\n ", sign );

    //dechiffrement du message
    mpz_init_set_str(cipher, "1",0);
	dechiffre_Msg (cipher, msg_chiffre ,d ,n);
	gmp_printf("\n\n\t Le message dechiffre :\t%Zd\n\n",cipher);

	//verifier la signature du message
     verifier_sign( sign , message ,e , n);

/

	printf("\t ------------ Retour au menu ------------------\n\n\n\n ");

    // liberer les variables locales
	mpz_clear(p); mpz_clear(q); mpz_clear(cipher);
	mpz_clear(e);mpz_clear(phi);mpz_clear(n);
	mpz_clear(message);mpz_clear( msg_chiffre);
	mpz_clear(sign);

}

// Mode de CRT du RSA
void crypterCRT()
{
    // Variable locales
    mpz_t p , q ,e ,d , n , phi , message,msg_chiffre ,cipher ,
           msg_dechiffre , dp , dq , ip ,ed ,sp ,sq ,sign;

    //initialiser les variables locales
    //mpz_init_set_str(message, "12345678901234567890",0);

    mpz_init(msg_chiffre); mpz_init(cipher);mpz_init ( message);
    mpz_init( msg_dechiffre) ;mpz_init(e); mpz_init(n);
    mpz_init(p); mpz_init(q); mpz_init(d); mpz_init(phi);
    mpz_init(dp); mpz_init(dq ); mpz_init(ip);mpz_init(ed);
    mpz_init(sp); mpz_init(sq );mpz_init(sign );

    // initialisationn du generateur
    gmp_randstate_t state;
    InitializeRandom(state);
    Genere_nbPremier( p,q ,512, state);

    // la valeur de N
    mpz_mul ( n , p , q);

    // les variablesP et Q
    gmp_printf ("\n\n \t P  \t: \t%Zd \n", p );
    gmp_printf ("\n\n \t Q  \t: \t%Zd \n", q );

    // Generer la clé public
    Genere_publicKey( e, p ,q , state);
    gmp_printf("\n\n \t clef pubic : \t%Zd \n",e);

    // Calculer la valeur de phi
    Calcul_CRT( ip ,dp ,dq ,e , p , q);
    mpz_sub_ui( sp , p , 1);
    mpz_sub_ui( sq , q , 1);
    mpz_mul( phi , sp , sq) ;

    // genere la cle privee
    Genere_privateKey ( d , e , phi );
    gmp_printf("\n\n \t clef prive : {\t%Zd%\n ,\n\t%Zd\n\n ,\t%Zd\n\n ,\t%Zd\n\n ,\t%Zd \n\n}", p, q,dp, dq,ip);

    // le message a chiffre
    printf("\n\n\n\t Entrez le message a crypter: ");
    gmp_scanf("%Zd",&message);

    //Chiffre le message en mode CRT
    chiffre_Msg(  cipher , message, e , n);
    gmp_printf("\n\n \t Voici le message chiffre :  %Zd\n ", cipher );

    // Signer le message
    signer_MsgCRT( sign,message , dp, p, dq, q , ip);
    gmp_printf("\n\n \t Voici la signature du message au mode CRT:  %ld\n ", sign );

    //Dechiffre le message au mode CRT
    mpz_init_set_str(msg_dechiffre, "1",0);

    dechiffre_MsgCRT(msg_dechiffre, cipher , dp,  p,  dq,  q,  ip);
    gmp_printf("\n\n\t Le message apres le decryptage :  %Zd\n", msg_dechiffre);

    //verifier la signature du message
     verifier_sign( sign , message ,e , n);

    printf("\t ------------ Retour au menu ------------------\n\n\n\n ");

    // Liberer l'espace occupé par les variables locaux
   mpz_clear( message); mpz_clear( cipher );mpz_clear( msg_dechiffre );
   mpz_clear(d);mpz_clear(p);mpz_clear(q); mpz_clear(n); mpz_clear(phi);
   mpz_clear(dp); mpz_clear(dq); mpz_clear(ip);mpz_clear (msg_dechiffre);
   mpz_clear(ed);mpz_clear(sp); mpz_clear(sq);mpz_clear(sign);

}

// calculer different parametre de la clé
void Calcul_CRT(mpz_t ip ,mpz_t dp ,mpz_t dq , mpz_t e,mpz_t  p,mpz_t q)
{
    //Variable local
    mpz_t ep, eq ;
    //initialiser les variable locaux
    mpz_init ( ep ); mpz_init ( eq );

    mpz_sub_ui(ep , p , 1 ) ;
    mpz_sub_ui(eq , q , 1 ) ;

    Genere_privateKey( ip , p ,q  );
    Genere_privateKey( dp , e , ep );
    Genere_privateKey( dq , e, eq );

    //liberer l'espaces de variables locaux
    mpz_clear ( ep );mpz_clear ( eq );
}

  le Main **********************************************************


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include "rsa_gmp.h"

int main()
{
   int choix, quit = 0;
/*
   printf("\n\n\t\t\t ********************\n");
   printf("\t\t\t *MENU CRYPTOGRAPHIE*\n");
   printf("\t\t\t ********************\n\n\n\n");

   while ( quit!=1 )
    {
        printf("\t TAPEZ :\n\n\n\n");
        printf("\t\t1\t POUR\t RSA en mode STANDARD\n\n");
        printf("\t\t2\t POUR\t RSA en mode CRT\n\n");
		printf("\t\t3\t POUR\t Quitter\n\n\n");
        printf("\t CHOIX : ");
        scanf("%d",&choix);

        switch(choix)
        {

            case 1 : crypter();
                   break;

            case 2 : crypterCRT();
                   break;

			case 3 : quit = 1;
                   break;
         }
  }

  
/

     crypter();
   return 0;

}