/*****************************************************************************************************************************
*                                          FAHRÝYE GÜN / 150112025                                                           *
******************************************************************************************************************************/
//ÖDEV 10 TABANINA KADAR YAPILDI. 10DAN BÜYÜK TABANLARLA ÝLGÝLÝ ÝÞLEM YAPILMAZ.
#include <stdio.h>

int control(int ,int);
int base_of_number(int,int, int );
int getExponent(int,int);

int main(){
	int base1, base2, number1, number2;

	do{
		printf("enter base1 (between 2 and 10):");//prompt user base1
	    scanf("%d", &base1);
		printf("enter a number in base1: ");//prompt user number1
	    scanf("%d", &number1);	
	    printf("Enter base2 (between 2 and 10):");//prompt user base2
        scanf("%d",&base2);
	 if(control(number1,base1)==0)//check it
          {
              printf("number1 is not match with base1");
              getch();
              system("cls");
          }
     if((base1<2) || (base1>10) )
          {
              printf("Base1 is not defined..");
              getch();
              system("cls");
          }
     if((base2<2) || (base2>10) )
          {
              printf("Base2 is not defined..");
              getch();
              system("cls");
          }
	}
	
      while(control(number1,base1)==0 || base1<2 || base1>10 || base2<2 || base2>10) ;
       printf("%d in base%d equals to %d in base%d",number1,base1,base_of_number(base1,base2,number1),base2);//show result
        getch();
      
   	printf("");
   	return 0;
} 

/////////////CONTROL FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int control(int number1,int base1)
{
    int divisor,digit;
    for(divisor=1; divisor<number1; divisor*=10)//this for loop find that start with units digit of number
    {
       digit =(number1/divisor)%10;
       if(digit>=base1)//if digit is larger than base1, return 0.
       return 0;
   }
    return 1;
}
////////////BASE_OF_NUMBER FUNCTION//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int base_of_number(int base1,int base2, int number1)
{
    int divisor,digit,exponent=0,sum=0,number2=0;
   for(divisor=1; divisor<number1; divisor*=10)
    {
       digit =(number1/divisor)%10;
       
       sum = sum + digit *getExponent(base1 ,exponent);//turn to base10
       exponent++;
    }
	exponent=1;
    while(sum >=base2)
    {
        number2 = number2 +(sum % base2) * exponent;
        sum= sum/base2;
        exponent*=10;
    }
    number2 = number2 + sum*exponent;
    return number2;
}

///////////////GETEXPONENT FUNCTÝON/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getExponent(int base1, int exponent)
{
    int i,multiply =1;
    for(i=1; i<=exponent ;i++)
    {
       multiply =multiply*base1;
    }
    return multiply;
}



