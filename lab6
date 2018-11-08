#include <stdio.h>
#include <stdlib.h>
void QuickSort (int *a, int l,int r){
    int t;
    int i=l,j=r;
    int x=a[(l+r)/2];
    do{
        while(a[i]<x) i++;
        while(a[j]>x) j--;
        if(i<=j) {
            t=a[i];
            a[i]=a[j];
            a[j]=t;
            i++;
            j--;
        }
    }while(i<j);
    if (i<r)  QuickSort(a,i,r);
    if (j>l) QuickSort (a,l,j);
}
int a[2000000];
int n,k;
int main(){
    scanf("%d \n",&n);
    for (k=0;k<n;k++) scanf("%d",&a[k]);
    QuickSort(a,0,n-1);
    for (k=0;k<n;k++) printf("%d " ,a[k]);
    return 0;
}
