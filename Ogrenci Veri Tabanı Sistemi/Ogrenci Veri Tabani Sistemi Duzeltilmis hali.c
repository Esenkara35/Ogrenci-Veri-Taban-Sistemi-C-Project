#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"
int row_ogr;
int row_ders;
int toplam_ders;
ogrenci ogr_bil[3000];
ders ders_bil[1000];
void menu();
void ogrenci_ekle();
void ders_ekle();
void ogrenci_ders_kayit();
void ogrenci_derslerini_listele();
void dersi_alan_ogrencileri_listele();
void loadogrenciler();
void loaddersler();
void saveogrenciler();
int main(void)
{
	printf("Main started");
	menu();
}
void menu()
{
	int a = 0;
	printf("                  Ogrenci Veri Tabani Sistemi                \n");
	printf("-------------------------------------------------------------\n");
	printf("1: Ogrenci ekle\n");
	printf("2: Ders ekle\n");
	printf("3: Ogrenciyi Derse Kaydet\n");
	printf("4: Ogrenci Derslerini Listele\n");
	printf("5: Dersi Alan Ogrencileri Listele\n");
	printf("6:Cikis\n");
	printf("Seciminiz:");
	scanf_s("%d", &a);
	do
	{
		switch (a)
		{
		case 1:
			ogrenci_ekle();
			break;
		case 2:
			ders_ekle();
			break;
		case 3:
			ogrenci_ders_kayit();
			break;
		case 4:
			ogrenci_derslerini_listele();
			break;
		case 5:
			dersi_alan_ogrencileri_listele();
			break;
		case 6:
			return 0;
		}
		printf("Seciminiz:");
		scanf_s("%d", &a);
	} while (a != 6);
}
void ogrenci_ekle()
{
	ogrenci o;
	loadogrenciler();
	FILE *in_og = fopen("C:\\Users\\esenk\\OneDrive\\Masaüstü\\CSE124\\Ogrenci Listesi.txt", "a");
	printf("Ogrenci Isim:");
	scanf_s("%20s", o.name, 20);
	printf("Ogrenci Soyisim:");
	scanf_s("%20s", o.surname, 20);
	printf("Ogrenci Numarasi:");
	scanf_s("%d", &o.stu_id);
	for (int i = 0; i < row_ogr; i++)
	{
		if((strcmp(ogr_bil[i].name, o.name) == 0) && (strcmp(ogr_bil[i].surname,o.surname) == 0) || ogr_bil[i].stu_id == o.stu_id)
		{
			printf("Bu ogrenci daha once eklenmis ya da numara yanlis girildi.\n");
			return;
		}
	}
	fprintf(in_og, "%d,%s %s\n", o.stu_id, o.name, o.surname);
	printf("Ogrenci eklendi.\n");
	fclose(in_og);
}
void ders_ekle()
{
	int c;
	ders o;
	loaddersler();
	while ((c = getchar()) != '\n' && c != EOF) {}
	FILE *in_drs = fopen("C:\\Users\\esenk\\OneDrive\\Masaüstü\\CSE124\\Ders Listesi.txt", "a");
	printf("Ders Ismi:");
	fgets(o.course_name, sizeof(o.course_name), stdin);
	o.course_name[strcspn(o.course_name, "\n")] = '\0';
	printf("Ders Kodu:");
	fgets(o.course_code, sizeof(o.course_code), stdin);
	o.course_code[strcspn(o.course_code, "\n")] = '\0';
	for (int i = 0; i < row_ders; i++)
	{
		if (((strcmp(ders_bil[i].course_name, o.course_name) == 0) || (strcmp(ders_bil[i].course_code, o.course_code) == 0)) && ders_bil[i].course_name[0] != '\0')
		{
			printf("Bu ders daha once eklenmis ya da ders kodu yanlis girildi.\n");
			return;
		}
	}
	fprintf(in_drs, "%s-%s\n", o.course_name, o.course_code);
	printf("Ders eklendi.\n");
	fclose(in_drs);
}
void ogrenci_ders_kayit()
{
	int c;
	char eklemek_istenilen_ders_kodu[21];
	int num;
	printf("Ogrenci Numarasi:");
	scanf_s("%d", &num);
	while ((c = getchar()) != '\n' && c != EOF) {}
	loadogrenciler();
	loaddersler();
	for (int i = 0; i < row_ogr; i++)
	{
		if(ogr_bil[i].stu_id == num)
		{
			printf("Eklemek istediginiz dersin kodu:");
			fgets(eklemek_istenilen_ders_kodu, 20, stdin);
			eklemek_istenilen_ders_kodu[strcspn(eklemek_istenilen_ders_kodu, "\n")] = '\0';
			for(int j = 0; j < row_ders; j++)
			{
				if (strcmp(ogr_bil[i].courses[j] , eklemek_istenilen_ders_kodu) == 0)
				{
					
					printf("Ogrenci bu derse kayitli.\n");
					return;
				}
				else if(strcmp(ders_bil[j].course_code, eklemek_istenilen_ders_kodu) == 0)
				{
					
					for (int k = 0; k < 10; k++)
					{
						if (ogr_bil[i].courses[k][0] == '\0')
						{
							strcpy(ogr_bil[i].courses[k],eklemek_istenilen_ders_kodu);
							saveogrenciler();
							return;
						
						}
					}
				}
			}
			printf("Ders bulunamadi.\n");
			return;
		}
	}
	printf("Ogrenci Bulunamadi.\n");
	return;

}
void dersi_alan_ogrencileri_listele()
{
	char code[11];
	loadogrenciler();
	printf("Ders kodunu giriniz:");
	scanf_s("%s", code, 10);
	for (int i = 0; i < row_ogr; i++)
	{
		for (int j = 0; j < row_ogr; j++)
		{
			if (strcmp(ogr_bil[i].courses[j], code) == 0)
			{
				printf("%d,%s %s\n", ogr_bil[i].stu_id, ogr_bil[i].name, ogr_bil[i].surname);
				break;
			}
		}
	}
}
void ogrenci_derslerini_listele()
{
	loadogrenciler();
	int num;
	printf("Ogrenci Numarasi:");
	scanf_s("%d", &num);
	for (int i = 0; i < row_ogr; i++)
	{
		if (ogr_bil[i].stu_id == num)
		{
			for (int j = 0; j < 10; j++)
			{
				if (ogr_bil[i].courses[j][0] != '\0')
				{
					printf("%s\n", ogr_bil[i].courses[j]);
				}
				else if (ogr_bil[i].courses[0][0] == '\0')
				{
					printf("Ogrenci henuz derse kaydolmadi.\n");
					break;
				}
			}
			return;
		}
	}
	printf("Ogrenci Bulunamadi.\n");
}
void loadogrenciler()
{
	row_ogr = 0;
	char line[100];
	FILE* lfptr = fopen("C:\\Users\\esenk\\OneDrive\\Masaüstü\\CSE124\\Ogrenci Listesi.txt", "r");
	if (lfptr == NULL) {
		printf("Ogrenci Listesi.txt açýlamadý");
		return;
	}
	
	while (fgets(line, sizeof(line), lfptr) != NULL)
	{
		int ders_sayisi = 0;
		line[strcspn(line, "\n")] = '\0';

		char* tok = strtok(line, ",");
		if (tok == NULL)
			continue;
		ogr_bil[row_ogr].stu_id = atoi(tok);
		 
		tok = strtok(NULL, " ");
		if (tok == NULL)
			continue;
		strcpy(ogr_bil[row_ogr].name, tok);
		
		tok = strtok(NULL, " ");
		if (tok == NULL)
			continue;
		strcpy(ogr_bil[row_ogr].surname, tok);
		for (int k = 0; k < 10; k++)
		{
			ogr_bil[row_ogr].courses[k][0] = '\0';
		}
			while ( (tok = strtok(NULL, "-")) != NULL && ders_sayisi < 10)
		{
			strcpy(ogr_bil[row_ogr].courses[ders_sayisi], tok);
			ders_sayisi++;
		}
		row_ogr++;
	}
	fclose(lfptr);
}
void loaddersler()
{
	row_ders = 0;
	char line[100];
	toplam_ders = 0;
	FILE *lfptr = fopen("C:\\Users\\esenk\\OneDrive\\Masaüstü\\CSE124\\Ders Listesi.txt", "r");
	if (lfptr == NULL)
	{
		printf("Ders Listesi.txt açýlamadý.");
		return;
	}
	while (fgets(line, sizeof(line), lfptr) != NULL)
	{
		char* tok = strtok(line, "-");
		if (tok == NULL)
		{
			return;
		}
		strcpy(ders_bil[row_ders].course_name, tok);
		tok = strtok(NULL, "\n");
		strcpy(ders_bil[row_ders].course_code, tok);
		row_ders++;
	}
	fclose(lfptr);
}

void saveogrenciler()
{
	FILE* svfptr = fopen("C:\\Users\\esenk\\OneDrive\\Masaüstü\\CSE124\\Ogrenci Listesi.txt", "w");
	if(svfptr == NULL){
		printf("Dosya acilamadi.");
		return;
	}
	for (int i = 0; i < row_ogr; i++)
	{
		fprintf(svfptr,"%d,%s %s ", ogr_bil[i].stu_id, ogr_bil[i].name, ogr_bil[i].surname);
		for (int j = 0; j < 10 && ogr_bil[i].courses[j][0] != '\0'; j++)
		{
			fprintf(svfptr,"-%s", ogr_bil[i].courses[j]);
		}
		fprintf(svfptr, "\n");
	}
	fclose(svfptr);
}

