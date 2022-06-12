#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

typedef struct Dersler{
	
	char kod[15];
	char ders_ismi[60];
	int kredi;	
	int kontenjan;
	int doluluk;
	int *num_listesi;
	struct Dersler *next;
	struct Dersler *prew;
	
}ders;

typedef struct Ogrenciler{
	
	struct Ogrenciler *before;
	struct Ogrenciler *next;
	int numara;
	char ad[30];
	char soyad[30];
	int ogr_kredi;
	int ogr_ders;	
}ogr;

typedef struct sonuc{
	
	int islem_num;	
	char tarih[20];
	char durum[20];
	struct sonuc *next;
	int numlar;
	char ders_kodlari[20];
	
}islem;

int ogr_kontrol(ogr *head ,int num);
int ders_kontrol(ders *head ,char *kod);

void ogr_traverse(ogr *head);
void ders_traverse(ders *head);
void islem_traverse(islem *head);

void print_ogr(ogr *n);
void print_ders(ders *n);
void print_islem(islem *n);

ogr *ogr_olustur(int num ,char *ad , char*soyad , int kredi , int ders);
ders *ders_olustur(char* kod ,char *ders_ismi , int kredi ,int kontenjan);
islem *islem_olustur(int islem_numarasi , char *ders_kodu , int ogr_num , char *tarih , char *durum);

void ders_sil(ders **head,char *kod,islem *head_islem ,ogr *head_ogr);
void ogr_sil(ogr **head,int num ,islem *head_islem);

void ogr_sirali_ekleme(ogr **head, int num ,char *ad , char *soyad , int kredi , int ders);
void ders_sirali_ekleme(ders **head, char *kod , char *ders_ismi , int kredi , int kontenjan);
void islem_sirali_ekleme(islem **head, int islem_num ,char *ders_kodu , int ogr_num , char *tarih , char *durum);

ogr *ogr_bulucu(ogr *head ,int num);
ders *ders_bulucu(ders *head ,char *ders_kodu);
int son_islem_bulucu(islem *head);

void Dersin_Listesine_Ogrenci_Ekleme(ogr *head_ogr, ders *head_ders , islem *head_islem ,char *kod ,int  num);
void Dersin_Listesinden_Ogrenci_Silme(ogr *head_ogr, ders *head_ders , islem *head_islem ,char *kod ,int  num);

int Ders_Listesinde_Ogrenci_Kontrol(ders *head_ders , int num , char *ders_kodu);

void Ogrenci_Dersten_Kayit_Silme(ogr *head_ogr, ders *head_ders , islem *head_islem);
void OgrenciDerseKayit(ogr *head_ogr, int max_kredi , int max_ders_sayisi , ders *head_ders , islem *head_islem);

void islemleri_dosyaya_yazdirma(islem *head_islem , FILE *islem_yazma);
void ogrencileri_dosyaya_yazdirma(ogr *head_ogr , FILE *ogr_yazma);

void durum_yaz(islem *head);
void sinif_listeleri_olusturma(ders *head_ders);
void ogr_yaz(ogr *head);
void ders_yaz(ders *head);
void sinif_listeleri_yazdirma(ders *head_ders);

int main(){

	setlocale(LC_ALL, "Turkish");
	char *p;
	int i , j , counter ;
	char dizi_kod[15][10];
	char satir[50];
	char dizi_ders_ismi[13][50];
	int kredi[13];
	int kontenjan[13];
	
	int ogr_numara[20];
	char ogr_ad[20][25];
	char ogr_soyad[20][25];
	int ogr_kredi[13];
	int ogr_ders_sayisi[13];
	
	int islem_numarasi[20];	
	char tarih[20][20];
	char durum[20][20];
	int numlar[20];
	char ders_kodlari[20][20];
	
	
	char dizi[25][250];
	
	ders *head_ders , *tmp_ders , *prev_ders ,*tail_ders;
	
	ogr *head_ogr , *tmp_ogr , *tmp2_ogr , *tail_ogr;
	
	islem *head_islem , *tmp_islem , *tail_islem;
	
	FILE *ders_oku , *ogr_oku , *islem_oku , *islem_yazma , *ogr_yazma;
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	ders_oku = fopen("Lectures.txt","r");
	
	i = 0 , j = 0;
	
	while(fgets(dizi[i],sizeof(dizi),ders_oku)){           //// DERSLERÝN OLDUÐU DOSYA PARÇALANIP DÝZÝLERE DAÐITILIYOR
				
		char *token = strtok(dizi[i],",");
		   
		   while( token != NULL ) {
		   		
		   		if(j==0){
				strcpy(dizi_kod[i],token);
				}
				
				else if(j==1){
				strcpy(dizi_ders_ismi[i],token);
				}
				
				else if(j==2){
				kredi[i] = atoi(token);
				}
				
				else if(j==3){
				kontenjan[i] = atoi(token);
				}
      			
				token = strtok(NULL, ",");
					
				  j++; 
   				}
   			j = 0;	
		i++;
	}
	
	fclose(ders_oku);
	
	counter = i; 
		 
	head_ders = NULL;
	
	tail_ders = NULL;
	
	for(i = 0 ; i < counter ; ++i) {                   //// DERSLERÝN OLDUÐU DÝZÝLER STRUCTLARA DAÐITILIYOR
	
/////////////////////////////////////////////////////////////		
		// Ders Bilgilerini Node Ekleme
		if(head_ders == NULL) {
		
		ders *tmp =(ders*)malloc(sizeof(ders));

		strcpy(tmp->kod,dizi_kod[i]);
		
		strcpy(tmp->ders_ismi, dizi_ders_ismi[i]);

		tmp->kredi = kredi[i];
		
		tmp->kontenjan = kontenjan[i];
		
		tmp->doluluk = 0;
		
		tmp->num_listesi = (int*)malloc(1*sizeof(int));
		
		tmp->next = NULL;

		head_ders = tail_ders = tmp;
		
		}
		
		else  {
			
			ders *tmp = (ders*)malloc(sizeof(ders));
			
			strcpy(tmp->kod , dizi_kod[i]);
			//printf("%s " ,tmp->kod);
			
			strcpy(tmp->ders_ismi,dizi_ders_ismi[i]);
			//printf("%s " ,tmp->kod);
			
			tmp->kredi = kredi[i];
			
			tmp->kontenjan = kontenjan[i];
			
			tmp->doluluk = 0;
			
			tmp->num_listesi = (int*)malloc(1*sizeof(int));
			
			tail_ders->next = tmp;
			
			tail_ders = tmp;
			
		}
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
	i = 0 , j = 0; 
	
	ogr_oku = fopen("Students.txt","r");
	
	if(ogr_oku == NULL){
		printf("hata");
	}
		
		while(fgets(dizi[i],sizeof(dizi),ogr_oku)){           //// ÖÐRENCÝLERÝN OLDUÐU DOSYA PARÇALANIP DÝZÝLERE DAÐITILIYOR
				
		char *token = strtok(dizi[i],",");
		   
		   while( token != NULL ) {
		   		
		   		if(j==0){
				ogr_numara[i] = atoi(token);
				}
				
				else if(j==1){
				strcpy(ogr_ad[i],token);
				}
				
				else if(j==2){
				strcpy(ogr_soyad[i],token);	
				}
				
				else if(j==3){
				ogr_kredi[i] = atoi(token);
				}
				
				else if(j==4){
				ogr_ders_sayisi[i] = atoi(token);
				}
      			
				token = strtok(NULL, ",");

				  j++; 
   				}
   			j = 0;	
		i++;
	}
	fclose(ogr_oku);	
//////////////////////////////////////////////////////////////////////////	
	counter = i;
	
	head_ogr = NULL;
	
	tail_ogr = NULL;
	
	for(i = 0 ; i < counter ; ++i) {							 //// ÖÐRENCÝLERÝN OLDUÐU DÝZÝLER STRUCTLARA DAÐITILIYOR
		
		// Öðrenci Bilgilerini Node Ekleme
		if(head_ogr == NULL) {
		
		ogr *tmp1 =(ogr*)malloc(sizeof(ogr));
		
		tmp1->numara = ogr_numara[i];
		
		strcpy(tmp1->ad,ogr_ad[i]);
		
		strcpy(tmp1->soyad, ogr_soyad[i]);
		
		tmp1->ogr_kredi = ogr_kredi[i];
		
		tmp1->ogr_ders = ogr_ders_sayisi[i];
				
		tmp1->next = NULL;
		
		head_ogr = tail_ogr = tmp1;
		
		}
		
		else  {
			
			ogr *tmp1 = (ogr*)malloc(sizeof(ogr));
			
			tmp1->numara = ogr_numara[i];
			
			strcpy(tmp1->ad,ogr_ad[i]);
			
			strcpy(tmp1->soyad,ogr_soyad[i]);
			
			tmp1->ogr_kredi = ogr_kredi[i];
						
			tmp1->ogr_ders = ogr_ders_sayisi[i];
			
			tail_ogr->next = tmp1;
			
			tail_ogr = tmp1;
			
			tail_ogr->next = NULL;
			
		}
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	/*
	int islem_numarasi[20];	
	char tarih[20][20];
	char durum[20][20];
	int numlar[20];
	char ders_kodlari[20][20]; */
	
	islem_oku = fopen("StudentLectureProcess.txt","r");
	
	i = 0 , j = 0;
	
	while(fgets(dizi[i],sizeof(dizi),islem_oku)){           //// ÝSLEMLERÝN OLDUÐU DOSYA PARÇALANIP DÝZÝLERE DAÐITILIYOR
				
		char *token = strtok(dizi[i],",");
		   
		   while( token != NULL ) {
		   		
		   		if(j==0){
				islem_numarasi[i] = atoi(token);
				}
				
				else if(j==1){
				strcpy(ders_kodlari[i],token);
				}
				
				else if(j==2){
				numlar[i] = atoi(token);
				}
				
				else if(j==3){
				strcpy(tarih[i],token);
				}
				
				else if(j==4){
				token[strlen(token)-1] = '\0';
				strcpy(durum[i],token);
				}
				
      			
				token = strtok(NULL, ",");
					
				  j++; 
   				}
   			j = 0;	
		i++;
	}
	
	fclose(islem_oku);
	
	counter = i; 
		 
	head_islem = NULL;
	
	tail_islem = NULL;
	
	
	for(i = 0 ; i < counter ; ++i) {                   //// ÝÞLEMLERÝN OLDUÐU DÝZÝLER STRUCTLARA DAÐITILIYOR
	
		
		// Ders Bilgilerini Node Ekleme
		if(head_islem == NULL) {
		
		islem *tmp_islem =(islem*)malloc(sizeof(islem));
		
		tmp_islem->islem_num = islem_numarasi[i];
		
		strcpy(tmp_islem->tarih,tarih[i]);
		
		strcpy(tmp_islem->durum,durum[i]);
	
		strcpy(tmp_islem->ders_kodlari,ders_kodlari[i]);
		
		tmp_islem->numlar = numlar[i];
		
		tmp_islem->next = NULL;
		
		head_islem = tail_islem = tmp_islem;
		
		}
		else  {
			
			islem *tmp_islem =(islem*)malloc(sizeof(islem));
	
			tmp_islem->islem_num = islem_numarasi[i];
			
			strcpy(tmp_islem->tarih,tarih[i]);
			
			strcpy(tmp_islem->durum,durum[i]);
			
			strcpy(tmp_islem->ders_kodlari,ders_kodlari[i]);
			
			tmp_islem->numlar = numlar[i];
			
			tail_islem->next = tmp_islem;
			
			tail_islem = tmp_islem;
			
			tmp_islem->next = NULL;

		}
	}
	
///////////////////////////////////////////////////////////////////////////// TEXTTE YAPILAN ÝÞLEMLERÝ NODELARA ÝÞLÝYORUZ //////
		
	char *kayitli = "kayitli";
	char *sildi = "sildi";
	char *ders_kapandi = "ders kapandi";
		
	tmp_islem = head_islem;
	tmp_ogr = head_ogr;
	tmp_ders = head_ders;
	
	while(tmp_islem != NULL ){

		if(strcmp(tmp_islem->durum,kayitli) == 0){
			
			tmp_ogr = ogr_bulucu(head_ogr,tmp_islem->numlar);
			
			tmp_ders = ders_bulucu(head_ders,tmp_islem->ders_kodlari);
			
			Dersin_Listesine_Ogrenci_Ekleme(head_ogr,head_ders ,head_islem ,tmp_ders->kod ,tmp_ogr->numara);
			
			tmp_ders->doluluk = tmp_ders->doluluk + 1;			
		}
		
	tmp_islem = tmp_islem->next;
	}
	
///	//////////////////////////////////////////////////// NODELARA ÝÞLEMELERÝN BÝTTÝÐÝ YER ////////////////////////////////////////////
		
	int secim , max_ders , max_kredi;
	int cikis = 1;
	
	printf("Ogrencinin Alabilecegi Max Kredi Sayisini Giriniz : ");
	scanf("%d",&max_kredi);
	
	printf("Ogrencinin Alabilecegi Max Ders Sayisini Giriniz : ");
	scanf("%d",&max_ders);
	
	
	while(cikis == 1){

	printf("\n\nOgrenci Eklemek Icýn 1'e Basiniz : \n\n");
	printf("Ders Eklemek Icýn 2'e Basiniz : \n\n");
	printf("Ogrenci Silmek Icýn 3'e Basiniz : \n\n");
	printf("Ders Silmek Icýn 4'e Basiniz : \n\n");
	printf("Ogrenciyi Derse Kaydetmek Icýn 5'e Basiniz : \n\n");
	printf("Ogrencinin Dersten Kaydini Silmek Icýn 6'ya Basiniz : \n\n");
	printf("Derslere Kayitli Ogrencileri Goruntulemek Icin 9'a Basiniz : \n\n");
	printf("Ogrencileri Goruntulemek Icin 10'a Basiniz : \n\n");
	printf("Dersleri Goruntulemek Icin 11'e Basiniz : \n\n");
	printf("Islemleri Goruntulemek Icin 12'ye Basiniz : \n\n");
	printf("Cýkmak Icýn 13'e Basiniz : \n\n");
	
	scanf("%d",&secim);
	
	if(secim == 1){
			
			int num;
			
			char ad[25];
			
			char soyad[25];
			
			int ders_sayi;
			
			int alinan_kredi;
			
			printf("Ogrenci Numarasini Giriniz : ");
			scanf("%d",&num);
			
			if(ogr_kontrol(head_ogr,num) == 1){
				printf("Kayitli Numaraya Sahip Bir Ogrenci Vardir Lutfen Baska Bir Numara Giriniz");
			}
			else {	
			printf("Ogrenci Ad Giriniz : ");
			scanf("%s",ad);
			
			printf("Ogrenci Soyad Giriniz : ");
			scanf("%s" ,soyad);
			
			printf("Ogrenci Ders Sayisi Giriniz : ");
			scanf("%d" ,&ders_sayi);
			
			printf("Ogrenci Kredisini Giriniz : ");
			scanf("%d" ,&alinan_kredi);
			
			ogr_sirali_ekleme(&head_ogr,num,ad,soyad,alinan_kredi,ders_sayi);
			ogr_yaz(head_ogr);
			}
		

			
	}
	
	else if(secim == 2){
		
		char kod[20];
		char ders_ismi[60];
		int dersin_kredisi;
		int kontenjan;
		
		printf("Eklemek Istediginiz Dersin Kodunu Giriniz : ");
		scanf("%s",kod);
		if(ders_kontrol(head_ders,kod)== 1){
			printf("Kayitli Koda Sahip Bir Ders Vardir Lutfen Baska Bir Kod Giriniz\n\n");
		}
		else if(ders_kontrol(head_ders,kod)== 0){
			printf("Dersin Ismini Giriniz : ");
			scanf("%s",ders_ismi);
			
			printf("Dersin Kredisini Giriniz : ");
			scanf("%d",&dersin_kredisi);
			
			printf("Dersin Kontenjanýný Giriniz : ");
			scanf("%d",&kontenjan);
			
			ders_sirali_ekleme(&head_ders,kod,ders_ismi,dersin_kredisi,kontenjan);
			durum_yaz(head_islem);
			ogr_yaz(head_ogr);
			ders_yaz(head_ders);
			//sinif_listeleri_yazdirma(head_ders);
		}

		
	}
	
	else if(secim == 3){
		
		int num;
		
		printf("Silmek Istediginiz Ogrencinin Numarasini Giriniz : ");
		scanf("%d",&num);		
		if(ogr_kontrol(head_ogr,num) == 1){			
		ogr_sil(&head_ogr,num,head_islem);
		}
		else if(ogr_kontrol(head_ogr,num) == 0){
			printf("Silmek Istediginiz Numaraya Sahip Bir Ogrenci Bulunmamaktadir.\n");
		}

		durum_yaz(head_islem);
		//sinif_listeleri_yazdirma(head_ders);
	}
	
	else if(secim == 4){
		
		char kod[10];
		
		printf("Silmek Istediginiz Dersin Kodunu Giriniz : ");
		scanf("%s",kod);
		if(ders_kontrol(head_ders,kod) == 1){			
		ders_sil(&head_ders,kod,head_islem,head_ogr);
		}
		else if(ders_kontrol(head_ders,kod) == 0){
			printf("Silmek Istediginiz Kod Ismine Sahip Bir Ders Bulunmamaktadir.\n\n");
		}
		durum_yaz(head_islem);
		ogr_yaz(head_ogr);
		ders_yaz(head_ders);
		//sinif_listeleri_yazdirma(head_ders);

		
	}
	
	else if(secim == 5){
		
		OgrenciDerseKayit(head_ogr,max_kredi,max_ders,head_ders,head_islem);
		
		durum_yaz(head_islem);
		ogr_yaz(head_ogr);
		//sinif_listeleri_yazdirma(head_ders);
	}
	
	else if(secim == 6){
		
		Ogrenci_Dersten_Kayit_Silme(head_ogr, head_ders ,head_islem);
		
		durum_yaz(head_islem);
		ogr_yaz(head_ogr);
		//sinif_listeleri_yazdirma(head_ders);
	}
	
	else if(secim == 9){
	
	sinif_listeleri_olusturma(head_ders);	
	
	}

	else if(secim == 10){
		ogr_traverse(head_ogr);
	}
	
	else if(secim == 11){
		ders_traverse(head_ders);
	}
	
	else if(secim == 12){
		islem_traverse(head_islem);
	}
	
	else if(secim == 13){
		cikis = 0;	
	}	
	else{
		printf("Hatali Giris Lutfen Gecerli Bir Sayi Giriniz\n");
	}
	
	}
	
	
	fclose(islem_yazma);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// FONKSÝYONLAR //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ogr_kontrol(ogr *head ,int num){
	ogr *tmp=head;
	while(tmp!=NULL){
		if(tmp->numara == num){
			return 1;
		}
		tmp = tmp->next;
	}															//       KONTROLLER				
	return 0;
}

int ders_kontrol(ders *head ,char *kod){
	ders *tmp=head;
	while(tmp!=NULL){
		if(strcmp(tmp->kod,kod) == 0){
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

ogr *ogr_bulucu(ogr *head ,int num){
	ogr *tmp=head;
	while(tmp!=NULL){
		if(tmp->numara == num){
			return tmp;
		}
		tmp = tmp->next;
	}															//       BULUCU				

}

ders *ders_bulucu(ders *head ,char *ders_kodu){
	ders *tmp=head;
	while(tmp!=NULL){
		if(strcmp(tmp->kod,ders_kodu) == 0){
			return tmp;
		}
		tmp = tmp->next;
	}	
	return NULL;														//       BULUCU			

}

int son_islem_bulucu(islem *head){
	
	islem *tmp = head;
	
	while(tmp->next!=NULL){
		tmp = tmp->next;
	}
	
	return tmp->islem_num;			

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ogr_traverse(ogr *head){       ////// ÖÐRENCÝLERÝ DOLANMA
	ogr *tmp=head;
	while(tmp!=NULL){
		print_ogr(tmp);
		printf("\n");
		tmp = tmp->next;
	}
	printf("\n");
}

void print_ogr(ogr *n){             //// ÖÐRENCÝLERÝ YAZDIRMA
	printf("%d ",n->numara);
	printf("%s ",n->ad);
	printf("%s ",n->soyad);
	printf("%d ",n->ogr_kredi);
	printf("%d ",n->ogr_ders);
}
///////////////////////////////////////////////////////////////////	        DOLANMA VE YAZDIRMALAR              
void ders_traverse(ders *head){     ///// DERSLERÝ DOLANMA
	ders *tmp=head;
	while(tmp!=NULL){
		print_ders(tmp);
		printf("\n");
		tmp = tmp->next;
	}
	printf("\n");
	

}

void print_ders(ders *n){   ///////// DERSLERÝ YAZDIRMA
	int i = 0;
	printf("%s ",n->kod);
	printf("%s ",n->ders_ismi);
	printf("%d ",n->kredi);
	printf("%d ",n->kontenjan);
	printf("%d ",n->doluluk);
		
}

///////////////////////////////////////////////////////////////////
void islem_traverse(islem *head){     ///// ÝSLEMLERÝ DOLANMA
	islem *tmp=head;
	while(tmp!=NULL){
		print_islem(tmp);
		printf("\n");
		tmp = tmp->next;
	}
	printf("\n");
}

void print_islem(islem *n){   ///////// ÝÞLEMLERÝ YAZDIRMA
	printf("%d ",n->islem_num);
	printf("%s ",n->ders_kodlari);
	printf("%d ",n->numlar);
	printf("%s ",n->tarih);
	printf("%s ",n->durum);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
ogr *ogr_olustur(int num ,char *ad , char*soyad , int kredi , int ders){
	ogr* tmp;
	tmp = (ogr*) malloc(sizeof(ogr));	
	tmp->numara = num;
	strcpy(tmp->ad,ad); 
	strcpy(tmp->soyad,soyad);
	tmp->ogr_kredi = kredi;
	tmp->ogr_ders = ders;
	tmp->next = NULL;
	return tmp;
}                                                          	////////           DERS VE ÖÐRENCÝ OLUÞTURMA

ders *ders_olustur(char* kod ,char *ders_ismi , int kredi ,int kontenjan){
	ders* tmp;
	tmp = (ders*) malloc(sizeof(ders));	
	strcpy(tmp->kod,kod); 
	strcpy(tmp->ders_ismi,ders_ismi);
	tmp->kredi = kredi;
	tmp->kontenjan = kontenjan;
	tmp->doluluk = 0;
	tmp->num_listesi = (int*)malloc(1*sizeof(int));
	tmp->next = NULL;
	return tmp;
}

islem *islem_olustur(int islem_numarasi , char *ders_kodu , int ogr_num , char *tarih , char *durum){
	islem* tmp;
	tmp = (islem*) malloc(sizeof(islem));	
	tmp->islem_num = islem_numarasi;
	strcpy(tmp->ders_kodlari,ders_kodu);
	tmp->numlar = ogr_num;
	strcpy(tmp->tarih,tarih);
	strcpy(tmp->durum,durum);
	tmp->next = NULL;

	return tmp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ogr_sirali_ekleme(ogr **head, int num ,char *ad , char *soyad , int kredi , int ders){
	ogr *tmp;
	ogr *newNode= ogr_olustur(num,ad,soyad,kredi,ders);
	if(*head==NULL){
		newNode->next = *head;
		*head = newNode;
		
	}																		        	//          ÖÐRENCÝ EKLEME
	else{
		tmp = *head;
		while(tmp->next!= NULL && tmp->next->numara < num){
			tmp= tmp->next;
		}
		if(tmp->next==NULL){
			tmp->next=newNode;
		}
		else{
			newNode->next = tmp->next;
			tmp->next=newNode;	
		}
	}
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ders_sirali_ekleme(ders **head, char *kod , char *ders_ismi , int kredi , int kontenjan){
	ders *tmp;
	ders *newNode= ders_olustur(kod,ders_ismi,kredi,kontenjan);
	if(*head==NULL){
		newNode->next = *head;
		*head = newNode;
	}																		        	//          DERS EKLEME
	else{
		
		if(strcmp(kod,(*head)->kod) < 0){
			newNode->next = (*head);
			(*head)= newNode;
		}
		else{
			tmp = *head;
			while(tmp->next!= NULL && strcmp(tmp->next->kod,kod) < 0){
				tmp= tmp->next;
			}
			if(tmp->next==NULL){
				tmp->next=newNode;
			}
			else{
				newNode->next = tmp->next;
				tmp->next=newNode;	
			}
		}
	}
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void islem_sirali_ekleme(islem **head, int islem_num ,char *ders_kodu , int ogr_num , char *tarih , char *durum){
	islem *tmp;
	islem *newNode= islem_olustur(islem_num,ders_kodu,ogr_num,tarih,durum);
	if(*head==NULL){
		newNode->next = *head;
		*head = newNode;
	}																		        	//          ÝÞLEM EKLEME
	else{
		tmp = *head;
		while(tmp->next!= NULL && tmp->next->islem_num < islem_num){
			tmp= tmp->next;
		}
		if(tmp->next==NULL){
			tmp->next=newNode;
		}
		else{
			newNode->next = tmp->next;
			tmp->next=newNode;	
		}
	}
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ogr_sil(ogr **head,int num,islem *head_islem){
	ogr *tmp,*tmp2;
	if((*head)->numara == num){
		tmp=(*head)->next;
		printf("%d Silindi\n",(*head)->numara);
		free(*head);
		(*head)->next=NULL;
		*head = tmp;		
	}
	else{
		tmp = *head;
		while(tmp->next!=NULL && tmp->next->numara!=num){
			tmp = tmp->next;
		}
		if(tmp== NULL){
			printf("Bulunamadi\n");
		}
		else{
			tmp2=tmp->next;
			tmp->next=tmp->next->next;
			printf("\n%d Silindi\n",tmp2->numara);
			free(tmp2);
			tmp2=NULL;
		}
		
	}
	while(head_islem!=NULL){
		if( head_islem->numlar==num)
		strcpy(head_islem->durum,"Ogrenci_Silindi");
		head_islem=head_islem->next;
	}
	
}
                                                          /////            ÖÐRENCÝ VE DERS SÝLME
void ders_sil(ders **head,char *kod ,islem *head_islem ,ogr *head_ogr){
	ders *tmp,*tmp2;
	
	if(strcmp((*head)->kod,kod) == 0){
		char date[20];
		
			char durum[20] = "Ders Kapandi";			
			printf("Tarih Giriniz : ");
			scanf("%s",date);			
			int f = 0;
			
			for(f = 0 ; f < (*head)->doluluk ;f++){
			int num = (*head)->num_listesi[f];
			ogr *tmp_ogr = ogr_bulucu(head_ogr,num);
			tmp_ogr->ogr_ders--;
			tmp_ogr->ogr_kredi = tmp_ogr->ogr_kredi - (*head)->kredi;
			}
		tmp=(*head)->next;
		printf("%s Silindi\n",(*head)->kod);
		free(*head);
		(*head)->next=NULL;
		*head = tmp;		
	}
	else{
		tmp = *head;
		while(tmp->next!=NULL && strcmp(tmp->next->kod,kod) != 0){
			tmp = tmp->next;
		}
		if(tmp == NULL){
			printf("Silmek Istediginiz Ders Bulunamadi\n");
		}
		else{
			tmp2=tmp->next;
			tmp->next=tmp->next->next;
			
			char date[20];
			char *durum = "Ders Kapandi";
			
			printf("Tarih Giriniz : ");
			scanf("%s",date);
			
			printf("\n%s Silindi\n",tmp2->kod);
			
			int f = 0;
			
			for(f = 0 ; f < tmp2->doluluk ;f++){
		
			int num = tmp2->num_listesi[f];
			ogr *tmp_ogr = ogr_bulucu(head_ogr,num);
			tmp_ogr->ogr_ders--;
			tmp_ogr->ogr_kredi = tmp_ogr->ogr_kredi - tmp2->kredi;
			}
			
			free(tmp2);
			tmp2=NULL;
		}
	}
	while(head_islem!=NULL){
		if(strcmp(head_islem->ders_kodlari,kod)==0)
		strcpy(head_islem->durum,"Ders_Kapandi");
		head_islem=head_islem->next;
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OgrenciDerseKayit(ogr *head_ogr, int max_kredi , int max_ders_sayisi , ders *head_ders , islem *head_islem){
	
	char *ders_kodu;
	int num;
	ogr *tmp_ogr;
	tmp_ogr = head_ogr;
	ders *tmp_ders;
	                                                            ///////      ÖÐRENCÝYÝ DERSE KAYDETTÝRME
	printf("Kayit Etmek Istediginiz Ogrencinin Numarasini Giriniz : ");
	scanf("%d" ,&num);
	
	if(ogr_kontrol(head_ogr,num) == 1){
			
		tmp_ogr = ogr_bulucu(head_ogr ,num);
		
		if(tmp_ogr->ogr_kredi < max_kredi){
			
			if(tmp_ogr->ogr_ders < max_ders_sayisi){
			
				printf("Ogrenciye Eklemek Istediginiz Dersin Kodunu Giriniz : ");
				scanf("%s" ,ders_kodu);
				
				if(ders_kontrol(head_ders,ders_kodu) == 1){
					
					if(Ders_Listesinde_Ogrenci_Kontrol(head_ders , num , ders_kodu) == 0){
						
						tmp_ders = ders_bulucu(head_ders,ders_kodu);
						
						if(tmp_ogr->ogr_kredi + tmp_ders->kredi <= max_kredi){
					
					
							if(tmp_ders->doluluk < tmp_ders->kontenjan) {
								
								char durum[] = {"kayitli"};
								char tarih[] = {"06.01.2022"};
								Dersin_Listesine_Ogrenci_Ekleme(head_ogr,head_ders ,head_islem ,tmp_ders->kod ,tmp_ogr->numara);
								tmp_ders->doluluk ++;
								tmp_ogr->ogr_kredi = tmp_ogr->ogr_kredi + tmp_ders->kredi;
								tmp_ogr->ogr_ders++;
								printf("Kayit Islemi Basariyla Gerceklesmistir");						
								int son_numara = son_islem_bulucu(head_islem) + 1;
								islem_sirali_ekleme(&head_islem,son_numara,ders_kodu,num,tarih,durum);
							}
							else{
								printf("Dersin Kontenjani Doludur\n");
							}
						}else
						{
							printf("Alinacak Dersle Beraber Toplam Kredi Siniri Asmaktadir.");
						}
					}
					else {
						printf("Ogrenci Bu Derse Zaten Kayitlidir\n");
					}
					 
				}
				
				else
					{
						printf("Böyle Bir Ders Bulunmamaktadir\n");
					}
			}
			else{
				printf("Ogrenci Max Ders Adedince Ders Almistir\n");
			}
		}
		else{
			printf("Kredisi Doludur Ders Kaydi Yapilamaz\n");
		}	
	}
	else{
		printf("Bu Numaraya Sahip Bir Ogrenci Bulunmamaktadir. ");
	}
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ogrenci_Dersten_Kayit_Silme(ogr *head_ogr, ders *head_ders , islem *head_islem){
	
	char dersin_kodu[15];
	int num;
	ogr *tmp_ogr;
	tmp_ogr = head_ogr;
	ders *tmp_ders;
	tmp_ders = head_ders;
	islem *tmp_islem;
	tmp_islem = head_islem;
	
	printf("Dersten Kaydini Silmek Istediginiz Ogrencinin Numarasini Giriniz : ");
	scanf("%d" ,&num);
	                                                                    ///////     ÖÐRENCÝNÝN DERS KAYDINI SÝLME
	if(ogr_kontrol(head_ogr,num) == 1){
			
		tmp_ogr = ogr_bulucu(head_ogr ,num);
		
			printf("Silmek Istediginiz Dersin Kodunu Girin : ");
			
			scanf("%s",dersin_kodu);
			if(ders_kontrol(head_ders,dersin_kodu) == 1){
				
				if(Ders_Listesinde_Ogrenci_Kontrol(head_ders , num , dersin_kodu) == 1){
					
					char tarih[30];
					char durum[30] ="Ogrenci Dersi Birakti";
					
					printf("Tarih Giriniz : ");
					scanf("%s",tarih);
					
					tmp_ders = ders_bulucu(head_ders,dersin_kodu);
					Dersin_Listesinden_Ogrenci_Silme(head_ogr, head_ders , head_islem ,dersin_kodu , num);
					tmp_ders->doluluk--;
					tmp_ogr->ogr_ders--;
					tmp_ogr->ogr_kredi = tmp_ogr->ogr_kredi - tmp_ders->kredi;
					printf("Silme Islemi Basariyla Gerceklesmistir");
				}
				else{
					printf("Ogrencinin Bu Derse Kaydi Mevcut Degildir.");
				}
			}
			else{
				printf("Böyle Bir Ders Bulunmamaktadir\n");		
			}		
	}
	else{
		printf("Bu Numaraya Sahip Bir Ogrenci Bulunmamaktadir. ");
	}
	while(head_islem!=NULL && (strcmp(head_islem->ders_kodlari,dersin_kodu)!=0|| head_islem->numlar!=num ))
	head_islem=head_islem->next;
	if(head_islem!=NULL)
	strcpy(head_islem->durum,"Ogrenci_Birakti");
}

////////////////////////////////////////////////////////////////////////  ÖÐRENCÝ DERS LÝSTESÝNE DERS EKLEME
	
void Dersin_Listesine_Ogrenci_Ekleme(ogr *head_ogr, ders *head_ders , islem *head_islem ,char *kod ,int  num){
	
	ders *tmp_ders;
	tmp_ders = ders_bulucu(head_ders,kod);
	int boyut = tmp_ders->doluluk + 1;
	tmp_ders->num_listesi = (int*)realloc(tmp_ders->num_listesi,boyut*sizeof(int)); 
	tmp_ders->num_listesi[tmp_ders->doluluk] = num;
	
}

void Dersin_Listesinden_Ogrenci_Silme(ogr *head_ogr, ders *head_ders , islem *head_islem ,char *kod ,int  num){
	
	ders *tmp_ders;
	tmp_ders = ders_bulucu(head_ders,kod);
	int z = 0;
	if(Ders_Listesinde_Ogrenci_Kontrol(head_ders , num , kod) == 1){
		while(tmp_ders->num_listesi[z] != num){
			z++;
		}
	
	    for(z = 0 ; z< tmp_ders->doluluk ; z++){
        
		tmp_ders->num_listesi[z] = tmp_ders->num_listesi[z+1];
        
		}
	}
	
	else{
		printf("Ilgili Ogrencinin Bu Derste Kaydi Olmadigi Icin Silinemez.");
	}
	
}

int Ders_Listesinde_Ogrenci_Kontrol(ders *head_ders , int num , char *ders_kodu){
	
	int z = 0;
	ders *tmp_ders = head_ders;
	tmp_ders = ders_bulucu(head_ders,ders_kodu);
	
	for(z = 0 ; z < tmp_ders->doluluk+1 ; z++){
		if(tmp_ders->num_listesi[z] == num){
			return 1;
		}
	}
	return 0;
	
}
	
void islemleri_dosyaya_yazdirma(islem *head_islem , FILE *islem_yazma){
	
	islem *tmp_islem = head_islem;
	
	while(tmp_islem != NULL){
		fprintf(islem_yazma,"%d %s %d %s %s\n",tmp_islem->islem_num,tmp_islem->ders_kodlari,tmp_islem->numlar,tmp_islem->tarih,tmp_islem->durum);
		tmp_islem = tmp_islem->next;
	}
}

void ogrencileri_dosyaya_yazdirma(ogr *head_ogr , FILE *ogr_yazma){
	
	ogr *tmp_ogr = head_ogr;
	
	while(tmp_ogr != NULL){
		fprintf(ogr_yazma,"%d %s %s %d %d\n",tmp_ogr->numara,tmp_ogr->ad,tmp_ogr->soyad,tmp_ogr->ogr_kredi,tmp_ogr->ogr_ders);
		tmp_ogr = tmp_ogr->next;
	}
}

void durum_yaz(islem *head){
	FILE * fp;
	fp=fopen("StudentLectureProcess.txt","w");
	if(fp==NULL){
		printf("Dosya acilamadi");
	}
	else{
		while(head!=NULL){
			fprintf(fp,"%d,%s,%d,%s,%s\n", head->islem_num , head->ders_kodlari , head->numlar , head->tarih , head->durum);
			head=head->next;
		}
		fclose(fp);
		
	}
}

void sinif_listeleri_olusturma(ders *head_ders){
	
	ders *tmp_ders = head_ders;
	
	while(tmp_ders != NULL){
		int i = 0;
		printf("\n%s\n",tmp_ders->kod);
		for(i = 0 ; i < tmp_ders->doluluk; i++){
		printf("%d  ",tmp_ders->num_listesi[i]);
		}
		tmp_ders = tmp_ders->next;
	}
}

void ogr_yaz(ogr *head){
	FILE * fp;
	fp=fopen("Students.txt","w");
	ogr *tmp = head;
	if(fp==NULL){
		printf("Dosya acilamadi");
	}
	else{
		while(tmp!=NULL){
			fprintf(fp,"%d,%s,%s,%d,%d\n",tmp->numara,tmp->ad,tmp->soyad,tmp->ogr_kredi,tmp->ogr_ders);
			tmp=tmp->next;
		}
		fclose(fp);
	}
}

void ders_yaz(ders *head){
	FILE * fp;
	fp=fopen("Lectures.txt","w");
	ders *tmp = head;
	if(fp==NULL){
		printf("Dosya acilamadi");
	}
	else{
		while(tmp!=NULL){
			fprintf(fp,"%s,%s,%d,%d\n",tmp->kod,tmp->ders_ismi,tmp->kredi,tmp->kontenjan);
			tmp=tmp->next;
		}
		fclose(fp);
	}
}

void sinif_listeleri_yazdirma(ders *head_ders){
	
	char kod[30];
	FILE * fp;
	ders *tmp_ders = head_ders;
	
	while(tmp_ders =! NULL){
	int i;	
	strcpy(kod,tmp_ders->kod);
	strcat(kod,".txt");
	fp=fopen(kod,"w");
	for(i = 0 ; i < tmp_ders->doluluk ;i++){
		fprintf(fp,"\n %d \n",tmp_ders->num_listesi[i]);
	}
	tmp_ders = tmp_ders->next;
	
	fclose(fp);
	
	}
}


