#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stddef.h>

struct Kisi {
	char ad[20]; 
	char soyad[20];  
	char tel[20];
	char adres[20];
	char id[20];  
	char parola[20];
	char parolaTekrar[20]; 	
};

struct Oto {
	int numara; 
	char marka[20]; 
	char model[20] ; 
	int fiyat; 	
};

void aracKirala( struct Kisi k1 ) 
{
	struct Oto o1; 
	char tarih[20]; 
	int numara;
	int toplamUcret; 
	int gunSayisi; 
	int sonuc=0; 
	
    system("color 0a");
	printf("mevcut arac bilgileri \n\n") ; 
	printf("%s\t%s\t%s\n", "SIRANO", "MARKA", "MODEL", "FIYAT" ) ; 
	
	FILE *ptr = fopen("otomobiller.txt", "r") ; 
	if( ptr!=NULL  )
	{
		while ( ( fscanf(ptr, "%d\t%s\t%s\t%d\n", &o1.numara, o1.marka, o1.model, &o1.fiyat ) ) != EOF )  
		{
			printf("%d\t%s\t%s\t%d\n", o1.numara, o1.marka, o1.model, o1.fiyat ) ; 
			
		}
		
		rewind(ptr) ; 
		
		printf("kiralamak istediginiz aracin numarasini girin : ") ; scanf("%d", &numara) ; 
		while ( ( fscanf(ptr, "%d\t%s\t%s\t%d\n", &o1.numara, o1.marka, o1.model, &o1.fiyat ) ) != EOF )  
		{
			if( numara == o1.numara ) 
			{
				printf("sectiginiz aracin bilgileri : %d\t%s\t%s\t%d\n", o1.numara, o1.marka, o1.model, o1.fiyat ) ; 
				sonuc =1; 
				fclose(ptr) ; 
				break; 								
			} 			
			
		}
		if( sonuc ==1 )		
		
		{
			printf("kiralama tarihini giriniz  :  ") ; 
			scanf("%s", tarih) ; 
			printf("kiralama yapilcak gun sayisi :  ") ; 
			scanf("%d", &gunSayisi) ; 
			toplamUcret = gunSayisi * o1.fiyat ; 
			printf("\n kiralama sozlesmeniz basariyla gerceklestirildi \n") ; 
			printf("toplam ucret olan %d TL yi asagidaki IBAN numarasina yatirmaniz gerekmektedir \n", toplamUcret) ; 
			printf("oto kiralama sozlesmeniz kesinlesmis olacaktir \n") ; 
			
			FILE *ptr2= fopen( "kiralananAraclar.txt", "a+") ; 
			if( ptr2!= NULL  ) 
			{
				fprintf ( ptr2, "\n\n****************************************** \n" ) ; 
				fprintf(ptr2, "Kisi bilgileri : %s\t%s\t%s\t%s\n",  k1.ad, k1.soyad, k1.tel, k1.adres  ) ; 
				fprintf(ptr2, "Arac bilgileri : %d\t%s\t%s\n", o1.numara, o1.marka, o1.model  ) ; 
				fprintf(ptr2, "Kiralama tarihi: %s\n", tarih   ) ; 
				fprintf(ptr2, "Ucret bilgileri: %d X %d = %d ", gunSayisi, o1.fiyat, toplamUcret ) ; 
				
				fclose(ptr2) ; 
				
			}  
		}
		else
		{
			system("cls") ; 
			printf("hatali secim yaptiniz \n ") ; 
			aracKirala(k1) ; 
		}
		
	}	
}

void giris()
{
	char id[20], parola[20] ; 
	int static adet= 0; 
	int sonuc= 0; 
	struct Kisi k1; 
	printf("giris ekrani \n "); 
	printf("kullanici adi ( ID ) : "); scanf("%s", id) ; 
	printf("parola               : ") ;
	char ch; 
	int i=0; 
	ch= getch() ; 
	while( ch!= 13  ) 
	{
		parola[i] = ch; 
		printf(" * ") ; 
		ch= getch(); 
		i++; 
	}
	parola[i] = '\0' ; 
	
	FILE *ptr= fopen( "musteriBilgileri.dat", "r+"  ) ; 
		if( ptr!=NULL  ) 
		{
			while( (  fread( &k1, sizeof(struct Kisi), 1, ptr ) ) !=NULL     )
			{
				if( strcmp( id, k1.id ) ==0 && strcmp( parola, k1.parola ) ==0    ) 
				{
					system("cls") ; 
					printf("\ngiris basarili \n\n") ; 
					printf("hos geldiniz %s %s \n\n", k1.ad, strupr(k1.soyad )  ) ; 
					fclose(ptr) ; 
					sonuc= 1; 
										
					break; 					
				}
					
			}
			

				
		}
		
		if( sonuc==0  ) 
		{
			system("cls") ; 
			printf("\nhatali kullani adi veya parola \n") ; 
			adet++; 
			if( adet==3  ) 
			{
				printf("\n 	Ana menuye Yonlendiriliyorsunuz \n") ; 
				adet=0; 
				return 0; 
			}
			
			giris(); 			
		}
		else
		{
			aracKirala(k1); 			
		}	
	
}
void yeniKayit()
{
	struct Kisi k1; 
	printf("\nyeni kayit ekrani, \n\n") ; 
	printf("ad          : ") ; scanf(" %[^\n]s", k1.ad) ; 
	printf("soyad       : ") ; scanf(" %[^\n]s", k1.soyad) ; 
	printf("GSM         : ") ; scanf(" %[^\n]s", k1.tel) ; 
	printf("adres       : ") ; scanf(" %[^\n]s", k1.adres) ; 
	printf("ID          : ") ; scanf(" %[^\n]s", k1.id) ; 
	printf("parola (en az 10 karakter) : ") ; 
	char ch; 
	int i=0; 
	ch= getch() ; 
	while( ch!= 13  ) 
	{
		k1.parola[i] = ch; 
		printf(" * ") ; 
		ch= getch(); 
		i++; 
	}
	k1.parola[i] = '\0' ; 
	
	printf("\nparola tekrari            : ") ; 
	i=0; 
	ch= getch() ; 
	while( ch!= 13  ) 
	{
		k1.parolaTekrar[i] = ch; 
		printf(" * ") ; 
		ch= getch(); 
		i++; 
	}
	k1.parolaTekrar[i] = '\0' ; 
	
	if( strcmp( k1.parola, k1.parolaTekrar ) ==0 && strlen(k1.parola) >=8   ) 
	{
		FILE *ptr= fopen( "musteriBilgileri.dat", "a+b"  ) ; 
		if( ptr!=NULL  ) 
		{
			fwrite( &k1, sizeof(struct Kisi), 1, ptr ) ; 
			fclose(ptr) ; 
			system("cls") ; 			
			printf("\nkayit islemi basarili \n") ; 			
		}
		
	}
	else
	{
		printf("\n kayit islemi hatasi !!! \n") ; 
		yeniKayit(); 
	} 
	
}


int menu () 
{
	int secim; 
	printf("\nOTO KIRALAMA UYGULAMASI \n\n") ; 
	printf("1- giris \n") ; 
	printf("2- yeni kayit \n") ; 
	printf("3- cikis \n") ; 
	printf("seciminiz : ") ; scanf("%d", &secim ); 
	return secim; 
}



int main() 
{
	int secim= menu(); 
	while (secim != 3 ) 
	{
		switch( secim  ) 
		{
			case 1: giris(); break; 
			case 2: yeniKayit(); break; 
			case 3: printf("cikis yaptiniz \n") ; break; 
			default : printf("hatali secim yaptiniz \n") ; 
		}
		secim = menu(); 		
	}	
	
	
	return 0; 
}
