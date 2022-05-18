/* Entrada y salida estándar */
#include <stdio.h>

/* manipulación de Strings */
#include <string.h>

#include "import.h"
#include "menu.h"
#include "util.h"
#include "search.h"
#include "list.h" 
#include "map.h"
#include "word.h"

int lower_than_string(void* key1, void* key2);
int is_equal_string(void * key1, void * key2);


/* main function */
int main(){
    Map * mapBooks = createMap(is_equal_string);
    Map * mapWords = createMap(is_equal_string);

    char in = '\0';

    while(in != 'q' ){
        mostrarMenu();
        fflush(stdin);
        scanf("%c", &in);
        getchar();

        switch(in) {
            case ('c'): // Importar libro
                importBook(mapBooks, mapWords);
                break;

            case ('m'): // Mostrar documentos 
                showWords(mapWords);
                break;
            case('b'): // Buscar libro
                break;
            case('B'): // Mostrar palabras mas frecuentes
                break;
            case('A'): // Mostrar palabras mas relevantes
                break;
            case('X'): // Buscar palabra
                searchWord(mapWords);
                break;
            default:
                break;
          } 

    } // while (in != q)
    printf("Bye bye\n");
    return 0;
}


int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
    return 0;
}
