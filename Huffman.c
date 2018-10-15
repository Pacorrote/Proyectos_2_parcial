//
//  main.c
//  Proyecto Huffman
//
//  Created by Usuario on 03/10/18.
//  Copyright © 2018 Usuario. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct Arbol Arbol;
typedef struct Nodo Nodo;
struct Arbol{
    int letra,fr;
    struct Arbol*izq;
    struct Arbol*der;
};

struct Nodo{
    Arbol*raiz;
    struct Nodo*siguiente;
    struct Nodo*anterior;
};

void algoritmoHoffman();
void insertarOrden(Arbol*dato);
Arbol*desencolar();
void insertarCola(int dato);
int buscarASCII(int dato);
Arbol*nuevoArbol(int dato,int n);
Nodo*nuevoNodo(Arbol*dato);
void ordenar();
void inorden(FILE*hola,Arbol*r,int n);
int colaVacia();
void lineas(FILE*Leer,int num);
void comprimir(char*binario);
int binAdecimal(int bin);

Nodo*inicio=NULL;
Nodo*final=NULL;
int N=0,f=0;
char cad[100];

int main(int argc, char *argv[]){
    int len,i,j;
     FILE*frase1 = fopen("Frase.txt", "r");
    if(frase1==NULL){
        printf("Error en el archivo\n");
        return 0;
    }
    while(!feof(frase1)){
        printf("El contenido de este mensaje es: \n\n");
        printf(getc(frase1));
    }
    char codigo[100],*binario=NULL,aux[100];
    FILE*frase = fopen("Frase.txt","rb");
    FILE*frase1 = fopen("Frase.txt", "r");
    if(frase==NULL){
        printf("Error en el archivo\n");
        return 0;
    }
    while(!feof(frase)){
        char caracter=fgetc(frase);
        if(caracter==-1)
            break;
        insertarCola(caracter);
    }
    fclose(frase);
    ordenar();
    algoritmoHoffman();
    FILE*hola=fopen("Decode.txt","wb");
    inorden(hola,inicio->raiz,7);
    fclose(hola);
    FILE*Leer = fopen("Decode.txt","rb");
    FILE*Palabra = fopen("Frase.txt","rb");
    if(Leer==NULL || Palabra==NULL){
        printf("Error en el archivo\n");
        return 0;
    }
    while(!feof(Palabra)){
        char caracter=fgetc(Palabra);
        if(caracter==-1)
            break;
        for(i=0;i<N;i++){
            lineas(Leer,i+1);
            char c=fgetc(Leer);
            if(caracter==c){
                fseek(Leer,2, SEEK_CUR);
                fscanf(Leer," %s",&codigo);
                len=strlen(codigo);
                if(binario==NULL){
                    binario=malloc((len+1)*sizeof(char));
                    for(j=0;j<(len+1);j++){
                        binario[j]=0;
                    }
                }else{
                    binario=realloc(binario,(strlen(binario)+len+1)*sizeof(char));
                }
                strcat(binario,codigo);
                goto cont;
            }
        }
    cont:
        rewind(Leer);
    }
    fclose(Palabra);
    fclose(Leer);
    comprimir(binario);
}

void comprimir(char*binario){
    FILE*ASCII=fopen("Decode.txt","ab");
    int len=strlen(binario);
    printf("\n%i Bits\n",len);
    printf("Codigo Binario: ");
    puts(binario);
    int bytes=len/8,sb=len%8,num,aux,j,i;
    char byte[8],sll[7];
    printf("Frase Encriptado: ");
    for(i=1;i<=bytes+1;i++){
        aux=0;
        if(i<bytes+1){
            for(j=8*(i-1);j<8*i;j++){
                byte[aux]=binario[j];
                aux++;
            }
            num=binAdecimal(atoi(byte));
            printf("%c",num);
            fprintf(ASCII,"%c",num);
        }else if(sb!=0){
            for(j=8*(i-1);j<(8*(i-1))+sb;j++){
                sll[aux]=binario[j];
                aux++;
            }
            num=binAdecimal(atoi(sll));
            printf("%c",num);
            fprintf(ASCII,"%c",num);
        }
    }
    printf("\n");
    fclose(ASCII);
}

int binAdecimal(int bin){
    int c=1,d=0,p;
    while(bin>0)
    {
        p=0;
        p=c*(bin%10);
        d+=p;
        c*=2;
        bin/=10;
    }
    return d;
}

void algoritmoHoffman(){
    int n;
    if(inicio==final)
        return;
    Arbol*nuevo1=desencolar();
    Arbol*nuevo2=desencolar();
    n=nuevo1->fr+nuevo2->fr;
    Arbol*arbolito=nuevoArbol(46,n);
    arbolito->izq=nuevo1;
    arbolito->der=nuevo2;
    insertarOrden(arbolito);
    algoritmoHoffman();
    
}

void insertarOrden(Arbol*dato){
    Nodo*nuevo=nuevoNodo(dato);
    Nodo*aux=inicio,*ant=NULL;
    while(aux!=NULL){
        if(aux->raiz->fr==nuevo->raiz->fr){
            if(aux==inicio){
                nuevo->siguiente=inicio;
                inicio->anterior=nuevo;
                inicio=nuevo;
            }else{
                ant->siguiente=nuevo;
                nuevo->anterior=ant;
                nuevo->siguiente=aux;
                aux->anterior=nuevo;
            }
            return;
        }
        ant=aux;
        aux=aux->siguiente;
    }
    if(inicio==NULL && final==NULL){
        inicio=nuevo;
        final=nuevo;
    }else{
        final->siguiente=nuevo;
        nuevo->anterior=final;
        final=nuevo;
    }
}

Arbol*desencolar(){
    Nodo*aux;
    if(colaVacia()){
        return NULL;
    }else{
        aux=inicio;
        inicio=inicio->siguiente;
        aux->siguiente=NULL;
        if(inicio!=NULL){
            inicio->anterior=NULL;
        }else{
            final=NULL;
        }
    }
    Arbol*resultado=aux->raiz;
    free(aux);
    return resultado;
}

void insertarCola(int dato){
    N++;
    if(buscarASCII(dato)==1){
        return;
    }
    Arbol*arbolito=nuevoArbol(dato,1);
    Nodo*nuevo=nuevoNodo(arbolito);
    if(inicio==NULL && final==NULL){
        inicio=nuevo;
        final=nuevo;
    }else{
        final->siguiente=nuevo;
        nuevo->anterior=final;
        final=nuevo;
    }
}

Arbol*nuevoArbol(int dato,int n){
    Arbol*nuevo=(Arbol*)malloc(sizeof(Arbol));
    nuevo->letra=dato;
    nuevo->fr=n;
    nuevo->izq=NULL;
    nuevo->der=NULL;
    return nuevo;
}

Nodo*nuevoNodo(Arbol*dato){
    Nodo*nuevo=(Nodo*)malloc(sizeof(Nodo));
    nuevo->raiz=dato;
    nuevo->siguiente=NULL;
    nuevo->anterior=NULL;
    return nuevo;
}

int buscarASCII(int dato){
    Nodo*aux=inicio;
    while(aux!=NULL){
        if(aux->raiz->letra==dato){
            aux->raiz->fr++;
            return 1;
        }
        aux=aux->siguiente;
    }
    return 0;
}

void ordenar(){
    if(inicio!=NULL){
        Nodo*piv=inicio;
        Nodo*apiv=NULL;
        Nodo*aux=inicio->siguiente;
        Nodo*max=inicio;
        Nodo*ant=inicio;
        while(piv!=NULL){
            while(aux!=NULL){
                if(aux->raiz->fr<max->raiz->fr){
                    ant->siguiente=aux->siguiente;
                    if(ant->siguiente==NULL)
                        final=ant;
                    aux->siguiente=piv;
                    if(piv==inicio){
                        inicio=aux;
                    }else{
                        apiv->siguiente=aux;
                    }
                    max=aux;
                    piv=aux;
                    aux=ant->siguiente;
                }else{
                    aux=aux->siguiente;
                    ant=ant->siguiente;
                }
            }
            apiv=piv;
            piv=piv->siguiente;
            max=max->siguiente;
            if(piv==NULL){
                aux=NULL;
            }else{
                aux=piv->siguiente;
            }
            ant=piv;
        }
    }
}

void inorden(FILE*hola,Arbol*r,int n){
    if(r!=NULL){
        inorden(hola,r->izq,n*10);
        if(r->letra!=46){
            if(hola==NULL){
                perror("Error en el cargado del archivo");
                return;
            }
            fprintf(hola,"%c %i\n",r->letra,n);
        }
        inorden(hola,r->der,n*10+1);
    }
    f=0;
}

int colaVacia(){
    if(inicio==NULL && final==NULL){
        return 1;
    }else{
        return 0;
    }
}

void lineas(FILE*Leer,int num){
    int conta=num-1;
    fseek(Leer, 0, SEEK_SET);
prueba:
    if (conta>0)
    {
        while (fgetc(Leer) != '\n');
        conta--;
        goto prueba;
    }
}
