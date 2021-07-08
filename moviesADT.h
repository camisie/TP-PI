#ifndef moviesADT_H
#define moviesADT_H

typedef struct moviesCDT * moviesADT;


//Crea un nuevo TAD vacio
moviesADT newMoviesADT();

//ver si es necesario que este aca
//static void addYear(moviesADT m, unsigned int year){

//Agrega la pelicula o serie
int addMovieSeries(moviesADT m, char ** genre, unsigned int dim, unsigned int year, char * data, char * title, unsigned int votes, double rating);

//Permite iterar por todos los años en orden descendente
void toBeginYear(moviesADT m);

//Retorna 1 si queda un año por recorrer o 0 sino
unsigned int hasNextYear(moviesADT m);

//Retorna el siguiente año, si no hay aborta
//Deja en el parametro movies y series la cantidad de peliculas y series que hubo en ese año
unsigned int nextYear(moviesADT m, unsigned int *movies, unsigned int *series);

//Permite iterar por los generos del año indicado en el parametro year
void toBeginGenre(moviesADT m, unsigned int year);

//Retorna 1 si queda un genero por recorrer, 0 sino
unsigned int hasNextGenre(moviesADT m);

//Retorna el siguiente genero, si no hay aborta. Deja en el parametro de salida movies la cantidad de peliculas que tiene ese genero
char * nextGenre(moviesADT m, unsigned int * movies);

//Recibe un año y retorna el titulo de la pelicula mas votada de ese año.
//Deja en los parametros de salida la cantidad de votos y el rating de esa pelicula.
char * mostVotedMovie(moviesADT m, unsigned int year, unsigned int * movieVotes, double * movieRating);

//Recibe un año y retorna el titulo de la serie mas votada de ese año.
//Deja en los parametros de salida la cantidad de votos y el rating de esa serie.
char * mostVotedSerie(moviesADT m, unsigned int year, unsigned int * serieVotes, double * serieRating);

// //Deja en los parametros de salida los datos de la pelicula y serie mas votadas en el año (indicado en el parametro year)
// void mostVoted(moviesADT m, unsigned int year, char ** movieTitle, unsigned int * movieVotes, double * movieRating, char ** serieTitle, unsigned int * serieVotes, double * serieRating);

//Libera todos los recursos reservados por el TAD
void freeMoviesADT(moviesADT m);

#endif
