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

int insertBegin(char* ime, char* prez, int god, Position p) {
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL) {
		free(newPerson); 
		printf("Greška kod alokacije memorije!\n");
		return -1;
	}//provjera alokacije memorije!!
	newPerson->birthYear = god;
	strcpy(newPerson->name, ime);
	strcpy(newPerson->lastName, prez);
	newPerson->next = NULL;
	insertAfter(p, newPerson);

	return 0;
} //dodavanje na pocetak liste, zad pod a

void ispis(Position p) {
	for (Position q = p->next; q != NULL; q = q->next) {
		printf("%s %s %d\n", q->name, q->lastName, q->birthYear);
	}
	
}//ispis liste, zad pod b

int insertEnd(char* ime,char* prez, int god, Position p) {
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL) {
		free(newPerson);
		printf("Greška kod alokacije memorije!\n");
		return -1;
	}
	newPerson->birthYear = god;
	strcpy(newPerson->name, ime);
	strcpy(newPerson->lastName, prez);
	newPerson->next = NULL;
	while (p->next != NULL) {
		p = p->next;
	}//putujemo do zadnjeg elementa liste
	insertAfter(p, newPerson);

	return 0;
} //dodavanje na kraj liste, zad pod c

Position findLName(char* lastN, Position p) {
	for (Position q = p->next;q!=NULL; q = q->next) {
		if (strcmp(q->lastName, lastN) == 0)
			return q;//vraca adresu osobe
		
		}
	return NULL;//ako ne nade osobu vraca NULL
}//trazenje po prezimenu, zad pod d

int deletePerson(const char* lastN, Position p) {
	Position prev = p;//postavljeno na head
	Position curr = prev->next; //postavljeno na prvi stvarni element liste
	while (curr != NULL && strcmp(curr->lastName, lastN) != 0) {
		prev = curr;
		curr = curr->next;
	}//prev i curr micemo dok ne nadjemo osobu s tim prezimenom ili dok ne dodjemo do kraja liste
	if (curr == NULL) {
		printf("Osoba s tim prezimenom ne postoji!\n");
		return -1;
	}
	prev->next = curr->next;//spaja clan prije i poslje curr
	free(curr);//oslobadja memoriju
	return 0;
} //brisanje osobe iz liste, zad pod e

int main() {
	Person head = { .name = "", .lastName = "", .birthYear = 0, .next = NULL };
	Position p = &head;

	insertBegin("Eren","Yeager", 2004, p);
	insertBegin("Mikasa","Ackerman", 2005, p);
	insertEnd("Armin", "Arlert", 2005, p);
	ispis(p);

	Position found = findLName("Ackerman", p);
	if (found != NULL) {
		printf("\nOsoba %s %s %d je pronadena\n\n", found->name, found->lastName, found->birthYear);
	}
	else {
		printf("Osoba nije pronadena\n");
	}

	deletePerson("Yeager", p);
	ispis(p);
	return 0;
}
