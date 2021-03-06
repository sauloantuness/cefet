#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 2
#define TAM_FILA 10

int fila[TAM_FILA];
int head = 0;
int turn = 0;
int wants[2] = {0, 0};

void enter(int task){
	int other = task ? 0 : 1;
	wants[task] = 1;
	turn = task;
	while( (turn == task) && wants[other]);
}

void leave(int task){
	wants[task] = 0;
}

void imprime(){
	int i;	
	for (i = 0; i < TAM_FILA; ++i)
		printf("%2d ", fila[(head + i) % TAM_FILA]);

	printf("\n");
}

void *threadBody (void *id){
	int i, novo, velho, n;
	n = 10;

	while(n--){
		sleep((long)id);
		enter( (int) id );
		velho = fila[head];
		novo = rand() % 100;
		fila[head] = novo;
		head = (head + 1) % TAM_FILA;

		printf("thread %02ld: tira %d, poe %d, fila: ", (long)id, velho, novo);
		imprime();

		leave( (int) id );
	}

   pthread_exit (NULL) ;
}

int main (){
	int j;
	head = 0;
	srand(time(NULL));

	for (j = 0; j < TAM_FILA; ++j)
		fila[j] = rand() % 100;

	pthread_t thread [NUM_THREADS] ;
	long i, status ;

	for (i=0; i<NUM_THREADS; i++)
		pthread_create (&thread[i], NULL, threadBody, (void *) i) ;

	pthread_exit (NULL) ;
}