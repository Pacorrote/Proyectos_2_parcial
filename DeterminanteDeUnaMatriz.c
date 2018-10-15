#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int det(int **mat,int n){
	int a=0,ac;
	int **ma;
	ma=(int **)malloc((n-1)*sizeof(int*));
	for(int a=0;a<(n-1);a++){
		ma[a]=(int*)malloc((n-1)*sizeof(int));
	}
	if(n==1){
		return mat[0][0];
	}
	else{
		for(int i=0;i<n;i++){
			ac=0;
			for(int k=0;k<n-1;k++){
				if(k==i){
					ac++;	
				}
				for(int f=0;f<n-1;f++){
					ma[k][f]=mat[ac][f+1];
				}
				ac++;
			}
			a+=mat[i][0]*(pow(-1,i))*det(ma,n-1);
		}
		return a;
	}
}



int main(int argc, char *argv[]) {
	int **mat;
	int d;
  int x;
  printf("Tamanno de la matriz nxn: ");
  scanf("%d", &x);
	mat=(int **)malloc(x*sizeof(int*));
	for(int a=0;a<x;a++){
		mat[a]=(int*)malloc(x*sizeof(int));
	}
	for(int i=0;i<x;i++){
		for(int j=0;j<x;j++){
      printf("Inserte el elemento: ");
			scanf("%d",&d);
			mat[i][j]=d;
		}	
	}
	
	printf("\nLa determinante de la matriz es: %d",det(mat,x));
	return 0;
}
