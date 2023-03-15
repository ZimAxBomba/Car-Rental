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
	char imie[20];
	char nazwisko[50];
	char adres[50];
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

void SaveOsoba(struct Osoba osoba){
	FILE* plik = fopen("Osoby.txt","a+");
	if(plik==NULL){
		puts("Blad zapisu w pliku");
	}
	else{
	fprintf(plik,"%d ",osoba.nr_klienta);
	fprintf(plik,"%d ",osoba.karta);
	fprintf(plik,"%s ",osoba.imie);
	fprintf(plik,"%s ",osoba.nazwisko);
	fprintf(plik,"%s ",osoba.adres);
	fprintf(plik,"%d\n",osoba.telefon);
	}
}

void SaveAuto(struct Auto a){
	FILE* plik = fopen("Auta.txt","a+");
	if(plik==NULL)
		puts("Blad zapisu w pliku");
	else{
		fprintf(plik,"%d ",a.nr_samochodu);
		fprintf(plik,"%d ",a.rejestracja);
		fprintf(plik,"%s ",a.marka);
		fprintf(plik,"%s ",a.model);
		fprintf(plik,"%d ",a.rok);
		fprintf(plik,"%s ",a.kolor);
		fprintf(plik,"%d\n",a.przebieg);
		}
	}


void SaveWypozyczenie(struct Wypozyczenia w){
	FILE* plik = fopen("Wypozyczenia.txt","a+");
	if(plik==NULL)
		puts("Blad zapisu w pliku");
	else{
		fprintf(plik,"%d ",w.nr_wyp);
		fprintf(plik,"%d ",w.nr_klienta);
		fprintf(plik,"%d ",w.nr_samochodu);
		fprintf(plik,"%d ",w.data_wyp);
		fprintf(plik,"%d ",w.data_zwrotu);
		fprintf(plik,"%d ",w.kaucja);
		fprintf(plik,"%d\n",w.cena);

	}
}

void LoadOsoba(struct Osoba *o){
	FILE* plik = fopen("Osoby.txt","r");
	if(plik==NULL)
		puts("Blad odycztu pliku");
	else{
		fscanf(plik,"%d",&o->nr_klienta);
		fscanf(plik,"%d",&o->karta);
		fscanf(plik,"%s",&o->imie);
		fscanf(plik,"%s",&o->nazwisko);
		fscanf(plik,"%s",&o->adres);
		fscanf(plik,"%d",&o->telefon);
	}
}
void LoadAuto(struct Auto *a){
	FILE* plik = fopen("Auta.txt","r");
	if(plik==NULL)
		puts("Blad odycztu pliku");
	else{
		fscanf(plik,"%d",&a->nr_samochodu);
		fscanf(plik,"%d",&a->rejestracja);
		fscanf(plik,"%s",&a->marka);
		fscanf(plik,"%s",&a->model);
		fscanf(plik,"%d",&a->rok);
		fscanf(plik,"%s",&a->kolor);
		fscanf(plik,"%d",&a->przebieg);
	}
}
void LoadWypozyczenie(struct Wypozyczenia *w){
	FILE* plik = fopen("Wypozyczenia.txt","r");
	if(plik==NULL)
		puts("Blad odycztu pliku");
	else{
		fscanf(plik,"%d",&w->nr_wyp);
		fscanf(plik,"%d",&w->nr_klienta);
		fscanf(plik,"%d",&w->nr_samochodu);
		fscanf(plik,"%d",&w->data_wyp);
		fscanf(plik,"%d",&w->data_zwrotu);
		fscanf(plik,"%d",&w->kaucja);
		fscanf(plik,"%d",&w->cena);
	}
}
