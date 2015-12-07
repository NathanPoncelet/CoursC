#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
typedef struct information{
        char *mot;
        int occ;
	struct information *psuivant;
}information;
typedef struct Dico{
    struct information *premier;
}Dico;


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

void add(struct Dico dico,char * mot){
	struct information *Nouv=malloc(sizeof(information));
/*	if(dico==NULL || Nouv==NULL)
		return;*/
	Nouv->mot=mot;
	Nouv->psuivant=dico.premier;
	dico.premier=Nouv;
}

int recherche(struct Dico dico,char *mot){
	int n=0;
	/*if(dico==NULL)	
		return;*/
	struct information *pos =malloc(sizeof(information));
	*pos = *dico.premier;
	while(pos != NULL){
		if(strcmp(pos->mot,mot)==0)
			return 1;
		pos=pos->psuivant;
	}
	return n;
}

void occ(struct Dico dico,char *mot){
        /*if(dico==NULL)
                return;*/
        struct information *pos=malloc(sizeof(information));
	pos=dico.premier;
        while(pos != NULL){
                if(strcmp(pos->mot,mot)==1)
                        pos->occ++;
                pos=pos->psuivant;
        }
}

void ajouter_mot(char *buff, struct Dico dico){
        int aide=recherche(dico,buff); //position du mot
        if (aide==0) { // si le mot n'est pas la alors place du mot = total
                add(dico,buff);
        }
        else
                        occ(dico,buff); // si mot trouver alors occ du mot incrémente
}

void afficherListe(struct Dico *dico){
    struct information *p = dico->premier;
    while (p != NULL) {
        printf("mot:%s occ:%d \n ", p->mot,p->occ);
        p = p->psuivant;
    }
}

/***********************************************************************/


   main(int argc, char * argv[]) {
      FILE *fp;
      struct Dico *dico = malloc(sizeof(Dico));
      if (argc < 2)
         return;
      if ((fp = fopen(argv[1], "r")) == NULL) {
         printf("\n Pb d'ouverture du fichier %s \n", argv[1]);
         return;
      } 
      else {
         char buffer[512];
			int n = 0;
         while (lireMot(fp, &buffer[0])) {
		ajouter_mot(buffer,*dico);		
         }
			afficherListe(dico);
			printf("\n\n Il y a %d mots dans %s", n, argv[1]);
      }
   }



