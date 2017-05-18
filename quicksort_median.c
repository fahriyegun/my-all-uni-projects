  #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <limits.h>
    #include <sys/time.h>
    #define SIZE 50000
 
    void swap(int *x, int *y)
    {
    	int temp = *x;
    	*x = *y;
    	*y = temp;
    	return ;
    }
 
 int find_pivot(int a[], int left,int right){
 	int middle= (right+left)/2;
 	int temp[3],c,d,t;
 		temp[0]=a[left];
 		temp[1]=a[middle];
 		temp[2]=a[right];
 		
		for (c = 1 ; c <= 2; c++) {
    		d = c;
    		while ( d > 0 && temp[d] < temp[d-1]) {
     		t = temp[d];
      		temp[d]   = temp[d-1];
     	    temp[d-1] = t;
      		d--;
    }
  }
  	if(temp[1]==a[left]){
  		return left;
  	}
  	else if(temp[1]==a[middle]){
  		return middle;
  	}
  	else if(temp[1]==a[right]){
  		return right;
  	}
    	
	}
	
    int median3(int a[], int left, int right)//Uses median of three partitioning technique
    {
    	int center =find_pivot(a,left,right);
    	if (a[center] < a[left]) 
    		swap(&a[left],&a[center]);
    	if (a[right] < a[left])
    		swap(&a[left],&a[right]);
    	if (a[right]< a[center])
    		swap(&a[center],&a[right]);
 
    	swap(&a[center], &a[right - 1]);//since the largest is already in the right.
    	return a[right - 1];
    }
    
    
 
    void quicksort(int a[], int left, int right)
    {
      if (left < right) {
    	int pivot = median3(a,left,right);
        if (left == right - 1) return;
    	int i = left;
    	int j = right - 1;
    	for ( ; ;) {
    		while(a[++i]<pivot) {} 
    		while(pivot<a[--j]) {} 
    		if ( i < j)
    			swap(&a[i],&a[j]);
    		else
    			break ;
    	}
    	swap(&a[i],& a[right -1]);
    	quicksort(a,left,i-1);
    	quicksort(a,i+1,right);
      }
    	return ;
    }
 
    int main(int argc, char* argv[]){	
    	struct timeval start,end;
		gettimeofday(&start,NULL);
    	FILE *myFile;
    	//myFile = fopen("random.txt", "r");
    	myFile = fopen("ascending.txt", "r");
    	//myFile = fopen("descending.txt", "r");
    	int numberArray[SIZE];
    	int i,c,d,t;
    	
    	for (i = 0; i < SIZE; i++){
        	fscanf(myFile, "%d", &numberArray[i]);
    	}

    	quicksort(numberArray,0,(SIZE-1));
    	
    	//for ( i = 0 ; i < SIZE ; i++)
    		//printf("%d\n",numberArray[i]);
    		
    		gettimeofday(&end,NULL);
			printf("\n\nThe loop used %f seconds.\n", (double)(end.tv_usec - start.tv_usec)/1000000+(double)(end.tv_sec-start.tv_sec));
    	return 0;
    }
