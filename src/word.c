#include "import.h"
#include "util.h"
#include "menu.h"
#include "map.h"
#include "word.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//Comparar Strings
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

//Agregue los valores iniciales para el book
Book *createBook(){
    Book * book = (Book*) malloc(sizeof(Book));
    book->words = createMap(is_equal_string,lower_than_string);
    strcpy(book -> bookName, "");
    strcpy(book -> fileName, "");
    book -> totalChar = 0;
    book -> totalWords = 0;
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

void showWords(Map * mapWords){
    for(Word *word = firstMap(mapWords);
            word != NULL; 
            word = nextMap(mapWords)) 
    {
        strcat(buf, word ->name);
        strcat(buf, "\n");
    }
}

void showInContext(char *_word, char *_title, Map *mapWords, Map *mapBooks){
    Word *word = searchMap(mapWords, _word);
    Book *book = searchMap(mapBooks, _title);
    FILE *file = fopen(book ->fileName , "r");

    int contPalabras = 0;
    char mensaje[100];
    int pos = 0;

    for (Pos* i = listFirst(word->ocurrencias); i != NULL; i = listNext(word->ocurrencias) ){
        if(strcmp(i -> bookName, book ->bookName) == 0){
            fseek(file, i->pos, SEEK_SET);
            while(contPalabras < 10){
                mensaje[pos] = fgetc(file);
                pos++;
                if(mensaje[pos] == ' ' || mensaje[pos] == '\n' || mensaje[pos] == ',' || mensaje[pos] == '.'){
                    contPalabras++;
                }
            }
            strcat(buf, "Ocurrencia: ");
            strcat(buf, mensaje);
        }
    }
    fclose(file);
}


/*Problemas


totalChar cuenta caracteres demas(hay palabras que cuenta caracteres de mas, por ejemplo en hola.txt a Gutenberg le cuenta 11 caracteres)
totalWords cuenta palabras de mas(Es raro porque num en cada palabra si corresponde con la cantidad de veces que sale la palabra)
Falta quitar algunos caracteres en la funcion (no se cuales son pero quedan palabras con cosas  raras)
*/
