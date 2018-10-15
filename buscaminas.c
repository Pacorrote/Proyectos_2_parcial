#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matriz matriz;
struct matriz{
    int oculto;
    int dato;
    int visitado;
};

int inicializar(matriz minas[10][10],int a,int b){
    int ac=0;
    for(int i=0;i<10;i++){
        minas[rand()%11][rand()%11].dato=207;
    }
    for (int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            if(minas[i][j].dato!=207){
                minas[i][j].dato=48;
            }else{
                ac++;
            }
        }
    }
    for (int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            minas[i][j].oculto=35;
            minas[i][j].visitado=0;
        }
    }
    return ac;
}

void imprimirmatriz1(matriz mapp[10][10],int i,int j){
    for (int a=0;a<i;a++){
        printf("%d  ",a+1);
        for(int b=0;b<j;b++){
            printf("%c ",mapp[a][b].oculto);
        }
        printf("\n\n");
    }
}

void imprimirmatriz2(matriz mapp[10][10],int i,int j){
    for (int a=0;a<i;a++){
        for(int b=0;b<j;b++){
            printf("%c ",mapp[a][b].dato);
        }
        printf("\n");
    }
}

void abrircelda(matriz m[10][10],int i, int j){
    if(((i>=0)&&(i<10))&&((j>=0)&&(j<10))){
        if(m[i][j].visitado==0){
            m[i][j].visitado=1;
            if(m[i][j].dato==48){
                for(int k=i-1;k<=i+1;k++){
                    for(int l=j-1;l<=j+1;l++){
                        m[i][j].oculto=m[i][j].dato;
                        abrircelda(m,k,l);
                    }
                }
            }
            else if((m[i][j].dato>48)&&(m[i][j].dato<58)){
                m[i][j].oculto=m[i][j].dato;
            }
        }
    }
}

void ponernumeros(matriz m[10][10],int i, int j){
    for (int a=0;a<i;a++){
        for(int b=0;b<j;b++){
            if((m[a][b].dato==207)&&(m[a][b].visitado==0)){
                m[a][b].visitado=1;
                for(int k=a-1;k<=a+1;k++){
                    for(int l=b-1;l<=b+1;l++){
                        if(((k>=0)&&(k<i))&&((l>=0)&&(l<j))){
                            if((m[k][l].dato==207)&&(m[k][l].visitado==0)){
                                ponernumeros(m,k,l);
                            }
                            else if(m[k][l].dato!=207){
                                m[k][l].dato+=1;
                            }
                        }
                    }
                }
            }
        }
    }
}


int buscamina(matriz m[10][10],int i, int j){
    if(m[i][j].dato==207){
        return 1;
    }
    else{
        abrircelda(m,i,j);
        return 0;
    }
}

int main(int argc, char *argv[]) {
    int a1,b1,r,ac,ac1=0;
    matriz minas[10][10];
    ac=inicializar(minas,10,10);
    ponernumeros(minas,10,10);
    printf("\t1 2 3 4 5 6 7 8 9 10\n\n");
    imprimirmatriz1(minas,10,10);
    do{
        do{
            printf("Ingrese sus coordenadas separadas por una coma\n");
            scanf("%d,%d",&a1,&b1);
        }while(((a1>10)&&(b1<10))&&((a1>1)&&(b1<1)));
        system("cls");
        r=buscamina(minas,a1+1,b1+1);
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(minas[i][j].oculto==35){
                    ac1++;
                }
            }
        }
        printf("\t1 2 3 4 5 6 7 8 9 10\n\n");
        imprimirmatriz1(minas,10,10);
    }while((r!=1)&&(ac!=ac1));
    if(r==1){
        printf("¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ YA PERDISTE !!!!!!!!!!!!!!!!!!!!!!!!!\n");
    }
    imprimirmatriz2(minas,10,10);
    return 0;
}
