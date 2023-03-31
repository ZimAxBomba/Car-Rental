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
//alt
int LoadOsobaAlt(struct Osoba *o,int pos){
	FILE* plik = fopen("Osoby.txt","r");
	fseek(plik,pos,SEEK_SET);
	if(plik==NULL)
		puts("Blad odczytu pliku");
	else{
		char string[200];
		fgets(string,200,plik);
		//printf("%s\n",string);
		//more robust than scanf()
		char *temp = strtok(string,";");
		/*
		while(temp!=NULL){
			printf("%s\n",temp);
			temp = strtok(NULL,";");
		}
		*/
		o->nr_klienta=atoi(temp);
		temp = strtok(NULL,";");
		o->karta=atoi(temp);
		temp = strtok(NULL,";");
		memcpy(o->imie,temp,sizeof(o->imie));
		temp = strtok(NULL,";");
		memcpy(o->nazwisko,temp,sizeof(o->nazwisko));
		temp = strtok(NULL,";");
		memcpy(o->adres,temp,sizeof(o->adres));
		temp = strtok(NULL,";");
		o->telefon=atoi(temp);
	}
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
int InitTableOsoby(struct Osoba **tOsoby){
//alokuje pamiec dla *tOsoby
	int lines = CountLines("Osoby.txt");
	*tOsoby = malloc(lines*sizeof(struct Osoba));
	if(*tOsoby==NULL)
		puts("Inicializacjia tablicy Osob nie powidodla sie");

//wczytuje wszystkie osoby do tablicy
	int pos=0;
	struct Osoba temp;
	for(int i=0;i<lines;i++){
		pos = LoadOsoba(&temp,pos);
		(*tOsoby)[i].nr_klienta = temp.nr_klienta;
		(*tOsoby)[i].karta = temp.karta;
		memcpy((*tOsoby)[i].imie,temp.imie,sizeof(temp.imie));
		memcpy((*tOsoby)[i].nazwisko,temp.nazwisko,sizeof(temp.nazwisko));
		memcpy((*tOsoby)[i].adres,temp.adres,sizeof(temp.adres));
		(*tOsoby)[i].telefon = temp.telefon;
	}
	return lines;
}

int InitTableAuta(struct Auto **tAuta){
//alokuje pamiec dla *tAuta
	int lines = CountLines("Auta.txt");
	*tAuta = malloc(lines*sizeof(struct Auto));
	if(*tAuta==NULL)
		puts("Inicializacjia tablicy Aut nie powidodla sie");

//wczytuje wszystkie Auta do tablicy
	int pos=0;
	struct Auto temp;
	for(int i=0;i<lines;i++){
		pos = LoadAuto(&temp,pos);
		(*tAuta)[i].nr_samochodu = temp.nr_samochodu;
		(*tAuta)[i].rejestracja = temp.rejestracja;
		memcpy((*tAuta)[i].marka,temp.marka,sizeof(temp.marka));
		memcpy((*tAuta)[i].model,temp.model,sizeof(temp.model));
		(*tAuta)[i].rok = temp.rok;
		memcpy((*tAuta)[i].kolor,temp.kolor,sizeof(temp.kolor));
		(*tAuta)[i].przebieg = temp.przebieg;
	}
	return lines;
}

int InitTableWypozyczenia(struct Wypozyczenia **tWypozyczenia){
//alokuje pamiec dla *tWypozyczenia
	int lines = CountLines("Wypozyczenia.txt");
	*tWypozyczenia = malloc(lines*sizeof(struct Wypozyczenia));
	if(*tWypozyczenia==NULL)
		puts("Inicializacjia tablicy Wypozyczen nie powidodla sie");

//wczytuje wszystkie wypozyczenia do tablicy
	int pos=0;
	struct Wypozyczenia temp;
	for(int i=0;i<lines;i++){
		pos = LoadWypozyczenie(&temp,pos);
		(*tWypozyczenia)[i].nr_wyp = temp.nr_wyp;
		(*tWypozyczenia)[i].nr_klienta = temp.nr_klienta;
		(*tWypozyczenia)[i].nr_samochodu = temp.nr_samochodu;
		(*tWypozyczenia)[i].data_wyp = temp.data_wyp;
		(*tWypozyczenia)[i].data_zwrotu= temp.data_zwrotu;
		(*tWypozyczenia)[i].kaucja = temp.kaucja;
		(*tWypozyczenia)[i].cena = temp.cena;
	}
	return lines;
}

int AddOsoba(struct Osoba temp,struct Osoba **tOsoby,int lines){
	*tOsoby = realloc(*tOsoby,(lines+1)*sizeof(struct Osoba));

	(*tOsoby)[lines].nr_klienta = temp.nr_klienta;
		(*tOsoby)[lines].karta = temp.karta;
		memcpy((*tOsoby)[lines].imie,temp.imie,sizeof(temp.imie));
		memcpy((*tOsoby)[lines].nazwisko,temp.nazwisko,sizeof(temp.nazwisko));
		memcpy((*tOsoby)[lines].adres,temp.adres,sizeof(temp.adres));
		(*tOsoby)[lines].telefon = temp.telefon;
		return lines+1;
}

int RemoveOsoba(int index,struct Osoba **tOsoby,int lines){
//albo wyzerowac element i uwzglednic to przy zapisywaniu
//albo cofnac cala tablice o jeden i realokowac
}
