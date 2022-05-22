#include <stdio.h>
#include <stdlib.h>
typedef struct Word{
    char* word;
    int length;
}Word;
typedef struct Array{
    Word* Words;
    int NumOfWords;
}Array;
typedef struct numbers{
    int letter;
    int count;
}numbers;
numbers* finding(int start,Array* arr,int maxwidth,numbers* num);
void printEmpty(int number);
void print(numbers* num,Array* arr,int maxwidth,int start);
void fileprintEmpty(FILE* file,int number);
void fileprint(FILE* file,numbers* num,Array* arr,int maxwidth,int start);
void MemoryCleaner(Array* arr);