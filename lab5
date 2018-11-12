#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
void swap(int z[],int z1,int z2){
    int t=z[z1];
    z[z1]=z[z2];
    z[z2]=t;
}
void sift (int* a,int j,int n){
    int maxp,done=0;
    while ((j<=n/2-1)&&(!done)){
        if (j*2+2==n) maxp=j*2+1;
        else if (a[j*2+1]>a[j*2+2]) maxp=j*2+1;
        else maxp=j*2+2;
        if (a[maxp]>a[j]) swap(a,maxp,j);
        else done=1;
        j=maxp;
    }
}
void heaps (int* a,int n){
    int i;
    for (i=n/2-1;i>=0;i--) sift(a,i,n);
    for (i=n-1;i>0;i--){
        swap(a,0,i);
        sift(a,0,i);
    }
}
int main() {
   int n,i;
   int *a;
   scanf("%d", &n);
   a=(int*)malloc(n*sizeof(int));
   for (i=0;i<n;i++) scanf("%d",&a[i]);
   heaps(a,n);
   for (i=0;i<n;i++) printf("%d ",a[i]);
   free(a);
   return 0;
}
