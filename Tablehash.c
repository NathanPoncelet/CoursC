#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
struct information{
	int key;
	int occ;
	struct information *suivant;
}information;

/***********************************************************************/
	

int lireMot(FILE * fp, char * mot) {
      int i;
      char c;
      while ( ! (isalpha (c = fgetc(fp)))) {
         if  (c == EOF) {
            mot[0] = '\0';
            return 0;
         }
      }
      mot[0] = c & 0xdf;
      i = 1;
      while ( isalpha (c = fgetc(fp))) {
         mot[i] = c & 0xdf;
         i++;
      }
      mot[i] = '\0';
      return 1;
   }


int recherche(char *mot,struct information dico[], int total){
	int i=0;
	for(i=0; i<total ; i++){
		if(strcmp(dico[i].mot,mot)==0)
			return i;// si découverte du mot renvoie a la position ou l'on a trouvé le mot
	}
	return -1; // retourne -1 si non decouverte du mot
}

int ajouter_mot(char *buff, int total, struct information dico[]){
	int aide=recherche(buff,dico,total); //position du mot
	if (aide==-1) { // si le mot n'est pas la alors place du mot = total
		//total ++;
		
		dico[total].mot=strdup(buff);
		//dico[total].mot=malloc(sizeof(char));
		
		//strcpy(buff,dico[total].mot);
		dico[total].occ=1;
		total++;
 	}
	else
		dico[aide].occ++; // si mot trouver alors occ du mot incrémente
	return total;
}

int affichedico(struct information dico[],int total){
	int i=0;
	 for(i=0; i<total ; i++){
               printf(" dico : mot = %s occurence = %d \n",dico[i].mot,dico[i].occ);
        }
}

int Hash(char *mot,int tailletableau,struct information dico[]){






}
/***********************************************************************/


   main(int argc, char * argv[]) {
   
      FILE *fp;
   
      if (argc < 2)
         return;
   
      if ((fp = fopen(argv[1], "r")) == NULL) {
         printf("\n Pb d'ouverture du fichier %s \n", argv[1]);
         return;
      } 
      else {
	 int tailledico=200;
         struct information *dico;
	 dico=malloc(sizeof(struct information)*tailledico);
	 char buffer[512];
	 int n = 0;
         while (lireMot(fp, &buffer[0])) {
	   // printf("a");
	   // printf ("%s",buffer);
            n=ajouter_mot(buffer,n,dico);	
	}
			affichedico(dico,n);
			printf("\n\n Il y a %d mots dans %s", n, argv[1]);
      }
   
   }



