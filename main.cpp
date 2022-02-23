
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>



int fak (int sayi)                     // Faktoriyel hesaplar
{
    int fac=1;
    if (sayi == 1 || sayi == 0)
            return 1;
    else{
        for(int i=2; i<=sayi; i++){
            fac = fac*i;
        }
    }
    return fac;
}


int kom (int n, int r){                       // Kombinasyon hesaplar

    int sonuc = fak(n)/(fak(n-r)*fak(r));
    return sonuc;
}

int main(){

    int gd=DETECT, gm;           // DETECT grafik sürücüsünü otomatik secer
    initgraph(&gd,&gm,NULL);   // grafik ekrani baslatir.

//------------------------------------------------------------------------------------------------------------------------------

    setbkcolor(WHITE);    // renk secer
    cleardevice();         // ekrana secilen renge boyar.

//-----------------------------------------------------------------------------------------------------------------------------

    setcolor(GREEN);        // koordinat cizgilerinin rengini yesil yapar
    line(25,220,625,220);   // x eksen cizgisi
    line(325,460,325,5);    // y eksen  ''

    for(int i=335; i<=625; i=i+10){     //  koordinat cizgilerinin aralik degerleri
        circle(i,220,1);                 // nokta olarak basar ----- circle (x,y,r)  r->yaricap
    }
    for(int i=315; i>=25; i=i-10){
        circle(i,220,1);                // her 10 uzunluk 1 uzunluk degerinde
    }
    for(int i=230; i<=460; i=i+10){
        circle(325,i,1);
    }
    for(int i=210; i>=5; i=i-10){
        circle(325,i,1);
    }

//------------------------------------------------------------------------------------------------------------------------------

    int s;
    printf("kac nokta gireceksin = ");
    scanf("%d",&s);                            // txt kac adet nokta girildigini yazar
    s=s*2;                                     // x ve y eksen oldugundan *2
    FILE *dosya;
    dosya=fopen("Koordinatnokta.txt","r");          // dosyayi okur
    int N[s];                                // txt girilen degerlerin atanacagi dizi
    if(dosya!=NULL){                  // dosya acilmis mi kontrol eder
        for(int i=0;i<s;i++){
            fscanf(dosya,"%d",&N[i]);   // actigimiz diziye txt degerlerini atar
        }
    }else {
        printf("dosya bulunamdi.");
    }
    fclose(dosya);            //  dosyayi kapar

// -----------------------------------------------------------------------------------------------------------------------------

    for(int i=0;i<s;i=i+2){           // dosyadan alinan degerleri koordinat sis. degerlerine uyarla
        if(N[i]>=0){                       // x ekseni noktalari
            N[i]=325+N[i]*10;          // txt den alinan noktanin ekrandaki konumuna uyarlanmasi
        }else{
            N[i]=325+(N[i]*10);
        }
    }
    for(int i=1;i<=s;i=i+2){             // y eksen noktalari
        if(N[i]>=0){
            N[i]=220-(N[i]*10);
        }else{
            N[i]=220-(N[i]*10);
        }
    }

    setcolor(RED);
    for(int i=0;i<s;i=i+2){         // dosyadan alinan noktalari korrdinatta gösterir
        circle(N[i],N[i+1],2);
    }

//----------------------------------------------------------------------------------------------------------------------------

    int rr;
    int rx;
    int ry;
    int k=0;
    for(int i=0;i<s-1;i=i+2){                                      // noktalar arasi en uzak olan iki noktayi cap kabul
        for(int j=i+2;j<s;j=j+2){                                  // ettik daireyi cizdirdik
            rr=(sqrt(pow((N[i]-N[j]),2)+pow((N[i+1]-N[j+1]),2)))/2;
            if(rr>k){
                k=rr;
                rx=(N[i]+N[j])/2;
                ry=(N[i+1]+N[j+1])/2;
            }
        }
    }

    for(int i=0;i<s-1;i=i+2){                                  // dairenin disinda nokta bulunursa; merkezi noktalarin
        if(sqrt(pow((N[i]-rx),2)+pow((N[i+1]-ry),2))>=k){          // daire yaricapini büyütürüz
            k=sqrt(pow((N[i]-rx),2)+pow((N[i+1]-ry),2));
        }
    }
    setcolor(RED);
    circle(rx,ry,k);            // en son olusan daireyi cizer


//-----------------------------------------------------------------------------------------------------------------------------

    //  cemberin üzerine yaricap,merkez noktalari basar
    setcolor(BLACK);
    circle(rx,ry,1);           // cemberin merkez noktasi
    int x=(rx-325)/10;
    int y=-(ry-220)/10;
    int r=k/10;
    char sayi[3];
    settextstyle(2,0,5);         // x,y,k degerlerini
    sprintf(sayi,"%d",x);        // sayi dizisine , rx koordinat noktasini atariz
    outtextxy(rx-15,ry-15,"(");    // outtextxy(x,y,string)
    outtextxy(rx-12,ry-15,sayi);   // outtextxy(x,y,int) ise char dizi olusturur diziye atanmis sayi kullanilir
    sprintf(sayi,"%d",y);
    outtextxy(rx,ry-15,",");
    outtextxy(rx+2,ry-15,sayi);
    outtextxy(rx+14,ry-15,")");
    //outtextxy(20,35,"yaricap: ");
    line(rx,ry,rx-k,ry);              // yaricap cizer
    sprintf(sayi,"%d",r);
    outtextxy((rx+rx-k)/2,ry-10,sayi);      // yaricap cizgisinin uzerine yaricap uzunlugunu basar


    printf("\nDairenin merkez noktasi: %d,%d",x,y);  // Yaricap ve merkez noktalari cikti olarak gösterir.
    printf("\nCemberin yaricapi: %d\n",r);

//------------------------------------------------------------------------------------------------------------------------------

    int tmp,tmp2;
    for(int i=0; i< (s/2)-1; i++){
        for(int j=0; j<s-2; j=j+2){          // txt den alinan x degerlerini siralar
            if(N[j]>N[j+2]){                // splne cizmeye yarar
                tmp    =  N[j];
                N[j]  =  N[j+2];
                N[j+2]=  tmp;
                tmp2   =  N[j+1];
                N[j+1]=  N[j+3];
                N[j+3]=  tmp2;
            }
        }
    }

// -----------------------------------------------------------------------------------------------------------------------------
    int c = s/2-1;

    for(float i=0; i<=1; i+=0.001){                    //  bezier egrisini cizer
        int a=0,b=0,p=0;
        for(int j=0; j<=c; j++){                           // c degeri toplam nokta sayisini gosterir
            a += kom(c,j)* pow(i,j)* pow(1-i,c-j) *N[2*p];
            b += kom(c,j)* pow(i,j)* pow(1-i,c-j)* N[2*p+1];
            p++;
        }
        putpixel(a,b,YELLOW);          // egri boyunca nokta basarak egriyi olusturur.
    }

// -----------------------------------------------------------------------------------------------------------------------------

    getch();         // Kullanýcý etkileþimi
    closegraph();   // grafik ekranini kapar


    return 0;
}





