#include "moviesADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DIV ";"

void addData(moviesADT m, char * genre, unsigned int year, char * data, char * title, unsigned int votes, double rating);

int main(int argc, char * argv[]){
    
    //Se verifica la cantidad de argumentos
    if (argc != 2){
        fprintf(stderr, "You must include one file only\n");
        return 1;
    }
    
    //Se valida que se haya ingresado el archivo correcto
    //Utilizamos argv[1] ya que argv[0] tiene la info de como pasan los datos
    if (strstr(argv[1], "imdbv2.csv") == NULL){
        fprintf(stderr, "Wrong file\n");
        return 1;
    }
    //Si el archivo de los queries ya existe, se notifica que hay un error
    if (fopen("query1.csv", "r") != NULL || fopen("query2.csv", "r") != NULL || fopen("query3.csv", "r") != NULL){
        fprintf(stderr, "That file already exists\n");
        return 1;
    }
    
    //Se genera el archivo
    FILE *movieSeries = fopen(argv[1], "r");

    //Se comprueba que el archivo exista y se puede abrir
    if(movieSeries == NULL){
        fprintf(stderr, "File not found\n");
        return 1;
    }
    
    //Se crea un nuevo TAD vacio
    moviesADT movieList = newMoviesADT();

    //Se verifica que haya memoria disponible
    if (movieList == NULL){
        fprintf(stderr, "Not enough memory available\n");
        return 1;
    }
}
