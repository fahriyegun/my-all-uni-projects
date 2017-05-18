.data

menu:	.asciiz "\nPlease select an option:
				\n1. C-to-MIPS convert
				\n2. Print Numbers
				\n3. Word Finder
				\n4. Print x-th Number
				\n5. Exit\n"
msg1:	.asciiz	"Please enter a number (greater than 0):"
msg2:	.asciiz " "
msg3:	.asciiz "\n"
msg4:	.asciiz "\nWRONG INPUT!!!\nPlease enter a number (greater than 0):"				
prompt1:	.asciiz "\nEnter a number between 1 to 5:"
prompt2:	.asciiz "\nEnter k-value(greater than 0):"
prompt3:	.asciiz	"enter input:"
prompt4:	.asciiz	"Please enter a number (greater than 1):"
prompt5:	.asciiz "\nWRONG INPUT!!!\nPlease enter a number (greater than 1):"
prompt6:	.asciiz "\n***THE END***"
prompt7:	.asciiz "In position "
prompt8:	.asciiz ", the value is "
arr:	.word 0:100
input:	.space 100

.text
.globl main

main:

menu_print:li	$v0,4													#PRINT ALL MENU
		la	$a0, menu			
		syscall
		j take
	
take:li	$v0,4															#SELECT OPTION
	la	$a0, prompt1			
	syscall
	li	$v0,5					
	syscall	
	move	$t0,$v0
	j control
	
control:bgt $t0, 5, take												#GO TO YOUR ANSWER
		blt $t0, 1, take
		beq $t0, 1, func1
		beq $t0, 2, question2
		beq $t0, 3, question3
		beq $t0, 4, question4
		beq $t0, 5, exit
	
func1:li $v0,4															#START FUNC1
	la	$a0, prompt2													#ENTER K-VALUE
	syscall
	li $v0,5					
	syscall
	move $t1,$v0				#k=t1
	ble $t1,0, func1  			#t1=k 
	la $t2, arr					#t2= address of arr[]
	li $s7,0					#i=0
	li $s1,0					#s=0
	loop1st: bge $s7, $t1, go	#if i<k; continue
		add $a0, $s7, $zero
		jal func2														#GO TO FUNC2
		move $a0,$v0			#a0=func2(i)
		sll $s6, $s7,2
		add $s6, $t2, $t6
		sw $a0, 0($s6)			#arr[i]=func2(i)
		addi $s7, $s7,1
		j loop1st
		
	go:li $s7,0	#i=0
	loop2nd: bge $s7, $t1, go2	#if i<k; continue
		sll $s6, $s7,2
		add $s6, $t2, $t6
		lw $a0, 0($s6)			#a0=arr[i]
		add $s1, $s1, $a0 		#s=s+arr[i]
		addi $s7, $s7,1
		j loop2nd
	
	go2:li	$v0,1													#PRINT RESULT OF QUESTION1
		move	$a0, $s1																
		syscall
		j menu_print												#GO TO MENU

func2:li $t3,2
	addi $t4, $a0,0	  			#k=t4
	div $t4,$t3       			# k % 2
    mfhi $a1          			# result of mod=$a1
	beq $a1, 1, else			#if (k%2)=0; continue
	mul $t4, $t4, $t4			#t4=k*k
	addi $t4, $t4,2				#t4= k*k+2
	j return_k					#go to return value
	else:
	li $t3, -1					#t3=-1
	mul $t4, $t4, $t3			#t4= k*(-1)
    return_k:add $v0, $t4, $zero 	#result value:v0=t4
	jr $ra 						#jump to return address
	
	
question2:															#START QUESTION2
	li	$v0,4					# Print string msg1:
	la	$a0, msg1				#"Please enter a number (greater than 0):"
	syscall
	li	$v0,5					# read_int syscall code = 5									
	syscall	
	move	$t0,$v0				# syscall results returned in $v0 ($t0=number)
	
loop1:bgt $t0,0,go1
	li	$v0,4					# Print:
	la	$a0, msg4				#"\nWRONG INPUT!!!\nPlease enter a number (greater than 0):"
	syscall
	li	$v0,5					# Again get input from user and save
	syscall	
	move	$t0,$v0		
	j loop1
	
go1:	li	$t1, 1				# Initialize counter (i=1)(t1)
loop2:	bgt $t1, $t0,go2go    	#if(i<=number), continue
		li	$t2, 1				# Initialize counter (j=1)(t2)
		j loop3	
loop3:	bgt $t2, $t1,exit1		#if(j<=i), continue
		li	$v0,1				
		move	$a0, $t2		#print number
		syscall
		li	$v0, 4				
		la	$a0, msg2			#print " "
		syscall
		addi	$t2, $t2, 1		#j++
		j loop3
exit1:	li	$v0, 4				
		la	$a0, msg3
		syscall					#print "\n"
		addi	$t1, $t1, 1		#i++
		j	loop2

go2go:
	j menu_print													#GO TO MENU
		
question3:
	li $s3, ' '					#save all punctuations to registers
	li $s4, '.'
	li $s5, ','
	li $s6, '!'
	li $s7, '?'
	li $t4, '_'
	li $t5, '-'
	li $t6, '('
	li $t7, ')'
	li $t8, '\n'
	li $v0,4					# Print:"Enter input:"
	la $a0, prompt3				
	syscall
	la $a0,input				#a0=input[]
	li	$v0,8					#take string
	syscall	
	li $t3,0
	add $t3,$a0, $t3			
	li $s2,0
loop:
	lb $t9,0($t3)				#t3=input[i]
	
	beq $t8,$t9,endloop			#compare all punctiution with each char of input
	beq $s3,$t9,label
	beq $s4,$t9,label
	beq $s5,$t9,label
	beq $s6,$t9,label
	beq $s7,$t9,label
	beq $t4,$t9,label
	beq $t5,$t9,label
	beq $t6,$t9,label
	beq $t7,$t9,label
	move $a0,$t9
	li $v0,11				#print char
	syscall
	li $s2,0
	addi $t3,$t3,1			#i++
	j loop
	
label:
	addi $s2, $s2,1
	bgt $s2,1,loo
    move $a0,$t8
	li	$v0,11
	syscall
loo:addi $t3,$t3,1
	j loop
endloop:
	j menu_print												#GO TO MENU
		
question4:
	li	$v0,4					# Print:"Please enter a number (greater than 1):"
	la	$a0, prompt4			
	syscall
	li	$v0,5					# Get input
	syscall	
	move $t0,$v0				#($t0=size)
	
loop4:bgt $t0,0,go5
	li	$v0,4					# Print:"\nWRONG INPUT!!!\nPlease enter a number (greater than 1):"
	la	$a0, prompt5			
	syscall
	li	$v0,5					# Again get input
	syscall	
	move	$t0,$v0		
	j loop4
go5:la $t1, input				#  $t1=input[]
	li	$t2, 0					#  $t2 = 0  
	sw $t2, ($t1)				#  input[0]=0;
	li $t2, 1					#  $t1 = 1
	sw $t2, 4($t1)				#  input[1]=1;
	li $t8,8
	li	$t2, 2					#  $t2=i=2
loop5:bge $t2,$t0,last			# if(i<size); continue
	sub $t3,$t2,1				# t3 = i-1
	sll $t3, $t3, 2				# t3 = 4*t3		
	add $t5, $t1, $t3			# t5 = address of array[i-1]
	lw $t6, 0($t5)				# t6= array[i-1]		
	sll $t6, $t6,2				# t6 = 4* array[i-1]
	sub $t3,$t2,2				# t3 = i-2
	sll $t3, $t3, 2				# t3 = 4*t3																		
	add $t4, $t1, $t3			# t4 = address of array[i-2]
	lw $t7, 0($t4)				# t7= array[i-2]
	sub $t4, $t6, $t7			# t4 = 4* array[i-1] - array[i-2]
	sll $t8, $t2,2 				# $t2=i=2 now i*4=8
	add $t9, $t1,$t8			# t1= adress of array[i]
	sw $t4,0($t9)
	
	addi $t2, $t2, 1			#i++
	j loop5

last:
	li	$v0,4					# Print:"In position "
	la	$a0, prompt7			
	syscall
	li	$v0,1				    # print position
	move $a0,$t0																	
	syscall
	li	$v0,4					# Print:"the value is: "
	la	$a0, prompt8			
	syscall
	li	$v0,1					# print_int syscall code = 1
	lw $a0,0($t9)				#print number
	syscall
	j menu_print
		
exit:
	li	$v0,4					# print_string :"***THE END***"
	la	$a0, prompt6		
	syscall
	li	$v0,10					# exit
	syscall