/*****
 
 @NAME        	 	: 	KONSOL POKER (v5) 
 @AUTHOR     	 	: 	M. YILDIRIM BAYRAKÇI 
 @LAST UPDATE	 	:	18/09/2018
 
 # BASKENT UNIVERSITY - MANAGEMENT INFORMATION SYSTEMS
 # This is a console game file prepared for entertaintment. All rights free.

*****/																			

/*/ Kutuphaneler - Libraries /*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*/ Fonksiyon Prototipleri Baslangic /*/
void kar(int[][13]);															/* Kartlari karistirir */
void acikDagit(const int [],const char *[],const char *[]);		/* Kartlari acik bir sekilde dagitir. */ 
int pairCheck(const int [],int *);										/* 5 kartin birbiriyle eslesme sayisini dondurur.*/
int flushCheck(const int []);												/* Elde flush olup olmadigini kontrol eder. */
int straightCheck(const int []);											/* Elde straight durumu olup olmadigini kontrol eder.*/
void sortBubble(int[]);														/* Eli 2,3,4,...,J,O,K,A seklinde siralar. */
int pwrOfHand(const int []);												/* Elin gucune karar verir ve bir guc degeri dondurur. */
int compareHands(const int[],const int[]);							/* Iki elin gucunu karsilastirir. Kazanani belirler. */
void sonucYaz(int);															/* Kazanani ve ne ile kazandigini yazdirir.*/
void desteCopy(int [],int [],const int [4][13]);					/* Destedeki ilk 10 kagidi el dizilerine kopyalar. */
int checkEquals(const int [],const int [],int);						/* Elgucleri esit ise esitlik durumlarini inceler, kazanani belirler. */
void kapaliDagit(void);														/* Kapali bir sekilde dagitir. Herhangi bir bilgi icermez. */
void girisYazdir(void);														/* Program giris menusunu yazdirir. */
void swap(int[],int,const int[4][13]);									/* Oyuncu veya AI kart isterse desteden yeni kartlarla degistirilir. */
void yazdirRules(void);														/* Oyun kurallarini yazdirir. */
void elDurumuYazdir(const int []);										/* Elin hangi durumda oldugunu yazdirir. */
int swapOfComputer(int [],const int [4][13]);						/* AI'nin hangi durumda kac kart isteyecegini ayarlar. */
void clearBuffer(void);														/* Input'taki kullanici kaynakli ekstra girdileri temizler.*/
/*/ Prototipler Bitis /*/

int main()
{	
	srand(time(0));  // rassallýk aktif.
	
	/* DEGISKEN TANIMLARI */
	int i,j,c; 	// sayaclar
	int deste[4][13]={0};																								// 2 boyutlu desteyi temsil eden dizi tanimlandi.
	const char *takim[4]  = {"KUPA","KARO","MA\200A","S\230NEK"};											// Kart takimini temsil eden string/pointer dizisi
	const char *taraf[13] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};					// Kart tarafini temsil eden string/pointer dizisi
	int el1[5]; 	//Oyuncu 1(AI) elini temsil eder.
	int el2[5]; 	//Oyuncu 2(User) elini temsil eder.
	int kartSec,kacSwap; // Hangi kartlarin degistirilecegi ve kac degisim yapilacagini tutan degiskenler.
	char nextTour;			// Bir sonraki ele baslanip baslanmayacagi kararini tutan degisken.
	int sayac,money,bet,maxBet;	// Oyuncu parasini, bahsini ve maksimum bahis miktarini tutan degiskenler.
	char secim,secim2;				// Oyun ici secimler.
	int compBet,pot,acilis;			// Bilgisayar bahsi, ortadaki para ve acilis parasini tutan degiskenler.
	/* TANIMLAR BITIS	*/
	
	/* Oyun basi para, maksimum bahis ve acilis parasi miktarlari atandi. */
	money = 100000;
	maxBet = 10000;
	acilis=1000;
	
	/* Program girisi */
  	girisYazdir(); // Oyun basligi ve kurallari yazdirildi.

	printf("\n\n Oyuna baslamak icin bir tusa basiniz.\n ");
	getch();			// Kullanici herhangi bir tusa basar ve oyun baslar.

	while(nextTour!='\33')	/* Kullanici her el sonunda 'ESC'ye basmadikca oyun devam eder. */
	{
		/* Bazi ilk degerler atandi.*/
		secim='\32';
		compBet=0;	// S
		bet=0;
		pot=acilis;
		
		/*/ Desteye sayi degerleri atandi. 0-51 araliginda. /*/
		c=0;
		for(i=0;i<4;i++)
			for(j=0;j<13;j++)
			{
				deste[i][j]=c;
				c++;
			}
		/*/*/
		
		kar(deste);kar(deste);kar(deste);
		kar(deste);kar(deste);kar(deste);
		/*/ Desteyi kar. (6 defa karýldý. Istege bagli olarak artirilabilir ya da azaltilabilir.) /*/
	
		desteCopy(el1,el2,deste); //destedeki kartlar ellere dagitildi.
		sortBubble(el1);	//el1(AI) siralandi.
		sortBubble(el2);  //el2(User) siralandi.
	
		printf("\n   Bilgisayar :"); // AI kartlari kapali sekilde, oyuncu acik sekilde dagitildi, para ve el durumu yazdirildi.
		kapaliDagit();		
		printf("\n\n   Siz : ");
		elDurumuYazdir(el2);
		printf("\n   Paraniz = %+d\44",money);
		acikDagit(el2,taraf,takim);
		/*-------------------------------------------------------------------------------------------------------------------*/
	
		printf("   1. Bahis koy  2. Pas (-%d\44)     *** Maksimum bahis miktari = %d\44 ***",acilis,maxBet);
		
		while(secim!='\61'&&secim!='\62') // 1 ve 2 disinda karakter girilirse ihmal et.
		secim=getch();
		
		if(secim=='\61') // Bahis koyulmak istenildi ise..
		{
			printf("\n   Bahsi gir:");
			scanf("%9d",&bet);
			clearBuffer(); // Buffer temizlendi.
			
			if(bet>maxBet)
			bet=maxBet;
			else if(bet<0)
			bet=0;
			
			printf("\n   Bilgisayar %d\44 bahsinizi gordu.",bet);
			pot+=bet;
			printf("\n   1.Kart iste  2.Kart isteme");
			secim2='\32';
			while(secim2!='\61'&&secim2!='\62') // 1 ve 2 disinda karakter girerse ihmal et.
			secim2=getch();
			if(secim2=='\61')
			{
				printf("\n   Kac kart istiyorsunuz? :(1-3)\n   "); // KART DEGISIMI BASLANGIC
				scanf("%1d",&kacSwap);
				clearBuffer();
				if(kacSwap>0)
				{
					if(kacSwap>3)
					kacSwap=3;
					printf("\n   Kart iste - Degistirmek istediginiz kartlarin sirasini giriniz(1-5 arasinda)\n");
					for(i=1;i<=kacSwap;i++)
					{
						printf("   %d.Degisim:",i);
						scanf("%1d",&kartSec);
						clearBuffer();
						swap(el2,kartSec,deste);
					}
				}
			}	// KART DEGISIMI BITIS
			
			sortBubble(el2); // Degisimden sonra eli tekrar sirala.
			printf("\n   Bilgisayar %d kart istedi... (Bir tusa basin.)",swapOfComputer(el1,deste)); 
			sortBubble(el1);
			getch();
			
			printf("\n   Bilgisayar : ");
			kapaliDagit();
			printf("\n   Siz : ");
			elDurumuYazdir(el2);
			printf("\n   Paraniz = %+d\44",money);
			acikDagit(el2,taraf,takim);
			if(compBet==0)
			{
				secim2='\32';
				printf("\n   1.Bahis koy  2. Kartlari Ac	  *** Maksimum bahis miktari = %d\44 ***",maxBet);
				while(secim2!='\61'&&secim2!='\62') // 1 ve 2 disinda karakter girerse ihmal et.
				secim2=getch();
			}
			else
			;
			
			if(secim2=='\61')
			{
				printf("\n   Bahsi gir:");
				scanf("%9d",&bet);
				clearBuffer();
				if(bet>maxBet)
				bet=maxBet;
				else if(bet<0)
				bet=0;
				printf("\n   Bilgisayar %d\44 bahsinizi gordu.",bet);
				pot+=bet;
			}
			else
			;
			
			//kartlar acildi. sonuc kismi
			if(compareHands(el1,el2)>9&&compareHands(el1,el2)<38)
			money-=pot;
			else if(compareHands(el1,el2)>49&&compareHands(el1,el2)<78)
			money+=pot;
			printf("\n----------------------------------------------------------------------------------------------\n");
			printf("\n   Bilgisayar : ");
			elDurumuYazdir(el1);
			acikDagit(el1,taraf,takim);
			printf("   Siz : ");
			elDurumuYazdir(el2);
			printf("\n   Paraniz = %d\44",money);
			acikDagit(el2,taraf,takim);
				
			printf("   *** ");
			sonucYaz(compareHands(el1,el2));
			printf(" *** ");
		} // end outer if
		else // oyuncu pas durumu
		{
			money-= acilis;
			printf("\n\n   ***Paraniz : %d\44",money);
		}
	
		if(money<= -100000) // Para -100000 ve kucukse oyun kaybedilir.
		{
			printf("\n\n   Daha fazla borc alamazsiniz. Uzgunum, oyunu kaybettiniz. :( \n");
			return;
		}
		if(money>= 10000000){
			printf("\n\n   TEBRIKLER! Bilgisayarin parasi kalmadi. Oyunu kazandiniz!\n");
			return;
		}
		
		printf("\n\n   Bir sonraki ele baslamak icin herhangi bir tusa basiniz. Oyunu sonlandirmak icin 'ESC' tusuna basiniz.");
		nextTour=getch();
		maxBet += 2000;
		acilis += 500;
	} //end outer while
	printf("\n\n   ***Oyun sonu paraniz : %d\n\n",money);
	printf("\n\n   Kumar kotuluklerin anasidir.. Gule gule..\n\n");
	return 0;	
} //end main

void kar(int wDeste[][13])			// Her kartý rastgele bir kartla deðiþtirerek desteyi karan fonksiyon. 
{	
	int ranSatir,ranSutun,hold,i,j;			// rastgele satir ve sutun degiskenleri, gecici degisken ve sayaclar
	for(i=0;i<4;i++)								// kart siralari 1-den 52 ye atanmisti..
	for(j=0;j<13;j++)								// sirayla her elemani, rastgele bir siradaki elemanla degistirme islemi..
	{
		ranSatir = rand()%4;	
 		ranSutun = rand()%13;					//rastgele satir ve sutunda bir kart bulundu
		hold = wDeste[i][j];
		wDeste[i][j] = wDeste [ranSatir][ranSutun];
		wDeste[ranSatir][ranSutun]=hold;		// kartlarin yerleri degistirildi. 52 defa yapilir.
	}
}

void desteCopy(int elA[],int elB[],const int deck[][13]) /* Destenin 10 kartýný ellere kopyalar.*/
{
	int i,j;
	for(i=0;i<5;i++)		 		// el1 desteden kopyalandi.
	elA[i] = deck[0][i];
	
	for(i=5,j=0;i<10;i++,j++)	//el2 desteden kopyalandi.
	elB[j] = deck[0][i];
}

void sortBubble(int El[]) // Dagitilan desteyi siralayan fonk. simdilik 5 kart. (2,3,4,..,J,O,K,A sirasi)
{
	int tur,i,hold;
	int k1,k2;
	for(tur=0;tur<4;tur++)
	for(i=0;i<4;i++)
	{
		k1=El[i]%13;
		k2=El[i+1]%13;
		
		if(k1>k2) // > yerine < yapilarak siralama terslenebilir.
		{
			hold = El[i]; 
			El[i]= El[i+1];
			El[i+1]=hold;
		}
	}
}
void acikDagit(const int hand[],const char *wTaraf[],const char *wTakim[])		/*Dagit fixed ++*/
{
	int i,k,j;
			
		//ust cerceve
	printf("\n         ");									// sol margin her satir basi + 1 vert + 9 bosluk +1 vert
	for(i=0;i<5;i++)													// kartarsi bosluk ==> tekrarla..
	{
	printf("\311"); //solustkose
	for(j=1;j<10;j++)
	printf("\315"); // ===
	printf("\273"); //sagustkose
	printf(" 	"); //kartarasibosluk
	}
	
	
	//orta kisim
	for(k=0;k<7;k++) //7 satir
	{
		printf("\n         ");
		for(i=0;i<5;i++) // her kart
		{
			printf("\272"); //vert ||
			if(k==0)
			{
				for(j=0;j<7;j++) //ilk satirsa 7 bosluk + taraf(2 hane)
				printf(" ");
				printf("%-2s",wTaraf[hand[i]%13]);
			}
			else if(k==3)
			{
			printf("  "); //2 bosluk - 5 string - 2 bosluk seklinde
			//takim
			printf("%5s",wTakim[hand[i]/13]);
			
			printf("  ");
			}
			else if(k==6)
			{	
				printf("%2s",wTaraf[hand[i]%13]);
				for(j=0;j<7;j++)
				printf(" ");
				
			}
			else
			for(j=0;j<9;j++)
			printf(" ");
			
			printf("\272"); //vert ||
			printf(" 	"); //kartarasibosluk
		}
	}
	

	//alt kisim/
	printf("\n         ");
	for(i=0;i<5;i++)													// kartarsi bosluk ==> tekrarla..
	{
		printf("\310"); //solaltkose
		for(j=1;j<10;j++)
		printf("\315"); // ===
		printf("\274"); //sagaltkose
		printf(" 	"); //kartarasibosluk
	}
	printf("\n\n");
}

int pairCheck(const int hand[5],int *winPtr) /* Elde kac adet eslesme oldugunu dondurur. pointer son eþleþen kartlardan birini göstermek için. */
{
	int z,t,match=0;
	for(z=0;z<4;z++)		
	{	
		for(t=z+1;t<5;t++)
		{
			if(hand[z]%13==hand[t]%13)
			{
				match++;
				*winPtr = hand[z];
			}
		}		
	}
	return match;
}

int flushCheck(const int hand[5])  //flush durumu var mi 
{
	int z; // dongu sayaci
	int karo,sinek,maca,kupa;	//takim sayaci
	int m; //takýmýn numarasý
	kupa=maca=karo=sinek=0;
	for(z=0;z<5;z++)
	{
		m = hand[z]/13;
		if(m==3)
		sinek++;
		else if(m==2)
		maca++;
		else if(m==1)
		karo++;
		else if(m==0)
		kupa++;
		else
		printf("\nBir hata olustu! Hata kodu: FLS181\n");
	}	
	if (kupa==5||maca==5||karo==5||sinek==5)		
	return 1; 
	else
	return 0;
}

int straightCheck(const int hand[5]) // straight var mi?	*fixed.
{
	int i,match=0;
	for(i=0;i<4;i++)
	{
		if(hand[i]%13+1==hand[i+1]%13)
		match++;
	}
	if(match==4)
	return 1;
	else if(match==3)
	{
		if(hand[0]%13==0 && hand[1]%13==1 && hand[4]==12)	// 2,3,4,5,AS siralamasi var ise.
		return 1;
		else 
		return 0;
	}
	else
	return 0;
}

/* EL DURUMU                PUAN(Pwr)    pairChecksonucu				  		
& Royal Straight Flush &		1000				   0
& Straight Flush		  &      500					0
& Four of a Kind 	     &	   300               6		
& Full House 			  &		200               4	
& Flush 			 		  &	 	185               0
& Straight  			  &      165	            0				
& Three of a Kind  	  &	   150               3
& Two Pair 				  &      100					2
& One Pair  			  &	   50						1
& High Card				  &      0+X					0		(X= Kartin degeri (0-12)) (Ornek "As"=12,"K"=11,"2"=0,"3"=1..)
*/
int pwrOfHand(const int hand[])
{
	int handPwr,a;
	handPwr = 50*pairCheck(hand,&a);
	
	if(handPwr<155&&handPwr>0&&flushCheck(hand)==1)	//flushtan degersiz eslesme varsa(1p,2p,3ofakind) ve flush varsa pwr=flush(185) olur.
	handPwr=185;							
	
	if(handPwr==0) //el1 icin eslesme yok ise (olasiliklar = royal flush, str flush, flush, str , high card)
	{
		if(flushCheck(hand)==0&&straightCheck(hand)==0) // high card
		{
			handPwr = hand[4]%13;
		}
		else if(flushCheck(hand)==0&&straightCheck(hand)==1) //flush yok, straight var. Straight
		{
			handPwr = 165;
		}
		else if(flushCheck(hand)==1&&straightCheck(hand)==0)	//flush var, straight yok. Flush
		{
			handPwr = 185;
		}
		else if(flushCheck(hand)==1&&straightCheck(hand)==1) // straight ve flush varsa. 
		{
			if(hand[4]%13==12) //son eleman As ise, royal flush
			handPwr = 1000;
			else //degilse straight flush
			handPwr = 500;
		}
	}
	return handPwr;
}

int compareHands(const int hand1[],const int hand2[])
{
	int hand1Pwr,hand2Pwr; // ellerin gucleri
	
	hand1Pwr = pwrOfHand(hand1);
	hand2Pwr = pwrOfHand(hand2);

	if( hand1Pwr > hand2Pwr ) // 1 kazandi
	{
		if(hand1Pwr<13) // highcard 
		return 10;
		else if(hand1Pwr==50) // one pair
		return 11;
		else if(hand1Pwr==100) // two pair
		return 12;
		else if(hand1Pwr==150) // three of a kind
		return 13;
		else if(hand1Pwr==165) // straight
		return 14;
		else if(hand1Pwr==185) // flush
		return 15;
		else if(hand1Pwr==200) // full house
		return 16;
		else if(hand1Pwr==300) // four of a kind
		return 17;
		else if(hand1Pwr==500) // straight flush
		return 18;
		else if(hand1Pwr==1000) // royal flush
		return 19;
		else
		return 404; //hatali durum kodu
	}
	else if ( hand2Pwr > hand1Pwr ) // 2 kazandi
	{
		if(hand2Pwr<13) // highcard
		return 50;
		else if(hand2Pwr==50) // one pair
		return 51;
		else if(hand2Pwr==100) // two pair
		return 52;
		else if(hand2Pwr==150) // three of a kind
		return 53;
		else if(hand2Pwr==165) // straight
		return 54;
		else if(hand2Pwr==185) // flush
		return 55;
		else if(hand2Pwr==200) // full house
		return 56;
		else if(hand2Pwr==300) // four of a kind
		return 57;
		else if(hand2Pwr==500) // straight flush
		return 58;
		else if(hand2Pwr==1000) // royal flush
		return 59;
		else
		return 405; //hatali durum hata kodu.
	}
	else //esitlik durumunda : 
	return checkEquals(hand1,hand2,hand1Pwr); //hand1Pwr, hand2Pwr esit. 
}	


int checkEquals(const int hand1[],const int hand2[],int eqPwr)
{
	int pairAddr; // pairCheckin pointer parametresine gonderilen adres degisken.	
	int hold1,hold2; // bilgi tutan degiskenler
	pairCheck(hand1,&pairAddr);
	hold1 = pairAddr;  	//el1 son eslenen	kartin degerini hold1 ile tut.							
	
	pairCheck(hand2,&pairAddr);								
	hold2 = pairAddr;		//el2 son eslenen kart degerini hold2 ile tut.
	
	int i,j,k;
	int hand1Kart5,hand2Kart5;
	if(eqPwr<13) // high card durumunda esitlik. (en yuksek kontrol edilmisti. kartin rengine bakilir)
	{
		if(hand1[4]/13>hand2[4]/13) // 0kupa>1karo>2maca>3sinek  bolumlerden sonucu kucuk olan kazanir.
		return 60;	// 2. oyuncu high kart esitligi renk siralamasindan kazanir
		else if(hand2[4]/13>hand1[4]/13)
		return 20; // 1. oyuncu high kart esitligi renk siralamasindan kazanir
		else
		return 406; // hatali durum hata kodu.    
	}
	else if(eqPwr==50) // one pair de esitlik. Esitlik durumunda, Per’in büyüklügüne bakilir. Bu degerler ayni ise sirasiyla 
	{										//3. 4. ve 5. kartlarin kartin büyüklügüne bakilir; bunlarda esit ise per’in rengine bakilir.
		if(hold1%13>hold2%13)	// pairleri karsilastir,
		return 21;					//el1 pair buyukse
		else if(hold2%13>hold1%13)
		return 61;					//el2 pair buyukse
		else //per esitligi
		{
			i=4; 
			j=4;
			for(k=1;k<4;k++)
			{
				while(hand1[i]%13==hold1%13)
				i--;
				while(hand2[j]%13==hold2%13)
				j--;
				if(hand1[i]%13>hand2[j]%13)
				return 22;
				else if(hand2[j]%13>hand1[i]%13)	//
				return 62;
				else
				{
					i--;
					j--;
				}
			}
			if(hold2/13>hold1/13) // buraya ulastiysa renge bak.
			return 23;
			else
			return 63;			
		}
	}												
	else if(eqPwr==100) // two pair esitligi
	{
		if(hand1[3]%13>hand2[3]%13)	//Buyuk pairleri kontrol et.
		return 24;
		else if(hand2[3]%13>hand1[3]%13)
		return 64;
		else if(hand1[1]%13>hand2[1]%13) //kucuk pairleri kontrol et.
		return 25;
		else if(hand2[1]%13>hand1[1]%13)
		return 65;
		else //buyuk ve kucuk pairler esitse, 5. karti bulup karsilastir.
		{
			if(hand1[4]%13!=hand1[3]%13)        //el1 5.kart sonda ise
			hand1Kart5 = hand1[4];
			else if(hand1[0]%13!=hand1[1]%13)  //basta ise
			hand1Kart5 = hand1[0];
			else											// ortada ise
			hand1Kart5 = hand1[2];
	
			if(hand2[4]%13!=hand2[3]%13)		//el2 5.kart sonda ise
			hand2Kart5 = hand2[4];
			else if(hand2[0]%13!=hand2[1]%13)	//basta ise
			hand2Kart5 = hand2[0];
			else											// ortada ise
			hand2Kart5 = hand2[2];
			//5. kartlar bulundu
			//Onlari karsilastir.
			if(hand1Kart5%13>hand2Kart5%13)		//buyukluk karsilastirma
			return 26;
			else if(hand2Kart5%13>hand1Kart5%13)
			return 66;
			else if(hand1Kart5/13<hand2Kart5/13)				//renk karsilastirma
			return 27;
			else if(hand2Kart5/13<hand1Kart5/13)
			return 67;
			else
			return 416; // hatali durum hata kodu.
		}	// 5. eleman kontrol sonu.
	} // two pair kontrol sonu.
	
	else if(eqPwr==150) // three of a kind esitligi
	{
		// 3 er li eslesenler karsilastirilir. tek karsilastirma yeter.
		if(hold1%13>hold2%13)
		return 28;
		else if(hold2%13>hold1%13)
		return 68;
		else
		return 417; // hatali durum hata kodu. ulasilmamasi gerekir.
	}
	else if(eqPwr==165) // straight esitligi
	{
		if(hand1[4]%13>hand2[4]%13)	//son kartlar
		return 29;
		else if (hand2[4]%13>hand1[4]%13)
		return 69;
		else // esitse
		{
			if(hand2[4]/13>hand1[4]/13)
			return 30;
			else if(hand1[4]/13>hand2[4]/13)
			return 70;
			else 
			return 418; //hatali durum hata kodu. ulasilmamasi gerekir.
		}
	}
	else if(eqPwr==185)
	{
		if(hand1[4]%13>hand2[4]%13)	//son kartlar kontrol, flush.
		return 31;
		else if (hand2[4]%13>hand1[4]%13)
		return 71;
		else if (hand1[4]%13==hand2[4]%13)
		{
			if(hand2[4]/13>hand1[4]/13)
			return 32;
			else if(hand1[4]/13>hand2[4]/13)
			return 72;
			else 
			return 419; //hatali durum hata kodu. ulasilmamasi gerekir.
		}
	}
	else if(eqPwr==200) //full house esitligi 3 lu kartlardan biri her zaman ortadadir.
	{
		if(hand1[2]%13>hand2[2]%13)
		return 33;
		else if(hand2[2]%13>hand1[2]%13)
		return 73;
		else
		return 420;//hatali durum hata kodu. ulasilmamasi gerekir.
	}
	else if(eqPwr==300) // four of a kind esitligi
	{
		if(hold1%13>hold2%13)
		return 34;
		else if(hold2%13>hold1%13)
		return 74;
		else 
		return 421;  //hatali durum hata kodu. ulasilmamasi gerekir.
	}
	else if(eqPwr==500) //straight flush
	{
		if(hand1[4]%13>hand2[4]%13)	//son kartlar
		return 35;
		else if (hand2[4]%13>hand1[4]%13)
		return 75;
		else if (hand1[4]%13==hand2[4]%13)
		{
			if(hand2[4]/13>hand1[4]/13)
			return 36;
			else if(hand1[4]/13>hand2[4]/13)
			return 76;
			else 
			return 422; //hatali durum hata kodu. ulasilmamasi gerekir.
		}
	}
	else if(eqPwr==1000)	// royal flush
	{
		if(hand2[4]/13>hand1[4]/13)
		return 37;
		else if(hand1[4]/13>hand2[4]/13)
		return 77;
		else 
		return 423; //hatali durum hata kodu. ulasilmamasi gerekir.
	}
	else
	return 424; //hatali durum hata kodu. ulasilmamasi gerekir.
	
} //fonksiyon sonu

void elDurumuYazdir(const int el[])
{
	int x;
	x = pwrOfHand(el);
	if(x<13)
	printf("(High Card)");
	else if(x==50)
	printf("(One pair)");
	else if(x==100)
	printf("(Two pair)");
	else if(x==150)
	printf("(Three of a Kind)");
	else if(x==165)
	printf("(Straight)");
	else if(x==185)
	printf("(Flush)");
	else if(x==200)
	printf("(Full House)");
	else if(x==300)
	printf("(Four of a Kind)");
	else if(x==500)
	printf("(Straight Flush)");
	else if(x==1000)
	printf("(Royal Straight Flush)");
	else
	printf("Bir hata olustu. Hata Kodu : 425"); 
}

void sonucYaz(int s)
{
	switch(s)
	{
		case 10:
			printf("Bilgisayar, \"Yuksek Kart\" ile kazandi.");
			break;
		case 11:
			printf("Bilgisayar, \"One Pair\" ile kazandi.");
			break;
		case 12:
			printf("Bilgisayar, \"Two Pair\" ile kazandi.");
			break;
		case 13:
			printf("Bilgisayar, \"Three of a Kind\" ile kazandi.");
			break;
		case 14:
			printf("Bilgisayar, \"Straight\" ile kazandi.");
			break;
		case 15:
			printf("Bilgisayar, \"Flush\" ile kazandi.");
			break;
		case 16:
			printf("Bilgisayar, \"Full House\" ile kazandi.");
			break;
		case 17:
			printf("Bilgisayar, \"Four of a Kind\" ile kazandi.");
			break;
		case 18:
			printf("Bilgisayar, \"Straight Flush\" ile kazandi.");
			break;
		case 19:
			printf("Bilgisayar, \"Royal Straight Flush\" ile kazandi.");
			break;
		case 50:
			printf("Tebrikler, \"Yuksek Kart\" ile kazandiniz.");
			break;
		case 51:
			printf("Tebrikler, \"One Pair\" ile kazandiniz.");
			break;
		case 52:
			printf("Tebrikler, \"Two Pair\" ile kazandiniz.");
			break;
		case 53:
			printf("Tebrikler, \"Three of a Kind\" ile kazandiniz.");
			break;
		case 54:
			printf("Tebrikler, \"Straight\" ile kazandiniz.");
			break;
		case 55:
			printf("Tebrikler, \"Flush\" ile kazandiniz.");
			break;
		case 56:
			printf("Tebrikler, \"Full House\" ile kazandiniz.");
			break;
		case 57:
			printf("Tebrikler, \"Four of a Kind\" ile kazandiniz.");
			break;
		case 58:
			printf("Tebrikler, \"Straight Flush\" ile kazandiniz.");
			break;
		case 59:
			printf("Tebrikler, \"Royal Straight Flush\" ile kazandiniz.");
			break;
		case 20:
			printf("Bilgisayar, \"Yuksek Kart\" (Renk ustunlugu) ile kazandi.");
			break;
		case 21:
			printf("Bilgisayar, \"One Pair\" (Yuksek pair) ile kazandi.");
			break;
		case 22:
			printf("Bilgisayar, \"One Pair\" (Yuksek kart) ile kazandi.");
			break;
		case 23:
			printf("Bilgisayar, \"One Pair\" (Renk ustunlugu) ile kazandi.");
			break;
		case 24:
			printf("Bilgisayar, \"Two Pair\" (Buyuk pair ustunlugu) ile kazandi.");
			break;
		case 25:
			printf("Bilgisayar, \"Two Pair\" (Kucuk pair ustunlugu) ile kazandi.");
			break;
		case 26:
			printf("Bilgisayar, \"Two Pair\" (5. kart ustunlugu) ile kazandi.");
			break;
		case 27:
			printf("Bilgisayar, \"Two Pair\" (5. kart renk ustunlugu) ile kazandi.");
			break;
		case 28:
			printf("Bilgisayar, \"Three of a Kind\" (Yuksek 3'lu) ile kazandi.");
			break;
		case 60:
			printf("Tebrikler, \"Yuksek Kart\" (Renk ustunlugu) ile kazandiniz.");
			break;
		case 61:
			printf("Tebrikler, \"One Pair\" (Yuksek pair) ile kazandiniz.");
			break;
		case 62:
			printf("Tebrikler, \"One Pair\" (Yuksek kart) ile kazandiniz.");
			break;
		case 63:
			printf("Tebrikler, \"One Pair\" (Renk ustunlugu) ile kazandiniz.");
			break;
		case 64:
			printf("Tebrikler, \"Two Pair\" (Buyuk pair ustunlugu) ile kazandiniz.");
			break;
		case 65:
			printf("Tebrikler, \"Two Pair\" (Kucuk pair ustunlugu) ile kazandiniz.");
			break;
		case 66:
			printf("Tebrikler, \"Two Pair\" (5. kart ustunlugu) ile kazandiniz.");
			break;
		case 67:
			printf("Tebrikler, \"Two Pair\" (5. kart renk ustunlugu) ile kazandiniz.");
			break;
		case 68:
			printf("Tebrikler, \"Three of a Kind\" (Yuksek 3'lu) ile kazandiniz.");
			break;
		case 29:
			printf("Bilgisayar, \"Straight\" (Yuksek straight) ile kazandi.");
			break;
		case 69:
			printf("Tebrikler, \"Straight\" (Yuksek straight) ile kazandiniz.");
			break;
		case 30:
			printf("Bilgisayar, \"Straight\" (Renk ustunlugu) ile kazandi.");
			break;
		case 70:
			printf("Tebrikler, \"Straight\" (Renk ustunlugu) ile kazandiniz.");
			break;
		case 31:
			printf("Bilgisayar, \"Flush\" (Yuksek kart) ile kazandi.");
			break;
		case 71:
			printf("Tebrikler, \"Flush\" (Yuksek kart) ile kazandiniz.");
			break;
		case 32:
			printf("Bilgisayar, \"Flush\" (Renk ustunlugu) ile kazandi.");
			break;
		case 72:
			printf("Tebrikler, \"Flush\" (Renk ustunlugu) ile kazandiniz.");
			break;
		case 33:
			printf("Bilgisayar, \"Full House\" (Yuksek 3'lu) ile kazandi.");
			break;
		case 73:
			printf("Tebrikler, \"Full House\" (Yuksek 3'lu) ile kazandiniz.");
			break;
		case 34:
			printf("Bilgisayar, \"Four of a Kind\" (Yuksek 4'lu) ile kazandi.");
			break;
		case 74:
			printf("Tebrikler, \"Four of a Kind\" (Yuksek 4'lu) ile kazandiniz.");
			break;
		case 35:
			printf("Bilgisayar, \"Straight Flush\" (Yuksek straight) ile kazandi.");
			break;
		case 36:
			printf("Bilgisayar, \"Straight Flush\" (Yuksek renk) ile kazandi.");
			break;
		case 75:
			printf("Tebrikler, \"Straight Flush\" (Yuksek straight) ile kazandiniz.");
			break;
		case 76:
			printf("Tebrikler, \"Straight Flush\" (Yuksek renk) ile kazandiniz.");
			break;
		case 37:
			printf("Bilgisayar, \"Royal Straight Flush\" (Yuksek renk) ile kazandi.");
			break;
		case 77:
			printf("Tebrikler, \"Royal Straight Flush\" (Yuksek renk) ile kazandiniz.");
			break;
		
		default:
			printf("Bir hata olustu! Hata Kodu : %d",s);
			break;
			
	}
}

void kapaliDagit(void)
{
	int i,j,k;
	printf("\n         	");									// sol margin her satir basi + 1 vertical + 9 bosluk +1 vertical
	for(i=0;i<5;i++)												// her kartin ust kismi
	{
	printf("\311"); //solustkose
	for(j=1;j<10;j++)
	printf("\315"); // ===
	printf("\273"); //sagustkose
	printf(" 	"); //kart arasi bosluk
	}
	
	//orta kisim
	for(k=0;k<7;k++)
	{
		printf("\n         	");
		for(i=0;i<5;i++)
		{
			printf("\272"); //vert ||
			
			for(j=0;j<9;j++)
			printf("\260");
			
			printf("\272"); //vert ||
			printf(" 	"); //kartarasibosluk
		}
	}
		printf("\n         	");
	for(i=0;i<5;i++)													// her kartin alt kismi
	{
	printf("\310"); //solaltkose
	for(j=1;j<10;j++)
	printf("\315"); // ===
	printf("\274"); //sagaltkose
	printf(" 	"); //kartarasibosluk
	}
	
}

void girisYazdir(void)
{
	int i,j;

	printf("\n   \311"); //sol ust kose karakteri

	for(i=1;i<113;i++)  // yatay cizgiler (ust kenar)  
	{printf("\315");}

	printf("\273");  //sag ust kose karakteri

	for(i=1;i<4;i++) //satirlar = 3 satir					112 46 20 46 		43 - 19 - 50
	{
		printf("\n   \272"); //her satir basi boslugu ve dikey cizgi (sol kenar)
		for(j=1;j<113;j++)  // her satir icin kenardan kenara karakterler
		{
			if(i==1)     //1.satir ise (260) karakteri= low noktalar
			{printf("\260");
			}
			else if(i==2)  //2. satir ise 43 defa medium noktalar (261) -- sonra ismim -- sonra medium noktalar 
				{
				if(j<=46)
				printf("\261");
				else if(j==47)
				{
					printf("%20s","  KONSOL POKER v.1  "); // \200 = 'Ç' karakteri
					j=66;
				}
				else if(j>=67)
				printf("\261");
				}
		
			else if(i==3)    // 3. satir heavy noktalar (262)
			{printf("\262");}
			
		}
	printf("\272"); // satir sonu ve dikey cizgi (sag kenar)
	}

	printf("\n   "); // soldan birakilan bosluk

	printf("\310");  // sol alt kose karakteri

	for(i=1;i<113;i++) // yatay cizgiler (alt kenar)
	printf("\315");		

	printf("\274");		// sag alt kose karakteri
	printf("\n");
	printf("%117s","by Yildirim Bayrakci.");
	printf("\n"); 
	yazdirRules();
}

void swap(int hand[],int whichCard,const int deck[][13])
{
	static int nextCard = 0;
	hand[whichCard-1] = deck[1][nextCard];
	nextCard++;
	if(nextCard==6)
	nextCard=0;
}

void yazdirRules(void)
{
	printf(" # OYUN KURALLARI\n");
	printf(" 5 er kagit dagitilir. Oyuncular ellerinin durumuna gore; bahisi artirabilir veya pas gecebilirler ve ellerindeki \n\
 kartlardan en fazla 3'unu degistirebilirler. Oyun sonunda eller acilir ve kazanan duruma gore belirlenir. Oyuna \n\
 100000\44 ile baslanir. Maksimum 100000\44 borc alinabilir. Paraniz -100000\44 altina duserse oyun kaybedilmis olur. \n\
 Kart buyuklukleri sirasi ile: A, K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, 2'dir.\n\
 Kart renkleri deger sirasi ile: KUPA, KARO, MA\200A, S\230NEK'tir.\n");
	printf("\n DURUMLAR\n");
	printf(" Royal Straight Flush : A-K-Q-J-10 sirasinda ve ayni renk ise.\n\
 Straight Flush       : Sirali ve ayni renk ancak A(Royal) yok.\n\
 Four of a Kind       : 4 kartin ayni olmasi\n\
 Full House           : Bir 3'lu ve bir 2'li olmasi.\n\
 Flush                : 5 kartin da ayni renk olmasi\n\
 Straight             : Kartlarin rengi farketmeksizin sirali olmasi\n\
 Three of a Kind      : 3 kartin ayni olmasi.\n\
 Two Pair             : 2 adet 2'linin bulunmasi\n\
 One Pair             : 1 adet 2'li olmasi.\n\
 High Card            : Hicbir durum soz konusu olmadiginda, en yuksek kart.");
}




int swapOfComputer(int handPc[],const int deste[][13])
{
	int power, holdMatch=0;
	int i;
	pairCheck(handPc,&holdMatch);
	
	power = pwrOfHand(handPc);
	if(power<13)	//High Card ise ilk ilk 3 karti swaplasin
	{
		swap(handPc,1,deste);
		swap(handPc,2,deste);
		swap(handPc,3,deste);
		return 3;
	}
	
	else if(power==50)	//One Pair ise pair olmayan 3 karti swaplasin
	{
		for(i=1;i<6;i++)
		{
			if(holdMatch%13!=handPc[i-1]%13)
			swap(handPc,i,deste);
		}
		return 3;
	}
	
	else if(power==100)	//Two Pair ise pair olmayan tek karti swaplasin.
	{
		if(handPc[4]%13!=handPc[3]%13)        //el1 5.kart sonda ise swapla
		swap(handPc,5,deste);
		else if(handPc[0]%13!=handPc[1]%13)  //basta ise swapla
		swap(handPc,1,deste);
		else											// ortada ise swapla
		swap(handPc,3,deste);
		return 1;	
	}
	
	else if(power==150)	//Three of a Kind ise eslesmeyen 2 karti swapla
	{
		for(i=1;i<6;i++)
		{
			if(holdMatch%13!=handPc[i-1]%13)
			swap(handPc,i,deste);
		}
		return 2;
	}
	else	// Bilgisayar eli straight ve yuksegi ise kart istemeyecek.
	return 0;
	
}


void clearBuffer(void){
	int ch;
	while((ch = getchar()) != '\n' && ch != EOF)
	;
}








