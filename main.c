#include "moviesADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DIV ";\n\r\t"
#define GDIV ","
#define MAX 500
#define BLOCK 20

enum  dataset {TYPE = 0, TITLE, STARTY, ENDY, GENRE, RATING, VOTES, TIME};

//Implementamos una funcion que luego de leer el string con los distintos generos (separados por ,), devuelve un vector,
//donde en cada posicion almacena un genero, y deja su dimension en un parametro de salida
char ** genreVec(char * s, unsigned int * dim){
    char token[MAX];
    char * line;
    char ** vec = malloc(sizeof(char *) * BLOCK);
    unsigned int i;

    while(fgets(token, MAX, s) != NULL){
        line = strtok(token, GDIV);
        if(i % BLOCK == 0)
            vec = realloc(vec, BLOCK + i + 1);
        vec[i++] = line;
    }
    vec = realloc(vec, i + 1);
    *dim = i;
    return vec;
}

void readData(moviesADT m, FILE * data){
    char token[MAX];
    char * line;

    //Hay que saltear la primera linea
    fgets(token, MAX, data);
    int i;
    int year, votes;
    double rating;
    char type[50];
    char title[50];
    char genre[50];


    while (fgets(token, MAX, data) != NULL){
        line = strtok(token, DIV);
        for (i = 0; i <= VOTES; i++){
            switch (i){
                case TYPE: strncpy(type, line, strlen(line));
                break;
                case TITLE: strncpy(title, line, strlen(line));
                break;
                case STARTY: year = atoi(line);
                break;
                case GENRE: strncpy(genre, line, strlen(line));
                break;
                case RATING: rating = atof(line);
                break;
                case VOTES: votes = atoi(line);
                break;
                default: break;
            }
            line = strtok(NULL, DIV);
        }
        unsigned int dim = 0;
        char ** vec = genreVec(genre, &dim);

        int added = addMovieSeries(movieList, vec, dim, year, type, title, votes, rating);

        //Se chequea que se haya agregado correctamente
        if (!added) {
            fprintf(stderr, "Error adding data\n");
            return;
        }
    }  
}

void solQ1(moviesADT m){
    toBeginYear(m);

    FILE * f1 = fopen("./query1.csv", "w");
    fprintf(f1, "year;films;series\n");

    unsigned int year, films, series;

    while(hasNextYear(m)){
        year = nextYear(m, &films, &series);
        fprintf(f1, "%d;%d;%d\n", year, films, series);
    }

    fclose(f1);
}

void solQ2(moviesADT m){
    toBeginYear(m);

    FILE * f2 = fopen("./query2.csv", "w");
    fprintf(f1, "year;genre;films\n");

    unsigned int year, filmsYear, series, filmsGenre;

    while(hasNextYear(m)){
        year = nextYear(m, &filmsYear, &series);
        toBeginGenre(m, year);
        char * s = nextGenre(m, &filmsGenre);
        fprintf(f2, "%d;%c;%d\n", year, s, filmsGenre);
    }

    fclose(f2);
}

void solQ3(moviesADT m){
    toBeginYear(m);

    FILE * f3 = fopen("./query3.csv", "w");
    fprintf(f3, "startYear;film;votesFilm;ratingFilm;serie;votesSerie;ratingSerie\n");

    unsigned int year, votesF, votesS, films, series;
    double ratingF, ratingS;
    char * s1; //la pelicula mas votada
    char * s2; //la serie mas votada

    while(hasNextYear(m)){
        year = nextYear(m, &films, &series);
        mostVoted(m, year, &s1, &votesF, &ratingF, &s2, &votesS, &ratingS);  
        fprintf(f3, "%d;%c;%d;%g;%c;%d;%g\n", year, s1, votesF, ratingF, s2, votesS, ratingS);
    }

    fclose(f3);
}

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

    //Con los datos del archivo .csv completamos la lista
    readData(movieList, movieSeries);
    
    //Una vez leido el archivo, ejecutamos los queries
    solQ1(movieList);
    solQ2(movieList);
    solQ3(movieList);
    
    //Se libera la memoria utilizada
    freeMoviesADT(movieList);
    
    return 0;
}
