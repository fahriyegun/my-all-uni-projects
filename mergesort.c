#include<stdio.h>
#include <time.h>
#include <sys/time.h>
#define SIZE 10000

void mergeSort(int arr[],int low,int mid,int high);
void partition(int arr[],int low,int high);

int main(){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	FILE *myFile;
    //myFile = fopen("random.txt", "r");
    myFile = fopen("ascending.txt", "r");
    //myFile = fopen("descending.txt", "r");
   
    int merge[SIZE];
    int i,n=SIZE;
    
	//read file into array
    for (i = 0; i < SIZE; i++){
        fscanf(myFile, "%d", &merge[i]);
    }

	printf("before merge sort:\n");
    //for (i = 0; i < 300000; i++){
      //  printf("-%d", merge[i]);
    //}
	partition(merge,0,(SIZE-1));

    printf("\nAfter merge sorting elements are:\n ");
    /*for(i=0;i<n;i++){
         //printf("-%d",merge[i]);
    }*/
	gettimeofday(&end,NULL);
	printf("\n\nThe loop used %f seconds.\n", (double)(end.tv_usec - start.tv_usec)/1000000+(double)(end.tv_sec-start.tv_sec));
   return 0;
}

void partition(int arr[],int low,int high){

    int mid;

    if(low<high){
         mid=(low+high)/2;
         partition(arr,low,mid);
         partition(arr,mid+1,high);
         mergeSort(arr,low,mid,high);
    }
}

void mergeSort(int arr[],int low,int mid,int high){

    int i,m,k,l,temp[SIZE];

    l=low;
    i=low;
    m=mid+1;

    while((l<=mid)&&(m<=high)){

         if(arr[l]<=arr[m]){
             temp[i]=arr[l];
             l++;
         }
         else{
             temp[i]=arr[m];
             m++;
         }
         i++;
    }

    if(l>mid){
         for(k=m;k<=high;k++){
             temp[i]=arr[k];
             i++;
         }
    }
    else{
         for(k=l;k<=mid;k++){
             temp[i]=arr[k];
             i++;
         }
    }
   
    for(k=low;k<=high;k++){
         arr[k]=temp[k];
    }
    

}

