/* Entrada y salida estándar */
#include <stdio.h>

/* manipulación de Strings */
#include <string.h>
/*Probando*/
#include "import.h"
#include "menu.h"
#include "util.h"
#include "search.h"
#include "list.h" 
#include "map.h"
#include "word.h"




/* main function */
int main(){
    Map * mapBooks = createMap(is_equal_string,lower_than_string);
    Map * mapWords = createMap(is_equal_string,lower_than_string);
    Book * test = createBook();
    Book * test2 = createBook();

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
                initBook(test,"hola");
                readBook(test);
                bookToMap(mapBooks,test);
                initBook(test2,"67937");
                readBook(test2);
                bookToMap(mapBooks,test2);
                scanf("%c",&in);
                break;
            case('B'): // Mostrar palabras mas frecuentes
                break;
            case('A'): // Mostrar palabras mas relevantes
                break;
            case('X'): // Buscar palabra
                searchWord(mapWords);
                break;
            case('C'):
            /*
                char *palabra = (char *) malloc(sizeof(char)*50);
                printf("Ingresa la palabra que quiere buscar: ");
                fflush(stdin);
                scanf("%[^\n]*s", palabra);
                getchar();

                char *titulo = (char *) malloc(sizeof(char)*50);
                printf("Ingresa el titulo del libro: ");
                fflush(stdin);
                scanf("%[^\n]*s", titulo);
                getchar();

                showInContext(palabra, titulo, mapWords, mapBooks);
                break;
            */
            default:
                break;
          } 

    } // while (in != q)
    printf("Bye bye\n");
    return 0;
}


