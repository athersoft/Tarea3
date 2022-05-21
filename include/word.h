#ifndef WORD_H
#define WORD_H
#include "list.h"
#include "map.h"
#include <stdio.h>

typedef struct{
    Map * words;
    char bookName[50];
    char fileName[20];
    long totalChar; //Cuenta el total de caracteres del libro
    long totalWords;
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
void initBook(Book * book,char *id);
void searchWord(Map* mapWords);
void showWords(Map*mapWords);
void readBook(Book * book);


int is_equal_string(void * key1, void * key2);
int lower_than_string(void * key1, void * key2);
#endif