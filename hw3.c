////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////         FAHRÝYE GÜN               ////////////////////////////////////
////////////////////////////////          150112025                /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
	int data;
	struct node *next;
};

typedef struct node node;
typedef struct node* nodePtr;
typedef struct node** nodePtrPtr;

int insert(nodePtrPtr, int);
void display(nodePtr);
nodePtr sortedMerge(nodePtr, nodePtr);
void generateRandom();
void segregateEvenOdd(nodePtrPtr);


nodePtr list1, list2, merged;


int main(){

list1=NULL;
list2=NULL;
merged=NULL;

generateRandom();

printf(">> List1: ");
display(list1);

printf(">> List2: ");
display(list2);

printf(">> Merged List: ");
merged=sortedMerge(list1,list2);
display(merged);

segregateEvenOdd(&merged);
printf(">> Odd List: ");
display(list1);

printf(">> Even List: ");
display(list2);

printf(">> End of progam..\n\n");



return 0;
}


int insert(nodePtrPtr header, int x){

	nodePtr newNode, temp, prev;

	// create node to insert and assign values to its fields
	newNode=malloc(sizeof(node));
	newNode->data=x;
	newNode->next=NULL;

	// if LL empty
	if (*header == NULL)
		*header=newNode;
	// if LL not empty
	else {
		temp=*header;
		while (temp != NULL && temp->data<newNode->data) {
			prev=temp;
			temp=temp->next;
		}

//      if you want that two same node cannot exist uncomment code block below
//		if (temp!=NULL && temp->x==newNode->x) {
//			printf("existent key");
//			return 0;
//		}

		// insert node in a sorted fashion
		if (temp!=NULL)
			newNode->next=temp;

		// if value to insert is the least in LL then have header point to node
		if (temp==*header)
			*header=newNode;
		// otherwise insert node in correct position
		else
			prev->next=newNode;
	}

	return 1;

}

void generateRandom(){

	srand(time(NULL));

	int r,i;

 	for(i=0;i<10;i++){
		r=rand()%41;
        insert(&list1,r);
    }

    for(i=0;i<10;i++){
		r=rand()%41;
        insert(&list2,r);
    }

}

void display(nodePtr header){
    nodePtr temp=header;
    if (temp == NULL)
    printf ("\nList is empty");
    else {
    while(temp != NULL){
        printf("%2d ",temp->data);
        temp = temp->next;
    }
    }
    printf("\n\n");

}


nodePtr sortedMerge(nodePtr a, nodePtr b)
{
  nodePtr result = NULL;

  /* Base cases */
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);

  /* Pick either a or b, and recur */
  if (a->data <= b->data)
  {
     a->next = sortedMerge(a->next, b);
     return(a);
  }
  else
  {
     b->next = sortedMerge(a, b->next);
     return(b);
  }

}



void segregateEvenOdd(nodePtrPtr head_ref)
{
    nodePtr end = *head_ref;

    nodePtr prev = NULL;
    nodePtr curr = *head_ref;

    /* Get pointer to the last node */
    while (end->next != NULL)
        end = end->next;

    nodePtr new_end = end;

    /* Consider all odd nodes before the first even node
       and move then after end */
    while (curr->data %2 != 0 && curr != end)
    {
        new_end->next = curr;
        curr = curr->next;
        new_end->next->next = NULL;
        new_end = new_end->next;
    }

    // 10->8->17->17->15
    /* Do following steps only if there is any even node */
    if (curr->data%2 == 0)
    {
        /* Change the head pointer to point to first even node */
        *head_ref = curr;

        /* now current points to the first even node */
        while (curr != end)
        {
            if ( (curr->data)%2 == 0 )
            {
                prev = curr;
                curr = curr->next;
            }
            else
            {
                /* break the link between prev and current */
                prev->next = curr->next;

                /* Make next of curr as NULL  */
                curr->next = NULL;

                /* Move curr to end */
                new_end->next = curr;

                /* make curr as new end of list */
                new_end = curr;

                /* Update current pointer to next of the moved node */
                curr = prev->next;
            }
        }
    }

    /* We must have prev set before executing lines following this
       statement */
    else prev = curr;

    /* If there are more than 1 odd nodes and end of original list is
      odd then move this node to end to maintain same order of odd
      numbers in modified list */
    if (new_end!=end && (end->data)%2 != 0)
    {
        prev->next = end->next;
        end->next = NULL;
        new_end->next = end;
    }

    //Up till now we have a list that at its begining has even number and at its end odd number, now we separete this list into two lists list1=odd numbers and list2=even numbers

    list1=NULL;
    list2=NULL;

    nodePtr temp=merged;

    while(temp != NULL){
        if(temp->data%2){

            if (list1 == NULL){
            list1=temp;
            }

        }

        else{

            if (list2 == NULL){
                list2=temp;
            }

            if ((temp->next)->data%2){
                list1=temp->next;
                temp->next=NULL;
            }

        }
        temp = temp->next;
    }



    return;
}


