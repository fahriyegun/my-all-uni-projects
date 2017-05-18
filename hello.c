#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <semaphore.h>  /* Semaphore */


struct data{
	int number;
   	int isPrime;
	int come;
	long which;
};

struct data *list;
int counter =0,until;
pthread_mutex_t mutex;

void *PrimeNumber(void *arg){
	int i,a,count=0,num;
	long id=(long)arg;
	i=0;
	pthread_mutex_lock (&mutex);
  	
	while(i<until-2){
		if(list[i].come==1){
			pthread_mutex_unlock (&mutex);
			continue;
		}
		list[i].which=id;	
		for(a=2;a<=list[i].number/2;a++){
        		if(list[i].number%a==0){
                		 count++;
				pthread_mutex_unlock (&mutex);
            			break;
        		}
		pthread_mutex_unlock (&mutex);
    		}
        	if((count==0 && list[i].number!= 1 || list[i].number==2) && list[i].number!=0){
			list[i].isPrime=1;
			pthread_mutex_unlock (&mutex);
			//printf("%d %ld\n",list[i].number,list[i].which);
		}
		count=0;
		i++;
		pthread_mutex_unlock (&mutex);
//sleep(1); 
	}
   pthread_exit(NULL);
}



int main(int argc, char *argv[]){
	long t;
	int rc, numT=2;
	char filename[10];
	FILE *fp;
	if(argc==5){
		if(strcmp(argv[1],"-n")==0 && strcmp(argv[3],"-o")==0){
			until = atoi(argv[2]);
			strcpy(filename,argv[4]);
			}else{
			printf("invalid instruction.(ie: -n 100 -o outputfilename)\n");	
			exit(1);	
		}
	}else if(argc==7){
		if(strcmp(argv[1],"-n")==0 && strcmp(argv[3],"-t")==0 && strcmp(argv[5],"-o")==0){
			until = atoi(argv[2]);
			numT = atoi(argv[4]);
			strcpy(filename,argv[6]);
		}else{
			printf("invalid instruction.(ie: -n 100 -t 4 -o outputfilename)\n");
			exit(1);		
		}
	
	}else{
		printf("There is not enough arguman!!\n");
		exit(0);	
	}
	fp=fopen(filename,"w");		
	if(fp == NULL)
    		exit(-1);

	pthread_t threads[numT];
	list = malloc(sizeof(struct data)*(until+1));

	for(t=0; t<until-2;t++){
		list[t].number=t+2;//arrayde tuttuk bakılacak tüm sayıları
		list[t].isPrime=0;
		list[t].come=0;
		list[t].which =0;
		//printf("number:%d, isPrime:%d, come:%d,which:%d\n",list[t].number,list[t].isPrime,list[t].come,list[t].which);
	}

	pthread_mutex_init(&mutex, NULL);
		for(t=0;t<numT;t++){
			pthread_create(&threads[t], NULL,& PrimeNumber, (void *)t);
  		}
		for(t=0; t<numT; t++) {
      			pthread_join(threads[t], NULL);
		}

 		for(int i=0;i<=until-2;i++){
			if(list[i].isPrime==1){
				printf("Thread %d Prime %d\n",list[i].which,list[i].number);
				fprintf(fp,"Thread %d Prime %d\n",list[i].which,list[i].number);
			}else{
			//printf("Thread %d NOT Prime %d\n",list[i].which,list[i].number);
			}
		}
	fclose(fp);
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
	
}
