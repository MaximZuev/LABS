#include <stdio.h>
#include <stdlib.h>
void error(){
    printf("bad input");
    exit(0);
}
void swap(int z[],int z1,int z2){
   int t=z[z1];
   z[z1]=z[z2];
   z[z2]=t;
}
void nextset(int x[],int x1){
    int x2=x1-2;
    while((x2>=0)&&(x[x2]>=x[x2+1])) x2--;
    if (x2==-1) exit(0);
    int x3=x1-1;
    while(x[x3]<=x[x2]) x3--;
    swap(x,x2,x3);
    int l=x2+1;int r=x1-1;
    while (l<r) swap(x,l++,r--);
}
int main() {
    int t=0,n,j=0,i,q,a[11],b[11];
    char c;
    for (i=0;i<10;i++) a[i]=0;
    scanf("%c",&c);
    do{
         if ((c <'0')||(c >'9')) t++;
         if (a[c-'0']==0) {
             a[c-'0']=1;
             b[j++]=c-'0';
         }
         else t++;
         scanf("%c",&c);
    }while(c!='\n');
    scanf("%d",&n);
    if (t!=0) error();
    for (q=0;q<n;q++) {
       nextset(b,j);
       for (i=0;i<j;i++) printf("%d",b[i]);
       printf("\n");
    }
    return 0;
}
