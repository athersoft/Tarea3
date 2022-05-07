#include "map.h"
#include "item.h"
#include <assert.h>
#include <string.h>

/* funcion podria ir en util.h */
int isEqualString(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

void listItems(Map *map);
void showItemNoBuf(Item *item);


int main() {
    Map* mapaNombre = createMap(isEqualString);
    Item lecheColun;
    Item lecheCalo;
    strcpy(lecheColun.name, "Leche 200ml");
    strcpy(lecheCalo.name, "Leche 200ml");
    strcpy(lecheColun.brand, "colun");
    strcpy(lecheCalo.brand, "calo");
    strcpy(lecheColun.type, "lacteo");
    strcpy(lecheCalo.type, "lacteo");
    lecheColun.stock = 2;
    lecheCalo.stock = 3;
    lecheColun.price = 350;
    lecheCalo.price = 375;


    insertMap(mapaNombre, lecheColun.name, &lecheColun);
    insertMap(mapaNombre, lecheCalo.name, &lecheCalo);

    assert(lecheColun.stock == 2);

    printf("Lista principal: \n--------------\n");
    listItems(mapaNombre);

    /* liberamos el mapa para crear otro. Ahora usamos la función addItem */
    
    for(Item *item = firstMap(mapaNombre); item != NULL; item = nextMap(mapaNombre)){
        eraseMap(mapaNombre, item->name);
    }
    free(mapaNombre);

}

void listItems(Map* map) {
    for(Item *item = firstMap(map); item != NULL; item = nextMap(map)) {
        showItemNoBuf(item);
    }
}

void showItemNoBuf(Item *item) {
    printf("Nombre: %s\n", item->name);
    printf("Marca: %s\n", item->brand);
    printf("Tipo: %s\n", item->type);
    printf("Stock: %d\n", item->stock);
    printf("Precio: $%d\n", item->price);
}
