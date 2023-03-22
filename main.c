#include <stdio.h>
#include "DBfunc.h"
int main(){
/*
	struct Osoba o;
	o.nr_klienta = 1;
	o.karta = 9120387;
	o.imie = "Tomek";
	o.nazwisko = "Terka";
	o.adres = "test";
	o.telefon = 21378412;

	SaveOsoba(o);

	o.nr_klienta = 2;
	o.karta = 1237641;
	o.imie = "Andjrzej";
	o.nazwisko = "Duda";
	o.adres = "teseffefwef";
	o.telefon = 9999999;

	SaveOsoba(o);


	return 0;
	

	struct Osoba o;
	o.nr_klienta=0;
	//Uzycie referencji aby zmienic oryginalna wartosc
	int pos = LoadOsoba(&o,0);
	printf("%d",o.nr_klienta);
	puts("\n");
	printf("%d",o.karta);
	puts("\n");
	printf("%s",o.imie);
	puts("\n");
	printf("%s",o.nazwisko);
	puts("\n");
	printf("%s",o.adres);
	puts("\n");
	printf("%d",o.telefon);
	puts("\n");
	
	LoadOsoba(&o,pos);
	printf("%d",o.nr_klienta);
	puts("\n");
	printf("%d",o.karta);
	puts("\n");
	printf("%s",o.imie);
	puts("\n");
	printf("%s",o.nazwisko);
	puts("\n");
	printf("%s",o.adres);
	puts("\n");
	printf("%d",o.telefon);
	puts("\n");

	//InitTableOsoby(rozmiar,*tablica);
	*/
	struct Osoba *tOsoby;
	InitTableOsoby(&tOsoby);
	
	//printf("%d",tOsoby[0].nr_klienta);
	//printf("\n%d",tOsoby[1].nr_klienta);
	return 0;

}
