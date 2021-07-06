#ifndef moviesADT_H
#define moviesADT_H

typedef struct moviesCDT * moviesADT;


/*Crea un nuevo TAD vacio*/
moviesADT newMoviesADT();

/*Agrega la pelicula o serie */
void addMovieSeries(moviesADT m, char * genre, unsigned int year, char * data, char * title, unsigned int votes, double rating);

void toBeginYear(moviesADT m);

unsigned int hasNextYear(moviesADT m);

unsigned int nextYear(moviesADT m, unsigned int *movies, unsigned int *series);

void toBeginGenre(moviesADT m, unsigned int year);

unsigned int hasNextGenre(moviesADT m);

char * nextGenre(moviesADT m, unsigned int *movies);

void mostVoted(moviesADT m, unsigned int year, char *movieTitle, unsigned int *movieVotes, double *movieRating, char *serieTitle, unsigned int *serieVotes, double *serieRating);

/*Libera todos los recursos reservados por el TAD*/
void freeMoviesADT(moviesADT m);

#endif
