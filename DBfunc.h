#include <string.h>
#include <stdlib.h>
struct Auto{
	unsigned int nr_samochodu;
	unsigned int rejestracja;
	char marka[20];
	char model[50];
	unsigned int rok;
	char kolor[10];
	unsigned int przebieg;

};

struct Osoba{
	unsigned int nr_klienta;
	unsigned int karta;
	char imie[20];
	char nazwisko[50];
	char adres[50];
	unsigned int telefon;
};

struct Wypozyczenia{
	unsigned int nr_wyp;
	unsigned int nr_klienta;
	unsigned int nr_samochodu;
	unsigned int data_wyp;
	unsigned int data_zwrotu;
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
	fclose(plik);
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
	fclose(plik);
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
	fclose(plik);
}

int LoadOsoba(struct Osoba *o,int pos){
	FILE* plik = fopen("Osoby.txt","r");
	fseek(plik,pos,SEEK_SET);
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
	pos = ftell(plik);
	fclose(plik);
	return pos; 
}
int LoadAuto(struct Auto *a,int pos){
	FILE* plik = fopen("Auta.txt","r");
	fseek(plik,pos,SEEK_SET);
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
	pos = ftell(plik);
	fclose(plik);
	return pos;
}
int LoadWypozyczenie(struct Wypozyczenia *w,int pos){
	FILE* plik = fopen("Wypozyczenia.txt","r");
	fseek(plik,pos,SEEK_SET);
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
	pos = ftell(plik);
	fclose(plik);
	return pos;
}

unsigned int CountLines(char plik[20]){
	FILE *p = fopen(plik,"r");
	unsigned int lines = 0;
	char c;
	do{
		c = getc(p);
		if(c=='\n')
			lines++;
	}while(c!=EOF);
	fclose(p);
	return lines;
}
void InitTableOsoby(struct Osoba **tOsoby){
//alokuje pamiec dla *tOsoby
	int lines = CountLines("Osoby.txt");
	*tOsoby = (struct Osoba*)malloc(lines*sizeof(struct Osoba));
	if(*tOsoby==NULL)
		puts("Inicializacjia tablicy Osob nie powidodla sie");

//wczytuje wszystkie osoby do tablicy
	int pos=0;
	int pos2=0;
	struct Osoba temp;
	//Zaczyna od 2 lini?>?????>???
	//to chyba przez &
	for(int i=0;i<lines;i++){
		pos = LoadOsoba(&temp,pos2);
		pos2=pos;
		tOsoby[i]=&temp;
	}
}
