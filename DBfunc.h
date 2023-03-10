#include <string.h>
struct Auto{
	int nr_samochodu;
	int rejestracja;
	char marka[20];
	char model[50];
	int rok;
	char kolor[10];
	int przebieg;

};

struct Osoba{
	int nr_klienta;
	int karta;
	char* imie;
	char* nazwisko;
	char* adres;
	int telefon;
};

struct Wypozyczenia{
	int nr_wyp;
	int nr_klienta;
	int nr_samochodu;
	int data_wyp;
	int data_zwrotu;
	float kaucja;
	float cena;

};

void SaveOsoba(struct Osoba  osoba){
	FILE* plik = fopen("Osoby.txt","a+");
	if(plik==NULL){
		puts("Blad zapisu w pliku");
	}
	else{
	fprintf(plik,"%d;",osoba.nr_klienta);
	fprintf(plik,"%d;",osoba.karta);
	fprintf(plik,"%s;",osoba.imie);
	fprintf(plik,"%s;",osoba.nazwisko);
	fprintf(plik,"%s;",osoba.adres);
	fprintf(plik,"%d\n",osoba.telefon);
	}
}
