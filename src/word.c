#include "import.h"
#include "util.h"
#include "menu.h"
#include "map.h"
#include "word.h"
#include <string.h>
#include <ctype.h> //Para funcion toLower

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
    book -> totalChar = 0;
    return book;
}
//Lleva los caracteres de una cadena a minuscula
char* lower(char* word){
    int i = 0;
    while (word[i] != '\0'){
        word[i] = tolower(word[i]);
        i++;
    }
    return word;
}

void initBook(Book * book){
    //El archivo se abre y queda referenciado en book
    book -> arch = fopen("67937.txt", "r");
    if(book->arch == NULL){
        printf("Error al abrir archivo\n");
        return;
    }
    char x[1024];
    //Se salta las primeras palabras hasta llegar al inicio del titulo
    for(int i = 0; i < 5; i++){
        fscanf(book -> arch," %1023s", x);
    }
    //Lee hasta llegar al by que significa que se acabo el titulo del libro
    while (fscanf(book->arch, " %1023s", x) == 1){
        if(strcmp(x,"by") == 0){
            break;
        }else{
            //Agrega el las palabras(del titulo) al book
            strcat(book -> bookName,x);
        }
    }
    //Busca la posicion de la ,(siempre al final, no puede hacerlo con strlen) y la reemplaza con un /0
    char *coma = strchr(book->bookName, ',');
    *coma = '\0';
    //Vuelve al inicio del archivo
    rewind(book->arch);
    //Lee palabra por palabra
    while((fscanf(book->arch, " %1023s", x) == 1)){
        book -> totalChar += strlen(x);
        lower(x);
        Word *new = createWord();
        strcpy(new -> name, x);
        listPushBack(book -> mostFrecuents,new);
    }
    return;
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