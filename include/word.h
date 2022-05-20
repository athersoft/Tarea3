#ifndef WORD_H
#define WORD_H
#include "list.h"
#include "map.h"
#include <stdio.h>

typedef struct{
    List *mostRelevants;
    List *mostFrecuents;
    char bookName[50];
    char fileName[20];
    long totalChar; //Cuenta el total de caracteres del libro
    FILE* arch;     //Archivo
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
void initBook(Book * book);
void searchWord(Map* mapWords);
void showWords(Map*mapWords);

int quitar_caracteres(char* string, char* c);
int hayQueEliminar(char c, char* string_chars);

#endif