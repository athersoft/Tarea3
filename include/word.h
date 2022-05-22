#ifndef WORD_H
#define WORD_H
#include "list.h"
#include "map.h"
#include <stdio.h>

typedef struct{
    Map * words;    //Cambie por un mapa de palabras
    char bookName[50];
    char fileName[20];
    int totalPalabras;
    long totalChar; //Cuenta el total de caracteres del libro
    long totalWords;//Cuenta el total de palabras en libro
    FILE* arch;     //Archivo
}Book;

typedef struct{
    char name[100];
    int num;
    List *ocurrencias;
}Word;

typedef struct{
    long int pos;
    char bookName[100];
}Pos;

Word *createWord();
Pos *createPos();
Book *createBook();
void initBook(Book * book,char *id);    //Agregada
void searchWord(Map* mapWords);
void showWords(Map*mapWords);
void readBook(Book * book);             //Agregada
void bookToMap(Map *mapBook, Book *book);//Agregada

//Funciones para comparar strings
int is_equal_string(void * key1, void * key2);  
int lower_than_string(void * key1, void * key2);
void context(Book *book, char * word);

void showInContext(char *_word, char *_title, Map *mapWords, Map *mapBooks);
void searchContext(Map *mapWords, Map *mapBooks);
#endif