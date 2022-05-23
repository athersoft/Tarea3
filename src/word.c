#include "import.h"
#include "util.h"
#include "menu.h"
#include "map.h"
#include "word.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "treemap.h"


//Comparar Strings
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

int lower_than_int(void * key1, void * key2) {
    if((double*)key1 < (double*)key2) return 1;
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

listNode *createlistNode(){
    listNode *listnode = (listNode*) malloc(sizeof(listNode));
    strcpy(listnode -> name, "");
    listnode -> value = 0;
    return listnode;
}

//Agregue los valores iniciales para el book
Book *createBook(){
    Book * book = (Book*) malloc(sizeof(Book));
    book->words = createMap(is_equal_string,lower_than_string);
    strcpy(book -> bookName, "");
    strcpy(book -> fileName, "");
    book->totalPalabras = 0;
    book -> totalChar = 0;
    book -> totalWords = 0;
    book -> mostRelevant = listCreate();
    book -> mostFrecuent = listCreate();
    return book;
}



void initBook(Book * book,char *id){
    //El archivo se abre y queda referenciado en book
    char open[20];
    strcpy(open, id);
    strcat(open, ".txt");
    strcpy(book -> fileName,id);    //Le pone el filename al libro
    book -> arch = fopen(open, "r");//Abre el archivo
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
    rewind(book->arch);//Vuelve a abrir al inicio del archivo
    char * x = malloc(1024 * sizeof (char) );
    while((fscanf(book->arch, " %1023s", x) == 1)){ //recorre cada palabra del archivo
        //printf("%s largo = %lo\n",x,strlen(x));
        book -> totalChar += strlen(x);//Suma los caracteres de la palabra
        quitar_caracteres(x,".,;:-_()/?¡![]{}+*=%%$&‘’“");//elimina esos caracteres de la palabra
        lower(x);//Lo hace minuscula
        Word *aux = searchMap(book -> words,x);//ve si la palabra existe dentro del mapa libro (que almacena todas las palabras del libro)
        if(aux == NULL){//Si no existe la crea y agrega al mapa
            Word * new = createWord();
            strcpy(new -> name, x);
            insertMap(book -> words,new ->name,new);
        }else{//Si existe le suma 1 a la cantidad de veces que se repite
            (aux -> num)++;
        }          
    }

    /*for(Word *aux = firstMap(book -> words);
            aux != NULL; 
            aux = nextMap(book -> words)) 
    {
        printf("la cuenta va en %lo\n",book -> totalWords);
        (book -> totalWords)+= aux -> num;
        printf("%s: ",aux ->name);
        printf("%lo\n",aux ->num);
    }
    printf("%lo",book ->totalChar);*/
    return;
}

void bookToMap(Map *mapBook, Book *book){
//Agrega un libro al mapa
    Book *aux = searchMap(mapBook,book ->fileName);
    if(aux == NULL){
        insertMap(mapBook,book ->fileName,book);
    }else{
        printf("Libro ya existe");
    }
    /*for(Book *aux = firstMap(mapBook);
            aux != NULL; 
            aux = nextMap(mapBook)) 
    {
        printf("%s\n",aux -> fileName);
    }*/
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

long double relevanciaPalabras(char* palabra, char* titulo, Map* mapWords, Map* mapBooks){

    Word* word = createWord();
    Book* book = createBook();

    word = searchMap(mapWords, palabra);
    book = searchMap(mapBooks, titulo);

    int totalOcurrencias = 0;//Total de veces que aparece la palabra en el libro
    int totalLibros = 0;
    int librosDiferentes = 1;

    long double finalPart = 0;
    double firstPart = 0;
    double secondPart = 0;
    
    char lastBook[100];
    strcpy ( lastBook, titulo);

    if (word != NULL && book != NULL){
        for (Pos* i = listFirst(word->ocurrencias); i != NULL; i = listNext(word->ocurrencias)){
            if (strcmp(i->bookName, titulo) == 0){
                totalOcurrencias++;
            }else{
                
                if (strcmp(lastBook, i->bookName) != 0){
                    strcpy(lastBook, i->bookName);
                    librosDiferentes++;
                }
            }
        }
        

        firstPart = (double)totalOcurrencias / book->totalPalabras;
        
        

        for (Book* i = firstMap(mapBooks); i != NULL; i = nextMap(mapBooks)){
            totalLibros++;
        }

        int div = (double)totalLibros / librosDiferentes;
        secondPart = (double)log(div);  

        finalPart = firstPart * secondPart;
    }

    return finalPart;
}

void showInContext(char *_word, char *_title, Map *mapWords, Map *mapBooks){
    Word *word = searchMap(mapWords, _word);
    if(word == NULL){
        strcat(buf, "Palabra no encontrada");
        return;
    }
    Book *book = searchMap(mapBooks, _title);
    if(book == NULL){
        strcat(buf, "Libro no encontrado");
        return;
    }
    FILE *file = fopen(book ->fileName , "r");

    char *mensaje = (char*) malloc(sizeof(char)*100);

    clrscr();
    strcat(buf, "Ocurrencias en ");
    strcat(buf, _title);
    strcat(buf, ": \n");

    for (Pos* i = listFirst(word->ocurrencias); i != NULL; i = listNext(word->ocurrencias) ){
        if(strcmp(i -> bookName, book ->bookName) == 0){
            fseek(file, i->pos, SEEK_SET);
            fgets(mensaje,100,file);
            strcat(buf, "-");
            strcat(buf, mensaje);
        }
    }
    fclose(file);
}

void searchContext(Map *mapWords, Map *mapBooks){
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
}

List *makeRelevantTree(Map *mapWords, Map *mapBooks, char *title){
    List *map = listCreate();
    int found = 0;
    long double relev;

    int cont = 0;
    for(Word *i = firstMap(mapWords); i!= NULL; i = nextMap(mapWords)){
        for(Pos* j = listFirst(i->ocurrencias); j != NULL; j = listNext(i->ocurrencias) ){
            if(found == 0){
                if(strcmp(j->bookName, title) == 0){
                    found = 1;
                    break;
                }
            }
        }
        if(found == 1){

            if(cont < 11){
                relev = relevanciaPalabras(i -> name, title, mapWords, mapBooks);
                listNode *node = createlistNode();
                node -> value = relev;
                strcpy(node -> name, i -> name);
                listPushFront(map, node);
                cont++;
            }else{
                relev = relevanciaPalabras(i -> name, title, mapWords, mapBooks);
                listNode *node = createlistNode();
                node -> value = relev;
                strcpy(node -> name, i -> name);

                for(listNode *i = listFirst(map); i!=NULL; i = listNext(map)){
                    if(i -> value < node -> value){
                        listPushCurrent(map, node);
                        listPopBack(map);
                    }
                }
            }
        }
        found = 0;
    }
    
    return map;
}

void showMostRelevant(char *titulo, Map *mapBooks, Map *mapWords){
    Book *book = searchMap(mapBooks, titulo);
    if(book == NULL){
        strcat(buf, "Libro no encontrado");
        return;
    }
    strcat(buf, "Palabras mas relevantes:\n");
    
    for(listNode *i = listFirst(book -> mostRelevant); i!= NULL; i = listNext(book -> mostRelevant)){
        strcat(buf, i->name);
        strcat(buf, "\n");
    }


}

void searchMostRelevant(Map *mapBooks, Map *mapWords){
    char *titulo = (char *) malloc(sizeof(char)*100);
    printf("Ingresa el titulo del libro: ");
    fflush(stdin);
    scanf("%[^\n]*s", titulo);
    getchar();

    showMostRelevant(titulo, mapBooks, mapWords);
}

void searchBook(Map* mapBooks){
    //Word* aux = createWord();
    char titulo[100];
    printf("Ingresa la libro que quiere buscar: ");
    fflush(stdin);
    scanf("%[^\n]*s", titulo);
    getchar();
    char *token = (char *) malloc(sizeof(char)*50);
    List* palabraTitulo = listCreate();
    int cont = 0;
    int validaciones;
    token = strtok(titulo, " ");
    char aux[100];
    while (token != NULL) {
        listPushFront(palabraTitulo, token);
        token = strtok(NULL, " ");
        cont++;
    } 

    for (Book* k = firstMap(mapBooks); k != NULL; k = nextMap(mapBooks)){

        for (char* i = listFirst(palabraTitulo); i != NULL; i = listNext(palabraTitulo) ){

            if (strstr(k->bookName, i)){
                validaciones++;
                strcat(buf, k->bookName);
            }
        }

        if (validaciones == cont){
            strcat(buf, k->bookName);
            sprintf(aux, "Total de palabras: %i\nTotal de caracteres: %i", k->totalPalabras, k->totalWords);
            strcat(buf, aux);
        }
    }





}




List *makeFrecencyTree(Map *mapWords, char *title){
    List *map = listCreate();
    int frecuency = 0;
    int cont = 0;
    for(Word *i = firstMap(mapWords); i!= NULL; i = nextMap(mapWords)){
        for(Pos* j = listFirst(i->ocurrencias); j != NULL; j = listNext(i->ocurrencias) ){
            if(strcmp(j->bookName, title) == 0){
                frecuency++;
            }
        }
            if(cont < 11){
                listNode *node = createlistNode();
                node -> value = frecuency;
                strcpy(node -> name, i -> name);
            
                listPushFront(map, node);
                cont++;
            }else{
                listNode *node = createlistNode();
                node -> value = frecuency;
                strcpy(node -> name, i -> name);

                for(listNode *i = listFirst(map); i!=NULL; i = listNext(map)){
                    if(i -> value < node -> value){
                        listPushCurrent(map, node);
                        listPopBack(map);
                    }
                }
            }
    }
    return map;
}

void showMostFrecuent(char *titulo, Map *mapBooks, Map *mapWords){
    Book *book = searchMap(mapBooks, titulo);
    if(book == NULL){
        strcat(buf, "Libro no encontrado");
        return;
    }
    strcat(buf, "Palabras mas frecuentes:\n");

    for(listNode *i = listFirst(book -> mostFrecuent); i!= NULL; i = listNext(book -> mostFrecuent)){
        strcat(buf, i->name);
        strcat(buf, "\n");
    }

}

void searchMostFrecuent(Map *mapBooks, Map* mapWords){
    char *titulo = (char *) malloc(sizeof(char)*100);
    printf("Ingresa el titulo del libro: ");
    fflush(stdin);
    scanf("%[^\n]*s", titulo);
    getchar();

    showMostFrecuent(titulo, mapBooks, mapWords);
}



void showBook(Map * mapBook) {
    Book *aux = firstMap(mapBook);
    while(aux != NULL){
        strcat(buf, "ID: ");
        strcat(buf, aux->fileName);
        strcat(buf, "\n");
        strcat(buf, "Titulo: ");
        strcat(buf, aux->bookName);
        strcat(buf, "\n");
        strcat(buf, "Palabras: ");
        char num[10];
        sprintf(num, "%lo", aux->totalPalabras);
        strcat(buf, num);
        strcat(buf, "\n");
        strcat(buf, "Caracteres: ");
        sprintf(num, "%lo", aux->totalChar);
        strcat(buf, num);
        strcat(buf, "\n");
        aux = nextMap(mapBook);
    }

}

void context(Book *book, char * word){
    char open[20];
    strcpy(open, book -> fileName);
    strcat(open, ".txt");
    book -> arch = fopen(open, "r");
    char * x = malloc(1024 * sizeof(char));
    while (fscanf(book -> arch, "%[^\n] ", x) != EOF) {
        //lower(x);
        char * search = strstr(x,word);
        if(search != NULL){
            printf("> %s\n", x);
        }
        
    }
}

