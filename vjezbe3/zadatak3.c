#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person* Position;

typedef struct _Person {
	char name[50];
	char lastName[50];
	int birthYear;
	Position next; //pokazivac na sljedeci element u listi
} Person;

int insertAfter(Position p, Position newP) {
	newP->next = p->next;//bitno!!
	p->next = newP;
	return 0;
}

int insertEnd(char* ime, char* prez, int god, Position p) {
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL) {
		printf("Greska kod alokacije memorije\n");
		return -1;
	}
	newPerson->birthYear = god;
	strcpy(newPerson->name, ime);
	strcpy(newPerson->lastName, prez);
	newPerson->next = NULL;

	while (p->next != NULL) {
		p = p->next;
	}// putujemo do zadnjeg elementa liste
	insertAfter(p, newPerson);

	return 0;
}//dodavanje na kraj

void ispis(Position p) {
	if (p->next == NULL) {
		printf("Lista je prazna\n");
		return;
	}
	for (Position q = p->next; q != NULL; q = q->next) {
		printf("%s %s %d\n", q->name, q->lastName, q->birthYear);
	}
}//ispis liste

Position findLName(char* lastN, Position p) {
	for (Position q = p->next;q != NULL; q = q->next) {
		if (strcmp(q->lastName, lastN) == 0)
			return q;//vraca adresu osobe

	}
	return NULL;//ako ne nade osobu vraca NULL
}//trazenje po prezimenu



// treci zadatak
int insertAfterElement(char* targetLastName, char* ime, char* prez, int god, Position p) {
	Position target = findLName(targetLastName, p);
	if (target == NULL) {
		printf("Osoba iza koje zelite umetnuti novu ne postoji\n");
		return -1;
	}

	Position newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL) {
		printf("Greska kod alokacije memorije\n");
		return -1;
	}
	newPerson->birthYear = god;
	strcpy(newPerson->name, ime);
	strcpy(newPerson->lastName, prez);
	newPerson->next = NULL;

	insertAfter(target, newPerson);
	return 0;
}

int insertBeforeElement(char* targetLastName, char* ime, char* prez, int god, Position p) {
	Position prev = p;//head
	Position curr = prev->next;//prvi el

	while (curr != NULL && strcmp(curr->lastName, targetLastName) != 0) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL) {
		printf("Osoba ispred koje zelite umetnuti novu ne postoji\n");
		return -1;
	}

	Position newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL) {
		printf("Greska kod alokacije memorije\n");
		return -1;
	}
	newPerson->birthYear = god;
	strcpy(newPerson->name, ime);
	strcpy(newPerson->lastName, prez);
	newPerson->next = NULL;

	insertAfter(prev, newPerson);//ubacin nakon prev odnosno prije curr
	return 0;
}

int sortList(Position p) {
	if (p->next == NULL || p->next->next == NULL) {
		return 0;
	}//prazna lista ili jedan el

	Position i, prev_i;
	Position end = NULL;

	while (p->next != end) {
		prev_i = p;
		i = p->next;
		while (i->next != end) {
			if (strcmp(i->lastName, i->next->lastName) > 0) {
				Position temp = i->next;
				i->next = temp->next;
				temp->next = i;
				prev_i->next = temp;
				i = temp;
			}
			prev_i = i;
			i = i->next;
		}
		end = i;
	}
	printf("Lista je sortirana po prezimenima\n");
	return 0;
}//u kolokviju ce bit sortinarn unos,ne ovo

int writeToFile(Position p, char* filename) {
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Greska kod otvaranja datoteke\n");
		return -1;
	}

	for (Position q = p->next; q != NULL; q = q->next) {
		fprintf(fp, "%s %s %d\n", q->name, q->lastName, q->birthYear);
	}//upisuje u datoteku

	fclose(fp);
	printf("Lista je zapisana u datoteku '%s'\n", filename);
	return 0;
}

int readFromFile(Position p, char* filename) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Greska kod otvaranja datoteke\n");
		return -1;
	}

	char ime[50];
	char prez[50];
	int god;

	while (fscanf(fp, "%s %s %d", ime, prez, &god) == 3) {//gleda jesu ucitana sva 3 podatka
		insertEnd(ime, prez, god, p);
	}

	fclose(fp);
	printf("Lista je uspjesno ucitana iz datoteke '%s'\n", filename);
	return 0;
}

int freeList(Position p) {
	Position current = p->next;
	while (current != NULL) {
		Position temp = current;
		current = current->next;
		free(temp); // oslobodin svak cvor
	}
	p->next = NULL; // head vracan na null
	return 0;
}//za oslobodit memoriju


int main() {
	Person head = { .name = "", .lastName = "", .birthYear = 0, .next = NULL };
	Position p = &head;

	int izbor = 0;
	char ime[50], prez[50], targetPrez[50];
	int god;
	char filename[50] = "osobe.txt";

	do {
		printf("\n========== MENI ==========\n");
		printf("1. Dodaj osobu iza odredene osobe\n");
		printf("2. Dodaj osobu ispred odredene osobe\n");
		printf("3. Sortiraj listu po prezimenima\n");
		printf("4. Upisi listu u datoteku\n");
		printf("5. Citaj listu iz datoteke\n");
		printf("6. Ispisi listu\n");
		printf("0. Izlaz iz programa\n");
		printf("==========================\n");
		printf("Odaberite opciju: ");
		scanf("%d", &izbor);

		switch (izbor) {
		case 1:
			printf("Unesite prezime osobe nakon koje zelite umetnuti novu: ");
			scanf("%s", targetPrez);
			printf("Unesite ime, prezime i godinu rodenja nove osobe: ");
			scanf("%s %s %d", ime, prez, &god);
			insertAfterElement(targetPrez, ime, prez, god, p);
			break;

		case 2:
			printf("Unesite prezime osobe ispred koje zelite umetnuti novu: ");
			scanf("%s", targetPrez);
			printf("Unesite ime, prezime i godinu rodenja nove osobe: ");
			scanf("%s %s %d", ime, prez, &god);
			insertBeforeElement(targetPrez, ime, prez, god, p);
			break;

		case 3:
			sortList(p);
			break;

		case 4:
			writeToFile(p, filename);
			break;

		case 5:
			readFromFile(p, filename);
			break;

		case 6:
			ispis(p);
			break;

		case 0:
			freeList(p);
			printf("Izlaz iz programa...\n");
			break;

		default:
			printf("Krivi odabir! Pokusajte ponovno.\n");
		}
	} while (izbor != 0);

	return 0;
}
