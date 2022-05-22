#ifndef WORD_H
#define WORD_H
#include "list.h"
#include "map.h"
typedef struct{
    List *mostRelevants;
    List *mostFrecuents;
    char bookName[50];
    char fileName[20];
    int totalPalabras;
}Book;

typedef struct{
    char name[100];
    int num;
    List *ocurrencias;
}Word;

typedef struct{
    long int pos;
    char bookName[50];
}Pos;

Word *createWord();
Pos *createPos();
Book *createBook();

void searchWord(Map* mapWords);
void showWords(Map*mapWords);
#endif