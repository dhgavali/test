// Reader Writer 
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define R 5
#define W 5
int readcount,writecount;
sem_t y,z;
pthread_mutex_t x;
sem_t wsem,rsem;
int s=5;

void *reader1(void *a);
void *writer1(void *a);
void *reader2(void *a);
void *writer2(void *a);

int main(){
	int i,op;
	pthread_t thread_read[R],thread_write[W];
	pthread_mutex_init(&x,NULL);
	sem_init(&wsem,0,1);
	sem_init(&y,0,1);
	sem_init(&rsem,0,1);
	sem_init(&z,0,1);
	
	do{
		printf("MENU:-\n 1.READER IS PRIORITY\n2.WRITER IS PRIORITY\n3.EXIT\n");
		scanf("%d",&op);

		switch(op){
			case 1: readcount=0;
				for(i=0;i<W;i++){
					pthread_create(&thread_write[i],NULL, *writer1,(void *)i);
				}
				for(i=0;i<R;i++){
					pthread_create(&thread_read[i],NULL, *reader1, (void *)i);
				}
				for(i=0;i<W;i++){
					pthread_join(thread_write[i],NULL);
				}
				for(i=0;i<R;i++){
					pthread_join(thread_read[i],NULL);
				}
				break;
			case 2: readcount=0;
				writecount=0;
				for(i=0;i<W;i++){
                                        pthread_create(&thread_write[i],NULL, *writer2,(void *)i);
                                }
                                for(i=0;i<R;i++){
                                        pthread_create(&thread_read[i],NULL, *reader2, (void *)i);
                                }
                                for(i=0;i<W;i++){
                                        pthread_join(thread_write[i],NULL);
                                }
                                for(i=0;i<R;i++){
                                        pthread_join(thread_read[i],NULL);
                                }
                                break;
			case 3:
				break;
		}
	}while(op!=3);
}
void *reader1(void *a){
	int r= (int)a;
	int i=0;
	while(i<5){
		pthread_mutex_lock(&x);
		readcount++;
		if(readcount == 1)
			sem_wait(&wsem);
		pthread_mutex_unlock(&x);
		printf("\t\tREADER %d IS READING:- %d \n",r,s);
		pthread_mutex_lock(&x);
		readcount--;
		if(readcount ==0)
			sem_post(&wsem);
		pthread_mutex_unlock(&x);
		sleep(rand() % 10);
		i++;
	}
}

void *writer1(void *a){
	int w= (int)a;
	int i=0;
	while(i<2){
		sem_wait(&wsem);
		s+=5;
		printf("WRITER %d IS WRITING: %d \n",w,s);
		sem_post(&wsem);
		sleep(rand() % 10);
		i++;
	}
}
void *reader2(void *a){

	int i=0;
	int r=(int)a;
	while(i<5){
		sem_wait(&z);
		sem_wait(&rsem);
		pthread_mutex_lock(&x);
		readcount++;
		if(readcount == 1)
			sem_wait(&wsem);
		pthread_mutex_unlock(&x);
		sem_post(&rsem);
		sem_post(&z);
		printf("\t\t READER %d IS READING:%d",r,s);
		pthread_mutex_lock(&x);
		readcount--;
		if(readcount == 0)
			sem_post(&wsem);
		pthread_mutex_unlock(&x);
		sleep(rand() % 10);
		i++;
	}
}

void *writer2(void *a){
	int i=0;
	int w=(int)a;
	while(i<2){
		sem_wait(&y);
		writecount++;
		if(writecount == 1)
			sem_wait(&rsem);
		sem_post(&y);
		sem_wait(&wsem);
		s+=10;
		printf("WRITER %d IS WRITING: %d",w,s);
		sem_post(&wsem);
		sem_wait(&y);
		writecount--;
		if(writecount==0)
			sem_post(&rsem);
		sem_post(&y);
		sleep(rand() % 10);
		i++;
	}
}


/*
MENU:-
 1.READER IS PRIORITY
2.WRITER IS PRIORITY
3.EXIT
1
WRITER 0 IS WRITING: 10 
WRITER 1 IS WRITING: 15 
WRITER 4 IS WRITING: 20 
		READER 0 IS READING:- 20 
		READER 1 IS READING:- 20 
WRITER 2 IS WRITING: 25 
		READER 2 IS READING:- 25 
		READER 3 IS READING:- 25 
WRITER 3 IS WRITING: 30 
		READER 4 IS READING:- 30 
		READER 4 IS READING:- 30 
		READER 3 IS READING:- 30 
WRITER 0 IS WRITING: 35 
		READER 1 IS READING:- 35 
		READER 4 IS READING:- 35 
		READER 0 IS READING:- 35 
WRITER 2 IS WRITING: 40 
		READER 2 IS READING:- 40 
WRITER 1 IS WRITING: 45 
		READER 4 IS READING:- 45 
WRITER 4 IS WRITING: 50 
WRITER 3 IS WRITING: 55 
		READER 3 IS READING:- 55 
		READER 0 IS READING:- 55 
		READER 1 IS READING:- 55 
		READER 2 IS READING:- 55 
		READER 2 IS READING:- 55 
		READER 4 IS READING:- 55 
		READER 1 IS READING:- 55 
		READER 2 IS READING:- 55 
		READER 3 IS READING:- 55 
		READER 0 IS READING:- 55 
		READER 1 IS READING:- 55 
		READER 0 IS READING:- 55 
		READER 3 IS READING:- 55 
MENU:-
 1.READER IS PRIORITY
2.WRITER IS PRIORITY
3.EXIT
3
*/
