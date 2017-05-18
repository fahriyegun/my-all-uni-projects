#include <stdio.h> // printf()
#include <stdlib.h> // exit()
#include <dirent.h> // directory header
#include <string.h> //strcpy()

DIR *dir;
struct dirent *ent;
double sum=0;
int counter=-2;
struct review{
	int id;
	int length;
	char text[50];
	int polarity;
	struct review *next;
}*start;
struct score{
	double scoreNumber;
	int totalNumberOfReviews;
	struct score *nextScore;
	struct review *nextReview;
}*first, *deneme;	

//prototype of functions
int list();
void addScore(double);
void display();
int control(int);
int controlID(struct review *, int);
void addReview(double,int,char[],int,int);
double average();
void sil(double,double);
int menu();
void polarity(int);
void particularWord(char[]);

int main(){
	list();
	menu();
}

int menu(){
	int choice,totalReview,cntrl, cntrl2,id,polarity,length;
	double score,starting,ending;
	char text[160];
	printf("\n========================================================================");
	printf("\n1. Add a new review-score.");
	printf("\n2. Add a new review into a review-score.");
	printf("\n3.Calculate the average score of all of the reviews.");
	printf("\n4. Show the review id s and the total number of them in a specific polarity");
	printf("\n5. List the id s of reviews which have a particular word.");
	printf("\n6. Remove the reviews between in a specific score-scope.");
	printf("\n7. Show all score numbers and their reviews");
	printf("\n8. Exit");
	printf("\n========================================================================");
	printf("\nEnter your choice:");
	scanf("%d", &choice);
	fflush(stdin);
	
	switch (choice){
    case 1:
    	printf("\nEnter the score:");
		scanf("%lf", &score);		
		printf("\nEnter the number of total reviews:");
		scanf("%d", &totalReview);
		addScore(score);
		printf("SCORE IS ADDED!\n");
		//printf("score:%0.1lf - total number of review:%d",score,totalReview);	
    	display();
    	menu();
    	break;
    case 2:
    	printf("\nEnter the score:");
    	scanf("%lf", &score);
    	cntrl=control(score);
    	if(cntrl==0){//controlling score!
    	menu();//if there is not this score in linked,
    	break;//go to menu list.
    	}
    	else if(cntrl==1){
    	printf("\nEnter the id:");
    	scanf("%d", &id);
    	printf("\nthe review:");
    	scanf("%s", &text);
    	printf("\nthe length:");
    	scanf("%d",&length);
    	printf("\npolarity:(for pros=1, pros&cons=0, cons=-1):");
    	scanf("%d",&polarity);
    	addReview(score,id,text,length,polarity);
    	}
      break;
    case 3:
    	printf("the average score of all of the reviews: %0.1lf\n",average());
    	menu();
      break;
    case 4:
    	printf("\nShow that polarity.Enter the polarity:");
    	scanf("%d", &polarity);
    	//void polarity(polarity);
      break;
    case 5:
	    printf("\n\tEnter the word for search:");
	    scanf("%s",&text);
	    //particularWord(text);
      break;
    case 6:
    	printf("Enter the starting score to remove:");
    	scanf("%lf", &starting);
    	printf("Enter the ending score to remove:");
    	scanf("%lf", &ending);
    	sil(starting,ending);
    	printf("REMOVED!!");
    	display();
    	menu();
      break; 
	case 7:
		display();
    	menu();
      break;              
	case 8:
    	printf("\nClosing...");
        exit(0);
      break;        	
	default:
	printf("**Invalid Input.**\n");
	menu();
	return 0;

}
	
}

int list(){
	if ((dir = opendir ("C:\ReviewsAboutVideoAndTelevisions/home/std/ReviewsAboutVideoAndTelevisions"))!= NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			char *p,*n;
			double x;
			int y;
			p=strtok(ent->d_name,"_");
			counter++;
	   	 	n=p;
	    	p=strtok(NULL,".txt");
	    	x=atof(n);//converts the str to floating(type double) -> score
	    	sum=sum+x;
			y=atoi(p);//converts the str to integer ->id
	
			        
     		if(y!=0){
     			//printf("\nscore:%0.1f - id:%d",x,y);
     			addScore(x);
     		 }
        }
        closedir (dir);
	} else {
  		perror ("");/* could not open directory */
  		return EXIT_FAILURE;
	}

	return 0;
}

void addReview(double score,int id,char text[], int length,int polarity){
	struct score *newScore,*tempScore=NULL,*prevScore;
	newScore=malloc(sizeof(struct score));
	newScore->scoreNumber=score;
	newScore->nextScore=NULL;
	struct review *newReview,*tempReview=NULL,*prevReview;
	newReview=malloc(sizeof(struct review));
	newReview->id=id;
	newReview->length=length, newReview->polarity=polarity;
	newReview->next=NULL;
	
		tempScore=first;
//	while ( tempScore->scoreNumber==score){
//		printf("sfd");
//		prevScore=tempScore;
//		tempScore=tempScore->nextScore;
//		tempReview=tempScore->nextReview;
//	}
	if(tempReview==NULL || tempReview->id!=id){
			printf("INVALID ID.\nPLEASE TRY AGAIN.\n");
			menu();
	}
	else if(tempReview!=NULL && tempReview->id==id){
		printf("VALID ID");
		strcpy(tempReview->text,text);
		tempReview->length=newReview->length;
		tempReview->polarity=newReview->polarity;
		prevReview=tempReview;
		tempReview=tempReview->next;
		display();
		}
		if(tempReview!=NULL)
		newReview->next=tempReview;
		else
		prevReview->next=newReview;

	}

//void addReview(double score, int id,char text[], int length,int polarity){
//	struct score *currentScore;
//	currentScore=first;
//	int x=0;
//	while(currentScore!=NULL){
//		if(currentScore->scoreNumber==score){
//			x=1;
//			break;
//		}
//		currentScore=currentScore->nextScore;
//	}
//	if(x==0){
//		printf("there is no this score");
//	}
//	else{
//		if(controlID(currentScore->nextReview,id)==0){
//			struct review *newReview;
//			currentScore=first;
//			while(currentScore!=NULL){
//				if(currentScore->scoreNumber==score){
//					newReview=(struct review*)(malloc(sizeof(struct review)));
//					newReview->id=id;
//					strcpy(newReview->text,text);
//					newReview->length=length;
//					newReview->polarity=polarity;
//					newReview->next=NULL;
//					if(currentScore->nextReview==NULL){
//						currentScore->nextReview=newReview;
//						return;
//					}
//					struct review *temp;
//					temp=currentScore->nextReview;
//					struct review *prev;
//					prev=NULL;
//					while(temp!=NULL){
//						prev=temp;
//						temp=temp->next;
//					}
//					newReview->next=prev->next;
//					prev->next=newReview;
//				}
//				currentScore=currentScore->nextScore;
//			}
//		}
//		else{
//			printf("this ID is exist!");
//		}
//	}
//}

int controlID(struct review *currentControl, int id){
	struct review *control;
	control=currentControl;
	while(control!=NULL){
		if(control->id==id){
			return 1;
		}
		control=control->next;
	}
	return 0;
}

void addScore(double score){
	struct score *np, *temp=NULL, *prev;
	np=malloc(sizeof(struct score));
	np->scoreNumber = score;
	np->totalNumberOfReviews=1;
	np->nextScore=NULL;
	
	// if LL empty
	if (first == NULL)
		first=np;
	// if LL not empty
	else {
		temp=first;
		while (temp != NULL && temp->scoreNumber<score) {
			prev=temp;
			temp=temp->nextScore;
		}
		if(temp!=NULL && temp->scoreNumber==score){
		temp->totalNumberOfReviews++;
		//printf("aynýsý var");
		return ;
		}

	// addScore score in a sorted fashion
	if (temp!=NULL)
		np->nextScore=temp;

 // if value to addScore is the least in LL then have header point to score
 if (temp==first)
		first=np;
	// otherwise addScore node in correct position
 else
		prev->nextScore=np;
	}
}

void particularWord(char text[]){
}

void polarity(int polarity){
}

void display(){
	if(first==NULL)
	printf("LL is empty");
	else{
	deneme=first;
	printf("SCORE   TOTAL REVIEW\n");
    printf("=====   ============\n");
	while(deneme!=NULL){
		printf(" %0.1lf %9.d\n",deneme->scoreNumber,deneme->totalNumberOfReviews);
		deneme=deneme->nextScore;
	}
	}
}  

int control(int score){
	struct score *np, *temp=NULL, *prev;
	np=malloc(sizeof(struct score));
	np->scoreNumber = score;
	np->nextScore=NULL;
	// if LL empty
	if (first == NULL)
		return 0;
	// if LL not empty
	else {
		temp=first;
		while (temp != NULL && temp->scoreNumber!=score) {
			prev=temp;
			temp=temp->nextScore;
		}
		if(temp!=NULL && temp->scoreNumber==score){
		printf("SUCCESSFUL!");
		return 1;
		}
	// addScore score in a sorted fashion
	if (temp!=NULL)
		np->nextScore=temp;
	// if value to addScore is the least in LL then have header point to score
	if (temp==first)
		first=np;
	// otherwise addScore node in correct position
	else
		prev->nextScore=np;
	}
	printf("NOT FOUND THIS SCORE. \nTRY AGAÝN!!");	
	return 0;
}

double average(){
	double  average= sum/counter;
	return average;
}

void sil(double starting,double ending){
    struct score *temp, *prev;
    temp=first;
    while(temp!=NULL ){
    	if(temp->scoreNumber==starting){
        if(temp==first){
        first=temp->nextScore;
        free(temp);
        }
        else{
        while(temp->scoreNumber!=ending){
        prev->nextScore=temp->nextScore;
        temp=temp->nextScore;
    	}
		}
    }
    else{
        prev=temp;
        temp= temp->nextScore;
    }
    }
}


                
