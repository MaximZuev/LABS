#include <stdio.h>
#include <string.h>
#include <locale.h>

void tableofshifts(const unsigned char sample[],int table[]){
    int i=0,sizes=strlen(sample);
    for(;i<256;++i) table[i]=sizes;
    table[(int)(sample[sizes-1])]=sizes;
    for (i=0;i<sizes-1;++i) table[(int)(sample[i])]=sizes-i-1;
}
void bm(const unsigned char text[],const unsigned char sample[], int table[], int count){
    int sizes=strlen(sample),sizet=strlen(text),i=sizes,j=0;
    while (i<=sizet){
        if (text[i-1]==sample[sizes-1]){
            for (j=0;j<sizes;++j){
                if (text[i-1-j]==sample[sizes-1-j]) printf("%d %c",i-j+count,' ');
                else {
                    printf("%d %c",i-j+count,' ');
                    break;
                }
            }
        } else printf("%d %c",i+count,' ');
        i+=table[(int)(text[i-1])];
    }

}
int main() {
    setlocale(LC_ALL, "Russian");
    char sample[18], text[1025];
    int table[255],count=0;
    gets(sample);
    tableofshifts(sample,table);
    while (fgets(text,1024,stdin)){
        bm(text,sample,table,count);
        count+=strlen(text);
    }
    return 0;
}
