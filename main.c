#include "moviesADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#define DIV ";\n\r\t"
#define MAX 500

enum  dataset {TYPE = 0, TITLE, STARTY, ENDY, GENRE, RATING, VOTES, TIME};

void readData(moviesADT m, FILE * data){
    char token[MAX];
    char * line;

    //Hay que saltear la primera linea
    fgets(token, MAX, data);
    int i;
    int year, votes;
    double rating;
    char * type;
    char * title;
    char * genre;

    while (fgets(token, MAX, data) != NULL){
        line = strtok(token, DIV);
        for (i = 0; i <= VOTES; i++){
            switch (i){
                case TYPE: type = line;
                break;
                case TITLE: title = line;
                break;
                case STARTY: year = atoi(line);
                break;
                case GENRE: genre = line;
                break;
                case RATING: rating = atof(line);
                break;
                case VOTES: votes = atoi(line);
                break;
                default: break;
            }
            line = strtok(NULL, DIV);
        }

        int added = addMovieSeries(m, genre, year, type, title, votes, rating);

        //Se chequea que se haya agregado correctamente
        if (!added) {
            fprintf(stderr, "Error adding data\n");
            return;
        }

    }  
}

void solQ1(moviesADT m, FILE * f1){
    toBeginYear(m);

    fprintf(f1, "year;films;series\n");

    unsigned int year, films, series;

    while(hasNextYear(m)){
        year = nextYear(m, &films, &series);
        fprintf(f1, "%d;%d;%d\n", year, films, series);
    }
}

void solQ2(moviesADT m, FILE * f2){
    toBeginYear(m);

    fprintf(f2, "year;genre;films\n");

    unsigned int year, filmsYear, series, filmsGenre;

    while(hasNextYear(m)){
        year = nextYear(m, &filmsYear, &series);
        toBeginGenre(m, year);
        while(hasNextGenre(m)){
            char * s = nextGenre(m, &filmsGenre);
            fprintf(f2, "%d;%s;%d\n", year, s, filmsGenre);
        }
    }
}

void solQ3(moviesADT m, FILE * f3){
    toBeginYear(m);

    fprintf(f3, "startYear;film;votesFilm;ratingFilm;serie;votesSerie;ratingSerie\n");

    unsigned int year, votesF, votesS, films, series;
    double ratingF, ratingS;

    while(hasNextYear(m)){
        year = nextYear(m, &films, &series);
        char * s1 = mostVotedMovie(m, year, &votesF, &ratingF);
        char * s2 = mostVotedSerie(m, year, &votesS, &ratingS);
        fprintf(f3, "%d;%s;%d;%g;%s;%d;%g\n", year, s1, votesF, ratingF, s2, votesS, ratingS);
    }
}

int main(int argc, char * argv[]){
    
    //Se verifica la cantidad de argumentos
    if (argc != 2){
        fprintf(stderr, "You must include one file only\n");
        return 1;
    }
    
    //Se genera el archivo
    FILE * movieSeries = fopen(argv[1], "r");

    //Se abren los archivos csv
    FILE * f1 = fopen("./query1.csv", "w");
    FILE * f2 = fopen("./query2.csv", "w");
    FILE * f3 = fopen("./query3.csv", "w");

    //Se comprueba que el archivo exista y se puede abrir
    if(movieSeries == NULL){
        fprintf(stderr, "File not found or cannot access file\n");
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
    solQ1(movieList, f1);
    solQ2(movieList, f2);
    solQ3(movieList, f3);
    
    //Se libera la memoria utilizada
    freeMoviesADT(movieList);

    fclose(f1);
    fclose(f2);
    fclose(f3);

    printf("The queries were created successfully!\n");
    
    return 0;
}
