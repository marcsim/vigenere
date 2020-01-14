#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char tab[100]; 

void repetition(tab chaine)
{
	tab occ;
	tab chaineOcc;  

	int i, j; 
	for(i = 0 ; i<100 ; i++)
	{
		occ[i] = chaine[i]; 
		for(j = 1 ; j<100 ; j++)
		{
			if(occ[i] == chaine[j]){
				while(occ[i+1] == chaine[j+1])
				{
					occ[i+1] = chaine[j+1]; 
					i++; 
					j++;
					strcpy(chaineOcc, occ);
				}
				
			}
		}
	}
		printf("%s", chaineOcc);
}

int main()
{
	tab chaine;
	scanf("%s", chaine); 
	repetition(chaine);


	return 0; 
}

