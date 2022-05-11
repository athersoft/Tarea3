#ifndef WORD_H
#define WORD_H
include "list.h"

struct book{
    list *mostRelevants;
    list *mostFrecuents;
    char bookName[50];
}

struct word{
    char name[50];
    int num;
    list *ocurrencias;
}

struct ocurrencia{
    int pos;
    char bookName[50];
}