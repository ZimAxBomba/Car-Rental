/**
  *@file DBfunc.h
  *Plik zawierajace wszystkie funkcje potrzebne dla bazy danych.
  @author Jakub Golebiowski Oskar Firlej Kamil Zajac
  */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
/**
  *@brief Struktura zwierajaca pola rekordow dla aut.
  *@var nr_samochodu Unikalny numer ID samochodu.
  *@var rejestracja Rejestracja auta, maksymalna dlugosc 7 znakow.
  *@var marka Marka auta, maksymalnie 19 znakow.
  *@var model Model auta, maksymalnie 49 znakow.
  *@var rok Rok produkcji auta.
  *@var kolor Kolor auta, maksymalnie 9 znakow.
  *@var przebieg Przebieg auta.
  *@var wyp Wartosc 1 - auto jest wypozyczane, 0 - nie jest wypozyczane.
  */
struct Auto{
	unsigned int nr_samochodu;
	unsigned char rejestracja[8];
	char marka[20];
	char model[50];
	unsigned char rok[5];
	char kolor[10];
	unsigned int przebieg;
	unsigned int wyp;//ozyczenie

};
/**
  *@brief Struktura zawierajaca pola rekordow dla osoby.
  *@var nr_klienta Unikalny numer ID osoby.
  *@var imie Imie osoby, maksymalnie 19 znakow.
  *@var nazwisko Nazwisko osoby, maksymalnie 49 znakow.
  *@var adres Adres osoby, maksymalnie 49 znakow.
  *@var telefon Numer telefonu osoby, 9 cyfr.
  *@var wyp Wartosc 1 - osoba wypozycza auto, 0 - osoba nie wypozycza zadnego auta.
  */
struct Osoba{
	unsigned int nr_klienta;
	unsigned char karta[17];
	char imie[20];
	char nazwisko[50];
	char adres[50];
	unsigned char telefon[10];
	unsigned int wyp;//ozyczenie
};

/**
  *@brief Struktura zwierajaca dane na temat wypozyczenia.
  *@var nr_wyp Unikalny numer wypozyczenia.
  *@var nr_klienta Istniejacy juz numer klienta, ktory wypozycza dane auto.
  *@var nr_samochodu Numer auta, ktore jest wypozyczane.
  *@var data_wyp Data wypozyczneia auta w formacie dd-mm-yyyy.
  *@var data_zwrotu zwrotu auta w formacie dd-mm-yyyy.
  *@var kaucja Kaucja wypozyczenia.
  *@var cena Cena wypozyczenia.
  */
struct Wypozyczenia{
	unsigned int nr_wyp;
	unsigned int nr_klienta;
	unsigned int nr_samochodu;
	//dd-mm-yyyy
	unsigned char data_wyp[11];
	unsigned char data_zwrotu[11];
	float kaucja;
	float cena;

};
/**
  *@brief Zapisuje pojedyczna osobe do pliku Osoby.txt
  *@param osoba Struktura pojedynczej osoby.
  */
void SaveOsoba(struct Osoba osoba){
	FILE* plik = fopen("Osoby.txt","a");
	if(plik==NULL){
		puts("Blad zapisu w pliku");
	}
	else{
	fprintf(plik,"%d;",osoba.nr_klienta);
	fprintf(plik,"%s;",osoba.karta);
	fprintf(plik,"%s;",osoba.imie);
	fprintf(plik,"%s;",osoba.nazwisko);
	fprintf(plik,"%s;",osoba.adres);
	fprintf(plik,"%s;",osoba.telefon);
	fprintf(plik,"%d\n",osoba.wyp);
	}
	fclose(plik);
}
/**
  *@brief Zapisuje pojedyczne auto do pliku Auta.txt
  *@param osoba Struktura pojedynczego auta.
  */
void SaveAuto(struct Auto a){
	FILE* plik = fopen("Auta.txt","a");
	if(plik==NULL)
		puts("Blad zapisu w pliku");
	else{
		fprintf(plik,"%d;",a.nr_samochodu);
		fprintf(plik,"%s;",a.rejestracja);
		fprintf(plik,"%s;",a.marka);
		fprintf(plik,"%s;",a.model);
		fprintf(plik,"%s;",a.rok);
		fprintf(plik,"%s;",a.kolor);
		fprintf(plik,"%d;",a.przebieg);
		fprintf(plik,"%d\n",a.wyp);
		}
	fclose(plik);
}

/**
  *@brief Zapisuje pojedycze wypozyczenie do pliku Wypozyczenia.txt
  *@param osoba Struktura pojedynczego wypozyczenia.
  */
void SaveWypozyczenie(struct Wypozyczenia w){
	FILE* plik = fopen("Wypozyczenia.txt","a");
	if(plik==NULL)
		puts("Blad zapisu w pliku");
	else{
		fprintf(plik,"%d;",w.nr_wyp);
		fprintf(plik,"%d;",w.nr_klienta);
		fprintf(plik,"%d;",w.nr_samochodu);
		fprintf(plik,"%s;",w.data_wyp);
		fprintf(plik,"%s;",w.data_zwrotu);
		fprintf(plik,"%f;",w.kaucja);
		fprintf(plik,"%f\n",w.cena);

	}
	fclose(plik);
}
/**
  *@brief Wczytuja pojedyncza osobe z pliku Osoby.txt.
  *@param o Struktura do ktorej zapisywane sa wczytane dane.
  *@param pos Pozycja kursora w pliku.
  *@return Zwraca nowa pozycje kursora w pliku (nastepna linia).
  */
int LoadOsoba(struct Osoba *o,int pos){
	FILE* plik = fopen("Osoby.txt","r");
	fseek(plik,pos,SEEK_SET);
	if(plik==NULL)
		puts("Blad odczytu pliku");
	else{
		char string[200];
		fgets(string,200,plik);
		pos = ftell(plik);
		fclose(plik);
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
		memcpy(o->karta,temp,sizeof(o->karta));
		temp = strtok(NULL,";");
		memcpy(o->imie,temp,sizeof(o->imie));
		temp = strtok(NULL,";");
		memcpy(o->nazwisko,temp,sizeof(o->nazwisko));
		temp = strtok(NULL,";");
		memcpy(o->adres,temp,sizeof(o->adres));
		temp = strtok(NULL,";");
		memcpy(o->telefon,temp,sizeof(o->telefon));
		temp = strtok(NULL,";");
		o->wyp = atoi(temp);
	}
	return pos;
}
/**
  *@brief Wczytuja pojedyncze auto z pliku Auta.txt.
  *@param a Struktura do ktorej zapisywane sa wczytane dane.
  *@param pos Pozycja kursora w pliku.
  *@return Zwraca nowa pozycje kursora w pliku (nastepna linia).
  */
int LoadAuto(struct Auto *a,int pos){
	FILE* plik = fopen("Auta.txt","r");
	fseek(plik,pos,SEEK_SET);
	if(plik==NULL)
		puts("Blad odczytu pliku");
	else{
		char string[200];
		fgets(string,200,plik);
		pos = ftell(plik);
		fclose(plik);
		char *temp = strtok(string,";");
		
		a->nr_samochodu=atoi(temp);
		temp = strtok(NULL,";");
		memcpy(a->rejestracja,temp,sizeof(a->rejestracja));
		temp = strtok(NULL,";");
		memcpy(a->marka,temp,sizeof(a->marka));
		temp = strtok(NULL,";");
		memcpy(a->model,temp,sizeof(a->model));
		temp = strtok(NULL,";");
		memcpy(a->rok,temp,sizeof(a->rok));
		temp = strtok(NULL,";");
		memcpy(a->kolor,temp,sizeof(a->kolor));
		temp = strtok(NULL,";");
		a->przebieg = atoi(temp);
		temp = strtok(NULL,";");
		a->wyp = atoi(temp);
	}
	return pos;
}
/**
  *@brief Wczytuja pojedyncze wypozyczenie z pliku Wypozyczenia.txt.
  *@param w Struktura do ktorej zapisywane sa wczytane dane.
  *@param pos Pozycja kursora w pliku.
  *@return Zwraca nowa pozycje kursora w pliku (nastepna linia).
  */
int LoadWypozyczenie(struct Wypozyczenia *w,int pos){
	FILE* plik = fopen("Wypozyczenia.txt","r");
	fseek(plik,pos,SEEK_SET);
	if(plik==NULL)
		puts("Blad odczytu pliku");
	else{
		char string[200];
		fgets(string,200,plik);
		pos = ftell(plik);
		fclose(plik);
		char *temp = strtok(string,";");
		
		w->nr_wyp=atoi(temp);
		temp = strtok(NULL,";");
		w->nr_klienta=atoi(temp);
		temp = strtok(NULL,";");
		w->nr_samochodu=atoi(temp);
		temp = strtok(NULL,";");
		memcpy(w->data_wyp,temp,sizeof(w->data_wyp));
		temp = strtok(NULL,";");
		memcpy(w->data_zwrotu,temp,sizeof(w->data_zwrotu));
		temp = strtok(NULL,";");
		w->kaucja = atof(temp);
		temp = strtok(NULL,";");
		w->cena = atof(temp);
	}
	return pos;
}

/**
  *@brief Sprawdza czy podany ciag znakow jest liczba.
  *@param str Ciag znakow do sprawdzenia.
  */
int CheckIfNumber(char str[20]){
	//for supporting floats
	int dot=0;
	for(int i=0;i<strlen(str);i++){
		if(!isdigit(str[i])){
			if(str[i]=='.')
				dot++;
			else
				return 0;
			if(dot>1)
				return 0;
		}

	}
	return 1;
}

/**
  *@brief Sprawdza, ktora z podanych dat jest wieksza.
  *
  *Zwraca 1 jesli time1 jest wieksze, -1 jesli time2 jest wieksze oraz 0 gdy daty sa rowne.
  *@param time1 Ciag znakow reprezentujacy date.
  *@param time2 Ciag znakow reprezentujacy date.
  *@return Zwraca, ktora data jest wieksza.
  */
int CompareTime(char time1[11],char time2[11]){
	//1 - time1 wieksze
	//0 - rowne
	//-1 - time2 wieksze
	int d1,m1,y1;
	int d2,m2,y2;
	/*
	d1 = atoi(strtok(time1,"-"));
	m1 = atoi(strtok(NULL,"-"));
	y1 = atoi(strtok(NULL,"-"));
	//printf("\n%d %d %d",d1,m1,y1);


	d2 = atoi(strtok(time2,"-"));
	m2 = atoi(strtok(NULL,"-"));
	y2 = atoi(strtok(NULL,"-"));
	//printf("\n%d %d %d",d2,m2,y2);
	*/

	sscanf(time1,"%d-%d-%d",&d1,&m1,&y1);
	sscanf(time2,"%d-%d-%d",&d2,&m2,&y2);

	if(y1>y2)
		return 1;
	else if(y1<y2)
		return -1;
	else{
		if(m1>m2)
			return 1;
		else if(m1<m2)
			return -1;
		else{
			if(d1>d2)
				return 1;
			else if(d1<d2)
				return -1;
			else
				return 0;
		}
	}
}

/**
  *@brief Zwraca dzisiejsza date.
  */
char* CurrentTime(){
	time_t now;
	struct tm t;
	time(&now);
	t = *localtime(&now);
	char *returnTime = malloc(sizeof(char)*11);

	sprintf(returnTime,"%d-%d-%d",t.tm_mday,t.tm_mon+1,t.tm_year+1900);
	return returnTime;
}

/**
  *@brief Sprawdza poprawnosc daty.
  *
  *Sprawdza czy podana date jest poprawna dla formatu dd-mm-yyyy.
  *@param date Data do sprawdzenia.
  *@return Zwraca 1 jesli data jest prawidlowa, 0 jesli nie jest prawidlowa.
  */
int ValidateDate(char date[11]){
	//check if date format is valid
	for(int i=0;i<2;i++){
		if(!isdigit(date[i])){
			return 0;
		}
			}
	if(date[2]!='-')
		return 0;
	for(int i=3;i<5;i++){
		if(!isdigit(date[i])){
			return 0;
			}
		}
	if(date[5]!='-')
		return 0;
	for(int i=6;i<10;i++){
		if(!isdigit(date[i])){
			return 0;
			}
		}
	//check if date is too old or out of bounds
	char *currentDate = CurrentTime();
	int cd,cm,cy;
	sscanf(currentDate,"%d-%d-%d",&cd,&cm,&cy);
	int d,m,y;
	sscanf(date,"%d-%d-%d",&d,&m,&y);

	if(d>31){
		puts("Data jest niepoprawna, za duzo dni w miesiacu");
		return 0;
	}

	if(m>12){
		puts("Data jest niepoprawna, miesiac nie moze byc wiekszy niz 12");
		return 0;
	}
/*
	if(y<2023){
		puts("Nie mozna wypozycz auta w przeslosci");
		return 0;
	}
*/	

	return 1;
}

/**
  *@brief Czysci podany plik tekstowy
  *
  *@param n Nazwa pliku do wyczyszczenia.
  *Uzywana jest przed zapisem do plikow.
  */
//czysci plik txt (zapisuje go jako backup - w przyszlosci)
void Backup(char n[20]){
	FILE *p = fopen(n,"w");
	fclose(p);
}

/**
  *@brief Zwraca liczbe lini w pliku.
  *@param plik Nazwa pliku do sprawdzenia.
  *@return Zwraca ilosc lini.
  */
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

/**
  *@brief Inicjalizuje tablice osob.
  *
  *Funkcja tworzy dynamiczna tablice osob na podstawie plikow tekstowych z danymi.
  *@param tOsoby Wskaznik na tablice osob.
  *@return Zwraca liczbe rekordow w tablicy.
  */
int InitTableOsoby(struct Osoba **tOsoby){
//alokuje pamiec dla *tOsoby
	int lines = CountLines("Osoby.txt");
	*tOsoby = malloc(lines*sizeof(struct Osoba));
	if(*tOsoby==NULL)
		puts("Inicializacjia tablicy Osob nie powidodla sie");

//wczytuje wszystkie osoby do tablicy
	int pos=0;
	//struct Osoba temp;
	for(int i=0;i<lines;i++){
		struct Osoba temp;
		pos = LoadOsoba(&temp,pos);
		(*tOsoby)[i].nr_klienta = temp.nr_klienta;
		memcpy((*tOsoby)[i].karta,temp.karta,sizeof(temp.karta));
		memcpy((*tOsoby)[i].imie,temp.imie,sizeof(temp.imie));
		memcpy((*tOsoby)[i].nazwisko,temp.nazwisko,sizeof(temp.nazwisko));
		memcpy((*tOsoby)[i].adres,temp.adres,sizeof(temp.adres));
		memcpy((*tOsoby)[i].telefon,temp.telefon,sizeof(temp.telefon));
		(*tOsoby)[i].wyp = temp.wyp;
	}
	puts("Zainicjalizowano tablice osob.");
	return lines;
}

/**
  *@brief Inicjalizuje tablice aut.
  *
  *Funkcja tworzy dynamiczna tablice na podstawie plikow tekstowych z danymi.
  *@param tAuta Wskaznik na tablice aut.
  *@return Zwraca liczbe rekordow w tablicy.
  */
int InitTableAuta(struct Auto **tAuta){
//alokuje pamiec dla *tAuta
	int lines = CountLines("Auta.txt");
	*tAuta = malloc(lines*sizeof(struct Auto));
	if(*tAuta==NULL)
		puts("Inicializacjia tablicy Aut nie powidodla sie");

//wczytuje wszystkie Auta do tablicy
	int pos=0;
	for(int i=0;i<lines;i++){
		struct Auto temp;
		pos = LoadAuto(&temp,pos);
		(*tAuta)[i].nr_samochodu = temp.nr_samochodu;
		memcpy((*tAuta)[i].rejestracja,temp.rejestracja,sizeof(temp.rejestracja));
		memcpy((*tAuta)[i].marka,temp.marka,sizeof(temp.marka));
		memcpy((*tAuta)[i].model,temp.model,sizeof(temp.model));
		memcpy((*tAuta)[i].rok,temp.rok,sizeof(temp.rok));
		memcpy((*tAuta)[i].kolor,temp.kolor,sizeof(temp.kolor));
		(*tAuta)[i].przebieg = temp.przebieg;
		(*tAuta)[i].wyp = temp.wyp;
	}
	puts("Zainicjalizowano tablice aut.");
	return lines;
}

/**
  *@brief Inicjalizuje tablice wypozyczen.
  *
  *Funkcja tworzy dynamiczna tablice na podstawie plikow tekstowych z danymi.
  *@param tWypozyczenia Wskaznik na tablice wypozyczen.
  *@return Zwraca liczbe rekordow w tablicy.
  */
int InitTableWypozyczenia(struct Wypozyczenia **tWypozyczenia){
//alokuje pamiec dla *tWypozyczenia
	int lines = CountLines("Wypozyczenia.txt");
	*tWypozyczenia = malloc(lines*sizeof(struct Wypozyczenia));
	if(*tWypozyczenia==NULL)
		puts("Inicializacjia tablicy Wypozyczen nie powidodla sie");

//wczytuje wszystkie wypozyczenia do tablicy
	int pos=0;
	for(int i=0;i<lines;i++){
		struct Wypozyczenia temp;
		pos = LoadWypozyczenie(&temp,pos);
		(*tWypozyczenia)[i].nr_wyp = temp.nr_wyp;
		(*tWypozyczenia)[i].nr_klienta = temp.nr_klienta;
		(*tWypozyczenia)[i].nr_samochodu = temp.nr_samochodu;
		memcpy((*tWypozyczenia)[i].data_wyp,temp.data_wyp,sizeof(temp.data_wyp));
		memcpy((*tWypozyczenia)[i].data_zwrotu,temp.data_zwrotu,sizeof(temp.data_zwrotu));
		(*tWypozyczenia)[i].kaucja = temp.kaucja;
		(*tWypozyczenia)[i].cena = temp.cena;
	}

	puts("Zaininicjalizowane tablice wypozyczen.");
	return lines;
}

/**
  *@brief Dodaje osobe do tablicy osob.
  *@param temp Osoba do dodania do tablicy.
  *@param tOsoby Tablica osob do ktorej jest dodawana struktura.
  *@param lines Liczba rekordow w tablicy.
  *@return Zwraca nowa liczbe lini (lines+1).
  */
int AddOsoba(struct Osoba temp,struct Osoba **tOsoby,int lines){
		*tOsoby = realloc(*tOsoby,(lines+1)*sizeof(struct Osoba));
		
		(*tOsoby)[lines].nr_klienta = temp.nr_klienta;
		memcpy((*tOsoby)[lines].karta,temp.karta,sizeof(temp.karta));
		memcpy((*tOsoby)[lines].imie,temp.imie,sizeof(temp.imie));
		memcpy((*tOsoby)[lines].nazwisko,temp.nazwisko,sizeof(temp.nazwisko));
		memcpy((*tOsoby)[lines].adres,temp.adres,sizeof(temp.adres));
		memcpy((*tOsoby)[lines].telefon,temp.telefon,sizeof(temp.telefon));
		(*tOsoby)[lines].wyp = 0;
		return lines+1;
}

/**
  *@brief Dodaje auto do tablicy aut.
  *@param temp Auto do dodania do tablicy.
  *@param tAuta Tablica aut do ktorej jest dodawana struktura.
  *@param lines Liczba rekordow w tablicy.
  *@return Zwraca nowa liczbe rekordow (lines+1).
  */
int AddAuto(struct Auto temp,struct Auto **tAuta,int lines){
	*tAuta = realloc(*tAuta,(lines+1)*sizeof(struct Auto));
	
	(*tAuta)[lines].nr_samochodu = temp.nr_samochodu;
	memcpy((*tAuta)[lines].rejestracja,temp.rejestracja,sizeof(temp.rejestracja));
	memcpy((*tAuta)[lines].marka,temp.marka,sizeof(temp.marka));
	memcpy((*tAuta)[lines].model,temp.model,sizeof(temp.model));
	memcpy((*tAuta)[lines].rok,temp.rok,sizeof(temp.rok));
	memcpy((*tAuta)[lines].kolor,temp.kolor,sizeof(temp.kolor));
	(*tAuta)[lines].przebieg = temp.przebieg;
	(*tAuta)[lines].wyp = 0;
		return lines+1;
}

/**
  *@brief Dodaje wypozyczenie do tablicy wypozyczen.
  *@param temp Wypozyczenie do dodania do tablicy.
  *@param tWypozyczenia Tablica aut do ktorej jest dodawana struktura.
  *@param lines Liczba rekordow w tablicy.
  *@return Zwraca nowa liczbe rekordow (lines+1).
  */
int AddWypozyczenie(struct Wypozyczenia	temp,struct Wypozyczenia **tWypozyczenia,int lines){
	if(temp.cena==0)
		return lines;
	*tWypozyczenia = realloc(*tWypozyczenia,(lines+1)*sizeof(struct Wypozyczenia));
	
	(*tWypozyczenia)[lines].nr_wyp = temp.nr_wyp;
	(*tWypozyczenia)[lines].nr_klienta = temp.nr_klienta;
	(*tWypozyczenia)[lines].nr_samochodu = temp.nr_samochodu;
	memcpy((*tWypozyczenia)[lines].data_wyp,temp.data_wyp,sizeof(temp.data_wyp));
	memcpy((*tWypozyczenia)[lines].data_zwrotu,temp.data_zwrotu,sizeof(temp.data_zwrotu));
	(*tWypozyczenia)[lines].kaucja = temp.kaucja;
	(*tWypozyczenia)[lines].cena = temp.cena;
	return lines+1;
}

/**
  *@brief Usuwa osobe.
  *
  *Funkcja sprawdza czy podana osoba nie wypozycza auta.
  *Ustawia pole imie Osoby na "DELETE".
  *@param index Numer osoby w tablicy.
  *@param tOsoby Tablica osob.
  */
void RemoveOsoba(int index,struct Osoba **tOsoby){
	//sprawdzenie wypozyczenia
	if((*tOsoby)[index].wyp)
		puts("Nie mozna usunac osoby, ktora wypozycza auto");
	else
		memcpy((*tOsoby)[index].imie,"DELETE",sizeof("DELETE"));
}

/**
  *@brief Usuwa auto.
  *Funkcja sprawdza czy podane auto nie jest wypozyczone.
  *Ustawia pole model Auta na "DELETE".
  *@param index Numer osoby w tablicy.
  *@param tAuta Tablica aut.
  */
void RemoveAuto(int index,struct Auto **tAuta){
	//sprawdzenie wypozyczenia
	if((*tAuta)[index].wyp)
		puts("Nie mozna usunac auta , ktore jest wypozyczone");
	else
		memcpy((*tAuta)[index].model,"DELETE",sizeof("DELETE"));
}

/**
  *@brief Usuwa wypozyczenie.
  *Ustawia pole cena Wypozyczenia na 0.
  *@param index Numer wypozyczenia w tablicy.
  *@param tWypozyczenia Tablica wypozyczen.
  */
void RemoveWypozyczenie(int index,struct Wypozyczenia **tWypozyczenia){
	//usuwanie powiazan
	(*tWypozyczenia)->cena = 0.0;
}
/**
  *@brief Wyswietla dane osoby.
  *
  *Nie wypisuje usunietych rekordow.
  *@param o Tablica osob.
 *@param i Index tablicy w ktorej znajduje sie osoba do wyswietlenia.
  */
void WyswietlOsoba(struct Osoba **o,int i){
		if(!strcmp((*o)[i].imie,"DELETE"))
				return;
		printf("%d | %s | %s | %s | %s | %s | %d\n",
				(*o)[i].nr_klienta,
				(*o)[i].karta,
				(*o)[i].imie,
				(*o)[i].nazwisko,
				(*o)[i].adres,
				(*o)[i].telefon,
				(*o)[i].wyp);	
}

/**
  *@brief Wyswietla dane auta.
  *
  *Nie wypisuje usunietych rekordow.
  *@param a Tablica aut.
 *@param i Index tablicy w ktorej znajduje sie auto do wyswietlenia.
  */
void WyswietlAuto(struct Auto **a,int i){
		if(!strcmp((*a)[i].model,"DELETE"))
				return;
		printf("%d | %s | %s | %s | %s | %s | %d | %d\n",
				(*a)[i].nr_samochodu,
				(*a)[i].rejestracja,
				(*a)[i].marka,
				(*a)[i].model,
				(*a)[i].rok,
				(*a)[i].kolor,
				(*a)[i].przebieg,
				(*a)[i].wyp);	
}

/**
  *@brief Wyswietla dane wypozyczenia.
  *
  *Nie wypisuje usunietych rekordow.
  *@param w Tablica rekordow.
 *@param i Index tablicy w ktorej znajduje sie wypozyczenie do wyswietlenia.
  */
void WyswietlWypozyczenie(struct Wypozyczenia **w,int i){
		if((*w)[i].cena==0.0)
			return;
		printf("%d | %d | %d | %s | %s | %.2f | %.2f\n",
				(*w)[i].nr_wyp,
				(*w)[i].nr_klienta,
				(*w)[i].nr_samochodu,
				(*w)[i].data_wyp,
				(*w)[i].data_zwrotu,
				(*w)[i].kaucja,
				(*w)[i].cena);	
}


/**
  *@brief Tworzy nowa osobe.
  *
  *Dane sa podawane przez uzytkownika oraz sprawdzane sa pod katem poprawnosci.
  *ID jest dodawane automatycznie. Pole wyp jest domyslnie ustawione na 0.
  *@param o Tablica osob.
  *@param lines Liczba rekordow w tablicy.
  *@return Zwraca utworzona osobe.
  *@see AddOsoba().
  */
struct Osoba MakeOsoba(struct Osoba **o,int lines){
	struct Osoba os;
	if(lines==0)
		os.nr_klienta = 1;
	else
		os.nr_klienta = (*o)[lines-1].nr_klienta+1;
	//printf("Podaj numer klienta: ");
	//scanf("%d",&os.nr_klienta);
	//printf("MakeOsoba nr_klienta %d",&os.nr_klienta);
	int loop = 1;
	char temp[50];

	printf("\nPodaj numer karty: ");
	while(loop){
		scanf("%s",&temp);
		if(strlen(temp)==16){
			memcpy(os.karta,temp,sizeof(os.karta));
			loop=0;
		}
		else if(CheckIfNumber(temp)==0)
			puts("Nr karty musi byc liczba");
		else if(strlen(temp)!=16)
			puts("Niepoprawna dlugosc nr karty, powinna wynosic 16 cyfr");
	}
	loop=1;
	printf("\nPodaj imie: ");
	while(loop){
		scanf("%s",&temp);
		if(CheckIfNumber(temp)==1)
			puts("Imie nie moze byc liczba");
		else if(strlen(temp)<20){
			memcpy(os.imie,temp,sizeof(os.imie));
			loop=0;
		}
		
		else if(strlen(temp)>20)
			puts("Imie jest zbyt dlugie");
	}
	loop=1;
	printf("\nPodaj nazwisko: ");
	while(loop){
		scanf("%s",&temp);
		
		if(CheckIfNumber(temp)==1)
			puts("Nazwisko nie moze byc liczba");
		else if(strlen(temp)>50)
			puts("Nazwisko jest zbyt dlugie");
		else if(strlen(temp)<50){
			memcpy(os.nazwisko,temp,sizeof(os.nazwisko));
			loop=0;
		}
	}
	loop=1;
	printf("\nPodaj adres: ");
	while(loop){
		scanf("\n%[^\n]",&temp);
		
		if(strlen(temp)>50)
			puts("Adres jest zbyt dlugi");
		else if(strlen(temp)<50){
			memcpy(os.adres,temp,sizeof(os.adres));
			loop=0;
		}
	}
	loop=1;
	printf("Podaj numer telefonu: ");
	while(loop){
		scanf("%s",&temp);
		
		if(CheckIfNumber(temp)==0)
			puts("Nr telefonu musi byc liczba");
		else if(strlen(temp)!=9)
			puts("Niepoprawna dlugosc nr telefonu, powinna wynosic 9 cyfr");
		else if(strlen(temp)==9){
			memcpy(os.telefon,temp,sizeof(os.telefon));
			loop=0;
		}
	}
	os.wyp=0;
	return os;
}

/**
  *@brief Tworzy nowa auto.
  *
  *Dane sa podawane przez uzytkownika oraz sprawdzane sa pod katem poprawnosci.
  *ID jest dodawane automatycznie. Pole wyp jest domyslnie ustawione na 0.
  *@param a Tablica aut.
  *@param lines Liczba rekordow w tablicy.
  *@return Zwraca utworzone auto.
  *@see AddAuto().
  */
struct Auto MakeAuto(struct Auto **a,int lines){
	struct Auto au;
	if(lines==0)
		au.nr_samochodu = 1;
	else
		au.nr_samochodu = (*a)[lines-1].nr_samochodu+1;
	//printf("Podaj numer samochodu: ");
	//scanf("%d",&au.nr_samochodu);

	int loop = 1;
	char temp[50];
	
	printf("\nPodaj rejestracje: ");
	while(loop){
		scanf("%s",&temp);
		if(strlen(temp)==7){
			memcpy(au.rejestracja,temp,sizeof(au.rejestracja));
			loop=0;
		}
		else if(strlen(temp)!=16)
			puts("Niepoprawna dlugosc rejestracji, powinna wynosic 7 znakow");
	}
	loop=1;
	printf("\nPodaj marke: ");
	while(loop){
		scanf("%s",&temp);
		if(strlen(temp)<20){
			memcpy(au.marka,temp,sizeof(au.marka));
			loop=0;
		}
		
		else if(strlen(temp)>20)
			puts("Marka jest zbyt dluga");
	}
	loop=1;
	printf("\nPodaj model: ");
	while(loop){
		scanf("%s",&temp);
		if(strlen(temp)<50){
			memcpy(au.model,temp,sizeof(au.model));
			loop=0;
		}
		
		else if(strlen(temp)>50)
			puts("Model jest zbyt dlugi");
	}
	loop=1;
	printf("\nPodaj rok: ");
	while(loop){
		scanf("%s",&temp);
		if(strlen(temp)==4 && CheckIfNumber(temp)==1){
			memcpy(au.rok,temp,sizeof(au.rok));
			loop=0;
		}
		
		else if(strlen(temp)!=4)
			puts("Rok ma nieprawidlowa dlugosc");
		else if(CheckIfNumber(temp)!=1)
			puts("Rok musi byc liczba skladajaca sie z 4 cyfr");

	}
	loop=1;
	printf("Podaj kolor: ");
	while(loop){
		scanf("%s",&temp);
		if(strlen(temp)<10){
			memcpy(au.kolor,temp,sizeof(au.kolor));
			loop=0;
		}
		
		else if(strlen(temp)>10)
			puts("Kolor jest zbyt dlugi");
	}
	loop=1;
	printf("Podaj przebieg: ");
	while(loop){
		scanf("%s",&temp);
		if(CheckIfNumber(temp)==1){
			memcpy(au.kolor,temp,sizeof(au.kolor));
			loop=0;
		}
		
		else
			puts("Przebieg musi byc liczba");
	}
	au.wyp=0;
	return au;
}


/**
  *Wypisuje dostepne pola w podanej strukturze.
  *
  *@param typ Nazwa stroktory.
  */
void RekordHelper(char typ[20]){
	if(strcasecmp(typ,"osoba")==0){
		puts("Pola w rekordzie osoba:\n");
		puts("nrKlienta\n");
		puts("karta\n");
		puts("imie\n");
		puts("naziwsko\n");
		puts("adres\n");
		puts("telefon\n");
	}
	else if(strcasecmp(typ,"auto")==0){
		puts("Pola w rekordzie auta:\n");
		puts("nrSamochodu\n");
		puts("rejestracja\n");
		puts("marka\n");
		puts("model\n");
		puts("rok\n");
		puts("kolor\n");
		puts("przebieg\n");
	}
	else if(strcasecmp(typ,"wypozyczenia")==0){
		puts("Pola w rekordzie wypozyczenia:\n");
		puts("nrWypozyczenia\n");
		puts("nrKlienta\n");
		puts("nrsamochodu\n");
		puts("dataWypozyczenia\n");
		puts("dataZwrotu\n");
		puts("kaucja\n");
		puts("cena\n");
	}
}

/**
  *@brief Wyszukuje osobe w tablicy.
  *
  *Funkcja pyta uzytkownika ktore pole przeszukac oraz wyswietla wynik wyszukiwania na ekranie.
  *@param o Tablica do przeszukania.
  *@param lines Liczba lini w tablicy.
  */
void SearchOsoba(struct Osoba *o,int lines){
	char cmd[100];
	//tablica pasujacych rekordow
	struct Osoba *temp=malloc(sizeof(struct Osoba));
	int *tempId=malloc(sizeof(int));
	int tempLines=0;
	int searchVal=0;
	int loop=1;
	puts("Ktore pole przeszukac? Wpisz pola aby wyswietlic dostepne pola");
	while(loop){
	scanf("%s",&cmd);
	//okropne
	if(strcasecmp(cmd,"nrKlienta")==0){
		loop=0;
		puts("Nr. klienta do wyszukania: ");
		scanf("%s",&cmd);
		searchVal=atoi(cmd);
		for(int i=0;i<lines;i++){
			if(o[i].nr_klienta == searchVal){
				tempId[tempLines]=i;
				tempLines = AddOsoba(o[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlOsoba(&temp,i);
		}

	}

	else if(strcasecmp(cmd,"karta")==0){
		loop=0;
		puts("Nr. karty do wyszukania: ");
		scanf("%s",&cmd);

		for(int i=0;i<lines;i++){
			if(strstr(o[i].karta,cmd)!=NULL){
				tempId[tempLines]=i;
				tempLines = AddOsoba(o[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlOsoba(&temp,i);
		}

	}

	else if(strcasecmp(cmd,"imie")==0){
		loop=0;
		puts("Imie do wyszukania: ");
		scanf("%s",&cmd);

		for(int i=0;i<lines;i++){
			if(strstr(o[i].imie,cmd)!=NULL){
				tempId[tempLines]=i;
				tempLines = AddOsoba(o[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlOsoba(&temp,i);
		}

	}

	else if(strcasecmp(cmd,"nazwisko")==0){
		loop=0;
		puts("Nazwisko do wyszukania: ");
		scanf("%s",&cmd);

		for(int i=0;i<lines;i++){
			if(strstr(o[i].nazwisko,cmd)!=NULL){
				tempId[tempLines]=i;
				tempLines = AddOsoba(o[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlOsoba(&temp,i);
		}

	}

	else if(strcasecmp(cmd,"adres")==0){
		loop=0;
		puts("Adres do wyszukania: ");
		scanf("\n%[^\n]",&cmd);

		for(int i=0;i<lines;i++){
			//if(!strcmp(o[i].adres,cmd)){
			if(strstr(o[i].adres,cmd)!=NULL){
				tempId[tempLines]=i;
				tempLines = AddOsoba(o[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlOsoba(&temp,i);
		}

	}

	else if(strcasecmp(cmd,"telefon")==0){
		loop=0;
		puts("Telefon do wyszukania: ");
		scanf("%s",&cmd);

		for(int i=0;i<lines;i++){
			if(strstr(o[i].telefon,cmd)!=NULL){
				tempId[tempLines]=i;
				tempLines = AddOsoba(o[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlOsoba(&temp,i);
		}

	}

	else if(strcasecmp(cmd,"pola")==0)
		RekordHelper("osoba");
}

}
/*
for(int i=0;i<lines;i++){
			if(o[i].nr_klienta = searchVal)
				tempLines = AddOsoba(*o,&temp,tempLines);
		}
*/

/**
  *@brief Wyszukuje auto w tablicy.
  *
  *Funkcja pyta uzytkownika ktore pole przeszukac oraz wyswietla wynik wyszukiwania na ekranie.
  *@param a Tablica do przeszukania.
  *@param lines Liczba lini w tablicy.
  */

void SearchAuto(struct Auto *a,int lines){
	char cmd[100];
	//tablica pasujacych rekordow
	struct Auto *temp=malloc(sizeof(struct Auto));
	int *tempId=malloc(sizeof(int));
	int tempLines=0;
	int searchVal=0;
	int loop=1;
	puts("Ktore pole przeszukac? Wpisz pola aby wyswietlic dostepne pola");
	while(loop){
	scanf("%s",&cmd);
	//okropne
	if(strcasecmp(cmd,"NrSamochodu")==0){
		loop=0;
		puts("Nr. Samochodu do wyszukania: ");
		scanf("%s",&cmd);
		searchVal=atoi(cmd);
		for(int i=0;i<lines;i++){
			if(a[i].nr_samochodu == searchVal){
				tempId[tempLines]=i;
				tempLines = AddAuto(a[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlAuto(&temp,i);
			}	
		}
}

	else if(strcasecmp(cmd,"rejestracja")==0){
		loop=0;
		puts("Nr. Rejestracji do wyszukania: ");
		scanf("%s",&cmd);

		for(int i=0;i<lines;i++){
			if(strstr(a[i].rejestracja,cmd)!=NULL){
				tempId[tempLines]=i;
				tempLines = AddAuto(a[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlAuto(&temp,i);
		}

	}

	else if(strcasecmp(cmd,"marka")==0){
		loop=0;
		puts("Marka do wyszukania: ");
		scanf("%s",&cmd);

		for(int i=0;i<lines;i++){
			if(strstr(a[i].marka,cmd)!=NULL){
				tempId[tempLines]=i;
				tempLines = AddAuto(a[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlAuto(&temp,i);
		}

	}
	else if(strcasecmp(cmd,"model")==0){
		loop=0;
		puts("Model do wyszukania: ");
		scanf("%s",&cmd);

		for(int i=0;i<lines;i++){
			if(strstr(a[i].marka,cmd)!=NULL){
				tempId[tempLines]=i;
				tempLines = AddAuto(a[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlAuto(&temp,i);
		}

	}
	else if(strcasecmp(cmd,"rok")==0){
		loop=0;
		puts("Rok do wyszukania: ");
		scanf("%s",&cmd);

		for(int i=0;i<lines;i++){
			if(strstr(a[i].rok,cmd)!=NULL){
				tempId[tempLines]=i;
				tempLines = AddAuto(a[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlAuto(&temp,i);
		}

	}	
	else if(strcasecmp(cmd,"kolor")==0){
		loop=0;
		puts("Kolor do wyszukania: ");
		scanf("%s",&cmd);

		for(int i=0;i<lines;i++){
			if(strstr(a[i].kolor,cmd)!=NULL){
				tempId[tempLines]=i;
				tempLines = AddAuto(a[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlAuto(&temp,i);
		}

	}
	else if(strcasecmp(cmd,"Przebieg")==0){
		loop=0;
		puts("Maksymalny przebieg do wyszukania: ");
		scanf("%s",&cmd);
		searchVal=atoi(cmd);
		for(int i=0;i<lines;i++){
			if(a[i].przebieg <= searchVal){
				tempId[tempLines]=i;
				tempLines = AddAuto(a[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		int i;
		for(i=0;i<tempLines;i++){
			printf("%d.|",tempId[i]);
			WyswietlAuto(&temp,i);
			}	
		}
}
	else if(strcasecmp(cmd,"pola")==0)
		RekordHelper("auto");
		}
}
			
/**
  *@brief Wyszukuje wypozyczneie w tablicy.
  *
  *Funkcja pyta uzytkownika ktore pole przeszukac oraz wyswietla wynik wyszukiwania na ekranie.
  *@param w Tablica do przeszukania.
  *@param lines Liczba lini w tablicy.
  */
void SearchWypozyczenie(struct Wypozyczenia *w,int lines){
	char cmd[100];
	//tablica pasujacych rekordow
	struct Wypozyczenia *temp=malloc(sizeof(struct Wypozyczenia));
	int *tempId=malloc(sizeof(int));
	int tempLines=0;
	int searchVal=0;
	int loop=1;
	puts("Ktore pole przeszukac? Wpisz pola aby wyswietlic dostepne pola");
	while(loop){
	scanf("%s",&cmd);
	//okropne
	if(strcasecmp(cmd,"NrWypozyczenia")==0){
		loop=0;
		puts("Nr. Wypozyczenia do wyszukania: ");
		scanf("%s",&cmd);
		searchVal=atoi(cmd);
		for(int i=0;i<lines;i++){
			if(w[i].nr_wyp == searchVal){
				tempId[tempLines]=i;
				tempLines = AddWypozyczenie(w[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
	}
	else if(strcasecmp(cmd,"NrKlienta")==0){
		loop=0;
		puts("Nr. Klienta do wyszukania: ");
		scanf("%s",&cmd);
		searchVal=atoi(cmd);
		for(int i=0;i<lines;i++){
			if(w[i].nr_klienta == searchVal){
				tempId[tempLines]=i;
				tempLines = AddWypozyczenie(w[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
	}

	else if(strcasecmp(cmd,"NrSamochodu")==0){
		loop=0;
		puts("Nr. Samochodu do wyszukania: ");
		scanf("%s",&cmd);
		searchVal=atoi(cmd);
		for(int i=0;i<lines;i++){
			if(w[i].nr_klienta == searchVal){
				tempId[tempLines]=i;
				tempLines = AddWypozyczenie(w[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
	}

	else if(strcasecmp(cmd,"DataWypozyczenia")==0){
		loop=0;
		puts("Data wypozyczenia do wyszukania: ");
		scanf("%s",&cmd);
		searchVal=atoi(cmd);
		for(int i=0;i<lines;i++){
			if(!strcmp(w[i].data_wyp,cmd)){
				tempId[tempLines]=i;
				tempLines = AddWypozyczenie(w[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
	}

	else if(strcasecmp(cmd,"DataZwrotu")==0){
		loop=0;
		puts("Data zwrotu do wyszukania: ");
		scanf("%s",&cmd);
		searchVal=atoi(cmd);
		for(int i=0;i<lines;i++){
			if(!strcmp(w[i].data_zwrotu,cmd)){
				tempId[tempLines]=i;
				tempLines = AddWypozyczenie(w[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
	}

	else if(strcasecmp(cmd,"kaucja")==0){
		loop=0;
		puts("Kaucja do wyszukania: ");
		scanf("%s",&cmd);
		searchVal=atoi(cmd);
		for(int i=0;i<lines;i++){
			if(w[i].kaucja == searchVal){
				tempId[tempLines]=i;
				tempLines = AddWypozyczenie(w[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
	}

	else if(strcasecmp(cmd,"cena")==0){
		loop=0;
		puts("Cena do wyszukania: ");
		scanf("%s",&cmd);
		searchVal=atoi(cmd);
		for(int i=0;i<lines;i++){
			if(w[i].cena <= searchVal){
				tempId[tempLines]=i;
				tempLines = AddWypozyczenie(w[i],&temp,tempLines);
				tempId=realloc(tempId,(tempLines+1)*sizeof(int));
			}
		}
	}

	else if(strcasecmp(cmd,"pola")==0)
		RekordHelper("wypozyczenia");
		}
}
/**
  *@brief Edytuje pola podanej osoby.
  *
  *Funkcja pyta uzytkownika o osobe i pole do edycji. Niemozliwa jest edycja wypozyczen oraz ID.
  *@param o Tablica, w ktorej znajduje sie rekord do edycji.
  *@param lines Index osoby do edycji.
  */
void EditOsoba(struct Osoba **o,int lines){
	int index;
	char cmd[50];
	int lop=1;
	puts("Edytowac ktory rekord? Wpisz wyswietl aby pokazac wszystkie rekordy\n");
	puts("Wpisz szukaj aby wyszukac rekord\n");
	while(lop){
		scanf("%s",&cmd);
		if(CheckIfNumber(cmd)){
			index=atoi(cmd);
			while(lop){
				puts("Ktore pole edytowac? Wpisz wyswietl aby wyswietlic dostepne pola");
				scanf("%s",&cmd);
				if(strcasecmp(cmd,"imie")==0){
					int loop=1;
					puts("Podaj nowe imie:\n");
					while(loop){
						scanf("%s",&cmd);
						if(CheckIfNumber(cmd)==1)
							puts("Imie nie moze byc liczba");
						else if(strlen(cmd)<20){
							memcpy((*o)[index].imie,cmd,sizeof((*o)[index].imie));
							loop=0;
						}
						
						else if(strlen(cmd)>20)
							puts("Imie jest zbyt dlugie");
					}

					lop=0;
				}
				else if(strcasecmp(cmd,"nazwisko")==0){
					int loop=1;
					puts("Podaj nowe nazwisko:\n");
					while(loop){
						scanf("%s",&cmd);
						
						if(CheckIfNumber(cmd)==1)
							puts("Nazwisko nie moze byc liczba");
						else if(strlen(cmd)>50)
							puts("Nazwisko jest zbyt dlugie");
						else if(strlen(cmd)<50){
						memcpy((*o)[index].nazwisko,cmd,sizeof((*o)[index].nazwisko));
							loop=0;
						}
					}
					lop=0;
				}
				else if(strcasecmp(cmd,"adres")==0){
					int loop=1;
					while(loop){
						puts("Podaj nowy adres:\n");
						scanf("\n%[^\n]",&cmd);
						
						if(strlen(cmd)>50)
							puts("Adres jest zbyt dlugi");
						else if(strlen(cmd)<50){
							memcpy((*o)[index].adres,cmd,sizeof((*o)[index].adres));
							loop=0;
						}
					}
					lop=0;
				}
				else if(strcasecmp(cmd,"telefon")==0){
					puts("Podaj nowy nr. telefonu:\n");
					int loop=1;
					while(loop){
						scanf("%s",&cmd);
						
						if(CheckIfNumber(cmd)==0)
							puts("Nr telefonu musi byc liczba");
						else if(strlen(cmd)!=9)
							puts("Niepoprawna dlugosc nr telefonu");
						else if(strlen(cmd)==9){
							memcpy((*o)[index].telefon,cmd,sizeof((*o)[index].telefon));
							loop=0;
						}
					}
					lop=0;
				}
				else if(strcasecmp(cmd,"karta")==0){
					puts("Podaj nowy nr. karty:\n");
					int loop=1;
					while(loop){
						scanf("%s",&cmd);
						if(strlen(cmd)==16){
							memcpy((*o)[index].karta,cmd,sizeof((*o)[index].karta));
							loop=0;
						}
						else if(CheckIfNumber(cmd)==0)
							puts("Nr karty musi byc liczba");
						else if(strlen(cmd)!=16)
							puts("Niepoprawna dlugosc nr karty");
					}
					lop=0;
				}
				else if(strcasecmp(cmd,"wyswietl")==0)
						RekordHelper("osoba");
			}
		}
		else if(strcasecmp(cmd,"wyswietl")==0){
			printf("Index|Nr. klienta|Nr. karty|Imie|Nazwisko|Adres|Nr. telefonu|Wypozycza \n");
			if(!lines)
				puts("Brak osob");
			int i;
			for(i=0;i<lines;i++){
				printf("%d.|",i);
				WyswietlOsoba(o,i);
				}				
		}
		else if(strcasecmp(cmd,"szukaj")==0)
			SearchOsoba(*o,lines);
	}
}

/**
  *@brief Edytuje pola podanego auta.
  *
  *Funkcja pyta uzytkownika o auto i pole do edycji. Niemozliwa jest edycja wypozyczen oraz ID.
  *@param o Tablica, w ktorej znajduje sie rekord do edycji.
  *@param lines Index auta do edycji.
  */
void EditAuto(struct Auto **a,int lines){
	int index;
	char cmd[50];
	int lop=1;
	puts("Edytowac ktory rekord? Wpisz wyswietl aby pokazac wszystkie rekordy\n");
	puts("Wpisz szukaj aby wyszukac rekord\n");
	while(lop){
		scanf("%s",&cmd);
		if(CheckIfNumber(cmd)==1){
			index=atoi(cmd);
			while(lop){
				puts("Ktore pole edytowac? Wpisz wyswietl aby wyswietlic dostepne pola");
				scanf("%s",&cmd);
				if(strcasecmp(cmd,"rejestracja")==0){
				printf("\nPodaj rejestracje: ");
				int loop=1;
				while(loop){
					scanf("%s",&cmd);
					if(strlen(cmd)==7){
						memcpy((*a)[index].rejestracja,cmd,sizeof((*a)[index].rejestracja));
						loop=0;
					}
					else if(strlen(cmd)!=16)
						puts("Niepoprawna dlugosc rejestracji, powinna wynosic 7 znakow");
				}
					lop=0;
				}
				else if(strcasecmp(cmd,"marka")==0){
					int loop=1;
					while(loop){
					scanf("%s",&cmd);
					if(strlen(cmd)<20){
						memcpy((*a)[index].marka,cmd,sizeof((*a)[index].marka));
						loop=0;
					}
					
					else if(strlen(cmd)>20)
						puts("Marka jest zbyt dluga");
				}
					lop=0;
				}
				else if(strcasecmp(cmd,"model")==0){
					int loop=1;
				printf("\nPodaj model: ");
				while(loop){
					scanf("%s",&cmd);
					if(strlen(cmd)<50){
						memcpy((*a)[index].model,cmd,sizeof((*a)[index].model));
						loop=0;
					}
					
					else if(strlen(cmd)>50)
						puts("Model jest zbyt dlugi");
				}
					lop=0;
				}
				else if(strcasecmp(cmd,"rok")==0){
					int loop=1;
					while(loop){
					scanf("%s",&cmd);
					if(strlen(cmd)==4 && CheckIfNumber(cmd)==1){
						memcpy((*a)[index].rok,cmd,sizeof((*a)[index].rok));
						loop=0;
					}
					
					else if(strlen(cmd)!=4)
						puts("Rok ma nieprawidlowa dlugosc");
					else if(CheckIfNumber(cmd)!=1)
						puts("Rok musi byc liczba skladajaca sie z 4 cyfr");

				}
					lop=0;
				}
				else if(strcasecmp(cmd,"przebieg")==0){
					int loop=1;
				printf("Podaj przebieg: ");
				while(loop){
					scanf("%s",&cmd);
					if(CheckIfNumber(cmd)==1){
						(*a)[index].przebieg = atoi(cmd);
						loop=0;
					}
					
					else
						puts("Przebieg musi byc liczba");
				}
					lop=0;
				}
				else if(strcasecmp(cmd,"kolor")==0){
					int loop=1;
				printf("Podaj kolor: ");
				while(loop){
					scanf("%s",&cmd);
					if(strlen(cmd)<10){
						memcpy((*a)[index].kolor,cmd,sizeof((*a)[index].kolor));
						loop=0;
					}
					
					else if(strlen(cmd)>10)
						puts("Kolor jest zbyt dlugi");
				}
					lop=0;
				}
				
				else if(strcasecmp(cmd,"wyswietl")==0)
						RekordHelper("auto");
			}
		}
		else if(strcasecmp(cmd,"wyswietl")==0){
			printf("Nr. samochodu|Rejestracja|Marka|Model|Rok|Kolor|Przebieg|Wypozyczony \n");
				if(!lines)
					puts("Brak aut");
			int i;
			for(i=0;i<lines;i++){
				printf("%d.|",i);
				WyswietlAuto(a,i);
				}				
		}
		else if(strcasecmp(cmd,"szukaj")==0)
			SearchAuto(*a,lines);
	}
}

/**
  *@brief funkcja umozliwiajaca wypozyczenie auta.
  *
  *Funkcja przyjmuje wszystkie 3 tablice oraz liczbe ich lini dla poprawnego sprawdzenia czy wypozyczenia jest mozliwe.
  *Mozliwe jest wypozyczenie auta wiecej niz jeden raz, jesli daty sie niepokrywaja.
  *@return Zwraca utworzone wypozyczenie.
  *@see AddWypozyczenie().
  */
struct Wypozyczenia Wypozycz(struct Osoba **o,struct Auto **a,struct Wypozyczenia **w,int linesO,int linesA,int linesW){

	char cmd[50];
	int index;
	int error=1;
	struct Wypozyczenia wyp;
	if(linesW==0)
		wyp.nr_wyp = 1;	
	else
		wyp.nr_wyp = (*w)[linesW].nr_wyp+1;
	printf("\nPodaj Index klienta: ");
	puts("Wpisz wyswietl aby wyswietlic wszystkie osoby");
	puts("Wpisz szukaj aby wyszukac osobe");
	
	int loop=1;
	while(loop){
		scanf("%s",&cmd);
		if(CheckIfNumber(cmd)){
			loop=0;
			index = atoi(cmd);
			wyp.nr_klienta = (*o)[index].nr_klienta;
			//(*o)[index].wyp=1;
		}
		else if(strcasecmp(cmd,"wyswietl")==0){
			printf("Index|Nr. klienta|Nr. karty|Imie|Nazwisko|Adres|Nr. telefonu|Wypozycza \n");
				if(!linesO)
					puts("Brak osob");
				int i;
				for(i=0;i<linesO;i++){
					printf("%d.|",i);
					WyswietlOsoba(o,i);
					}			
			}
		else if(strcasecmp(cmd,"szukaj")==0){
			SearchOsoba(*o,linesO);
			}
		else if(!CheckIfNumber(cmd))
				puts("Podana wartosc nie jest liczba");
		}
	int lop=1;
	while(error){
	lop=1;
	//printf("\nPodaj date wypozyczenia dd-mm-yyyy: ");
	while(lop){
		printf("\nPodaj date wypozyczenia dd-mm-yyyy: ");
		scanf("%s",&cmd);
		if(ValidateDate(cmd)){
			memcpy(wyp.data_wyp,cmd,sizeof(wyp.data_wyp));
			lop=0;
					}
		else
			puts("Data jest niepoprawna");
	}
	lop=1;
	//printf("\nPodaj date zwrotu dd-mm-yyyy: ");
	while(lop){	
		printf("\nPodaj date zwrotu dd-mm-yyyy: ");
		scanf("%s",&cmd);
		if(ValidateDate(cmd)){
			memcpy(wyp.data_zwrotu,cmd,sizeof(wyp.data_zwrotu));
			lop=0;
					}
		else
			puts("Data jest niepoprawna");
	}

	loop=1;
	while(loop){
		printf("\nPodaj Index samochodu: ");
		puts("\nWpisz wyswietl aby wyswietlic wszystkie samochody");
		puts("Wpisz szukaj aby wyszukac samochod");
		//while(loop){
			scanf("%s",&cmd);
			if(CheckIfNumber(cmd)){
				loop=0;
				index = atoi(cmd);
				if((*a)[index].wyp){
					char *currentTime = CurrentTime();
					//check dates
					if(CompareTime(wyp.data_wyp,currentTime)==-1)
						puts("Blad! Nie mozna wypozyczycz samochodu w przeszlosci");
					for(int i=0;i<linesW;i++){
						//w.data_wyp < wyp.data_zwrotu && w.data_zwrotu > wyp.data_zwrotu
						//w.data_wyp < wyp.data_wyp && w.data_zwrotu < wyp.data_zwortu && wyp.data_wyp < w.data_zwrotu
						//w.data_wyp < wyp.data_wyp && w.data_zwrotu > wyp.data_zwrotu
						//w.data_wyp > wyp.data_wyp && w.data_zwrotu < wyp.data_zwrotu

						if(CompareTime(wyp.data_zwrotu,(*w)[i].data_wyp)==1 && CompareTime((*w)[i].data_zwrotu,wyp.data_zwrotu)==1){
							puts("Data nachodzi na istniejace wypozyczenie");
							loop=0;
							error=1;
							printf("%s - %s",(*w)[i].data_wyp,(*w)[i].data_zwrotu);
						}
						else if(CompareTime(wyp.data_wyp,(*w)[i].data_wyp)==1 && CompareTime(wyp.data_zwrotu,(*w)[i].data_zwrotu)==1 && CompareTime((*w)[i].data_zwrotu,wyp.data_wyp)==1){
							puts("Data nachodzi na istniejaca wypozyczneie");
							loop=0;
							error=1;
							printf("%s - %s",(*w)[i].data_wyp,(*w)[i].data_zwrotu);
						}
						else if(CompareTime(wyp.data_wyp,(*w)[i].data_wyp)==1 && CompareTime((*w)[i].data_zwrotu,wyp.data_zwrotu)==1){
							puts("Data nachodzi na istniejaca wypozyczneie");
							loop=0;
							error=1;
							printf("%s - %s",(*w)[i].data_wyp,(*w)[i].data_zwrotu);
						}
						else if(CompareTime((*w)[i].data_wyp,wyp.data_wyp)==1 && CompareTime(wyp.data_zwrotu,(*w)[i].data_zwrotu)==1){
							puts("Data nachodzi na istniejaca wypozyczneie");
							loop=0;
							error=1;
							printf("%s - %s",(*w)[i].data_wyp,(*w)[i].data_zwrotu);
						}
						else if(CompareTime((*w)[i].data_wyp,wyp.data_wyp)==0 && CompareTime(wyp.data_zwrotu,(*w)[i].data_zwrotu)==0){
							puts("Data nachodzi na istniejaca wypozyczneie");
							loop=0;
							error=1;
							printf("%s - %s",(*w)[i].data_wyp,(*w)[i].data_zwrotu);
						}
						else{
							loop=0;
							error=0;
							for(int i=0;i<linesA;i++){
								if(wyp.nr_samochodu = (*a)[i].nr_samochodu)
									(*a)[i].wyp=1;
							}
						}//else
					}//for

				}//if
				else{
					loop=0;error=0;
					(*o)[index].wyp=1;
					for(int i=0;i<linesA;i++){
						if(wyp.nr_samochodu = (*a)[i].nr_samochodu)
							(*a)[i].wyp=1;
							}
					}
			}//main if
			else if(strcasecmp(cmd,"wyswietl")==0){
				printf("Nr. samochodu|Rejestracja|Marka|Model|Rok|Kolor|Przebieg|Wypozyczony \n");
					if(!linesA)
						puts("Brak aut");
					int i;
					for(i=0;i<linesA;i++){
						printf("%d.|",i);
						WyswietlAuto(a,i);
						}			
				}
			else if(strcasecmp(cmd,"szukaj")==0){
				SearchAuto(*a,linesA);
				}
			//else if(!CheckIfNumber(cmd))
				//puts("Podana wartosc nie jest liczba");
		}//while(loop)
				
			}//while(error)
	//	}
	lop=1;
	printf("Podaj kacuje: ");
	while(lop){
		scanf("%s",&cmd);
		if(CheckIfNumber(cmd)){
			wyp.kaucja=atof(cmd);
			lop=0;
				}
		else
			puts("Kaucja musi byc liczba");
	}
	printf("Podaj cene: ");
	lop=1;
	while(lop){
		scanf("%s",&cmd);
		if(CheckIfNumber(cmd)){
			wyp.cena=atof(cmd);	
			lop=0;
				}
		else
			puts("Cena musi byc liczba");
	}
	return wyp;
}

/**
  *@brief Zwraca wypozyczony samochod.
  *
  *Funkcja przyjmuje wszystkie tablice. Usuwa tagi wyp z osoby i auta.
  */
void Zwroc(struct Osoba **o,struct Auto **a,struct Wypozyczenia **w,int linesO,int linesA,int linesW){
	char cmd[50];
	int index;
	int loop=1;
	puts("Ktore wypozyczenie zwrocic?");
	puts("Wpisz wyswietl aby zobaczyc wszystkie wypozyczenia");
	puts("Wpisz szukaj aby wyszukac wypozyczenie");
	while(loop){
		int picked = 0;
		scanf("%s",&cmd);
		if(strcasecmp(cmd,"wyswietl")==0){
			picked = 1;
			printf("Nr. wypozyczenia|Nr. klienta|Nr. samochodu|Data wypozyczenia|Data zwrotu|Kaucja|Cena \n");
			if(!linesW)
				puts("Brak wypozyczen");
			int i;
			for(i=0;i<linesW;i++){
				printf("%d.|",i);
				WyswietlWypozyczenie(w,i);
				}
			}
		else if(strcasecmp(cmd,"szukaj")==0){
			SearchWypozyczenie(*w,linesW); 	
			picked = 1;
		}
		else if(CheckIfNumber(cmd)){
			//printf("%d\n\n\n",atoi(cmd));
			loop=0;
			index = atoi(cmd);
			
			RemoveWypozyczenie(index,w);
			//remove tags from osoby auta
			int os = (*w)[index].nr_klienta;
			//printf("nr_klienta = %d\n",os);
			int au = (*w)[index].nr_samochodu;
			//printf("nr_auta = %d\n",au);
			//osoby
			for(int i=0;i<linesO;i++){
				if((*o)[i].nr_klienta==os)
					(*o)[i].wyp=0;
			}
			//auta
			for(int i=0;i<linesA;i++){
				if((*a)[i].nr_samochodu==au)
					(*a)[i].wyp=0;
			}
		}
		picked=0;
	}
}


/**
  *@brief Pokazuje wszystkie wypozyczenia danej osoby.
  *
  *Funckja przyjmuje wszystkie 3 tablice.
  */
void PokazWypozyczeniaOsoba(struct Osoba **o,struct Auto **a,struct Wypozyczenia **w,int linesO,int linesA,int linesW){
	char cmd[100];
	//tablica pasujacych rekordow
	struct Wypozyczenia *temp=malloc(sizeof(struct Wypozyczenia));
	int *tempId=malloc(sizeof(int));
	int tempLines=0;
	int searchVal=0;
	int loop=1;
	int index;
	puts("Podaj Index osoby do sprawdzenia wypozyczen");
	puts("Wpisz wyswietl aby wyswietlic wszystkie osoby\n Wpisz szukaj aby wyszukac osobe");
	while(loop){
		scanf("%s",&cmd);
		if(strcasecmp(cmd,"wyswietl")==0){
		printf("Index|Nr. klienta|Nr. karty|Imie|Nazwisko|Adres|Nr. telefonu|Wypozycza \n");
			if(!linesO)
				puts("Brak osob");
			int i;
			for(i=0;i<linesO;i++){
				printf("%d.|",i);
				WyswietlOsoba(o,i);
			}
		}
		else if(strcasecmp(cmd,"szukaj")==0){
			SearchOsoba(*o,linesO);
		}
		else if(CheckIfNumber(cmd)==1){
			index=atoi(cmd);
			int nr = (*o)[index].nr_klienta;
			for(int i=0;i<linesO;i++){
				if((*w)[i].nr_klienta==nr){
					tempId[tempLines]=i;
					tempLines = AddWypozyczenie((*w)[i],&temp,tempLines);
					tempId=realloc(tempId,(tempLines+1)*sizeof(int));
				}
				loop=0;
			}
			if(loop==0){
			int i;
			printf("\nWypozyczenia:");
			printf("Nr. wypozyczenia|Nr. klienta|Nr. samochodu|Data wypozyczenia|Data zwrotu|Kaucja|Cena \n");
			if(!linesW)
				puts("Brak wypozyczen");
			else{
			for(i=0;i<tempLines;i++){
				printf("%d.|",tempId[i]);
				WyswietlWypozyczenie(&temp,i);
				for(int j=0;j<linesA;j++){
					if(temp[i].nr_samochodu==(*a)[j].nr_samochodu){
						WyswietlAuto(a,j);
						}
				
					}
			
				}
			}
			}
		}
		
	}
}

/**
  *@brief Pokazuje wszystkie wypozyczenia danego auta.
  *
  *Funckja przyjmuje wszystkie 3 tablice.
  */
void PokazWypozyczeniaAuta(struct Osoba **o,struct Auto **a,struct Wypozyczenia **w,int linesO,int linesA,int linesW){
	char cmd[100];
	//tablica pasujacych rekordow
	struct Wypozyczenia *temp=malloc(sizeof(struct Wypozyczenia));
	int *tempId=malloc(sizeof(int));
	int tempLines=0;
	int searchVal=0;
	int loop=1;
	int index;
	puts("Podaj Index auta do sprawdzenia wypozyczen");
	puts("Wpisz wyswietl aby wyswietlic wszystkie auta\n Wpisz szukaj aby wyszukac auto");
	while(loop){
		scanf("%s",&cmd);
		if(strcasecmp(cmd,"wyswietl")==0){
		printf("Nr. samochodu|Rejestracja|Marka|Model|Rok|Kolor|Przebieg|Wypozyczony \n");
				if(!linesA)
					puts("Brak aut");
			int i;
			for(i=0;i<linesA;i++){
				printf("%d.|",i);
				WyswietlAuto(a,i);
				}
		}
		else if(strcasecmp(cmd,"szukaj")==0){
			SearchAuto(*a,linesA);
		}
		else if(CheckIfNumber(cmd)==1){
			index=atoi(cmd);
			int nr = (*a)[index].nr_samochodu;
			for(int i=0;i<linesA;i++){
				if((*w)[i].nr_samochodu==nr){
					tempId[tempLines]=i;
					tempLines = AddWypozyczenie((*w)[i],&temp,tempLines);
					tempId=realloc(tempId,(tempLines+1)*sizeof(int));
				}
				loop=0;
			}
			int i;
			printf("\nWypozyczenia:");
			printf("Nr. wypozyczenia|Nr. klienta|Nr. samochodu|Data wypozyczenia|Data zwrotu|Kaucja|Cena \n");
			if(!linesW)
				puts("Brak wypozyczen");
			else{
				for(i=0;i<tempLines;i++){
					printf("%d.|",tempId[i]);
					WyswietlWypozyczenie(&temp,i);
					for(int j=0;j<linesO;j++){
						if(temp[i].nr_klienta==(*o)[j].nr_klienta){
							WyswietlOsoba(o,j);
					}
				
				}
			
			}
			}
		}
	}
}




/**
  *Odsiweza wszystkie wypozyczenia, usuwa te, ktore juz minely.
  */
void UpdateWypozyczenia(struct Osoba **o,struct Auto **a,struct Wypozyczenia **w,int linesO,int linesA,int linesW){

	char *currentTime = CurrentTime();
	//check if rental expired
	for(int i=0;i<linesW;i++){
		if(CompareTime(currentTime,(*w)[i].data_zwrotu)==1){
			RemoveWypozyczenie(i,w);
			//remove tags from osoby auta
			int os = (*w)[i].nr_klienta;
			int au = (*w)[i].nr_samochodu;
			//osoby
			for(int j=0;j<linesO;j++){
				if((*o)[j].nr_klienta==os)
					(*o)[j].wyp=0;
			}
			//auta
			for(int j=0;j<linesA;j++){
				if((*a)[j].nr_samochodu==au)
					(*a)[j].wyp=0;
			}	
		}
	}
}






