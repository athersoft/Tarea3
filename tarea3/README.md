# Como compilar y ejecutar la tarea:

Para compilar es necesario GitBash y la herramienta "make", la cual puede ser instalada en el sig. sitio : [Descargar Make](https://sourceforge.net/projects/ezwinports/files/make-4.3-without-guile-w32-bin.zip/download).
~~Igual puede funcionar en el cmd, pero no cuenta con todas las caracteristicas que quisimos.~~ Agregada función [clrscr()](https://github.com/cykrr/tarea2/blob/d58cdbe62f4982770fefd75eb2d1d2e11775aec7/src/util.c#L26) para permitir
uso del comando especifico de cada sistema operativo.
     
El comando para compilar la tarea es el siguiente
```
make
```

Se pueden compilar los casos de prueba con:
```
make tests/map
make tests/list
make tests/cart
```


# Opciones que funcionan y las que no:

* Importar productos funciona bien, no hay problemas al leer el archivo, además separa los datos según las comas

* Exportar esta listo

* Agregar productos, funciona bien y no hemos encotrado errores

* Buscar por tipo muestra todos los datos correctamente

* Busca por marca también funciona bien

* Buscar por nombre igual que los otros funciona bien

* Mostrar todos los productos funciona sin problemas

* Agregar al carrito funciona, bien y en caso de que el carrito no exista crea otro con el nombre que se había ingresado además de  sumar el total a medida que se van agregando los productos

* Mostrar carritos, funciona bien, y los datos se mantienen separados

* Concretar compra funciona bien

* Eliminar ultimo producto funciona como debería.

  
# Aspectos positivos y a mejorar de cada integrante:
    
* Benjamín: 
     * '+' Liderazgo, mejoró en la división de trabajo

* Bryam: 
     * '+' Buena planificación respecto a la utilización de estructuras de datos
     * '-' Mejorar manejo de código ajeno, y confusión de manejo de punteros en multiples mapas

* Matias: 
     * '+' Mejora en la aplicación de codigo, respecto a la tarea anterior, y mayor autonmia en general
     * '-' Practicar las materias antes que tener que aplicarlas en las tareas (estudiar más), y prestar mayor atención a detalles en el código (sobretodo respecto a la memoria)

* Nestor: 
     * '+' Buena resolución de problemas, y solución de errores
     * '-' La participación en las reuniones de grupo (aunque participa tanto como puede)

# Puntos premio/castigo a cada integrante según el trabajo hecho:

* Benjamin: 1
* Bryam: -1
* Matias: -1
* Nestor: 1
