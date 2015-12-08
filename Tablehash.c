#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define RESEARCH_FAILURE -1

struct information{
	int key;
	int occ;
	char *mot;
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


int recherche(int key,struct information dico[], int total){
	int i=0;
	for(i=0; i<total ; i++){
		if(dico[i].key==key)
			return i;// si découverte du mot renvoie a la position ou l'on a trouvé le mot
	}
	return RESEARCH_FAILURE;
}


int ajouter_mot(char *buff, int total, struct information dico[],int tailletableau){
	int clef=Hash(buff,tailletableau);
	int aide=recherche(clef,dico,total); //position du mot
	if (aide==RESEARCH_FAILURE) { // si le mot n'est pas la alors place du mot = total
		dico[total].key=clef;
		dico[total].mot=strdup(buff);
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
               printf(" dico : mot = %s occurence = %d  key= %d \n",dico[i].mot,dico[i].occ,dico[i].key);
        }
}

int Hash(char *mot,int tailletableau){
	int ristouquette=0;
	int aide=sizeof(mot);
	int i;
	for(i=0;i<aide;i++){
		ristouquette=ristouquette+mot[i];
	}
	return ristouquette%tailletableau;
}




/*void RechercheMot(struct information dico[],int total,int tailletableau){
	printf("tape le mot que tu recherche pd \n");
	char *mot;
	scanf("%s",mot);
	int has=Hash(mot,tailletableau);
	printf("%d \n\n",has);
	int i=recherche(has,dico,total);
	printf("%d\n\n",i);
	if(i==RESEARCH_FAILURE)
		printf("Ael pd");
	else
		printf("Victime boloss");
}*/
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
            n=ajouter_mot(buffer,n,dico,tailledico);
	    printf("ristouquette : %d \n",Hash(buffer,tailledico));	
	}
			printf("resultat final : \n\n\n\n");
			affichedico(dico,n);
			printf("\n\n Il y a %d mots dans %s", n, argv[1]);
     			//printf("\n Maintenant viens rechercher un mot : \n\n");
			//RechercheMot(dico,n,tailledico);

	 }
   
   }



