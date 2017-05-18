#include <stdio.h>
#include <time.h>
#include <sys/time.h>
main(){
	struct timeval start,end;
	gettimeofday(&start,NULL);
    FILE *myFile;
    myFile = fopen("random.txt", "r");
    //myFile = fopen("ascending.txt", "r");
    //myFile = fopen("descending.txt", "r");
    int size=250000;
    int numberArray[size];
    int i,c,d,t;
	for (i = 0; i <size; i++){
        fscanf(myFile, "%d", &numberArray[i]);
    }
    //fclose(myFile);
	printf("before insertion sort:\n");
   // for (i = 0; i < 50000; i++){
      //  printf("-%d", numberArray[i]);
    //}
	for (c = 1 ; c <= (size-1); c++) {
    d = c;
    while ( d > 0 && numberArray[d] < numberArray[d-1]) {
      t          = numberArray[d];
      numberArray[d]   = numberArray[d-1];
      numberArray[d-1] = t;
      d--;
    }
  }
 	printf("\nSorted list in ascending order:\n");
  //for (c = 0; c <= 49999; c++) {
    //printf("-%d", numberArray[c]);
  //}
  	gettimeofday(&end,NULL);
	printf("\n\nThe loop used %f seconds.\n", (double)(end.tv_usec - start.tv_usec)/1000000+(double)(end.tv_sec-start.tv_sec));
}
