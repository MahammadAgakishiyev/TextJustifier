#include "library.h"

numbers* finding(int start,Array* arr,int maxwidth,numbers* num){
    int s=0;
    int m=0;     //shows letter count
    int f=0;     //shows letter+space count
    while (f<=maxwidth){

        m+=arr->Words[start+s].length;
        f+=arr->Words[start+s].length;
        if (f==maxwidth){
            num->count=s+1;
            num->letter=m;
            return num;
        }
        if (f>maxwidth){
            num->count=s;
            num->letter=m-arr->Words[start+s].length;
            return num;
        }
        f+=1;
        if (f==maxwidth){
            num->count=s+1;
            num->letter=m;
            return num;
        }
        if ((s+start)<arr->NumOfWords-1){
            s+=1;
        }
        else{
            num->count=s+1;
            num->letter=m;
            return num;
        }
    }
}
void printEmpty(int number){
    for (int i=0;i<number;i+=1){
        printf(" ");
    }
}

void print(numbers* num,Array* arr,int maxwidth,int start){
    int k=num->count-1;
    int d=maxwidth-num->letter;
    printf("'");
    if (num->count==1){
        printf("%s",arr->Words[start].word);
        printEmpty(d);
    }
    else if ((start+num->count)==arr->NumOfWords){
        int s=0;
        while (s<num->count-1){
            printf("%s",arr->Words[start+s].word);
            printEmpty(1);
            s+=1;
        }
        printf("%s",arr->Words[start+s].word);
        int h=d-(num->count-1);
        printEmpty(h);
    }
    else if (d%k==0){
        int s=0;
        while (s<num->count-1){
            printf("%s",arr->Words[start+s].word);
            printEmpty(d/k);
            s+=1;
        }
        printf("%s",arr->Words[start+s].word);
    }
    else{
        int m=d/k;
        int q=d%k;
        int s=0;
        while (q>0){
            printf("%s",arr->Words[start+s].word);
            printEmpty(m+1);
            s+=1;
            q-=1;
        }
        while (s<num->count-1){
            printf("%s",arr->Words[start+s].word);
            printEmpty(m);
            s+=1;
        }
        printf("%s",arr->Words[start+s].word);
    }
    printf("'");
    printf("\n");
}
void fileprintEmpty(FILE* file,int number){
    for (int i=0;i<number;i+=1){
        fprintf(file," ");
    }
}
void fileprint(FILE* file,numbers* num,Array* arr,int maxwidth,int start){
    int k=num->count-1;
    int d=maxwidth-num->letter;
    fprintf(file,"'");
    if (num->count==1){
        fprintf(file,"%s",arr->Words[start].word);
        fileprintEmpty(file,d);
    }
    else if ((start+num->count)==arr->NumOfWords){
        int s=0;
        while (s<num->count-1){
            fprintf(file,"%s",arr->Words[start+s].word);
            fileprintEmpty(file,1);
            s+=1;
        }
        fprintf(file,"%s",arr->Words[start+s].word);
        int h=d-(num->count-1);
        fileprintEmpty(file,h);
    }
    else if (d%k==0){
        int s=0;
        while (s<num->count-1){
            fprintf(file,"%s",arr->Words[start+s].word);
            fileprintEmpty(file,d/k);
            s+=1;
        }
        fprintf(file,"%s",arr->Words[start+s].word);
    }
    else{
        int m=d/k;
        int q=d%k;
        int s=0;
        while (q>0){
            fprintf(file,"%s",arr->Words[start+s].word);
            fileprintEmpty(file,(d/k)+1);
            s+=1;
            q-=1;
        }
        while (s<num->count-1){
            fprintf(file,"%s",arr->Words[start+s].word);
            fileprintEmpty(file,d/k);
            s+=1;
        }
        fprintf(file,"%s",arr->Words[start+s].word);
    }
    fprintf(file,"'");
    fprintf(file,"\n");
}
void MemoryCleaner(Array* arr){
    for (int i=0;i<arr->NumOfWords;i++){
        free(arr->Words[i].word);
    }
    free(arr->Words);
    free(arr);
}