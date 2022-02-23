#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

int factorial (int sayi)                     
{
    int factorial=1;
    if (sayi == 1 || sayi == 0)
            return 1;
    else{
        for(int i=2; i<=sayi; i++){
            factorial = factorial*i;
        }
    }
    return factorial;
}

int combination (int n, int r){                  

    int result = factorial(n)/(factorial(n-r)*factorial(r));
    return result;
}

int main(){
    int gd=DETECT, gm;           // DETECT automatically selects the graphics driver
    initgraph(&gd,&gm,NULL);   // Starts the graphic display.
    setbkcolor(WHITE);    // Chooses graphic color
    cleardevice();         // Paints the screen to the selected color
    setcolor(GREEN);        // Makes the color of the coordinate lines green
    line(25,220,625,220);   // x axis line
    line(325,460,325,5);    // y axis line

    for(int i=335; i<=625; i=i+10){     //  interval values of coordinate lines
        circle(i,220,1);                
    }
    for(int i=315; i>=25; i=i-10){
        circle(i,220,1);             
    }
    for(int i=230; i<=460; i=i+10){
        circle(325,i,1);
    }
    for(int i=210; i>=5; i=i-10){
        circle(325,i,1);
    }
    
    int num;
    printf("how many points will you enter = ");
    scanf("%d",&num);              
    num=num*2;                                  
    FILE *dosya;
    dosya=fopen("CoordinantPoint.txt","r");        
    int N[num];                            
    if(dosya!=NULL){            
        for(int i=0;i<num;i++){
            fscanf(dosya,"%d",&N[i]);   // It assigns txt values to the array we opened
        }
    }else {
        printf("File not found.");
    }
    fclose(dosya);            // File close

    for(int i=0;i<num;i=i+2){           // adapt values from file to coordinate system values
        if(N[i]>=0){                 
            N[i]=325+N[i]*10;         
        }else{
            N[i]=325+(N[i]*10);
        }
    }
    for(int i=1;i<=num;i=i+2){            
        if(N[i]>=0){
            N[i]=220-(N[i]*10);
        }else{
            N[i]=220-(N[i]*10);
        }
    }

    setcolor(RED);
    for(int i=0;i<num;i=i+2){         // shows the points taken from the file in coordinates
        circle(N[i],N[i+1],2);
    }
    
    int rr;
    int rx;
    int ry;
    int k=0;
    for(int i=0;i<num-1;i=i+2){                                 
        for(int j=i+2;j<num;j=j+2){                                  
            rr=(sqrt(pow((N[i]-N[j]),2)+pow((N[i+1]-N[j+1]),2)))/2;
            if(rr>k){
                k=rr;
                rx=(N[i]+N[j])/2;
                ry=(N[i+1]+N[j+1])/2;
            }
        }
    }

    for(int i=0;i<num-1;i=i+2){                                
        if(sqrt(pow((N[i]-rx),2)+pow((N[i+1]-ry),2))>=k){         
            k=sqrt(pow((N[i]-rx),2)+pow((N[i+1]-ry),2));
        }
    }
    setcolor(RED);
    circle(rx,ry,k);            // Draw Circle

    //  splits over the circle, pressing the center points
    setcolor(BLACK);
    circle(rx,ry,1);           // center point of the circle
    int x=(rx-325)/10;
    int y=-(ry-220)/10;
    int r=k/10;
    char sayi[3];
    settextstyle(2,0,5);         // x,y,k values
    sprintf(sayi,"%d",x);       
    outtextxy(rx-15,ry-15,"(");  
    outtextxy(rx-12,ry-15,sayi);  
    sprintf(sayi,"%d",y);
    outtextxy(rx,ry-15,",");
    outtextxy(rx+2,ry-15,sayi);
    outtextxy(rx+14,ry-15,")");
    //outtextxy(20,35,"yaricap: ");
    line(rx,ry,rx-k,ry);          
    sprintf(sayi,"%d",r);
    outtextxy((rx+rx-k)/2,ry-10,sayi);    

    printf("\nDairenin merkez noktasi: %d,%d",x,y);  // Displays the radius and center points as output.
    printf("\nCemberin yaricapi: %d\n",r);

    int tmp,tmp2;
    for(int i=0; i< (num/2)-1; i++){
        for(int j=0; j<s-2; j=j+2){         
            if(N[j]>N[j+2]){                // useful for drawing splines
                tmp    =  N[j];
                N[j]  =  N[j+2];
                N[j+2]=  tmp;
                tmp2   =  N[j+1];
                N[j+1]=  N[j+3];
                N[j+3]=  tmp2;
            }
        }
    }
    
    int c = s/2-1;
    for(float i=0; i<=1; i+=0.001){                 
        int a=0,b=0,p=0;
        for(int j=0; j<=c; j++){                         
            a += kom(c,j)* pow(i,j)* pow(1-i,c-j) *N[2*p];
            b += kom(c,j)* pow(i,j)* pow(1-i,c-j)* N[2*p+1];
            p++;
        }
        putpixel(a,b,YELLOW);      
    }

    getch();         // Kullanıcı etkileşimi
    closegraph();   // grafik ekranini kapar
    
    return 0;
}
