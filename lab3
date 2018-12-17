#include <stdio.h>
#include <string.h>
#include <math.h>
#include <locale.h>
int hashf(const unsigned char sample[], int M){
    int h=0,i=0,p=1;
    for(;i<M;++i){
        h+=(((int)(sample[i]))%3)*p;
        p*=3;
    }
    return h;
}
int needfornewhashf(const char sample[])   {
    double M = strlen(sample);
    return (int) pow(3.0, M - 1);
}
int newhashf(int h,const unsigned char out,const unsigned char in,int p){
    return ((h-((int)(out)%3))/3+((int)(in)%3)*p);
}
void rk(const unsigned char sample[], int M, const unsigned char text[], int N,int p,int hs,int count){
    int ht=hashf(text,M),counttext=0,countsample=0;
    for(;counttext<=N-M;++counttext){
        countsample=0;
        if (hs==ht) for(;countsample<M;++countsample){
            printf("%d %c", count+countsample+counttext+1,' ');
            if (sample[countsample]!=text[countsample+counttext]) break;
        }
        ht=newhashf(ht,text[counttext],text[counttext+M],p);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    char sample[18], text[1025];
    int hs = 0,count=0;
    gets(sample);
    hs = hashf(sample, strlen(sample));
    int p = needfornewhashf(sample);
    printf("%d %c", hs, ' ');
    while (fgets(text,1024,stdin)){
        rk(sample, strlen(sample), text, strlen(text),p, hs,count);
        count+=strlen(text);
    }
    return 0;
}
