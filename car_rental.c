#include <stdio.h>
#include "DBfunc.h"

int main(){
	char cmd[100];
	int loop = 1;

	int linesO=0;
	int linesA=0;
	int linesW=0;
	struct Osoba *tOsoby;
	struct Auto *tAuta;
	struct Wypozyczenia *tWypozyczenia;

	//tworzy tablice jestli nie istnieja
	FILE* pliko = fopen("Osoby.txt","a");
	fclose(pliko);
	FILE* plika = fopen("Auta.txt","a");
	fclose(plika);
	FILE* plikw = fopen("Wypozyczenia.txt","a");
	fclose(plikw);


	puts("Ladowanie tablic");
	linesO = InitTableOsoby(&tOsoby);
	linesA = InitTableAuta(&tAuta);
	linesW = InitTableWypozyczenia(&tWypozyczenia);
	puts("\nTablice wczytane");

	//main program loop
	while(loop){
		/*
komendy:
	wyswietl
		osoby
		auta
		wypozyczenia
	dodaj
		osobe
		auto
	usun
		osobe
		auto
	edytuj
		osobe
		auto
	szukaj
	wypozycz
	zwroc

		  */
		puts("\nPodaj komende:\n");
		scanf("%s",&cmd);
		//else if ladder eeeeww
		if(strcasecmp(cmd,"wyswietl")==0){
			scanf("%s",&cmd);
			if(strcasecmp(cmd,"osoby")==0)
				WyswietlOsoba(&tOsoby,linesO);
			else if(strcasecmp(cmd,"auta")==0)
				WyswietlAuto(&tAuta,linesA);
			else if(strcasecmp(cmd,"wypozyczenia")==0)
				WyswietlWypozyczenie(&tWypozyczenia,linesW);


		else if(strcasecmp(cmd,"dodaj")==0){
			scanf("%s",&cmd);
			if(strcasecmp(cmd,"osobe")==0)
				linesO = AddOsoba(MakeOsoba(),&tOsoby,linesO);
			else if(strcasecmp(cmd,"auto")==0)
				linesA = AddAuto(MakeAuto(),&tAuta,linesA);
		}
		else if(strcasecmp(cmd,"usun")==0){
			scanf("%s",&cmd);
			if(strcasecmp(cmd,"osobe")==0){
				char temp[50];
				int index;
				puts("Ktora osobe usunac? Wpisz wyswietl aby zobaczyc liste wszystkich osob.");
				if(strcasecmp(temp,"wyswietl")==0)
					WyswietlOsoba(&tOsoby,linesO);
			}
		}

		}
	}
}
