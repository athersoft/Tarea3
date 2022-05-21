#include "import.h"
#include "util.h"
#include "menu.h"
#include "map.h"
#include "word.h"
#include <string.h>


int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

Word *createWord(){
    Word *word = (Word*) malloc(sizeof(Word));
    strcpy(word -> name, "");
    word -> num = 1;
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
    book->words = createMap(is_equal_string,lower_than_string);
    strcpy(book -> bookName, "");
    strcpy(book -> fileName, "");
    book -> totalChar = 0;
    book -> totalWords = 0;
    return book;
}
//Lleva los caracteres de una cadena a minuscula


void initBook(Book * book,char *id){
    //El archivo se abre y queda referenciado en book
    char open[20];
    strcpy(open, id);
    strcat(open, ".txt");
    strcpy(book -> fileName,id);
    book -> arch = fopen(open, "r");
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
            if(quitar_caracteres(x, ",")){
                strcat(book -> bookName,x);
            }else{
                strcat(book -> bookName,x);
                strcat(book -> bookName," ");
            }
        }
    }

}

void readBook(Book * book){
    rewind(book->arch);
    char x[1024];
    while((fscanf(book->arch, " %1023s", x) == 1)){
        book -> totalChar += strlen(x);
        (book -> totalWords)++;
        quitar_caracteres(x,".,;:-_()/?¡![]{}+*=%%$&");
        lower(x);
        Word *aux = searchMap(book -> words,x);
        if(aux == NULL){
            Word * new = createWord();
            strcpy(new -> name, x);
            insertMap(book -> words,new ->name,new);
        }else{
            (aux -> num)++;
        }          
    }

    for(Word *aux = firstMap(book -> words);
            aux != NULL; 
            aux = nextMap(book -> words)) 
    {
        printf("%s: ",aux ->name);
        printf("%lo\n",aux ->num);
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

