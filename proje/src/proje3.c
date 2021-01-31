/*
 * proje3.c
 *
 *  Created on: 8 Ara 2017
 *      Author: ASUS
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef enum sex {
	M, F
} sex;
typedef struct {
	char name[20];
	char surname[20];
	int tcno;
	sex s;
} musteri;
typedef struct {
	int no;
	bool taken;
	musteri m;
} Seat;
typedef struct {
	char plate[15];
	char brand[15];
	int model;
	Seat seat[10][4];
} Bus;
//fileopen metodu 0'dan bir otobüs açmak için kullanýlmýþtýr ve sadece program ilk tasarlandýðý zaman
//çaðrýlmýþ bir kere çaðrýldýktan sonra çaðrýlmasýna gerek yoktur.
void fileopen(Bus *b) {
	int i, j, no = 1;
	FILE *f = NULL;
	f = fopen("otobus.txt", "w");
	if (f != NULL) {
		Seat **s = (Seat**) malloc(10 * sizeof(Seat*));
		for (int i = 0; i < 10; i++) {
			s[i] = (Seat*) malloc(4 * sizeof(Seat));
		}
		for (i = 0; i < 10; ++i) {
			for (j = 0; j < 4; ++j) {
				s[i][j].taken = false;
				s[i][j].no = no;
				no++;
			}
		}
		strcpy(b->brand, "Mercedes");
		strcpy(b->plate, "34 AZ 1221");
		b->model = 2016;
		fprintf(f, "%s\n", b->plate);
		fprintf(f, "%s\n", b->brand);
		fprintf(f, "%d\n", b->model);
		for (i = 0; i < 10; ++i) {
			for (j = 0; j < 4; ++j) {
				fprintf(f, "B/%d\n", s[i][j].no);
			}
		}
		for (i = 0; i < 10; ++i) {
			for (j = 0; j < 4; ++j) {
				b->seat[i][j].no = s[i][j].no;
				b->seat[i][j].taken = s[i][j].taken;
			}
		}
		fclose(f);
	}
}
//bu metod otobüste boþ olan koltuklarýn nolarýný dolu olanlarý ise X veya O harfleriyle ekrana
//dikdörtgen bir þekilde bastýran metoddur
void busStatus(Bus *b) {
	int i, j;
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 4; ++j) {
			if (b->seat[i][j].taken == true) {
				if (b->seat[i][j].m.s == M) {
					printf("%c\t", 'X');
				} else if (b->seat[i][j].m.s == F) {
					printf("%c\t", 'O');
				}
			} else if (b->seat[i][j].taken == false) {
				printf("%d\t", b->seat[i][j].no);
			}
		}
		printf("\n");
	}
	menu(b);
}
//Bu metod sistemdeki müþteriye bir koltuk satýlmasýný saðlar
void seatsale(Bus *b) {
	int Kno, i, j;
	bool sold = true;
	bool stop = false;
	char ad[20];
	char sad[20];
	int d, tc;
	int g;
	puts("adýnýz:");
	scanf("%s", ad);
	puts("soyadýnýz:");
	scanf("%s", sad);
	puts("cinsiyet(M=0/F=1):");
	scanf("%d", &d);
	puts("tc NO:");
	scanf("%d", &tc);
	puts("istediðiniz koltuðun numarasýný giriniz(1-40)");
	scanf("%d", &Kno);
	while (sold == true) {
		for (i = 0; (i < 10) && !stop; ++i) {

			for (j = 0; (j < 4) && !stop; ++j) {

				if (b->seat[i][j].no == Kno && b->seat[i][j].taken == false) {

					strcpy(b->seat[i][j].m.name, ad);
					strcpy(b->seat[i][j].m.surname, sad);
					b->seat[i][j].m.s = d;
					b->seat[i][j].m.tcno = tc;
					b->seat[i][j].taken = true;
					puts("iþlem baþarýlý!");
					stop = true;
					sold = false;
				} else if (b->seat[i][j].no
						== Kno&& b->seat[i][j].taken == true) {
					puts(
							"istediðiniz koltuk dolu baþka bir koltuk seçmek istermisiniz(evet=1/hayýr=0):");
					scanf("%d", &g);
					if (g == 1) {
						puts("koltuk numarasý giriniz:");
						scanf("%d", &Kno);
					} else if (g == 0) {
						stop = false;
						sold = false;
					}
				}

			}
		}
	}
	saveTotxt(b);
	menu(b);
}
//bu metod sistemde kayýtlý olan bir müþteriyi aramamýzý saðlar
void search(Bus *b) {
	bool pgoing = true;
	bool stop = false;
	bool found = false;
	int i, j, tc;
	int c;
	puts("Kiþinin tcnosunu giriniz:");
	scanf("%d", &tc);
	while (pgoing == true) {
		for (i = 0; (i < 10) && !stop; ++i) {
			for (j = 0; (j < 4) && !stop; ++j) {
				if (b->seat[i][j].m.tcno == tc) {
					printf("isim: %s\n", b->seat[i][j].m.name);
					printf("soyisim:%s\n", b->seat[i][j].m.surname);
					printf("koltuk no: %d\n", b->seat[i][j].no);
					printf("tc: %d\n", b->seat[i][j].m.tcno);
					puts("baþka birini aramak istemisiniz(evet=1/hayýr=0):");
					scanf("%d", &c);
					if (c == 1) {
						puts("kiþinin tcsini giriniz:");
						scanf("%d", &tc);
					} else if (c == 0) {
						pgoing = false;
						stop = true;
						found = true;
					}

				}

			}
		}
		if (found == false) {
			puts("bu tcde biri bulunmamakta");
			puts("baþka birini aramak istemisiniz(evet=1/hayýr=0):");
			scanf("%d", &c);
			if (c == 1) {
				puts("kiþinin tcsini giriniz:");
				scanf("%d", &tc);
			} else if (c == 0) {
				pgoing = false;
				stop = true;
			}
		}

	}
	menu(b);
}
//bu metod sistemin ilk ana menüsünü çaðýrýr
void menu(Bus *b) {
	puts("1-otobüs durumu göster");
	puts("2-koltuk satýþ");
	puts("3-kiþi arama");
	puts("4-çýkýþ");
	int a;
	scanf("%d", &a);
	if (a == 1) {
		busStatus(b);
	} else if (a == 2) {
		seatsale(b);
	} else if (a == 3) {
		search(b);
	} else if (a == 4) {
		puts("bizi tercih ettiðiniz için teþekkür ederiz");
		return;
	} else {
		puts("Menüde olmayan bir sayý girdiniz");
		menu(b);
	}
}
//bu metod kodun .txt dosyasýna kaydýný yapar
void saveTotxt(Bus *b) {
	int i, j;
	FILE *f = NULL;
	f = fopen("otobus.txt", "w");
	if (f != NULL) {
		for (i = 0; i < 10; ++i) {
			for (j = 0; j < 4; ++j) {
				if (b->seat[i][j].taken == true) {
					fprintf(f, "D %d %s %s %d %d\n", b->seat[i][j].no,
							b->seat[i][j].m.name, b->seat[i][j].m.surname,
							b->seat[i][j].m.s, b->seat[i][j].m.tcno);
				} else if (b->seat[i][j].taken == false) {
					fprintf(f, "B %d\n", b->seat[i][j].no);
				}
			}

		}
	}
	fclose(f);
}
//bu metod .txt dosyasýný okuyarak otobüsün koltuklarýný doldurur
void read(Bus *b) {
	FILE *f = NULL;
	f = fopen("otobus.txt", "r");
	int No, sex, i, j, tc;
	char ad[20];
	char Sad[20];
	char g;
	if (f != NULL) {
		for (i = 0; i < 10; ++i) {
			for (j = 0; j < 4; ++j) {
				fscanf(f, "%c\n", &g);
				if (g == 'D') {
					fscanf(f, "%d %s %s %d %d\n", &No, ad, Sad, &sex, &tc);
					b->seat[i][j].no = No;
					strcpy(b->seat[i][j].m.name, ad);
					strcpy(b->seat[i][j].m.surname, Sad);
					b->seat[i][j].m.s = sex;
					b->seat[i][j].m.tcno = tc;
					b->seat[i][j].taken = true;
				} else if (g == 'B') {
					fscanf(f, "%d\n", &No);
					b->seat[i][j].taken = false;
					b->seat[i][j].no = No;
				}

			}
		}
	}
	fclose(f);
}
int main(void) {
	setbuf(stdout, NULL);
	Bus *bus = (Bus *) malloc(sizeof(Bus));
	//fileopen(bus);
	read(bus);
	menu(bus);

}

