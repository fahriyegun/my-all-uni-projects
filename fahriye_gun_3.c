/********************************************************************************************
*********************************************************************************************
                                 FAHRÝYE GÜN
                                 150112025
                                 PROJECT_3
*********************************************************************************************
*********************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct course{
	char courseName[50];
	struct exam *nextExam;
	struct course *next;
};

struct exam{
	char cName[50];
	struct exam *nextExam;
};
struct node{
	 int x;
	 struct nodes *next;
};
struct course *cPtr;
FILE *fp;
void readFile();
void first();
void insert(struct course **,char *);
void display(struct course *);
void search(struct course *);
void second_insert(struct exam **,char *);
void second_display(struct exam *);
void enqueue(struct node **, struct node **, int);
int main(){
	struct course *temp;
	readFile();
	first();
	display(cPtr);
	printf("\n");
	temp=cPtr;
	while(temp!=NULL){
		search(temp);
		temp=temp->next;
	}
	printf("\n\nafter first insert:");
	display(cPtr);
	printf("\n");
	return 0;
}
void readFile(){
	int i=0;
	char line[300];
    FILE *file;
     file = fopen("input.txt","r" );
     if((file== NULL)){
		printf("Input File Could Not Be Opened!\n");
		return;
	}
	else{
		printf("READ FROM TXT FILE\n");
		printf("==================\n");
     while(!feof(file)){
     	i++;
     	fgets(line,300,file);
     	printf("%d.%s",i,line);
	}
	fclose(file);
	}
}

void first(){
	char counter[300],*course,*name;
	fp=fopen("input.txt","r");
	if((fp== NULL)){
		printf("Input File Could Not Be Opened!\n");
		return;
	}
	else{
	while(fgets(counter,300,fp)!=NULL){
		//fgets(counter,300,fp);
		//fscanf(fp,"%s",counter);
		course=strtok(counter,":,");
		name=course;
		course=strtok(NULL,",");
		
		while(course!=NULL){
			insert(&cPtr,course);
			course=strtok(NULL,",");
			course = strtok(course, "\n");
		}
		
		}
	fclose(fp);
}
}
void insert(struct course **header,char *x){

	struct course *newNode, *temp, *prev;

	// create node to insert and assign values to its fields
	newNode=malloc(sizeof(struct course));
	newNode->next=NULL;
	newNode->nextExam=NULL;
	strcpy(newNode->courseName,x);
	
	// if LL empty
	if (*header == NULL) {
		*header=newNode;
		return;
	}
	// if LL not empty
	else {
		temp=*header;
		while (temp != NULL && (strcmp(temp->courseName,newNode->courseName) < 0)) {
			prev=temp;
			temp=temp->next;
		}

		if (temp!=NULL && (strcmp(temp->courseName,newNode->courseName) == 0)) {
			//printf("existent key"); 
			return;
		}

		// insert node in a sorted fashion
		if (temp!=NULL && strstr(temp->courseName,newNode->courseName)==NULL)
			newNode->next=temp;

		// if value to insert is the least in LL then have header point to node
		if (temp==*header)
			*header=newNode;
		// otherwise insert node in correct position
		else 
			prev->next=newNode;
	}

	return;
}

void display(struct course *p){
	p=cPtr;    
				while(p != NULL){
					printf("\n>>%s ",p->courseName);
					second_display(p->nextExam);
					p = p->next;
				}
		
}

void search(struct course *header){
	int i=0;
	//while(header!=NULL){
//	printf("\n%s\n",header->courseName);
//	printf("===\n");
	FILE *file;
	char line[300],*ret,*course,*name,*cmp;
     file = fopen("input.txt","r" );
     if((file== NULL)){
		printf("Input File Could Not Be Opened!\n");
		return;
	}
	else{
		while(fgets(line,300,file)!=NULL){
		i++;
		ret=strstr(line, header->courseName);
		if(ret!=NULL){
			//printf("%s %d.satirda var\n",header->courseName,i);
			course=strtok(line,":,");
			name=course;
			course=strtok(NULL,":,");
		while(course!=NULL){
			cmp=strstr(header->courseName,course);
		if(strcmp(header->courseName,course)!=0){
			//printf(">>yandas dersi:%s\n",course);
			second_insert(&header->nextExam,course);
			}
			course=strtok(NULL,":,");
			//course = strtok(course, "\n");
		}

		}
		else{
			//printf("%s %d.satirda yok\n",header->courseName,i);
		}
		
	}i=0;
	}
	header=header->next;
//	}
}

void second_insert(struct exam **header,char *x){

	struct exam *newNode, *temp, *prev;

	// create node to insert and assign values to its fields
	newNode=malloc(sizeof(struct exam));
	newNode->nextExam=NULL;
	strcpy(newNode->cName,x);
	
	// if LL empty
	if (*header == NULL) {
		*header=newNode;
		return;
	}
	// if LL not empty
	else {
		temp=*header;
		while (temp != NULL && (strcmp(temp->cName,newNode->cName)< 0)) {
			prev=temp;
			temp=temp->nextExam;
		}

		if (temp!=NULL && (strcmp(temp->cName,newNode->cName) == 0)) {
			//printf("existent key"); 
			return;
		}

		// insert node in a sorted fashion
		if (temp!=NULL && strstr(temp->cName,x)==NULL)
			newNode->nextExam=temp;

		// if value to insert is the least in LL then have header point to node
		if (temp==*header)
			*header=newNode;
		// otherwise insert node in correct position
		else 
			prev->nextExam=newNode;
	}
	
	return;
}

void second_display(struct exam *p){
	//p=cPtr->nextExam;    
				while(p != NULL){
					printf("->%s ",p->cName);
					p = p->nextExam;
				}
		
}

//void enqueue(struct node **front, struct node **rear, int element)
//
//{
//
//    struct node * temp,*current;
//
//    current = malloc(sizeof(struct node*));
//
//    current->x = element;
//
//    current->next = NULL;
//
//    if(*front == NULL)
//
//    {
//
//          *front = *rear = current;
//
//     }
//
//     else
//
//    {
//
//          temp = *rear; //use pointer to structure to access structure members
//
//          temp->next=current;
//
//          temp=temp->next;
//
//          *rear=temp;
//
//     }
//
//} //enqueue

