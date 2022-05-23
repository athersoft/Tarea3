#ifndef WORD_H
#define WORD_H
#include "list.h"
#include "map.h"
#include "treemap.h"
#include <stdio.h>

typedef struct{
    Map * words;    //Cambie por un mapa de palabras
    char bookName[100];
    char fileName[20];
    List *mostRelevant;
    List *mostFrecuent;
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

typedef struct{
    char name[100];
    long double value;
}listNode;

Word *createWord();
Pos *createPos();
Book *createBook();
listNode *createlistNode();
void initBook(Book * book,char *id);    //Agregada
void searchWord(Map* mapWords);
void showWords(Map*mapWords);
void readBook(Book * book);             //Agregada
void bookToMap(Map *mapBook, Book *book);//Agregada

//Funciones para comparar strings
int is_equal_string(void * key1, void * key2);  
int lower_than_string(void * key1, void * key2);

void showInContext(char *_word, char *_title, Map *mapWords, Map *mapBooks);
void searchContext(Map *mapWords, Map *mapBooks);
List *makeRelevantTree(Map *mapWords, Map *mapBooks, char *title);
List *makeFrecencyTree(Map *mapWords, char *title);
void showMostRelevant(char *titulo, Map *mapBooks, Map *mapWords);
void searchMostRelevant(Map *mapBooks, Map* mapWords);
void searchMostFrecuent(Map *mapBooks, Map* mapWords);
void showMostFrecuent(char *titulo, Map *mapBooks, Map *mapWords);
#endif