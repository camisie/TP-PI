# TRABAJO PRACTICO FINAL

El programa consiste en procesar los datos de un archivo que contiene informacion de series y peliculas (provisto por la Cátedra) y realizar un ejecutable bajo ciertos criterios. En nuestro caso, debíamos responder a las siguientes queries:

1. Cantidad de peliculas y series por año
2. Cantidad de peliculas por año y por género
3. La pelicula y la serie con más votos de cada año


## Requerimientos previos a arrancar:

* Contar con una terminal para poder ejecutar el programa
* Asegurarse de que los siguientes archivos se encuentren descargados y en un mismo directorio:
    * imdbv3.csv
    * moviesADT.h
    * moviesADT.c
    * main.c
    * makefile
    

## Compilación

Ubicándose en el directorio previamente mencionado, ejecutar el siguiente comando en la terminal:
    `> make all `
Esto crea un ejecutable de nombre *imdb*.

En caso de querer eliminar el archivo ejecutable creado, se debe ingresar el siguiente comando:
    `> make clean`


## Ejecución

En la terminal, se ejecuta el siguiente comando:
    `./imdb imdbv3.csv`
en el mismo directorio en el que se viene trabajando y se utiliza el archivo imdbv3.csv como único argumento. En caso de utilizarse otro archivo de datos con las características requeridas, se inserta ese como argumento. 
    
**A tener en cuenta:** Si el archivo .csv no se encuentra en el mismo directorio que el ejecutable, debe invocarse agregando el path correspondiente. 


## Después de ejecutar

En la salida estándar se podrá leer el siguiente mensaje:
    `The queries were created successfully!`

Además, se habrán creado en el mismo directorio donde se ejecutó el programa los siguientes archivos:
* query1.csv
* query2.csv
* query3.csv

los cuales contendrán la información correspondiente a las consignas asignadas por la Cátedra. 

**Nota:** En caso de que en el directorio en el cual se está trabajando ya existan archivos con estos nombres, al ejecutar el programa los mismos serán sobreescritos con los nuevos archivos.
