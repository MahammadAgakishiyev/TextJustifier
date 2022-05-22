#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"


int main(){
    printf("terminal or file? ");
    char f[10];
    char term[9]="terminal";
    if (scanf("%[^\n]%*c",f)!=1){
        exit (0);
    }
    Array* array=(Array*) malloc(sizeof(Array));
    char space[2]=" ";
    if (strcmp(term,f)==0){
        char* arr=(char*) malloc(1000*sizeof(char));
        printf("words: ");
        if (scanf("%[^\n]%*c",arr)!=1){
            exit (0);
        }
        int WordsCount=1;
        for (int i=0;i<strlen(arr);i++){
            if (arr[i]==space[0]){
                WordsCount+=1;
            }
        }
        array->NumOfWords=WordsCount;
        int k=0;
        int m=0;
        array->Words=(Word*) malloc(array->NumOfWords*sizeof(Word));
        char* temporary;
        for (int i=0;i<strlen(arr);i+=1){
            if (arr[i]!=space[0]){
                if (m==0){
                    temporary=(char*) malloc(25*sizeof(char));
                }
                temporary[m]=arr[i];
                m+=1;
            }
            else{
                array->Words[k].word=(char*) malloc((m+1)*sizeof(char));
                strcpy(array->Words[k].word,temporary);
                array->Words[k].length=m;
                free(temporary);
                k+=1;
                m=0;
            }
        }
        array->Words[k].word=(char*) malloc((m+1)*sizeof(char));
        strcpy(array->Words[k].word,temporary);
        array->Words[k].length=m;
        free(temporary);
        free(arr);
    }
    else{
        char file[35];
        printf("enter file: ");
        if (scanf("%[^\n]%*c",file)!=1){
            exit (0);
        }
        FILE* fptr=fopen(file,"r");
        char* arr=(char*) malloc(1000*sizeof(char));
        array->NumOfWords=0;
        while (fscanf(fptr,"%[^\n]%*c",arr)!=EOF){
            for (int i=0;i<strlen(arr);i+=1){
                if (arr[i]==space[0]){
                    array->NumOfWords+=1;
                }
            }
            array->NumOfWords+=1;
        }
        fseek(fptr,0,SEEK_SET);
        array->Words=(Word*) malloc(array->NumOfWords*sizeof(Word));
        char* temporary;
        int k=0;
        int m=0;
        while (fscanf(fptr,"%[^\n]%*c",arr)!=EOF){
            for (int i=0;i<strlen(arr);i+=1){
                if (arr[i]!=*space){
                    if (m==0){
                        temporary=(char*) malloc(25*sizeof(char));
                    }
                    temporary[m]=arr[i];
                    m+=1;
                }
                else{
                    array->Words[k].word=(char*) malloc((m+1)*sizeof(char));
                    strcpy(array->Words[k].word,temporary);
                    array->Words[k].length=m;
                    free(temporary);
                    k+=1;
                    m=0;
                }
            }
            array->Words[k].word=(char*) malloc((m+1)*sizeof(char));
            strcpy(array->Words[k].word,temporary);
            array->Words[k].length=m;
            free(temporary);
            k+=1;
            m=0;
        }
        fclose(fptr);
        free(arr);
    }
    int maxwidth;
    printf("maxwidth = ");
    if (scanf("%d",&maxwidth)!=1){
        exit (0);
    }
    printf("do you want to write to file or terminal? ");
    char write[10];
    if (scanf("%s",write)!=1){
        exit (0);
    }
    char filename[30];
    FILE* newfile;
    int start=0;
    numbers* num= (numbers*) malloc(sizeof(numbers));
    if (strcmp(term,write)==0){
        while (start<array->NumOfWords){
            num=finding(start,array,maxwidth,num);
            print(num,array,maxwidth,start);
            start+=num->count;
        }
    }
    else{
        printf("which file: ");
        if (scanf("%s",filename)!=1){
            exit (0);
        }
        newfile=fopen(filename,"a+");
        while (start<array->NumOfWords){
            num=finding(start,array,maxwidth,num);
            fileprint(newfile,num,array,maxwidth,start);
            start+=num->count;
        }
    }
    char check[3]="no";
    printf("I think you want to add a new word, don't you? ");
    char str[5];
    if (scanf("%s",str)!=1){
        exit (0);
    }
    if (strcmp(str,check)!=0){
        char newword[20],word1[20];
        printf("enter new word: ");
        if (scanf("%s",newword)!=1){
            exit (0);
        }
        printf("after which word you want to add (you can choose beginning too):");
        if (scanf("%s",word1)!=1){
            exit (0);
        }
        Array* newarr=(Array*) malloc(sizeof(Array));
        newarr->NumOfWords=array->NumOfWords+1;
        newarr->Words=(Word*) malloc(newarr->NumOfWords*sizeof(Word));
        char compare[]="beginning";
        if (strcmp(compare,word1)==0){
            newarr->Words[0].word=(char*) malloc((strlen(newword)+1)*sizeof(char));
            strcpy(newarr->Words[0].word,newword);
            newarr->Words[0].length=strlen(newword);
            for (int i=1;i<newarr->NumOfWords;i+=1){
                newarr->Words[i].length=array->Words[i-1].length;
                newarr->Words[i].word=(char*) malloc((newarr->Words[i].length+1)*sizeof(char));
                strcpy(newarr->Words[i].word,array->Words[i-1].word);
                
            }
        }
        else {
            int z=0;
            for (int i=0;i<array->NumOfWords;i+=1){
                if (strcmp(array->Words[i].word,word1)==0){
                    z=i;
                    break;
                }
            }
            for (int k=0;k<newarr->NumOfWords;k+=1){
                if (k==z+1){
                    newarr->Words[k].length=strlen(newword);
                    newarr->Words[k].word=(char*) malloc((newarr->Words[k].length+1)*sizeof(char));
                    strcpy(newarr->Words[k].word,newword);
                    
                }
                else{
                    if (k<z+1){
                        newarr->Words[k].length=array->Words[k].length;
                        newarr->Words[k].word=(char*) malloc((newarr->Words[k].length+1)*sizeof(char));
                        strcpy(newarr->Words[k].word,array->Words[k].word);
                    }
                    else{
                        newarr->Words[k].length=array->Words[k-1].length;
                        newarr->Words[k].word=(char*) malloc((newarr->Words[k].length+1)*sizeof(char));
                        strcpy(newarr->Words[k].word,array->Words[k-1].word);
                    }
                }
            }
        }
        printf("do you want to change maxwidth: ");
        char answer[5];
        if (scanf("%s",answer)!=1){
            exit (0);
        }
        int newmaxwidth;
        if (strcmp(answer,check)==0){
            newmaxwidth=maxwidth;
        }
        else{
            printf("newmaxwidth: ");
            if (scanf("%d",&newmaxwidth)!=1){
                exit (0);
            }
        }
        num->count=0;
        num->letter=0;
        start=0;
        if (strcmp(term,write)==0){
            while (start<newarr->NumOfWords){
                num=finding(start,newarr,newmaxwidth,num);
                print(num,newarr,newmaxwidth,start);
                start+=num->count;
            }
        }
        else{
            while (start<newarr->NumOfWords){
                num=finding(start,newarr,newmaxwidth,num);
                fileprint(newfile,num,newarr,newmaxwidth,start);
                start+=num->count;
            }
        }
        MemoryCleaner(newarr);
    }
    printf("do you want to delete a word? ");
    char d[5];
    if (scanf("%s",d)!=1){
        exit (0);
    }
    if (strcmp(d,check)!=0){
        printf("which word do you want to delete: ");
        char word2[20];
        if (scanf("%s",word2)!=1){
            exit (0);
        }
        Array* newarray=(Array*) malloc(sizeof(Array));
        newarray->NumOfWords=array->NumOfWords-1;
        newarray->Words=(Word*) malloc(newarray->NumOfWords*sizeof(Word));
        int z=0;
        for (int i=0;i<array->NumOfWords;i+=1){
            if (strcmp(array->Words[i].word,word2)==0){
                z=i;
                break;
            }
        }
        for (int k=0;k<newarray->NumOfWords;k+=1){
            if (k<z){
                newarray->Words[k].length=array->Words[k].length;
                newarray->Words[k].word=(char*) malloc((newarray->Words[k].length+1)*sizeof(char));
                strcpy(newarray->Words[k].word,array->Words[k].word);
                
            }
            else{
                newarray->Words[k].length=array->Words[k+1].length;
                newarray->Words[k].word=(char*) malloc((newarray->Words[k].length+1)*sizeof(char));
                strcpy(newarray->Words[k].word,array->Words[k+1].word);
            }
        }
        printf("do you want to change maxwidth: ");
        char answer2[5];
        if (scanf("%s",answer2)!=1){
            exit (0);
        }
        int newmaxwidth2;
        if (strcmp(answer2,check)==0){
            newmaxwidth2=maxwidth;
        }
        else{
            printf("newmaxwidth: ");
            if (scanf("%d",&newmaxwidth2)!=1){
                exit (0);
            }
        }
        num->count=0;
        num->letter=0;
        start=0;
        if (strcmp(term,write)==0){
            while (start<newarray->NumOfWords){
                num=finding(start,newarray,newmaxwidth2,num);
                print(num,newarray,newmaxwidth2,start);
                start+=num->count;
            }
        }
        else{
            while (start<newarray->NumOfWords){
                num=finding(start,newarray,newmaxwidth2,num);
                fileprint(newfile,num,newarray,newmaxwidth2,start);
                start+=num->count;
            }
        }
        MemoryCleaner(newarray);
    }
    if (strcmp(term,write)!=0){
        printf("do you want to check whether text has been justified correctly in the file? ");
        char z[5];
        if (scanf("%s",z)!=1){
            exit (0);
        }
        if (strcmp(z,check)!=0){
            #include "print.h"
            printContent(newfile);
        }
        fclose(newfile);
    }
    MemoryCleaner(array);
    return 0;
}
