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
	puts("Wpisz pomoc aby wyswietlic wszystkie dostepne komendy");
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
		osoby
		auta
		wypozyczenia
	wypozycz
	zwroc
	//nowe
	pokazWypozyczenia
		osoby
		auta

		  */
		puts("\n\nPodaj komende:\n");
		scanf("%s",&cmd);
		//else if ladder eeeeww
		if(strcasecmp(cmd,"pomoc")==0){
			printf("Dostepne komendy:\n\tWyswietl\n\t\t osoby\n\t\t auta\n\t\t wypozyczenia\n\t Dodaj\n\t\t osobe\n\t\t auto\n\t Edytuj\n\t\t osobe\n\t\t auto\n\t Usun\n\t\t osobe\n\t\t auto\n\t Szukaj\n\t\t osobe\n\t\t auto\n\t\t wypozyczenia\n\t Wypozycz\n\t Zwroc");
		}
		else if(strcasecmp(cmd,"wyswietl")==0){
			scanf("%s)",&cmd);
			if(strcasecmp(cmd,"osoby")==0){
				printf("Index|Nr. klienta|Nr. karty|Imie|Nazwisko|Adres|Nr. telefonu|Wypozycza \n");
			if(!linesO)
				puts("Brak osob");
			int i;
			for(i=0;i<linesO;i++){
				printf("%d.|",i);
				WyswietlOsoba(&tOsoby,i);
				}
			}
			else if(strcasecmp(cmd,"auta")==0){
				printf("Nr. samochodu|Rejestracja|Marka|Model|Rok|Kolor|Przebieg|Wypozyczony \n");
				if(!linesA)
					puts("Brak aut");
			int i;
			for(i=0;i<linesA;i++){
				printf("%d.|",i);
				WyswietlAuto(&tAuta,i);
				}
			}
			else if(strcasecmp(cmd,"wypozyczenia")==0){
				printf("Nr. wypozyczenia|Nr. klienta|Nr. samochodu|Data wypozyczenia|Data zwrotu|Kaucja|Cena \n");
				if(!linesW)
					puts("Brak wypozyczen");
			int i;
			for(i=0;i<linesW;i++){
				printf("%d.|",i);
				WyswietlWypozyczenie(&tWypozyczenia,i);
			}
			}
		}


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
				int lop=1;
				char temp[50];
				int index;
				puts("Ktora osobe usunac? Wpisz wyswietl aby zobaczyc liste wszystkich osob.");
				puts("Wpisz szukaj aby wyszukac osobe do usuniecia");
				while(lop){
					scanf("%s",&temp);
					if(atoi(temp)){
						index=atoi(temp);
						RemoveOsoba(index,&tOsoby);
						lop=0;
						
					}
					else if(strcasecmp(temp,"wyswietl")==0){
						printf("Index|Nr. klienta|Nr. karty|Imie|Nazwisko|Adres|Nr. telefonu|Wypozycza \n");
					if(!linesO)
						puts("Brak osob");
						int i;
						for(i=0;i<linesO;i++){
							printf("%d.|",i);
							WyswietlOsoba(&tOsoby,i);
						}
					}		
					else if(strcasecmp(temp,"szukaj")==0)
						SearchOsoba(tOsoby,linesO);
				}
			}
		}
		else if(strcasecmp(cmd,"auto")==0){
			int lop=1;
			char temp[50];
			int index;
			puts("Ktora auto usunac? Wpisz wyswietl aby zobaczyc liste wszystkich aut.");
			puts("Wpisz szukaj aby wyszukac auto do usuniecia");
			while(lop){
				scanf("%s",&temp);
				if(atoi(temp)){
					index=atoi(temp);
					RemoveAuto(index,&tAuta);
					lop=0;
					
				}
				else if(strcasecmp(temp,"wyswietl")==0){
					printf("Nr. samochodu|Rejestracja|Marka|Model|Rok|Kolor|Przebieg|Wypozyczony \n");
				if(!linesA)
					puts("Brak aut");
					int i;
					for(i=0;i<linesA;i++){
						printf("%d.|",i);
						WyswietlAuto(&tAuta,i);
					}
				}		
				else if(strcasecmp(temp,"szukaj")==0)
					SearchAuto(tAuta,linesA);
			}	
		}
		else if(strcasecmp(cmd,"szukaj")==0){
			scanf("%s",&cmd);
			if(strcasecmp(cmd,"osobe")==0)
				SearchOsoba(tOsoby,linesO);
			else if(strcasecmp(cmd,"auto")==0)
				SearchAuto(tAuta,linesA);
			else if(strcasecmp(cmd,"wypozyczenie")==0)
				SearchWypozyczenie(tWypozyczenia,linesW);
		}
		else if(strcasecmp(cmd,"wypozycz")==0){
			linesW = AddWypozyczenie(Wypozycz(&tOsoby,&tAuta,&tWypozyczenia,linesO,linesA,linesW),&tWypozyczenia,linesW);	
		}
		else if(strcasecmp(cmd,"zwroc")==0){
			Zwroc(&tOsoby,&tAuta,&tWypozyczenia,linesO,linesA,linesW);
		}
		else if(strcasecmp(cmd,"edytuj")==0){
			scanf("%s",&cmd);
			if(strcasecmp(cmd,"osobe")==0)
				EditOsoba(&tOsoby,linesO);
		}
		else if(strcasecmp(cmd,"wypozyczenia")==0){
			scanf("%s",&cmd);
			if(strcasecmp(cmd,"osoby")==0){
				PokazWypozyczeniaOsoba(&tOsoby,&tAuta,&tWypozyczenia,linesO,linesA,linesW);
			}
			else if(strcasecmp(cmd,"auta")==0);
				PokazWypozyczeniaAuta(&tOsoby,&tAuta,&tWypozyczenia,linesO,linesA,linesW);
		}
		else if(strcasecmp(cmd,"zamknij")==0){
			puts("Zapisywanie plikow");
			Backup("Osoby.txt");
			for(int i=0;i<linesO;i++){
				if(strcmp(tOsoby[i].imie,"DELETE")==0)
					continue;
					SaveOsoba(tOsoby[i]);
				}
			puts("Zapisano osoby");

			Backup("Auta.txt");
			for(int i=0;i<linesA;i++){
				if(strcmp(tAuta[i].model,"DELETE")==0)
					continue;
					SaveAuto(tAuta[i]);
				}

			puts("Zapisano auta");

			Backup("Wypozyczenia.txt");
			for(int i=0;i<linesW;i++){
				if(tWypozyczenia[i].cena==0.0)
					continue;
					SaveWypozyczenie(tWypozyczenia[i]);
				}
			puts("Zapisano wypozyczenia");
			loop = 0;
		}

		else if(strcasecmp(cmd,"zapisz")==0){
			puts("Zapisywanie plikow");
			Backup("Osoby.txt");
			for(int i=0;i<linesO;i++){
				if(strcmp(tOsoby[i].imie,"DELETE")==0)
					continue;
					SaveOsoba(tOsoby[i]);
				}
			puts("Zapisano osoby");

			Backup("Auta.txt");
			for(int i=0;i<linesA;i++){
				if(strcmp(tAuta[i].model,"DELETE")==0)
					continue;
					SaveAuto(tAuta[i]);
				}

			puts("Zapisano auta");

			Backup("Wypozyczenia.txt");
			for(int i=0;i<linesW;i++){
				if(tWypozyczenia[i].cena==0.0)
					continue;
					SaveWypozyczenie(tWypozyczenia[i]);
				}
			puts("Zapisano wypozyczenia");
		}
	}
}
