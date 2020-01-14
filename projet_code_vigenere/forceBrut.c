#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef char CHAINE[1000];
char alphabet[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
CHAINE fichier,fichierSortie,chaine,clef,chaineChiffrer,chaine4;
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

  if(chaine >= 'a' && chaine <= 'z')
  {
    if(ch -cl < 0)
    {
      return alphabet[(ch-cl)+26]; 
    }else{
      return alphabet[ch-cl]; 
    }
  }else{
    return chaine;
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
   // printf("%c",tmp );
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
  printf("entrer le fichier dans lequel apparait le message chiffrer\n" );
  scanf("%s",fichierSortie);
// on va chercher la clé dans le fichier dico 

  FILE *dico;
  dico = fopen("Dico.txt", "r");
    if(dico == NULL){return 1 ; };
    while(fgets(chaine4,1000, dico) != NULL)
    {  

      if(strcmp(chaine4, "") != 0){
        strcpy(clef, chaine4);
        printf(" la clé est : %s\n", clef);
      }

  FILE *in2;
  in2 = fopen(fichierSortie,"r");
  if (in2==NULL) { perror(fichierSortie) ; return 1 ; }
  while(fgets(chaine,1000,in2)!=NULL)
  {
    remplirClef(chaine,&clef);
  //  printf("%s\n",chaine );
    DeChiffrervigenere(chaine,clef,fichier);

  }

fclose(in2);

  }
  fclose(dico);
  return 0;
}
