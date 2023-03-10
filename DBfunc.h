#include <string.h>
struct Auto{
	int nr_samochodu;
	int rejestracja;
	char[20] marka;
	char[50] model;
	int rok;
	char[10] kolor;
	int przebieg;

};

struct Osoba{
	int nr_klienta;
	int karta;
	char[20] imie;
	char[50] nazwisko;
	char[50] adres;
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


