/*********************************************************************************************************************
******************************************        FAHRÝYE GÜN       **************************************************
******************************************        150112025         **************************************************
*********************************************************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct node{
	int page, userNo;
	char userType;
	struct node *nextPtr;
};

struct node *qfp= NULL;

//PROTOTYPE OF FUNTCTIONS
void enqueue(char, int, int);
void dequeue();
void display(struct node*);

int main(){
	int i, p, d;
	char c;
	srand(time(NULL));
	
	printf("before queue:\n");
	
	for(i=1; i<51; i++){
		p= 1 + rand()%20;//RANDOM PAGE
		d = rand()%3;//RANDOM USERNO
		switch(d){//CHANGE FROM USERNO TO USERTYPE
			case 0:
				c='P';
				break;
			case 1:
				c='A';
				break;
			case 2:
				c='S';
				break;    		
		}
		printf("(%c,%d) ",c,p,d);
		if(i==10)
		printf("\n");
		if(i==20)
		printf("\n");
		if(i==30)
		printf("\n");
		if(i==40)
		printf("\n");
		enqueue(c,p,d);//APPLY ENQUEUE FUNCTION.
	}
	printf("\n\nafter queue:\n");
	display(qfp);//DISPLAY QUEUE
	
	printf("\n\nDeleted 50 persons in queue...\n");
	int s;
	for(s=0; s<50; s++){
		dequeue();//DEQUEUE LÝST
	}
	display(qfp);
	
	return 0;
}
//////////////////////////////////////////////    ENQUEUE FUNCTION     ////////////////////////////////////////////////////////////////////////////////////
void enqueue(char c, int p, int d){
	struct node *np, *temp, *prev=NULL;
	np = malloc(sizeof(struct node));
	np->userType = c;
	np->page = p;
	
	np->userNo = d;
	np->nextPtr= NULL;
	
	if(qfp==NULL){
		 qfp = np;
		return;
	}else {
		temp = qfp;
		while ((temp != NULL && temp->userNo<=np->userNo )) {
			
			if(temp != NULL && temp->userNo < np->userNo){
				prev=temp;
				temp=temp->nextPtr;
			}
			if(temp != NULL && temp->userNo == np->userNo){
				if(temp->page < np->page){
					//printf("sayfasi ufak\n");
					prev=temp;
					temp=temp->nextPtr;
				}else{
					//printf("sayfasi buyuk\n");
					prev=temp;
					temp=temp->nextPtr;
					//temp=np->nextPtr;
					//np=np->nextPtr;
				}
			}
		}
		
		if (temp!=NULL)
			np->nextPtr=temp;
		if (temp== qfp)
			qfp=np;
		else
			prev->nextPtr=np;
	}
}
////////////////////////////////////////////////    DEQUEUE FUNCTION    //////////////////////////////////////////////////////////////////////////
void dequeue(){
	struct node *np;
	np = qfp;
	if(np==NULL)
		printf("\n\nNo elements in queue...");
	else	
		qfp = qfp->nextPtr;
	free(np);
}

/////////////////////////////////////////////////    DISPLAY FUNCTION     /////////////////////////////////////////////////////////////////////////////
void display (struct node *header){
	struct node *save;
	int i;
    if (header == NULL)
       printf ("\n***List is empty!...***");
    else
    {  save = header;
       while (save != NULL){
       	for(i=1; i<51; i++){
       		printf ("(%c,%d) ",save->userType, save->page);
	   		save = save->nextPtr;
	   		if(i==10)
	   		printf("\n");
	   		if(i==20)
	   		printf("\n");
	   		if(i==30)
	   		printf("\n");
	   		if(i==40)
	   		printf("\n");
       	}
	   }
    }
return;
}


