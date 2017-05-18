 //pivot is always selected as the first element

#include<stdio.h>
#include <sys/time.h>
#include <time.h>
#define SIZE 5000

void quicksort(int [SIZE],int,int);

int main(){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	FILE *myFile;
    //myFile = fopen("random.txt", "r");
    //myFile = fopen("ascending.txt", "r");
    myFile = fopen("descending.txt", "r");

    //read file into array
    int x[SIZE];
    int i,n=SIZE;

    for (i = 0; i < SIZE; i++)
    {
        fscanf(myFile, "%d", &x[i]);
    }
	printf("before quick sort:\n");
    /*for (i = 0; i < SIZE; i++)
    {
        printf("-%d", x[i]);
    }*/

  quicksort(x,0,(SIZE-1));

  printf("\nSorted elements:\n");
  //for(i=0;i<n;i++)
    //printf(" %d",x[i]);
    
    gettimeofday(&end,NULL);
	printf("\n\nThe loop used %f seconds.\n", (double)(end.tv_usec - start.tv_usec)/1000000+(double)(end.tv_sec-start.tv_sec));

  return 0;
}

void quicksort(int x[SIZE],int first,int last){
    int pivot,j,temp,i;

     if(first<last){
         pivot=first;
         i=first;
         j=last;

         while(i<j){
             while(x[i]<=x[pivot]&&i<last)
                 i++;
             while(x[j]>x[pivot])
                 j--;
             if(i<j){
                 temp=x[i];
                  x[i]=x[j];
                  x[j]=temp;
             }
         }

         temp=x[pivot];
         x[pivot]=x[j];
         x[j]=temp;
         quicksort(x,first,j-1);
         quicksort(x,j+1,last);

    }
}

