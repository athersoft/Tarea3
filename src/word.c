#include "import.h"
#include "util.h"
#include "menu.h"
#include "map.h"
#include "word.h"
#include <string.h>

Word *createWord(){
    Word *word = (Word*) malloc(sizeof(Word));
    strcpy(word -> name, "");
    word -> num = 0;
    word -> ocurrencias = listCreate();

    return word;
}

Pos *createPos(){
    Pos *pos = (Pos*) malloc(sizeof(Pos));
    pos -> pos = 0;
    strcpy(pos -> bookName, "");

    return pos;
}

Book *createBook(){
    Book * book = (Book*) malloc(sizeof(Book));
    book -> mostRelevants = listCreate();
    book -> mostFrecuents = listCreate();
    strcpy(book -> bookName, "");
    strcpy(book -> fileName, "");

    return book;
}

void searchWord(Map* mapWords){
    Word* aux = createWord();
    char *palabra = (char *) malloc(sizeof(char)*50);
    printf("Ingresa la palabra que quiere buscar: ");
    fflush(stdin);
    scanf("%[^\n]*s", palabra);
    getchar();

    //char last_book[50] = NULL;

    if (searchMap(mapWords, palabra) != NULL){
        aux = searchMap(mapWords, palabra);
        listFirst(aux->ocurrencias);
        strcat(buf, "Libros en los que aparece: ");
        strcat(buf, "\n");
        for (Pos* i = listFirst(aux->ocurrencias); i != NULL; i = listNext(aux->ocurrencias) ){
            //if(strcmp(last_book, i -> bookName) != 0){
                strcat(buf, "Titulo: ");
                strcat(buf, i->bookName);
                strcat(buf, "\n");
                //strcpy(last_book[50], i->bookName);
            //}
        }
    }else{
        strcat(buf, "No se encontro la palabra\n");
    }


}

void showWords(Map * mapWords){
    for(Word *word = firstMap(mapWords);
            word != NULL; 
            word = nextMap(mapWords)) 
    {
        strcat(buf, word ->name);
        strcat(buf, "\n");
    }
}