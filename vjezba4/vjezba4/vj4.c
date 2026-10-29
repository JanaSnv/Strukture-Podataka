#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Poly* Position;
typedef struct _Poly {
	int coeff;
	int exp;
	Position next;
} polynom;

int insertAfter(Position p, Position newPoly) {
	newPoly->next = p->next;
	p->next = newPoly;
	return 0;
}//umetnen novi cvor iza nekog

// sortirano unosin i zbrajan iste
int insertSorted(int coef, int exp, Position p) {
	if (coef == 0) return 0; //samo preskocin ako mi je coeff 0

	Position prev = p;
	Position curr = p->next;

	while (curr != NULL && curr->exp > exp) {
		prev = curr;
		curr = curr->next;
	}//stavljan od najvecega exp

	if (curr != NULL && curr->exp == exp) {
		curr->coeff += coef;//ako su isti exp zbrajan coeff

		if (curr->coeff == 0) {//ako je sad neki coeff 0 brisen ga
			prev->next = curr->next;
			free(curr);
		}
	}
	else {
		Position newPoly = (Position)malloc(sizeof(polynom));
		if (newPoly == NULL) {
			printf("Greska kod alokacije memorije\n");
			return -1;
		}//ako nisu isti samo radin novi cvor
		newPoly->coeff = coef;
		newPoly->exp = exp;
		newPoly->next = NULL;

		insertAfter(prev, newPoly);
	}

	return 0;
}

void ispis(Position p) {
	Position q = p->next;
	if (q == NULL) {
		printf("0\n");
		return;
	}//ako mi je lista prazna

	while (q != NULL) {
		if (q->coeff > 0 && q != p->next) {
			printf("+");
		}//ako je pozz, a nije prvi clan ubacin + (ako je neg - ce se ionako ispisat)

		printf("%dx^%d ", q->coeff, q->exp);

		q = q->next;
	}
	printf("\n");
}

int readFromFile(Position p, char* filename) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Greska kod otvaranja datoteke '%s'\n", filename);
		return -1;
	}//otvorin datoteku i provjeravan!!

	int coef = 0;
	int exp = 0;

	while (fscanf(fp, "%d %d", &coef, &exp) == 2) {
		insertSorted(coef, exp, p);
	}//citan i sortiran dok god cita i coeff i exp

	fclose(fp); //zatvorin kad cin san gotova sa fileon, ne tek na kraju koda!!
	return 0;
}

int addPoly(Position p1, Position p2, Position pr) {
	Position q1 = p1->next;
	Position q2 = p2->next;

	while (q1 != NULL) {
		insertSorted(q1->coeff, q1->exp, pr);
		q1 = q1->next;
	}//slozin el iz prvog poly glavni polinom

	while (q2 != NULL) {
		insertSorted(q2->coeff, q2->exp, pr);
		q2 = q2->next;
	}//ubacin i el iz drugog poly, zbrojin ih u funkciji za sortiranje

	return 0;
}

int multiPoly(Position p1, Position p2, Position pr) {
	Position q1 = p1->next;

	while (q1 != NULL) {
		Position q2 = p2->next;
		while (q2 != NULL) {
			int newCoef = q1->coeff * q2->coeff;
			int newExp = q1->exp + q2->exp;
			//mnozin svaki el iz prvog poly sa svakin iz drugog

			insertSorted(newCoef, newExp, pr);
			q2 = q2->next;
		}//sortirano unesen i zbroje se isti
		q1 = q1->next;
	}

	return 0;
}

int freeList(Position p) {
	Position current = p->next;
	while (current != NULL) {
		Position temp = current;
		current = current->next;
		free(temp);
	}
	p->next = NULL;
	return 0;
}//oslobodi uvik na kraju!!

int main() {
	polynom headP1 = { .coeff = 0, .exp = 0, .next = NULL };
	polynom headP2 = { .coeff = 0, .exp = 0, .next = NULL };
	polynom headSuma = { .coeff = 0, .exp = 0, .next = NULL };
	polynom headProdukt = { .coeff = 0, .exp = 0, .next = NULL };

	char* file1 = "polinom1.txt";
	char* file2 = "polinom2.txt";

	if (readFromFile(&headP1, file1) != 0 || readFromFile(&headP2, file2) != 0) {
		printf("Prekid programa zbog greske s datotekama\n");
		return -1;
	}

	printf("Polinom 1 (iz %s): ", file1);
	ispis(&headP1);

	printf("Polinom 2 (iz %s): ", file2);
	ispis(&headP2);

	addPoly(&headP1, &headP2, &headSuma);
	printf("\nSuma polinoma: ");
	ispis(&headSuma);

	multiPoly(&headP1, &headP2, &headProdukt);
	printf("Produkt polinoma: ");
	ispis(&headProdukt);

	freeList(&headP1);
	freeList(&headP2);
	freeList(&headSuma);
	freeList(&headProdukt);

	return 0;
}
