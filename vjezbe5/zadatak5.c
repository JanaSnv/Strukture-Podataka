#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct stack* position;

typedef struct stack {
	int number;
	position next;
} stack; //stoj je kao lista al mogu samo upisivat i brisat sa vrha stoga

int push(int number, position head) {

	position new = (position)malloc(sizeof(stack));
	if (new == NULL) {
		printf("Greska kod alokacije memorije\n");
		return -1;
	}//alokacija i provjera

	new->number = number;
	new->next = head->next;
	head->next = new;

	return 0;
}//upis novog el na vrh stoga

int pop(position head, int* number) {
	if (head->next == NULL) return -1;//prazan stoga, greska

	position temp = head->next;
	*number = temp->number;//spreman ga da ga ne izgubin

	head->next = temp->next;//pomaknen pokazivac na iduci el
	free(temp); //zap obrisen onaj sa vrha iz memorije
	return 0;
}//brisanje el sa vrha stoga

int calc(char* file, position head, int* result) {

	FILE* fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Greska kod otvaranja datoteke '%s'\n", file);
		return -1;
	}//otvorin file za citat i provjeravan
	
	char c;//za ucitat znakove sa stoga
	int a, b, r;//za racunanje

	while (fscanf(fp, " %c", &c) == 1) {//vrti se dok cita znak iz filea

		if (isdigit((unsigned char)c)) {//provjera jel znak broj
			if (push(c - '0', head) == -1) {//c - '0' pretvara char u int ('0' je 48 a '1' je 49 itd)
				fclose(fp);
				return -1;
			}//ako je jednako -1 neka je greska, zatvaran file
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {//provjera jel skinuti el operator
			if (pop(head, &b) == -1 || pop(head, &a) == -1) {
				fclose(fp);
				return -1;
			}//skidan dva el sa vrha, b je zadnji, a predzadnji 
			//ako doden do kraja stoga, greska, zatvaran file

			switch (c) {
			case '+':
				r = a + b;
				break;
			case '-':
				r = a - b;
				break;
			case '*':
				r = a * b;
				break;
			case '/':
				if (b == 0) {
					fclose(fp);
					return -1;
				}//provjera zbog djeljenja sa 0
				r = a / b;
				break;
			}

			if (push(r, head) == -1) {
				fclose(fp);
				return -1;
			}//rezultat stavljan na vrh stoga + provjera
		}
	}

	if (head->next != NULL && head->next->next == NULL) {//provjerin jel mi samo rezultat na stogu
		pop(head, result);//skidan ga i spreman u result
	}
	else {
		fclose(fp);
		return -1;
	}
	fclose(fp);//zatvori file cin zavrsis radit sa njin!!!
	return 0;
}

void deleteAll(position head) {
	int broj;
	while (head->next != NULL) {//dok god ima el na stogu
		pop(head, &broj);
	}//skidan i brisan el sa stoga
}

int main() {
	stack head = { .number = 0, .next = NULL };//postavljan head na 0 i pokazuje na NULL (prazan stog)
	int result;

	if (calc("data.txt", &head, &result) == 0) {
		printf("Result: %d\n", result);
	}
	else printf("Greska");

	deleteAll(&head);

	return 0;
}