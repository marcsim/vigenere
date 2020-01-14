#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char alphabet[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

struct element 
{
	char lettre; 
	int occ; 
}; 

int main(int argc, char *argv[])
{
	struct element tabLettre[26];  
	FILE *fichier = NULL; 
	int tmp = 0; 
	fichier = fopen("fichierChiffre.txt", "r"); 

	if(fichier != NULL)
	{
		int pos=-1;
		int j=0;
		do{
			tmp = fgetc(fichier);//Lecture du caractère
			for(int i=0; (i<26)&&(pos==-1) ; i++)
			{
				if(tabLettre[i].lettre == tmp)
				{
					pos = i;
					printf("%d", pos);
				}
			}
			 
			if(pos == -1)
			{
				tabLettre[j].lettre = tmp;
				tabLettre[j].occ++; 
				j++;
			}else{
				tabLettre[pos].occ++;
			}

		}while(tmp != EOF); // On continue tant que fgetc ne retroune pas EOF
		
		fclose(fichier);
	}else{
		printf("Le fichier n'a pas été ouvert.\n");
	}



	for(int j=0 ; j<26 ; j++)
	{
		printf("(%c,%d) | ", tabLettre[j].lettre, tabLettre[j].occ);
	}

	printf("\n");

	return 0; 
}