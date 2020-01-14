#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef char CHAINE[1000];
char alphabet[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
CHAINE fichier,fichierSortie,chaine,clef,chaineChiffrer;
CHAINE fichierTest = "TexteDechiffre.txt";
int getIndice(char lettre){
  int res;
  for (int i = 0; i < 26; i++) {
    if (alphabet[i] == lettre) {
      res = i;
    }
  }
  return res;
}

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

  if (ch - cl <0) {
    return alphabet[(ch-cl)+26];
  }
  else{
    return alphabet[ch-cl];
  }
}

void remplirClef(CHAINE message,CHAINE * clef){

  CHAINE tmp = "";
   strcpy(tmp,*clef);
  while (strlen(*clef) < strlen(message)) {
    strcat(*clef, tmp);
  }

}


void ChiffrerVigenere(char message[],char clef[],CHAINE fichierSortie) {
  int compteur = 0;
  FILE *out;
  out = fopen(fichierSortie,"a");
  for (int i = 0; i < strlen(message); i++) {
    char tmp = ChiffrerLettre(message[i],clef[compteur]);
    fputc(tmp, out);
    printf("%c",tmp );
    if(message[i] >= 'a' && message[i] <= 'z'){
    compteur ++;
    }
  }
  printf("\n" );
  fclose(out);
}

void DeChiffrervigenere(char message[],char clef[],CHAINE fichierSortie) {
  int compteur = 0;
  FILE *out;
  out = fopen(fichierSortie,"a");
  for (int i = 0; i < strlen(message); i++) {
    char tmp = DechiffrerLettre(message[i],clef[compteur]);
    fputc(tmp, out);
    printf("%c",tmp );
    if(message[i] >= 'a' && message[i] <= 'z'){
    compteur ++;
    }
  }
  printf("\n" );
  fclose(out);
}

int main(int argc, char const *argv[]) {
  printf("entrer le fichier a chiffrer \n" );
  scanf("%s",fichier );
  printf("entrer la clef de chiffrement \n" );
  scanf("%s",clef );
  printf("entrer le fichier dans lequel apparait le message chiffrer\n" );
  scanf("%s",fichierSortie);
  FILE *in;
//  int nl = 0 ;
  in = fopen(fichier,"r") ;
  if (in==NULL) { perror(fichier) ; return 1 ; }
  while(fgets(chaine,1000,in)!=NULL)
  {
    remplirClef(chaine,&clef);
  //  printf("%s\n",chaine );
    ChiffrerVigenere(chaine,clef,fichierSortie);

  }
  fclose(in);

  FILE *in2;
  in2 = fopen(fichierSortie,"r");
  if (in2==NULL) { perror(fichierSortie) ; return 1 ; }
  while(fgets(chaine,1000,in2)!=NULL)
  {
    remplirClef(chaine,&clef);
  //  printf("%s\n",chaine );
    DeChiffrervigenere(chaine,clef,fichierTest);

  }
  fclose(in);

  return 0;
}
