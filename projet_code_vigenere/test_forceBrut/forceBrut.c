#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	affiche dans un fichier de sortie tous les messages déchiffrés à l'aide des différentes clefs du dico 
	cependant, il est nécessaire de vérifier soi même le fichier de sortie afin de voir si l'on a trouvé un déchiffrement cohérent. 
*/

typedef char CHAINE[1000];
char alphabet[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
CHAINE fichier,fichierSortie,fichierDico,chaine,clef,chaineChiffrer;

int getIndice(char lettre){
  int res;
  for (int i = 0; i < 26; i++) {
    if (alphabet[i] == lettre) {
      res = i;
    }
  }
  return res;
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

int main(int nbarg, char *argv[])
{
	//char chaine2[1000]; 
	//char chaine3[1000];
	char chaine4[1000]; 
	printf("entrer le fichier à casser\n" );
 	scanf("%s",fichier);
 	printf("entrer le fichier dictionnaire\n");
 	scanf("%s", fichierDico);
  	printf("entrer le fichier dans lequel apparait le message dechiffrer\n" );
  	scanf("%s",fichierSortie);

	FILE *in, *dico; 
	//char fichier = argv[1];  
	in = fopen(fichier, "r"); 
	if(in == NULL){  return 1 ; };
	dico = fopen(fichierDico, "r");
	if(dico == NULL){return 1 ; };
	while(fgets(chaine4,1000, dico) != NULL)
	{ 
		strcpy(clef, chaine4); //On copie chaque mot du fichier dico dans la clef et on la test. 	
		
		FILE *in2;
		in2 = fopen(fichier,"r");
		if (in2==NULL) { perror(fichier) ; return 1 ; }
		while(fgets(chaine,1000,in2)!=NULL)
		{
	    	remplirClef(chaine,&clef);
	    	DeChiffrervigenere(chaine,clef,fichierSortie); //On déchiffre normalement avec la clef en cours (dans le dictionnaire)
	    }

	    fclose(in2);
	}
	fclose(dico); 
	fclose(in); 
	return 0; 
}

