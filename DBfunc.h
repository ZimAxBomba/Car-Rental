#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

struct Osoba{
	unsigned int nr_klienta;
	unsigned char karta[17];
	char imie[20];
	char nazwisko[50];
	char adres[50];
	unsigned char telefon[10];
	unsigned int wyp;//ozyczenie
};

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

//czysci plik txt (zapisuje go jako backup - w przyszlosci)
void Backup(char n[20]){
	FILE *p = fopen(n,"w");
	fclose(p);
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

int AddOsoba(struct Osoba temp,struct Osoba **tOsoby,int lines){
	*tOsoby = realloc(*tOsoby,(lines+1)*sizeof(struct Osoba));

		(*tOsoby)[lines].nr_klienta = temp.nr_klienta;
		//printf("AddOsoba nr_klienta %d",temp.nr_klienta);
		memcpy((*tOsoby)[lines].karta,temp.karta,sizeof(temp.karta));
		memcpy((*tOsoby)[lines].imie,temp.imie,sizeof(temp.imie));
		memcpy((*tOsoby)[lines].nazwisko,temp.nazwisko,sizeof(temp.nazwisko));
		memcpy((*tOsoby)[lines].adres,temp.adres,sizeof(temp.adres));
		memcpy((*tOsoby)[lines].telefon,temp.telefon,sizeof(temp.telefon));
		(*tOsoby)[lines].wyp = 0;
		return lines+1;
}

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

int AddWypozyczenie(struct Wypozyczenia	temp,struct Wypozyczenia **tWypozyczenia,int lines){
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

void RemoveOsoba(int index,struct Osoba **tOsoby){
	//sprawdzenie wypozyczenia
	if((*tOsoby)[index].wyp)
		puts("Nie mozna usunac osoby, ktora wypozycza auto");
	else
		memcpy((*tOsoby)[index].imie,"DELETE",sizeof("DELETE"));
}
void RemoveAuto(int index,struct Auto **tAuta){
	//sprawdzenie wypozyczenia
	if((*tAuta)[index].wyp)
		puts("Nie mozna usunac auta , ktore jest wypozyczone");
	else
		memcpy((*tAuta)[index].model,"DELETE",sizeof("DELETE"));
}
void RemoveWypozyczenie(int index,struct Wypozyczenia **tWypozyczenia){
	//usuwanie powiazan
	(*tWypozyczenia)->cena = 0.0;
}
void WyswietlOsoba(struct Osoba **o,int i){
		printf("%d | %s | %s | %s | %s | %s | %d\n",
				(*o)[i].nr_klienta,
				(*o)[i].karta,
				(*o)[i].imie,
				(*o)[i].nazwisko,
				(*o)[i].adres,
				(*o)[i].telefon,
				(*o)[i].wyp);	
}

void WyswietlAuto(struct Auto **a,int i){
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
void WyswietlWypozyczenie(struct Wypozyczenia **w,int i){
		printf("%d | %d | %d | %s | %s | %f | %f\n",
				(*w)[i].nr_wyp,
				(*w)[i].nr_klienta,
				(*w)[i].nr_samochodu,
				(*w)[i].data_wyp,
				(*w)[i].data_zwrotu,
				(*w)[i].kaucja,
				(*w)[i].cena);	
}

struct Osoba MakeOsoba(){
	struct Osoba os;
	printf("Podaj numer klienta: ");
	scanf("%d",&os.nr_klienta);
	//printf("MakeOsoba nr_klienta %d",&os.nr_klienta);
	printf("\nPodaj numer karty: ");
	scanf("%16s",&os.karta);
	printf("\nPodaj imie: ");
	scanf("%s",&os.imie);
	printf("\nPodaj nazwisko: ");
	scanf("%s",&os.nazwisko);
	printf("\nPodaj adres: ");
	scanf("\n%[^\n]",&os.adres);
	printf("Podaj numer telefonu: ");
	scanf("%9s",&os.telefon);
	return os;
}

struct Auto MakeAuto(){
	struct Auto au;
	printf("Podaj numer samochodu: ");
	scanf("%d",&au.nr_samochodu);
	printf("\nPodaj rejestracje: ");
	scanf("%7s",&au.rejestracja);
	printf("\nPodaj marke: ");
	scanf("%s",&au.marka);
	printf("\nPodaj model: ");
	scanf("%s",&au.model);
	printf("\nPodaj rok: ");
	scanf("%4s",&au.rok);
	printf("Podaj kolor: ");
	scanf("%s",&au.kolor);
	return au;
}
struct Wypozyczenia MakeWypozyczenia(){
	struct Wypozyczenia wyp;
	printf("Podaj nr. wypozyczenia: ");
	scanf("%d",&wyp.nr_wyp);
	//printf("MakeWypozyczenia nr.wyp %d",wyp.nr_wyp);
	printf("\nPodaj nr. klienta: ");
	scanf("%d",&wyp.nr_klienta);
	//printf("MakeWypozyczenia nr.klienta %d",wyp.nr_klienta);
	printf("\nPodaj nr. samochodu: ");
	scanf("%d",&wyp.nr_samochodu);
	//printf("MakeWypozyczenia nr_samochodu %d",wyp.nr_samochodu);
	printf("\nPodaj date wypozyczenia dd-mm-yyyy: ");
	scanf("%10s",&wyp.data_wyp);
	//printf("MakeWypozyczenia data wyp %d",wyp.data_wyp);
	printf("\nPodaj date zwrotu dd-mm-yyyy: ");
	scanf("%10s",&wyp.data_zwrotu);
	//printf("MakeWypozyczenia data zwrotu %d",wyp.data_zwrotu);
	printf("Podaj kacuje: ");
	scanf("%f",&wyp.kaucja);
	//printf("MakeWypozyczenia kaucja %f",wyp.kaucja);
	printf("Podaj cene");
	scanf("%f",&wyp.cena);
	//printf("MakeWypozyczenia cena %f",wyp.cena);
	return wyp;
}


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

int SearchOsoba(struct Osoba *o,int lines){
	char cmd[100];
	//tablica pasujacych rekordow
	struct Osoba *temp;
	int *tempId;
	tempId=malloc(sizeof(int));
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
		searchVal = atoi(cmd);

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
	//analogicznie reszte pol Dxxxx

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

void SearchAuto(struct Auto *a,int lines){

}

void SearchWypozyczenie(struct Wypozyczenia *w,int lines){

}
