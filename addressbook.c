/**********************************************************************************
***************************                      **********************************
***************************     FAHRÝYE GÜN      **********************************
***************************      150112025       **********************************
***************************                      **********************************
**********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <String.h>

// prototype of functions
void list();
void update();
void create();
void deleteRecord();

struct recordData{

	int id;
	char firstName[15];
	char lastName[15];
	char phoneNum[30];
	char address[100];

};
struct recordData addressbook[100];
struct recordData dene;

FILE *rd, *rectemp;

int main(){
	int choice ;
	printf("\n ADDRESS BOOK\n");
	printf("1 - List all records\n");
	printf("2 - Update a record\n");
	printf("3 - Create a new record\n");
	printf("4 - Delete a record\n");
	printf("5 - exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);
	fflush(stdin);

	switch (choice)
    {
    case 1:
      list();
      break;
    case 2:
      update();
      break;
    case 3:
      create();
      break;
    case 4:
      deleteRecord();
      break;
    case 5:
	  printf("closing...");
      exit(0);
    break;
	default:
	printf("**Invalid Input.**\n");
	main();
 }
 return (0);
}
/////////////////////////////////// list functýon //////////////////////////////////////////////////////////////////////////////////////////
void list(){
	int a;
	
	printf("No   F.Name    L.Name   PhoneNum    Address\n");
    printf("==   ======    ======   ========    =======\n");
     	
    
	rd = fopen("addressbook.txt","r+");/* open file for read */
	
	if (rd == NULL){
	printf("There is not this file\n");
	}
	else {
     do {
     	a = getc(rd);    /* read a character  */
        putchar(a);         /* display on console   */
     }while (a != EOF); /* read to END OF FILE */

     fclose(rd);
   }

   printf("\n");
   main();
}
///////////////////////////////////////// create function /////////////////////////////////////////////////////////////////////////////////
void create(){
	int i, foo=0;

    printf("Enter the record number to create a new record : ");
    scanf("%d", &i);
    fflush(stdin);

    rd = fopen("addressbook.txt", "r");
	while(!feof(rd)){
		fscanf(rd,"%3d %15s %15s %30s %[^\n]", &(dene.id), dene.firstName, dene.lastName, dene.phoneNum, dene.address);
		if(i == dene.id){
			foo=1;
        }

    }
    fclose(rd);

    if(foo){
      printf("**There is this id. Try again please**");
      main();
    }
    else{
    rd = fopen("addressbook.txt","a+");

	addressbook[i].id = i;
    printf("Enter Person's Name: ");
    scanf("%s",addressbook[i].firstName);
    fflush(stdin);
    printf("Enter the last name: ");
    scanf("%s",addressbook[i].lastName);
    fflush(stdin);
    printf("Enter the phone number: ");
    scanf("%s",addressbook[i].phoneNum);
    fflush(stdin);
    printf("Enter the address: ");
    scanf("%[^\n]",addressbook[i].address);
    fflush(stdin);
    fprintf(rd ,"%d     %s     %s     %s     %s ", addressbook[i].id, addressbook[i].firstName, addressbook[i].lastName, addressbook[i].phoneNum, addressbook[i].address);
    printf("\n");
	printf("%d     %s     %s     %s     %s \n", addressbook[i].id, addressbook[i].firstName, addressbook[i].lastName, addressbook[i].phoneNum, addressbook[i].address);
    getch();
    fclose(rd);
    system("cls");
    printf("Successful!!\n");
    main();
    }
}
///////////////////////////////////////////// deleteRecord function ////////////////////////////////////////////////////////////////////////////////////////////////
void deleteRecord()
{
	int end, loop, line;
    rd = fopen("addressbook.txt", "r");
    rectemp =fopen("rectemp.txt","w");
    if (rd == NULL) {
        printf("Failed to open file\n");

    }
    printf("Enter the id number to delete : ");
    scanf("%d", &line);

    while(!feof(rd)){

      fscanf(rd,"%d     %s      %s     %s     %[^\n]", &(dene.id), dene.firstName, dene.lastName, dene.phoneNum, dene.address);

      if(line == dene.id){
      	printf("%d     %s     %s     %s     %s\n", dene.id, dene.firstName, dene.lastName, dene.phoneNum, dene.address);
      	printf("**deleted**\n");	
      		
      }else{
	  fprintf(rectemp,"%d     %s     %s     %s     %s\n", dene.id, dene.firstName, dene.lastName, dene.phoneNum, dene.address);
      }
      
   }
fclose(rd);
fclose(rectemp);

remove("addressbook.txt");
rename("rectemp.txt","addressbook.txt");

list();
}
////////////////////////////////////////////// update function //////////////////////////////////////////////////////////////////////////////////////////////////
void update()
{
    int end, loop, line, a;
    char newNum[30];
    rd = fopen("addressbook.txt", "r");
    rectemp =fopen("rectemp.txt","w");
    
    if (rd == NULL) {
        printf("Failed to open file\n");

    }
	printf("Please enter the record number of the person you want to update : ");
    scanf("%d", &line);

    printf("\n1 - Update phone number\n");
    printf("2 - Update address\n");
    printf("enter your choice: ");
    scanf("%d", &a);
	
	if(a==1){
	printf("Enter the new number:");
    scanf("%s", newNum);
	
	while(!feof(rd)){

      fscanf(rd,"%d     %s      %s     %s     %[^\n]", &(dene.id), dene.firstName, dene.lastName, dene.phoneNum, dene.address);

      if(line == dene.id){
	  fprintf(rectemp,"\n%d     %s     %s     %s     %s", dene.id, dene.firstName, dene.lastName, newNum, dene.address);
      printf("**Updated**: ");
      }
	  else{
	  fprintf(rectemp,"\n%d     %s     %s     %s     %s", dene.id, dene.firstName, dene.lastName, dene.phoneNum, dene.address);
      }

   }

fclose(rd);
fclose(rectemp);

remove("addressbook.txt");
rename("rectemp.txt","addressbook.txt");

main();
}
    if(a==2){
    	printf("Enter the new number:");
        scanf("%s", newNum);
		
		while(!feof(rd)){
		fscanf(rd,"%d     %s      %s     %s     %[^\n]", &(dene.id), dene.firstName, dene.lastName, dene.phoneNum, dene.address);
		
		if(line == dene.id){
		fprintf(rectemp,"\n%d     %s     %s     %s     %s", dene.id, dene.firstName, dene.lastName, newNum, dene.address);
        printf("**Updated**: ");
        }
		else{
		fprintf(rectemp,"\n%d     %s     %s     %s     %s", dene.id, dene.firstName, dene.lastName, dene.phoneNum, dene.address);
        }

        }

fclose(rd);
fclose(rectemp);

remove("addressbook.txt");
rename("rectemp.txt","addressbook.txt");

main();

    }
}
