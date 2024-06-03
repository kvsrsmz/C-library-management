#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

//K�T�PHANE OTOMASYONU

typedef struct Kitap //K�TAP YAPISI ���NDE DE���KEN TUTMAYA YARIYOR
{
	int barkod;  //B�R�NC�L ANAHTAR YAN� BA�KA K�TAP �LE AYNI OLAMAZ
	char kitapAdi[30]; 
	char yazarAdi[30];                                                        //k�T�PHENEYE K�TAP EKLENMES� DURUMUNDA BU YAPIYI KULLANARAK ALACA�IZ
	char kitapTuru[30];
	int sayfaSayisi;
} kitap ;//YUKARIDAK� B�LG�LER� kitap �S�ML� DE���KENLE �A�IRALIM 

typedef struct Uye //UYE YAPISI ���NDE VER� TUTMAYA YARIYOR
{
	double uyeTC; //B�R�NC�L ANAHTAR YAN� BA�KA �YE �LE AYNI OLAMAZ
	char uyeAdSoyad[30];
	char uyeCinsiyet[30];                                                     //K�T�PHENEYE �YE EKLENMSE� DURUMUNDA BU YAPI KULLANILIR
	char uyelikTarihi[30];
} uye ;//YUKARIDAK� B�LG�LER� uye �S�ML� DE���KENLE �A�IRALIM

typedef struct Emanet
{
	double uyeTC2; //YABANCIL ANAHTAR
	char kitapAdi2[30];
	int kitapBarkod;
	int kullandigiGunSyisi;                                                   //EMANET K�TAP �SLEMLER� DURUMUNDA BU YAPIYI KULLANACA�IZ
	char iadeTarihi[30];
	char teslimTarihi[30];
} emanet ;//YUKARIDAK� B�LG�LER� emanet �S�ML� DE���KENLE �A�IRALIM

void kitapEkle()
{
	system("cls");//EKRAN TEM�ZLER YEN� EKRAN A�AR
	printf("\tKITAP EKLEME EKRANI \n\n");
	
	kitap k1; //YUKARIDA OLU�TURDU�UMUZ K�TAP YAPISININ ���NDEK� DE���KENLER� KULLANMAYA YARIYOR.
	
	printf("Barkod        : ");scanf("%d",&k1.barkod);
	printf("Kitap Adi        : ");scanf("%s",&k1.kitapAdi); 
	printf("Yazar Adi-Soyadi : ");scanf("%s",&k1.yazarAdi);
	printf("Kitap Turu       : ");scanf("%s",&k1.kitapTuru);
	printf("Sayfa Sayisi     : ");scanf("%d",&k1.sayfaSayisi);
	
	//DOSYAYA VER� EKLEMEK AMACIYA BU KOD SATIRLARINI KULLANACA�IZ
	FILE * ptr = fopen("kitaplar.dat" , "a+b");//kitaplar.dat ADLI DOSYA A�AR. DOSYAYA VER� EKLEMEK ���N a+b modu kullan�l�r.
	fwrite( &k1, sizeof(kitap), 1 , ptr);//OLU�TURULAN DOSYAYA K�TAP YA�ISINDA TANIMLADI�IMIZ DE���KENLER� YAZAR KAYDEDER.
	fclose(ptr);//A�ILAN DOSYAYI KAPATIR
	printf("KITAP KAYDI TAMAM! \n");
}

void kitapSil()
{  
    system("cls");//EKRAN TEM�ZLER YEN� EKRAN A�AR
	printf("\tKITAP SILME EKRANI \n\n");
	
	kitap k1; //YUKARIDA OLU�TURDU�UMUZ K�TAP YAPISININ ���NDEK� DE���KENLER� KULLANMAYA YARIYOR.
	int barkod;
	int sonuc=0;
	printf("Barkod        : ");scanf("%d",&barkod);
	
	//DOSYAYA VER� EKLEMEK AMACIYA BU KOD SATIRLARINI KULLANACA�IZ
	FILE * ptr = fopen("kitaplar.dat" , "r+b");//oku
	FILE * yptr = fopen("yedek.dat" , "w+b");//yaz
	while(fread( &k1, sizeof(kitap), 1 , ptr) !=  NULL )
	{
		if(barkod != k1.barkod)
		{
			fwrite( &k1, sizeof(kitap), 1 , yptr);
		}
		else
		{
			sonuc=1;
		}
			
	}
	
	fclose(ptr);//A�ILAN DOSYAYI KAPATIR
	fclose(yptr);
	if(sonuc==0)
	{
		printf("%d numarali barkod bulunamadi!\n",barkod);
	}
	else
	{
		remove("kitaplar.dat");
		rename("yedek.dat","kitaplar.dat");  //Bu kodlar, "kitaplar.dat" dosyas�ndan belirli bir barkod numaras�na sahip bir kitab�n verilerini siler ve "yedek.dat" adl� bir dosyadan bu kitap verilerini al�r. 
		printf("%d barkod numarali kitap silindi!\n",barkod);
	}

}

void kitapListele()
{
	system("cls");//EKRAN TEM�ZLER YEN� EKRAN A�AR
	printf("\tKITAP LISTELEME EKRANI \n\n");
	
	kitap k1; //YUKARIDA OLU�TURDU�UMUZ K�TAP YAPISININ ���NDEK� DE���KENLER� KULLANMAYA YARIYOR.
	
	
	//DOSYAYA VER� EKLEMEK AMACIYA BU KOD SATIRLARINI KULLANACA�IZ
	FILE * ptr = fopen("kitaplar.dat" , "r+b");//oku
	
	printf("%-20s%-30s%-30s%-30s%-20s\n","BARKOD","KITAP-ADI","YAZAR-ADI","KITAP TURU","SAYFA-SAYISI");
	
	while(fread( &k1, sizeof(kitap), 1 , ptr) !=  NULL )
	{
		printf("%-20d%-30s%-30s%-30s%-20d\n",k1.barkod,k1.kitapAdi,k1.yazarAdi,k1.kitapTuru,k1.sayfaSayisi);
		
	}
	
	
	fclose(ptr);//A�ILAN DOSYAYI KAPATI
	
	
}

void kitapIslemleri()
{
	system("cls");//EKRAN TEM�ZLER YEN� EKRAN A�AR
	printf("\tKITAP ISLEMLERI EKRANI \n\n");
	
	int secim;
	printf("1-Kitap Ekle \n");
	printf("2-Kitap Sil \n");
	printf("3-Kitaplari Listele \n");
	printf("0-Ana Menuye Don \n");
	printf("Seciminiz: ");
	scanf("%d",&secim);
	
	switch(secim)
	{
		case 1: kitapEkle();
		break;
			
		case 2: kitapSil();
		break;
		
		case 3: kitapListele();
		break;
		
		case 0:
		break;
		
		default:
			printf("Hatali secim yaptiniz, ana menuye yonlendiriliyorsunuz...\n");
			break; 
			
	}
}

void uyeEkle()
{
	system("cls");//EKRAN TEM�ZLER YEN� EKRAN A�AR
	printf("\tUYE EKLEME EKRANI \n\n");
	
	uye u1; //YUKARIDA OLU�TURDU�UMUZ K�TAP YAPISININ ���NDEK� DE���KENLER� KULLANMAYA YARIYOR.
	
	printf("T.C.            : ");scanf("%lf",&u1.uyeTC);
	printf("Uye Adi-Soyadi  : ");scanf("%s",&u1.uyeAdSoyad); //[^\n]s ifadesini anamd�m bunu bi ��ren sana zahmet
	printf("Uye Cinsiyeti   : ");scanf("%s",&u1.uyeCinsiyet);
	printf("Uyelik Tarihi   : ");scanf("%s",&u1.uyelikTarihi);
	
	//DOSYAYA VER� EKLEMEK AMACIYA BU KOD SATIRLARINI KULLANACA�IZ
	FILE * ptr = fopen("uyeler.dat" , "a+b");//kitaplar.dat ADLI DOSYA A�AR. DOSYAYA VER� EKLEMEK ���N a+b modu kullan�l�r.
	fwrite( &u1, sizeof(uye), 1 , ptr);//ptr dosyas�na k1 ADLI B�R kitap  YAPISININ BELLEK BLO�UNU YAZAR.
	fclose(ptr);//A�ILAN DOSYAYI KAPATIR
	printf("UYE KAYDI TAMAM! \n");
}
void uyeSil()
{
	system("cls");//EKRAN TEM�ZLER YEN� EKRAN A�AR
	printf("\tUYE SILME EKRANI \n\n");
	
	uye u1; //YUKARIDA OLU�TURDU�UMUZ K�TAP YAPISININ ���NDEK� DE���KENLER� KULLANMAYA YARIYOR.
	double tc;
	int sonuc=0;
	printf("T.C.        : ");scanf("%lf",&tc);
	
	//DOSYAYA VER� EKLEMEK AMACIYA BU KOD SATIRLARINI KULLANACA�IZ
	FILE * ptr = fopen("uyeler.dat" , "r+b");//oku
	FILE * yptr = fopen("yedek.dat" , "w+b");//yaz
	while(fread( &u1, sizeof(uye), 1 , ptr) !=  NULL )
	{
		if(tc != u1.uyeTC)
		{
			fwrite( &u1, sizeof(uye), 1 , yptr);
		}
		else
		{
			sonuc=1;
		}
			
	}
	
	fclose(ptr);//A�ILAN DOSYAYI KAPATIR
	fclose(yptr);
	if(sonuc==0)
	{
		printf("%.0lf T.C'li uye bulunamadi!\n",tc);
	}
	else
	{
		remove("uyeler.dat");
		rename("yedek.dat","uyeler.dat");
		printf("%.0lf T.C.'li uye silindi!\n",tc);
	}
}

void uyeListele()
{
	system("cls");//EKRAN TEM�ZLER YEN� EKRAN A�AR
	printf("\tUYE LISTELEME EKRANI \n\n");
	
	uye u1; //YUKARIDA OLU�TURDU�UMUZ K�TAP YAPISININ ���NDEK� DE���KENLER� KULLANMAYA YARIYOR.
	//int uyesayisi=0;
	
	//DOSYAYA VER� EKLEMEK AMACIYA BU KOD SATIRLARINI KULLANACA�IZ
	FILE * ptr = fopen("uyeler.dat" , "r+b");//oku
	
	printf("%-20s%-30s%-30s%-20s\n","TC","UYE-ADI","UYE-CINSIYETI","UYELIK-TARIHI");
	
	while(fread( &u1, sizeof(uye), 1 , ptr) !=  NULL )
	{
		printf("%-20.0lf%-30s%-30s%-20s\n",u1.uyeTC,u1.uyeAdSoyad,u1.uyeCinsiyet,u1.uyelikTarihi);
		//uyesayisi++;
	}
	
	
	fclose(ptr);//A�ILAN DOSYAYI KAPATI
	//printf("Toplam uye sayisi :%d\n",uyesayisi);
}

void uyeIslemleri()
{
	system("cls");//EKRAN TEM�ZLER YEN� EKRAN A�AR
	printf("\tUYE ISLEMLERI EKRANI \n\n");
	
	int secim;
	printf("1-Uye Ekle \n");
	printf("2-Uye Sil \n");
	printf("3-Uyeleri Listele \n");
	printf("0-Ana Menuye Don \n");
	printf("Seciminiz: ");
	scanf("%d",&secim);
	
	switch(secim)
	{
		case 1: uyeEkle();
		break;
			
		case 2: uyeSil();
		break;
		
		case 3: uyeListele();
		break;
		
		case 0:
		break;
		
		default:
			printf("Hatali secim yaptiniz, ana menuye yonlendiriliyorsunuz...\n");
			break; //neden break kulland�k bilmiyoruuuummmm
			
	}
}




void oduncKitapVer()
{
    system("cls");
    printf("\t ODUNC KITAP VERME EKRANI \n\n");

    emanet e1;
    uye u1;
    kitap k1;
    int usonuc = 0, ksonuc = 0;

    printf("T.C.    : ");
    scanf("%lf", &e1.uyeTC2);
    printf("Barkod  : ");
    scanf("%d", &e1.kitapBarkod);
    
    FILE * ptr = fopen("oduncler.dat", "a+b");
    fwrite( &e1, sizeof(emanet), 1, ptr);
    fclose(ptr);
    printf("Odunc kitap kaydi tamam!");
}	


void oduncKitapIade()
{
    system("cls");
    printf("\t ODUNC KITAP �ADE ALMA EKRANI \n\n");

    emanet e1;
    uye u1;
    kitap k1;
    int sonuc = 0, sayac = 0;
    int kitapBarkod;

    printf("T.C.    : ");
    scanf("%lf", &e1.uyeTC2);
    printf("Barkod  : ");
    scanf("%d", &kitapBarkod);
    
    FILE *ptr= fopen("oduncler.dat", "r+b");
    while(fread (&e1 , sizeof(emanet),1, ptr))
    {
    	if(kitapBarkod == e1.kitapBarkod)
    	{
    		sonuc=1;
    		break;
		}
		sayac++;
	}
	
	if(sonuc==0)
	{
		fclose(ptr);
		printf("%d barkod numarali kitap bulunamadi!",kitapBarkod);
		return;
	}
	else
	{
		rewind(ptr);
		fwrite(&e1, sizeof(emanet),1,ptr);
		fclose(ptr);
		printf("Odunc Kitap Iade Islemi Tamam!");
		
	}
    
    fseek ( ptr,(sayac)*sizeof(emanet),0);
    fwrite( &e1, sizeof(emanet), 1, ptr);
    fclose(ptr);

	
	
} 

void oduncKitapListele()
{
	system("cls");
	printf("\t ODUNC KITAPLAR LISTESI EKRANI\n\n");
	emanet e1;
	
	FILE * ptr = fopen("oduncler.dat","r+b");
	printf("%-20s%-20s%\n","TC","BARKOD");
	while(fread(&e1,sizeof(emanet),1,ptr) != NULL)
	{
		printf("%-20.0lf%-20d\n",e1.uyeTC2,e1.kitapBarkod);
	}
	fclose(ptr);
	
	
}
void emanetKitapIslemleri()
{
	system("cls");//EKRAN TEM�ZLER YEN� EKRAN A�AR
	printf("\tODUNC KITAP ISLEMLER� EKRANI \n\n");
	
	int secim;
	printf("1-Odunc Kitap Ver \n");
	printf("2-Odunc Kitabi Iade Al \n");
	printf("3-Odunc Kitaplari Listele \n");
	printf("0-Ana Menuye Don \n");
	printf("Seciminiz: ");
	scanf("%d",&secim);
	
	switch(secim)
	{
		case 1: oduncKitapVer();
		break;
			
		case 2: oduncKitapIade();
		break;
		
		case 3: oduncKitapListele();
		break;
		
		case 0:
		break;
		
		default:
			printf("Hatali secim yaptiniz, ana menuye yonlendiriliyorsunuz...\n");
			break; //neden break kulland�k bilmiyoruuuummmm
			
	}
}

int menu() //MEN� FONKS�YONU OLU�TURDUK
{
	int secim;
	printf("\n\tKUTUPHANE OTOMASYONU \n\n");
	printf("\t1- KITAP ISLEMLERI \n");
	printf("\t2- UYE ISLEMLERI \n");
	printf("\t3- EMANET KITAP  ISLEMLERI \n");
	printf("\t0- PROGRAMI KAPAT \n");
	printf("\tSeciminiz : ");
	scanf("%d",&secim);
	return secim;
	
}

int main()
{
	int secim = menu();
	
	while( secim != 0 )
	{
		switch(secim)
		{
			case 1: kitapIslemleri();
			break;
			
			case 2: uyeIslemleri();
			break;
			
			case 3: emanetKitapIslemleri();
			break;
			
			case 0:
			break;
			
			default:
				printf("Hatali secim yaptiniz ! \n");
			
		}
		secim = menu();//MEN� FONKS�YONUNU S�REKL� �A�IRSIN
	}
	
	printf("\tPROGRAMI KAPATTINIZ...");
	
	
	
	return 0;
}

