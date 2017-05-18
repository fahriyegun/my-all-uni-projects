/********************************************************************************************
*********************************************************************************************
                                 FAHRÝYE GÜN
                                 150112025
                                 PROJECT_2
*********************************************************************************************
*********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct score{
	double score;
	int totalReview;
	struct score *leftScore;
	struct score *rightScore;
	struct review *reviewPtr;
};

struct review{
	int id;
	char text[500];
	struct review *leftReview;
	struct review *rightReview;
};

//GLOBAL VARIABLES
struct score *scoreTree=NULL;
double sum=0;
int totalID=0;
FILE *fp,*file;
	
//PROTOTYPE OF FUNCTIONS
int readFile();
char* readText(char *);
void insertScore(struct score **,double, int, char*);
void insertReview(struct review **, int, char*);
void menu();
void addScore(struct score **,double);
struct score* search(struct score **,double);
struct review* searchID(struct review **,int);
void addReview1(struct score **,double,int,char*);
int counterID(struct review **);
double average(struct score **);
void specificWord(struct score *, char *);
void specificWordID(struct review *, char *);
struct score* findMin(struct score *);
struct score* sil(double, struct score *);
void deltree(struct review *);
void deletion(struct score **, struct score **, double );
void print_inorder(struct score *);
void print_inorderR(struct review *);
void print_preorder(struct score *);
void print_preorderR(struct review *);
void print_postorder(struct score *);
void print_postorderR(struct review *);
//MAIN FUNCTION
int main(){
	readFile();
	menu();
	return 0;
}

//READ FILE AND TAKE SCORE&ID AND CREATE MASTER BST.
int readFile(){
	char text1[300];
	char str[60],*s,*t,a[10],text[300],x[600];
	
	
	double score;
	int id;
	//printf("%s\n",x);
	fp=fopen("InputForProject2\\Order.txt","r");
	if(fp==NULL){
		perror("Error opening file..");
		return (-1);
	}
	while(!feof(fp)){
		if(fgets(str,60,fp)!=NULL){
			s=strtok(str,"_");
			t=s;
			s=strtok(NULL,"_");
			score=atof(t);
			id=atoi(s);
			itoa(id,a,10);//CONVERT ID TO CHAR
			strcat(t,"_");
			strcat(t,a);
			strcat(t,".txt");//TAKE SCORE&ID FILE NAME.
			strcpy(x,"");
			strcat(x,"InputForProject2\\");
			strcat(x,t);
			strcpy(text1,"");
			file=fopen(x,"r");//READ EVERY REVIEW FILE.
			if(file==NULL){
				perror("Error opening file..");
				return (-1);
			}
			
			while(!feof(file)){
				fgets(text,300,file);
				strcat(text1,text);//TAKE EVERY REVIEW TEXT.
				//printf("%s",text);
	}

			fclose(file);
			
			//printf("\nscore: %.1lf - id: %d - review:",score,id);
			
			
		}
		insertScore(&scoreTree,score,id,text1);//CREATE SCORE BST
	}
	fclose(fp);
	//print_inorder(scoreTree);
	return 0;
}

void insertScore(struct score **tree, double val, int id,char *text){//BEFORE CREATE SCORE BST AFTER CREATE THEIR REVIEW BST

	
	struct score *temp = NULL;
	struct review *tempReview = NULL;
	temp = (struct score *)malloc(sizeof(struct score));
        
    if(!(*tree))//IF TREE IS NULL,CREATE NEW NODE
    {
        tempReview = (struct review *)malloc(sizeof(struct review));
        tempReview->rightReview=tempReview->leftReview=NULL;
        tempReview->id=id;
        strcpy(tempReview->text,text);
        temp->leftScore = temp->rightScore = NULL;
        temp->score = val;
        temp->totalReview=0;
        temp->reviewPtr=tempReview;       
		temp->totalReview++;
        *tree = temp;
        return;
    }
    //IF YOU HAVE A SCORE, COMPARE WITH CURRENT NODE'S SCORE AND PLACE IN AVAILABLE POSITION. 
    if(val < (*tree)->score)
    {
        insertScore(&(*tree)->leftScore, val,id,text);
    }
    else if(val > (*tree)->score)
    {
        insertScore(&(*tree)->rightScore, val, id,text);
    }
    else if(val == (*tree)->score)//IF YOUR SCORE AND CURRENT SCORE ARE SAME, CREATE THEIR REVIEW BST.
    {
        insertReview(&(*tree)->reviewPtr, id,text);
        (*tree)->totalReview++;//AND THEN TOTAL NUMBER OF REVIEWS OF CURRENT SCORE IS INCREASE.
       
    }
}

void insertReview(struct review **reviewTree, int id,char *text){//CREATE REVIEW BST.
	struct review *temp = NULL;
    if(!(*reviewTree))//IF THERE IS ANY REVIEW, CREATE NEW REVIEW BST.
    {
        temp = (struct review *)malloc(sizeof(struct review));
        temp->leftReview = temp->rightReview = NULL;
        temp->id = id;
        strcpy(temp->text,text);
        *reviewTree = temp;
        return;
    }
    //IF YOU HAVE A REVIEW IN REVIEW BST, COMPARE WITH CURRENT REVIEW AND PLACE IN AVAILABLE POSITION.
    if(id < (*reviewTree)->id)
    {
        insertReview(&(*reviewTree)->leftReview, id,text);
    }
    else if(id > (*reviewTree)->id)
    {
        insertReview(&(*reviewTree)->rightReview, id,text);
    }
}
//OPERATON LIST.
void menu(){
	int choice,id,ctrl;
	double score,start,end,av,key;
	char *text=malloc(100);
	printf("==================================================================\n");
	printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n","1:Add a new review-score","2:Add some reviews into a review-score","3:Calculate the average score of all of the reviews","4:List the id s of reviews which have a particular word","5:Remove the reviews between in a specific score-scope","6:Display","7:EXIT");
    printf("==================================================================\n");
	printf("choice:");
    scanf("%d",&choice);
    switch(choice){
    	case 1:
    		printf("Enter the a review-score:");
    		scanf("%lf",&score);
    		if(search(&scoreTree,score)==NULL){//IF ENTERED SCORE IS NOT OCCURENCE, PLACE IN MASTER BST.
    			addScore(&scoreTree,score);
    			printf("\nScore is added in master BST!\n");
    		}
    		else{//IF ENTERED SCORE IS EXISTED BEFORE, TAKE NEW SCORE.
    			while(search(&scoreTree,score)){
    				printf("This score is existed. Please try again.\nEnter a new review-score:");
    				scanf("%lf",&score);
    			}
    		addScore(&scoreTree,score);
    			
    		}
    		//print_inorder(scoreTree);
    		menu();
    		break;
    	case 2:
			printf("Enter the review score:");
			scanf("%lf",&score);
			printf("\nEnter the review id:");
			scanf("%d", &id);
			printf("\nthe review:");
    	    gets(text);
    	    gets(text);
    	    if(search(&scoreTree,score)!=NULL){//IF THERE EXISTED THIS SCORE, CONTROL ID
    	    	if(searchID(&scoreTree->reviewPtr,id)==NULL){//IF THIS ID IS NOT EXISTED, PLACE IN MASTER BST.
    	    		addReview1(&scoreTree,score,id,text);
    	    		printf("\nReview is added im master BST!\n");
    	    		//print_inorder(scoreTree);
    	    	}
    	    	else{
    	    		printf("\nthis id is existed");
    	    	}
    	    }
    	    else{
    	    	printf("\nthis score is not existed. please try again..");
    	    }
			menu();
    	    break;
		case 3:
			av=average(&scoreTree);
			printf("average score of all of review:%.3lf\n",av);
			menu();
			break;
		case 4:
			printf("which word is wanted?\n");
			scanf("%s",text);
			specificWord(scoreTree,text);
			menu();
			break;
		case 5:
			printf("Enter starting score for delete:");
			scanf("%lf",&start);
			printf("Enter ending score for delete:");
			scanf("%lf",&end);
			if(search(&scoreTree,start)!=NULL){//IF STARTING SCORE IS IN BST, CONTROL ENDING SCORE.
    			if(search(&scoreTree,end)!=NULL){//IF ENDING SCORE IS EXISTED, DELETE THIS SCOPE.
    			key=start;
				do{
    				//sil(start,scoreTree);
    				deletion(&scoreTree,NULL,key);
					key+=0.5;   			
    			}while(key<end);
    			printf("\nOPERATION IS SUCCESSFULL.\n");
    			
    		}
    		else{
    			printf("\nTHERE IS NOT ENDING SCORE PLEASE TRY AGIN PLEASE..\n");
    		}
    		}
    		else{
    		printf("\nTHERE IS NOT STARTING SCORE IN BST. PLEASE TRY AGAIN PLEASE..\n");
			}
			menu();
			break;
		case 6:
			printf("\nfor inorder press 1");
			printf("\nfor postorder press 2");
			printf("\nfor preorder press 3\n");
			scanf("%d",&ctrl);
			switch(ctrl){
				case 1:
					print_inorder(scoreTree);
					menu();
					break;
				case 2:
					print_postorder(scoreTree);
					menu();
					break;	
				case 3:
					print_preorder(scoreTree);
					menu();
					break;
				default:
					printf("***invalid value***\n\n");
					menu();		
			}
			break;
		case 7:
			printf("\nClosing...");
        	exit(0);
			break;
		default:
			printf("***invalid value***\n\n");
			menu();
			
									
    }
}
//THIS FUNCTION SEARCH SPECIFIC SCORE IN TREE
struct score* search(struct score **tree, double val)
{
    if(!(*tree))//IF TREE IS NOT EXISTED, RETURN NULL.
    {
		return NULL;
    }
    else{//COMPARE WITH SPECIFIC SCORE AND CURRENT SCORE.. 
    	if(val < (*tree)->score){
    		search(&(*tree)->leftScore, val);
    	}
    	else if(val > (*tree)->score){
    		search(&(*tree)->rightScore, val);
    	}
    	else if(val == (*tree)->score){//IF SPECIFIC SCORE IS FOUND, RETURN TREE.
    		return *tree;
    	}
   	}
}
//THIS FUNCTION SEARCH SPECIFIC REVIEW IN TREE
struct review* searchID(struct review **tree, int id)
{
    if(!(*tree))
    {
		return NULL;
    }
    else{
    	if(id < (*tree)->id){
    		searchID(&(*tree)->leftReview,id);
    	}
    	else if(id > (*tree)->id){
    		searchID(&(*tree)->rightReview,id);
    	}
    	else if(id == (*tree)->id){
    		return *tree;
    	}
   	}
}
//ADD NEW SCORE IN MASTER BST.
void addScore(struct score ** tree, double val)
{
	struct score *temp = NULL;
	if(!(*tree))
    {
        temp = (struct score *)malloc(sizeof(struct score));
        temp->leftScore = temp->rightScore = NULL;
        temp->reviewPtr=NULL; 
		temp->score = val;  
		temp->totalReview=0;  
        *tree = temp;
        temp->totalReview++;
        return;
    }

    if(val < (*tree)->score)
    {
        addScore(&(*tree)->leftScore, val);
    }
    else if(val > (*tree)->score)
    {
        addScore(&(*tree)->rightScore, val);
    }
}
//ADD NEW REVIEW IN MASTER BST 
void addReview1(struct score **tree, double val,int id,char *text)
{
    if(!(*tree))
    {
		return;
    }
    else{
    	if(val < (*tree)->score){
    		addReview1(&(*tree)->leftScore, val,id,text);
    	}
    	else if(val > (*tree)->score){
    		addReview1(&(*tree)->rightScore, val,id,text);
    	}
    	else if(val == (*tree)->score){//BEFORE FIND TO WANTED SCORE.
    		insertReview(&(*tree)->reviewPtr,id,text);//AFTER GO TO THIS SCORE'S REVIEW TREE AND PLACE IN TREE.
    	}
   	}
}
//CALCULATE AVERAGE SCORE OF ALL OF REVIEWS.
double average(struct score **tree){
	int countID;
	double s,avg;
	if(!(*tree)){//IF TREE IS EMPTY, RETURN 0.
		return 0;
	}
	else{
	s=(*tree)->score;//TAKE SCORE NUMBER
	countID=(*tree)->totalReview;//TAKE TOTAL NUMBER OF REVIEWS.
	sum+=s*countID;//ADDITION ALL OF (SCORE NUMBER)*(TOTAL NUMBER OF REVIEW); 
	totalID+=countID;//INCREASE TOTAL NODE.
	average(&(*tree)->leftScore);
	average(&(*tree)->rightScore);
	avg=sum/totalID;
	return avg;
	}
}
//SEARCH SPECIFIC WORD.
void specificWord(struct score *tree, char *text){
	if(!(tree)){
		return;
	}
	else{
		specificWordID(tree->reviewPtr,text);//BEFORE CONTROL CURRENT SCORE'S REVIEW TREE.
		specificWord(tree->leftScore,text);//AFTER CONTROL OTHERS.
		specificWord(tree->rightScore,text);
	}
}
//CONTINUANCE OF SEARCHING SPECIFIC WORD
void specificWordID(struct review *tree, char *text){
	char *p;
	
	if(!(tree)){
		return;
	}
	
	else{//CONTROL CURRENT REVIEWTREE
		p=strstr(tree->text,text);
		if(p){
			printf("\nID:%d",tree->id);
		}
		else{//AFTER OTHERS..
			specificWordID(tree->leftReview,text);
			specificWordID(tree->rightReview,text);
		}
	}
}
struct score* findMin(struct score *tree)
{
if (tree != NULL){
while (tree->leftScore != NULL) {
	tree=tree->leftScore;
}
}
return tree;
}
struct score* sil(double key, struct score *p){
	struct score *TempPtr;
	if (p == NULL){
		return NULL;
	}
	if (key < p->score){
		sil(key,p->leftScore);
	}
	else if (key > p->score){
		sil(key,p->rightScore);
	}
	else{ //node with key found!!!
		deltree(p->reviewPtr);
		if (p->rightScore && p->leftScore) { //if node has two children
			TempPtr=findMin(p->rightScore); //find smallest key of right subtree of node with key
			p->score=TempPtr->score; //replace sild data by smallest key of right
			p->reviewPtr=TempPtr->reviewPtr;
			p->rightScore=sil(p->score,p->rightScore);
		}
		else { //if node has less than two children
			TempPtr=p;
			if (p->leftScore == NULL){
				p=p->rightScore;
			}
			else if (p->rightScore == NULL){
				p=p->leftScore;
			}
			free(TempPtr);
			}
			 return p;
	}
}
void deletion(struct score **node, struct score **parent, double score) {
	struct score *tmpNode, *tmpParent;
        if (*node == NULL)
                return;
             
        if ((*node)->score == score) {
        	deltree((*node)->reviewPtr);
                /* deleting the leaf node */
                if (!(*node)->leftScore && !(*node)->rightScore) {
                        if (parent) {
                                /* delete leaf node */
                                if ((*parent)->leftScore == *node)
                                        (*parent)->leftScore = NULL;
                                else
                                        (*parent)->rightScore = NULL;
                                free(*node);
                        } else {
                                /* delete root node with no children */
                                free(*node);
                                scoreTree=NULL;
                        }
                /* deleting node with one child */
                } else if (!(*node)->rightScore && (*node)->leftScore) {
                        /* deleting node with leftScore child alone */
                        tmpNode = *node;
                        (*parent)->leftScore = (*node)->leftScore;
                        free(tmpNode);
                        *node = (*parent)->leftScore;
                } else if ((*node)->rightScore && !(*node)->leftScore) {
                        /* deleting node with rightScore child alone */
                        tmpNode = *node;
                        tmpParent = (*node)->rightScore;
                        free(tmpNode);
                        (*node) = tmpParent;
                        free(tmpParent);
                } else if (!(*node)->rightScore->leftScore) {
                	    (*node)->rightScore->leftScore = (*node)->leftScore;
						free((*node)->leftScore);
						tmpNode = (*node)->rightScore;
                        *node = tmpNode;
                        free(tmpNode);
                } else {
                        tmpNode = (*node)->rightScore;
                        while (tmpNode->leftScore) {
                                tmpParent = tmpNode;
                                tmpNode = tmpNode->leftScore;
                        }
                        tmpParent->leftScore = tmpNode->rightScore;
                        tmpNode->leftScore = (*node)->leftScore;
                        tmpNode->rightScore =(*node)->rightScore;
                        free(*node);
                        *node = tmpNode;
                }
        } else if (score < (*node)->score) {
                /* traverse towards leftScore subtree */
                deletion(&(*node)->leftScore, node, score);
        } else if (score > (*node)->score) {
                /* traversing towards rightScore subtree */
                deletion(&(*node)->rightScore, node, score);
        }
  }
  
//DELETE DELETED SCORE'S REVIEW TREE
void deltree(struct review * tree)
{
    if (tree)
    {
        deltree(tree->leftReview);
        deltree(tree->rightReview);
        free(tree);
    }
}
//DISPLAY ALL TREE LIKE INORDER TYPE.
void print_inorder(struct score *tree)
{
    if (tree)
    {
        print_inorder(tree->leftScore);
        printf("\nscore:%0.1lf  total number of review:%d\n",tree->score, tree->totalReview);
        printf("====================================\n");
        print_inorderR(tree->reviewPtr);
        print_inorder(tree->rightScore);
    }
}
//DISPLAY ALL REVIEW TREE LIKE INORDER TYPE.
void print_inorderR(struct review * tree)
{
    if (tree)
    {
        print_inorderR(tree->leftReview);
        printf("\tid:%d --> text:%s\n",tree->id,tree->text);
        print_inorderR(tree->rightReview);
    }
}
//DISPLAY ALL TREE LIKE POSTORDER TYPE.
void print_postorder(struct score * tree)
{
    if (tree)
    {
        print_postorder(tree->leftScore);
        print_postorder(tree->rightScore);
        printf("\nscore:%.1lf total number of review:%d\n",tree->score, tree->totalReview);
        printf("================================\n");
        print_postorderR(tree->reviewPtr);
    }
}
//DISPLAY ALL REVIEW TREE LIKE POSTORDER TYPE.
void print_postorderR(struct review * tree)
{
    if (tree)
    {
        print_postorderR(tree->leftReview);
        print_postorderR(tree->rightReview);
        printf("\tid:%d-->text:%s\n",tree->id,tree->text);
    }
}
//DISPLAY ALL TREE LIKE PREORDER TYPE.
void print_preorder(struct score * tree)
{
    if (tree)
    {
        printf("\nscore:%.1lf total number of review:%d\n",tree->score, tree->totalReview);
        printf("================================\n");
        print_postorderR(tree->reviewPtr);
        print_preorder(tree->leftScore);
        print_preorder(tree->rightScore);
    }

}
//DISPLAY ALL REVIEW TREE LIKE POSTORDER TYPE.
void print_preorderR(struct review * tree)
{
    if (tree)
    {
    	printf("\tid:%d-->text:%s\n",tree->id,tree->text);
        print_preorderR(tree->leftReview);
        print_preorderR(tree->rightReview);
    }

}

