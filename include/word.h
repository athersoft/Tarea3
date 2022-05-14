#ifndef WORD_H
#define WORD_H
#include "list.h"

typedef struct{
    List *mostRelevants;
    List *mostFrecuents;
    char bookName[50];
}Book;

typedef struct{
    char name[100];
    int num;
    List *ocurrencias;
}Word;

typedef struct{
    int pos;
    char bookName[50];
}Ocurrencia;

Word *createWord();
#endif