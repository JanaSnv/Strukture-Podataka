#define _CRT_SECURE_NO_WARNINGS //ili _s za fopen, fscanf itd
#include <stdio.h>
#include <stdlib.h>

typedef struct _Student {
	char name[50];
	char lastName[50];
	int points;
}stud;

int main() {

	int i = 0;
	int brojac = 0;
	char buffer[50] = { 0 }; //za privremeno spremit podatke
	stud* studenti = NULL;

	FILE* fp;
	fp = fopen("popis.txt", "r");

	if (!fp) {
		printf("Greska");
		return -1;
	}

	/*while (!feof) {
		fgets(buffer, 50, fp);
			brojac++;

	sa predavanja - ne radi??
	vjv cita zadnji red dva puta, pitaj lanu
	}*/

	while (fgets(buffer, 50, fp) != NULL) {
		brojac++;
	} //di spreman, koliko cita, iz kojeg fajla


	printf("broj studenata: %d\n", brojac); //provjera


	studenti = (stud*)malloc(brojac * sizeof(stud));
	if (!fp) { //mozda bilo tocnije (studenti==NULL)?
		printf("Greska kod alokacije memorije\n");
		free(studenti);
		fclose(fp);
		return -1;
	}

	rewind(fp); //vraca pokazivac na pocetak datoteke

	/*while (!feof(fp)) {
		fscanf(fp, "%s %s %d", studenti[i].name, studenti[i].lastName, &studenti[i].points); //"%s %s %d" - bez zareza jer mi je tako u datoteci
			i++;
	}
	opet ne radi feof il ja ne kontan while petlju */

	for (i = 0; i < brojac; i++) {
		fscanf(fp, "%s %s %d", studenti[i].name, studenti[i].lastName, &studenti[i].points);
	}

	int maxBodovi = studenti[0].points; //predpostavin da prvi ima najvise bodova
	for (i = 1;i < brojac;i++) {
		if (studenti[i].points > maxBodovi){
			maxBodovi = studenti[i].points;
		}
	}//trazin max broj bodova za izracunat relativni broj bodova

	for (i = 0;i < brojac;i++) {
		float relativni = (float)studenti[i].points / maxBodovi * 100;
		//zadana formula za racunat relativne bodove

		printf("%s %s: %d, %.2f%% \n", studenti[i].name, studenti[i].lastName, studenti[i].points, relativni); //.2 - dvi decimale, %% pise posto
	}

	fclose(fp);
	free(studenti);//ocistit alociranu memoriju!!

	return 0;
}