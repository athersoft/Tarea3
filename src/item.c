#include "item.h"
#include "map.h"
#include "util.h"

//Crea un elemento de tipo Item
Item *createItem(){
	Item *item = (Item *)malloc(sizeof(Item));
        strcpy(item->name, "");
        strcpy(item->brand, "");
        strcpy(item->type, "");
        item -> stock = 0;
        item -> price = 0;
	return item;
}

//Agrega un nuevo producto o stock a un producto existente
int addItem(Map* mapNames, Map* mapTypes, Map* mapBrands){

    Item *item = createItem();


    fflush(stdin);
    printf("Nombre del producto: ");
    scanf("%[^\n]*s", item->name);
    getchar();

    printf("\nMarca: ");
    scanf("%[^\n]*s", item->brand);
    getchar();

    printf("\nTipo de producto: ");
    scanf("%[^\n]*s", item->type);
    getchar();

    printf("\nCantidad: ");
    scanf("%d", &item->stock);
    getchar();

    printf("\nPrecio: ");
    scanf("%d", &item->price);
    getchar();
    int found = 0;

    //Se guarda el item en los 3 mapas
    if(searchMap(mapNames,item -> name) == NULL) { 
        insertMap(mapNames, item->name, item);
        insertMapList(mapTypes, item -> type, item);
        insertMapList(mapBrands, item -> brand, item);
    } else{ 
        //comprobar que el producto sea 100% igual(nombre,marca,brand)
        Item *aux = searchMap(mapNames,item -> name);
        if (strcmp(item->brand, aux->brand) != 0 ||
                strcmp(item->type, aux->type) != 0) {
                strcat(buf, COLOR_RED"Error: El producto no coincide con\n"
                        "marca o tipo de otro producto del mismo "
                        "nombre"COLOR_RESET);

                return 1;
        }
        aux->stock += item->stock;
        found++;
    }

    putchar('\n');


    return found;

}

//Interta una lista a un mapa
void insertMapList(Map * map, char *key, Item * item){
    List *aux = searchMap(map,key);
    if(aux == NULL){
        aux = listCreate();
        insertMap(map, key, aux);
    }
    listPushBack(aux,item);
}

//Función para buscar un item usando como clave el nombre
void findItem(Map* map, void * key) {

    char name[60];
    printf("Nombre del producto: ");
    scanf("%[^\n]*s",name);
    getchar();

    Item *buscado = searchMap(map,name);
    if(buscado == NULL){
        printf("Producto no encontrado");
    }else{
        showItem(buscado);
    }
    return;
}


//Muestra los detalles de un producto
void showItem(Item *item){
    strcat(buf, "  Nombre: " );
    strcat(buf,item->name);
    strcat(buf, "\n    Brand: " );
    strcat(buf,item->brand);
    strcat(buf, "\n    Type: " );
    strcat(buf,item->type);
    char numero[10];
    sprintf(numero, "%d",item->stock);
    strcat(buf, "\n    Stock: " );
    strcat(buf, numero);
    strcat(buf, "\n    Precio: " );
    sprintf(numero, "%d",item->price);
    strcat(buf, numero);
    strcat(buf, "\n\n");
}

//Muestra todos los productos
void showItems(Map *nameMap) {
    int itemCount = 0;
    if(firstMap(nameMap)) {
        strcat(buf, "Lista de productos:\n");
    }
    for(Item *item = firstMap(nameMap);
            item != NULL; 
            item = nextMap(nameMap), itemCount++) 
    {
        showItem(item);
    }

    if(!itemCount) {
        strcat(buf, COLOR_RED 
                "Error!: No hay productos agregados\n"
                COLOR_RESET);
    }

}

//Muestra los productos de determinada marca
void showItemsByBrand(Map* mapBrands) {
    char brand[30];
    printf("Ingrese la marca a mostrar: ");
    scanf("%[^\n]*s", brand);
    getchar();
    List *list = searchMap(mapBrands, brand);
    if(!list) {
        strcat(buf, COLOR_RED "Error: no existe la marca ");
        strcat(buf, brand);
        strcat(buf, COLOR_RESET);
        strcat(buf, "\n");
    } else if (list) {
        strcat(buf, "Mostrando lista de productos de la marca ");
        strcat(buf, brand);
        strcat(buf, "\n");
        showList(list);
    }
}

//Muestra los productos de determinado tipo
void showItemsByType(Map* mapTypes) {
    char type[30];
    printf("Ingrese tipo de producto a mostrar: ");
    scanf("%[^\n]*s", type);
    getchar();
    List *list = searchMap(mapTypes, type);
    if(!list) {
        strcat(buf, COLOR_RED "Error: no existe el tipo ");
        strcat(buf, type);
        strcat(buf, COLOR_RESET);
        strcat(buf, "\n");
    } else if (list) {
        strcat(buf, "Mostrando lista de productos del tipo ");
        strcat(buf, type);
        strcat(buf, "\n");
        showList(list);
    }
}

//Funcion para mostrar una lista
void showList(List *list) {
    for(Item *item = listFirst(list);
            item != NULL; 
            item = listNext(list) ){
        showItem(item);
    }
}

//Busca un item
void searchItem(Map *map) {
    char nombre[60];
    printf("Ingrese nombre del producto: ");
    fflush(stdin);
    scanf("%[^\n]*s", nombre);
    getchar();
    Item *aux = searchMap(map, nombre);
    if(!aux) {
        strcat(buf, COLOR_RED "Error: No existe el producto\n"
                COLOR_RESET);
        return;
    }
    strcat(buf, "\n");
    showItem(aux);
}
