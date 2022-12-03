#include<stdlib.h>
#include<stdio.h>
#include <string.h>

	struct node{
		
		int no; 
		char ad[25]; 
		char soyad[25]; 
		int vize, final;
		float ort;
		bool sonuc;
		
		struct node *next;
		struct node *prev;
		
	};
	
	
	typedef struct node node;
	node *head = NULL;
	
	int cnt = 0;
	
	void Ekle(int n, char *a, char *s, int v, int f){
		
		node *ogr = (node *) malloc(sizeof(node));
			
		ogr->no = n;
		strcpy(ogr->ad,a);
		strcpy(ogr->soyad,s);
		ogr->vize = v;
		ogr->final = f;
		ogr->ort = ogr->vize * 0.4 + ogr->final * 0.6;
		ogr->sonuc = ogr->ort>49 ? true : false;
		
		if(head == NULL){
			
			head = ogr;
			head->next = head;
			head->prev = head;
			cnt++;
			
			printf("%d numarali ogrenci eklendi\n", head->no);
			
		}
		
		else{
			
			node * p = head;
			while(p->next!=head)
			p = p->next;
			ogr->next = head;
			head->prev = ogr;
			head = ogr;
			p->next = head;
			head->prev = p;
			
			cnt ++;
			
			printf("%d numarali ogrenci eklendi \n", head->no);
		}
		
		
		
	}
	
	void Sil(){
		
		if(head == NULL){
			printf("Listede Kayitli Ogrenci Yok\n");
		}
		else{
			
			int ogrNo;
			printf("Silmek İstediginiz Ogrencinin Numarasini Giriniz\n");
			scanf("%d", &ogrNo);
			
			if (cnt == 1 && head->no == ogrNo){
				
				printf("Listede Kalan Son Ogrenci Silindi\n");
				free(head);
				head = NULL;
				cnt--;	
			}
			
			else if(cnt != 1 && head->no == ogrNo){
				
				node *p	= head;
				while(p->next!=head)
				p = p->next;
				
				node *p2 = head->next;
				free(head);
				head = p2;
				
				head->prev = p;
				p->next = head;
				
			}
			
			else{
				
				node *p = head;
				node *p2 = head;
				node *p3 = head;
				
				while(p->next!=head){
					
					if(p->no == ogrNo){
						
						printf("%d numarali ogrenci silindi\n", p->no);
						p3 = p->next;
						free(p);
						p2->next = p3;
						p3->prev = p2;
						cnt--;
						break;
					}
					
					p2 = p;
					p= p->next;
				}
				
				if(p->no == ogrNo){
						
					printf("%d numarali ogrenci silindi\n", p->no);
					free(p);
					p2->next = head;
					head->prev = p2;
					cnt--;
					
				}
			}
			
		}
		
		
	}
	
	void Listele (){
		
		if( head == NULL){
			
			printf("Liste Boş");
		}
		else{
			
			node *p = head;
			while (p->next != head){
				
				printf("%d Numarali Ogrencinin Adi : %s\n Soyadi : %s\n Ortalamasi : %.2f\n Durumu : %s\n", p->no, p->ad, p->soyad, p->ort, (p->sonuc == true) ? "Dersten Gecti" : "Dersten Kaldi");
			
				p = p->next;
			
			}
			
			printf("%d Numarali Ogrencinin Adi : %s\n Soyadi : %s\n Ortalamasi : %.2f\n Durumu : %s\n", p->no, p->ad, p->soyad, p->ort, (p->sonuc == true) ? "Dersten Gecti" : "Dersten Kaldi");

		}
	}
	
	void DosyaYaz(){
		
		if(head == NULL){
			
			printf("Listelenilecek Kayıt Yok");
			
		}
		else{
			
			node * p = head;
			FILE * dosya = fopen("otomasyonkayit.txt", "w");
			
			while (p->next!=head){
				fprintf(dosya,"%d %s %s %d %d", p->no, p->ad, p->soyad, p->vize, p->final);
				p = p->next;
			}
			fprintf(dosya,"%d %s %s %d %d", p->no, p->ad, p->soyad, p->vize, p->final);
			fclose(dosya);
			printf("Veriler Dosyaya Kaydedildi\n");

			
		}
	}
	
	void DosyaVeriListele(){
		
		FILE * dosya = fopen("otomasyonkayit.txt", "r");
		
		while(feof(dosya)){
			
			int n, v, f;
			char a[25], s[25];
			fscanf(dosya, "%d%s%s%d%d", &n, a, s, &v, &f);
			Ekle(n,a,s,v,f);
		}
		
		fclose(dosya);
		//system("cls");
	}
	
	int main(){
		
		DosyaVeriListele();
		printf("Listeye Veriler Aktarildi\n");
		
		int secim, vize, final, no;
		float ort;
		char ad[20], soyad[20];
		
		while(1){
			
			printf("Uygulamaya Hosgeldiniz\n");
			printf("----MENU----\n");
			printf("1- Ekle\n");
			printf("2- Sil\n");
			printf("3- Listele\n");
			printf("4- Dosyaya Kaydet\n");
			printf("Islem Seciniz\n");
			
			scanf("%d", &secim);
			
			switch(secim){
				
				case 1 : 
					
					printf("Ogrencinin Numarasini Giriniz : ");
					scanf("%d", &no);
					printf("Ogrencinin Adini Giriniz : ");
					scanf("%s", ad);
					printf("Ogrencinin Soyadini Giriniz : ");
					scanf("%s", soyad);
					printf("Ogrencinin Vizesini Giriniz : ");
					scanf("%d", &vize);
					printf("Ogrencinin Finalini Giriniz : ");
					scanf("%d", &final);
					Ekle(no,ad,soyad,vize,final);
					
					break;
					
					
				case 2 :
					Sil();
					break;
					
				case 3 : 
					Listele();
					break;
					
				case 4 : 
					DosyaYaz();
					break;
						
				case 0:
					return 0 ;
					
				default :
					printf("Gecerli Bir Islem Seciniz!");
			}

			
		}
		
		return 0;
	}
	
	