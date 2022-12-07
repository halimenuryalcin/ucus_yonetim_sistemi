#include <stdio.h>
struct node {
	int oncelik;
	int ucakno;
	int inis_saat;
	int ertelenme;
	int kalkis_saat;
};
int front=-1,rear=0,adet=0,tekrar=24;
struct node ucak[28],inis[24],kalkis[24],temp,sil;
void kayit_sil(struct node sil,int yer);
void kontrol(struct node temp,int say);
//DOSYADAN VERİLERİ ALMA
void dosyayi_aktar()
{
  FILE *input=fopen("input.txt","r");
  if(input==NULL)
  {
    printf("dosya acilamadi\n");
  }
  else
  
  {
    while(rear<28)
    {
        if(rear==0)
        {
          front=0;rear=0;
          fscanf(input,"%d %d %d",&ucak[rear].oncelik,&ucak[rear].ucakno,&ucak[rear].inis_saat);
          ucak[rear].ertelenme=0;
          rear++;
        }
        else
        {
          fscanf(input,"%d %d %d",&ucak[rear].oncelik,&ucak[rear].ucakno,&ucak[rear].inis_saat);
          ucak[rear].ertelenme=0;
          rear++;
        }
    }
  }
  fclose(input);
}
//KONTROL FONKSİYON ÇAĞIRMA
void inis_cagir()
{
	int say=0;
	for(;say<28;say++)
	   kontrol(ucak[say],say);
}
//SAAT ERTELENME MKITARLARI KONTROLU
void kontrol(struct node temp,int say)
{
	int gez=0;
	if(gez>=24)
	printf("kapasite dolmustur.");
	for(;gez<24;gez++)
	{
		if((temp.ucakno != inis[gez].ucakno) )
		{	if(inis[gez].ertelenme<4)
			{
				if(temp.inis_saat==inis[gez].inis_saat)
				{
				if(temp.oncelik==inis[gez].oncelik)
				{
					if(temp.ucakno<inis[gez].ucakno)
					{
						inis[gez].ertelenme++;
						inis[gez].inis_saat++;
						inis[say]=temp;
						kontrol(inis[gez],gez);
					}
					else
					{
						temp.ertelenme++;
						temp.inis_saat++;
						inis[say]=temp;
            kontrol(inis[say],say);
					}
				}
				
				else if(temp.oncelik<inis[gez].oncelik)
				{
						inis[gez].ertelenme++;
						inis[gez].inis_saat++;
						inis[say]=temp;
						kontrol(inis[gez],gez);
				}
				else
				{
						temp.ertelenme++;
						temp.inis_saat++;
						inis[say]=temp;
						kontrol(inis[say],say);
				}
			}
			else
			inis[say]=temp;
			adet++;
			}
			else 
			kayit_sil(inis[gez],gez);
			
		}
	
	}

}
void kalkis_ayarla()
{
  int i=0;
  FILE *kalkis=fopen("output.txt","w");
  
  for(;i<24;i++)
  {
    inis[i].kalkis_saat=inis[i].inis_saat+inis[i].ertelenme+1;
    fprintf(kalkis,"ucak no: %d    inis saat: %d        gecikme suresi: %d         kalkis saat: %d \n",inis[i].ucakno,inis[i].inis_saat,inis[i].ertelenme,inis[i].kalkis_saat);
  }
  fclose(kalkis);
}
//SİLME İŞLEMİ
void kayit_sil(struct node sil,int yer)
{
	printf("%d nolu ucak sabiha hava limanina gonderildi.\n",sil.ucakno);
	for(;yer<23;yer++)
	{
		inis[yer]=inis[yer+1];
	}
	inis[23]=ucak[tekrar];
  
  
	tekrar++;
}

//YAZDIR
void yazdir()
{ 
	for(;front<24;front++)
  {
    printf("ucak no:%d    inis saat: %d        gecikme suresi: %d         kalkis saat: %d \n",inis[front].ucakno,inis[front].inis_saat,inis[front].ertelenme,inis[front].kalkis_saat);
  }	
}

int main()
{
	dosyayi_aktar();
	inis_cagir();
  kalkis_ayarla();
	yazdir();
}
