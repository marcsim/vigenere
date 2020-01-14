#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef char CHAINE[1000];


char alphabet[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

/*plus utile avec la version avec le code Ascii
int getIndice(char lettre){
int res;
for (int i = 0; i < 26; i++) {
if (alphabet[i] == lettre) {
res = i;
}
}
return res;
}

*/

CHAINE fichier,fichierSortie,chaine,clef,chaineChiffrer,fichierDico,chaineEspace,chaineSansEspace;

int decalage,debut;

//Version sans accents
char DechiffrerLettreAsci(char chaine,char clef){
  if(chaine >= 'a' && chaine <= 'z'){
    if (clef >= 'A' && clef <='Z') {
      clef+=32;
    }
    if (chaine - (clef -'a') <'a') {
      return 'z'+(chaine-clef+1);
    }
    else{
      return chaine-(clef - 'a');
    }
  }
  else if (chaine >= 'A' && chaine <= 'Z') {
    if (clef >= 'a' && clef <='z') {
      clef-=32;
    }
    if (chaine - (clef -'A') <'A') {
      return 'Z'+(chaine-clef+1);
    }
    else{
      return chaine-(clef- 'A');
    }
  }
  else{
    return chaine;
  }
}

char ChiffrerLettreAsci(char chaine, char clef){
  if(chaine >= 'a' && chaine <= 'z'){
    if (clef >= 'A' && clef <='Z') {
      clef+=32;
    }
    if (chaine + (clef-'a') > 'z') {
      return (chaine+clef -'a')-('z'-'a'+1);
    }
    else{
      return chaine+(clef-'a');
    }
  }else if (chaine >= 'A' && chaine <= 'Z') {
    if (clef >= 'a' && clef <='z') {
      clef-=32;
    }
    if (chaine + (clef-'A') > 'Z') {
      return (chaine+clef -'A')-('Z'-'A'+1);
    }
    else{
      return chaine+(clef-'A');
    }
  }else{
    return chaine;
  }
}

void ChiffrerVigenere(char message[],char clef[],CHAINE fichierSortie) {

  FILE *out;
  out = fopen(fichierSortie,"a");
  int j=0;
  char tmp;
  for (int i = 0; i < strlen(message); i++) {
    if ((message[i]>= 'a' && message[i] <= 'z') || (message[i]>= 'A' && message[i] <= 'Z')) {
       tmp = ChiffrerLettreAsci(message[i],clef[j%(strlen(clef))]);
      j++;
    }else{
       tmp = ChiffrerLettreAsci(message[i],clef[j%(strlen(clef))]);
    }
    printf("%c",tmp );
    fputc(tmp, out);

  }
  printf("\n" );
  fclose(out);
}

void DeChiffrervigenere(char message[],char clef[],CHAINE fichierSortie) {
  FILE *out;
  out = fopen(fichierSortie,"a");
  int j=0;
  char tmp;
  for (int i = 0; i < strlen(message); i++) {
    if ((message[i]>= 'a' && message[i] <= 'z') || (message[i]>= 'A' && message[i] <= 'Z')) {
       tmp = DechiffrerLettreAsci(message[i],clef[j%(strlen(clef))]);
      j++;
    }else{
       tmp = DechiffrerLettreAsci(message[i],clef[j%(strlen(clef))]);
    }
    fputc(tmp, out);
    printf("%c",tmp );
  }
  printf("\n" );
  fclose(out);
}

//Fin version sans accents

//Version avec accents et ponctuation

char ChiffrerLettreAccent(char chaine, char clef){
  return chaine+clef;
}

char DechiffrerLettreAccent(char chaine,char clef){
  return chaine-clef;
}

void ChiffrerVigenereAccent(char message[],char clef[],CHAINE fichierSortie,int decalage) {
  FILE *out;
  out = fopen(fichierSortie,"a");
  for (int i = 0; i < strlen(message); i++) {
    if(message[i]!=10){
      char tmp = ChiffrerLettreAccent(message[i],clef[(i+decalage)%(strlen(clef))]);
      if(tmp>255) tmp=tmp-256;
      fputc(tmp, out);
      printf("%c",tmp );
    }
    else {
      char tmp = 10;
      fputc(10, out);
      printf("%c",tmp );
    }
  }
  printf("\n" );
  fclose(out);
}

void DeChiffrervigenereAccent(char message[],char clef[],CHAINE fichierSortie,int decalage) {
  FILE *out;
  out = fopen(fichierSortie,"a");
  for (int i = 0; i < strlen(message); i++) {
    if(message[i]!=10){
      char tmp = DechiffrerLettreAccent(message[i],clef[(i+decalage)%(strlen(clef))]);
      if(tmp<0) tmp=256+tmp;
      fputc(tmp, out);
      printf("%c",tmp );
    }
    else {
      char tmp = 10;
      fputc(10, out);
      printf("%c",tmp );
    }
  }

  printf("\n" );
  fclose(out);
}

// Fin version avec accents
/*Version améliorer avec l'ascii ci dessus
char ChiffrerLettre(char chaine, char clef){
int ch=getIndice(chaine);
int cl=getIndice(clef);
if(chaine >= 'a' && chaine <= 'z'){
if (ch + cl > 25) {
return alphabet[(ch+cl)-26];
}
else{
return alphabet[ch + cl];
}
}else{
return chaine;
}

}


char DechiffrerLettre(char chaine,char clef){
int ch=getIndice(chaine);
int cl=getIndice(clef);
if(chaine >= 'a' && chaine <= 'z'){
if (ch - cl <0) {
return alphabet[(ch-cl)+26];
}
else{
return alphabet[ch-cl];
}
}
else{
return chaine;
}
}
*/

/* ne sert plus car on utilise modulo
void remplirClef(CHAINE message,CHAINE * clef){

CHAINE tmp = "";
strcpy(tmp,*clef);
while (strlen(*clef) < strlen(message)) {
strcat(*clef, tmp);
}

}
*/

void  creerFichier(CHAINE fichier) {
  FILE *out;
  out = fopen(fichier,"w+");
  fclose(out);
}

int main(int argc, char const *argv[]) {
  int choix;

  while (1) {
    printf("Chiffrer un message sans accents : 1\n" );
    printf("Dechiffrer un message sans accents : 2\n" );
    printf("Chiffrer un message avec accent/ponctuation : 3\n" );
    printf("Dechiffrer un message avec accent/ponctuation : 4\n" );

    printf("Casser un message par la force Brute : 5\n");
    printf("Casser un message de façon intelligente : 6\n" );
    printf("Quitter le programme : 0\n" );
    scanf("%d",&choix);
    switch (choix) {
      case 1:
        memset(chaineEspace,0,sizeof(chaineEspace));
      printf("entrer le fichier a chiffrer \n" );
      scanf("%s",fichier );
      printf("entrer la clef de chiffrement \n" );
      scanf("%s",clef );
      printf("entrer le fichier dans lequel apparait le message chiffrer\n" );
      scanf("%s",fichierSortie);
      FILE *in;
      in = fopen(fichier,"r") ;
      if (in==NULL) { perror(fichier) ; return 1 ; }
      creerFichier(fichierSortie);
      while(fgets(chaine,1000,in)!=NULL)
      {
          chaine[strlen(chaine)-1]=' ';
          strcat(chaineEspace,chaine);
      }
      fclose(in);

      ChiffrerVigenere(chaineEspace,clef,fichierSortie);
      break;

      case 2:
        memset(chaineEspace,0,sizeof(chaineEspace));
      printf("entrer le fichier a dechiffrer \n" );
      scanf("%s",fichier );
      printf("entrer la clef de dechiffrement \n" );
      scanf("%s",clef );
      printf("entrer le fichier dans lequel apparait le message chiffrer\n" );
      scanf("%s",fichierSortie);
      FILE *in2;
      in2 = fopen(fichier,"r");
      creerFichier(fichierSortie);
      if (in2==NULL) { perror(fichier) ; return 1 ; }

      while(fgets(chaine,1000,in2)!=NULL)
      {
        chaine[strlen(chaine)-1]=' ';
        strcat(chaineEspace,chaine);
      }
      fclose(in2);
      printf("\n message : %s\n",chaineEspace );
      printf("cle : %s \n",clef );
      printf("chaine: %s \n",chaine );
      DeChiffrervigenere(chaineEspace,clef,fichierSortie);
      break;

      case 3:
      printf("entrer le fichier a chiffrer \n" );
      scanf("%s",fichier );
      printf("entrer la clef de chiffrement \n" );
      scanf("%s",clef );
      printf("entrer le fichier dans lequel apparait le message chiffrer\n" );
      scanf("%s",fichierSortie);
      FILE *in5;
      creerFichier(fichierSortie);
      decalage=0;
      debut=0;
      in5 = fopen(fichier,"r") ;
      if (in5==NULL) { perror(fichier) ; return 1 ; }
      while(fgets(chaine,1000,in5)!=NULL)
      {
        decalage+=(strlen(chaine)%(strlen(clef)));
        if (debut == 0) {
          ChiffrerVigenereAccent(chaine,clef,fichierSortie,0);
          debut++;
        }
        else{
          ChiffrerVigenereAccent(chaine,clef,fichierSortie,decalage+1);
        }

      }
      fclose(in5);
      break;

      case 4:
      printf("entrer le fichier a dechiffrer \n" );
      scanf("%s",fichier );
      printf("entrer la clef de dechiffrement \n" );
      scanf("%s",clef );
      printf("entrer le fichier dans lequel apparait le message chiffrer\n" );
      scanf("%s",fichierSortie);
      FILE *in6;
      creerFichier(fichierSortie);
      decalage=0;
      debut=0;
      in6 = fopen(fichier,"r");
      if (in6==NULL) { perror(fichier) ; return 1 ; }
      while(fgets(chaine,1000,in6)!=NULL)
      {
        decalage+=(strlen(chaine)%(strlen(clef)));

        if (debut == 0) {
          DeChiffrervigenereAccent(chaine,clef,fichierSortie,0);
          debut++;
        }else{
          DeChiffrervigenereAccent(chaine,clef,fichierSortie,decalage+1);
        }
      }
      fclose(in6);
      break;

      case 5:
      printf("entrer le fichier à casser\n" );
      scanf("%s",fichier);
      printf("entrer le fichier dictionnaire\n");
      scanf("%s", fichierDico);
      printf("entrer le fichier dans lequel apparait le message dechiffrer\n" );
      scanf("%s",fichierSortie);
      creerFichier(fichierSortie);
      FILE *in3, *dico;
      decalage=0;
      debut=0;
      in3 = fopen(fichier, "r");
      if(in3 == NULL){  return 1 ; };
      dico = fopen(fichierDico, "r");
      if(dico == NULL){return 1 ; };
      while(fgets(clef,1000, dico) != NULL)
      {
        clef[strlen(clef)-1]='\0';
        FILE *in4;
        in4= fopen(fichier,"r");
        decalage =0;
        if (in4==NULL) { perror(fichier) ; return 1 ; }
        while(fgets(chaine,1000,in4)!=NULL)
        {
          decalage+=(strlen(chaine)%(strlen(clef)));

          if (debut == 0) {
      //      DeChiffrervigenere(chaine,clef,fichierSortie,0);
            debut++;
          }else{
        //    DeChiffrervigenere(chaine,clef,fichierSortie,decalage+1);
          }

        }
        fclose(in4);
      }
      fclose(dico);
      fclose(in3);
      break;

      case 0:
      return 0;
      break;
      default:
      printf("Choix taper non proposer veuillez réessayer.\n" );
      break;
    }
  }
  return 0;
}
