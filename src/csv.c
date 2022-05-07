#include "csv.h"
#include "util.h"
#include "menu.h"
#include "item.h"
#include "map.h"




const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    // en windows el getline devuelve \r\n al terminar el string.. 
    while(tmp[i] != '\0' && tmp[i] != '\n' && tmp[i] != '\r'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}


 
void populateList(CSV *csv, Map* mapNames, Map* mapTypes, Map* mapBrands){
    char line[2048];


    /* leer linea a "read" hasta EOF */
    while(fgets(line, 2047, csv->fd) != NULL) {
        // Implementar    
        Item* aux = createItem();

        strcpy(aux->name, get_csv_field(line, 0));
        strcpy(aux->brand, get_csv_field(line, 1));

        strcpy(aux->type, get_csv_field(line, 2));
        
        aux->stock = atoi(get_csv_field(line, 3));
        aux->price = atoi(get_csv_field(line, 4));

        if(searchMap(mapNames,aux -> name) == NULL) { 
            insertMap(mapNames, aux->name, aux);
            insertMapList(mapTypes, aux -> type, aux);
            insertMapList(mapBrands, aux -> brand, aux);
        }else{
            strcat(buf, COLOR_RED "Error:  Los datos ya existen\n"
                    COLOR_RESET);
            break;
        }
        
    }
}

void CSVimport(char *name, Map* mapNames, Map* mapTypes, Map* mapBrands){
    CSV *import = CSVnew();

    char *namecpy = _strdup(name);
    if(strchr(namecpy, '.')) *(strchr(namecpy, '.')) = '\0'; 

    strcpy(import->list->name, namecpy);

    import->fd = fopen(name, "r");
    if(!import->fd){ // nos vamos
        free(import);
        strcat(buf, COLOR_RED "Error:  Archivo no existe\n"
                COLOR_RESET);
        return;
    }

    populateList(import, mapNames, mapTypes, mapBrands);
    fclose(import->fd);
}

void CSVexport(Map *map, char *name){
    remove(name);
    FILE* file = fopen(name, "w");
    if (!file) {
        printf("Error creando el archivo %s\n", name);
    }
    
    for(Item *item = firstMap(map); item != NULL; item=nextMap(map)) {
        fprintf(file, "%s,", item->name);
        fprintf(file, "%s,", item->brand);
        fprintf(file, "%s,", item->type);
        fprintf(file, "%d", item->stock);
        fprintf(file, "%d", item->price);

        fprintf(file, "\n");

    }
    
    fclose(file);
}

void CSVcreate(CSV *csv){
    csv->fd = NULL;
    csv->list = listCreate(); // Almacena Song*
}

CSV *CSVnew() {
    CSV* csv = (CSV*)malloc(sizeof(CSV));
    if(!csv) { 
        strcpy(buf, "Error creando CSV\n");
        exit(1);
    }
    CSVcreate(csv);
    return csv;
}
void listaImportarArchivo(Map* mapNames, Map* mapTypes, Map* mapBrands) {
    char archivo[30];
    printf("Ingresa el nombre del archivo a importar: ");
    fflush(stdin);
    scanf("%[^\n]*s", archivo);
    getchar();
    CSVimport(archivo, mapNames, mapTypes, mapBrands);
}

void listaExportarArchivo(Map *map) {
    char fileName[60];

    printf("Ingrese el nombre del archivo a exportar: ");
    fflush(stdin);
    scanf("%[^\n]*s", fileName);
    getchar();
    strcat(fileName,".csv");

    FILE *file = fopen(fileName, "w");

    for(Item *item =firstMap(map); 
            item != NULL;
            item = nextMap(map)) {

        fprintf(file, "%s,", item->name);
        fprintf(file, "%s,", item->brand);
        fprintf(file, "%s,", item->type);
        fprintf(file, "%d,", item->stock);
        fprintf(file, "%d\n", item->price);
    }
    fclose(file);
}
