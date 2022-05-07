#ifndef CSV_H
#define CSV_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "util.h"
#include "map.h"


typedef struct {
    FILE *fd;
    List *list;
}CSV;

/*  Importar los datos de los productos desde un 
 *  archivo CSV (char* nombre_archivo):
 *  El usuario ingresa el nombre del
 *  archivo y la aplicación carga 
 *  todas la información.
 */
void CSVimport(char *fileName, Map* mapNames, Map* mapTypes, Map* mapBrands);

/*  Exportar información de productos
 *  CSV(char* nombre_archivo):
 *  La aplicación exporta la información de productos
 *  y sus datos a un archivo csv indicado
 *  por el usuario.
 */
void CSVexport(Map *map, char *name);

void CSVcreate(CSV *csv);

// Menú interactivo
void listaImportarArchivo(Map* mapNames, Map* mapTypes, Map* mapBrands);

void listaExportarArchivo(Map* mapNames);

CSV *CSVnew();
#endif
