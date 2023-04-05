#include <stdio.h>
#include "DBfunc.h"



int main(){
	int cmd;
	int loop = 1;
	int n;

	int linesO=0;
	int linesA=0;
	int linesW=0;
	struct Osoba *tOsoby;
	struct Auto *tAuta;
	struct Wypozyczenia *tWypozyczenia;

	puts("Ladowanie tablic");
	linesO = InitTableOsoby(&tOsoby);
	linesA = InitTableAuta(&tAuta);
	linesW = InitTableWypozyczenia(&tWypozyczenia);
	puts("\nTablice wczytane");


	while(loop){
		puts("\nPodaj komende:\n");
		scanf("%d",&cmd);
		switch(cmd){
		default:
			puts("Wpisz 0 aby wyswietlic pomoc, 9 aby wyjsc");
			break;
		case 0:
			puts("1 - Osoba\n 2 - Auto\n 3 - Wypozyczenia\n");
			puts("\n1(1,2,3) - wyswietl\n");
			puts("2(1,2,3) - dodaj\n");
			puts("3(1,2,3) - usun\n");
			break;

		case 11:
			WyswietlOsoba(&tOsoby,linesO);
			break;
		case 12:
			WyswietlAuto(&tAuta,linesA);
			break;
		case 13:
			WyswietlWypoczyenie(&tWypozyczenia,linesW);
			break;
		case 21:
			linesO = AddOsoba(MakeOsoba(),&tOsoby,linesO);
			break;
		case 22:
			linesA = AddAuto(MakeAuto(),&tAuta,linesA);
			break;
		case 23:
			linesW = AddWypozyczenie(MakeWypozyczenia(),&tWypozyczenia,linesW);
			break;
		case 31:
			puts("Usunac ktory wiersz tablicy?: ");
			scanf("%d",&n);
			RemoveOsoba(n,&tOsoby);
			break;
		//tak dalej
		case 9:
			loop = 0;
			break;
		}
	}

}
