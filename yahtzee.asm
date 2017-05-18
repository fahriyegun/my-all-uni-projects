INCLUDE Irvine32.inc
.data
welcome BYTE "Welcome the yahtzee game",0
baslik BYTE "Order 	 Combination Score",0
counter BYTE 0
count DWORD 0
score DWORD 12 DUP(0)
target BYTE 12 DUP(0)
dice DWORD 5 DUP(0)
temp BYTE 6 DUP(0)
menu BYTE "1.       Ones       ",
		  "2.       Twos       ",
		  "3.       Threes     ",
	      "4.       Fours      ",
	      "5.       Fives      ",
	      "6.       Sixes      ",
	      "7.       3 of a kind",
	      "8.       4 of a kind",
	      "9.       Yahtzee    ",
	      "10.      4 in row   ",
	      "11.      5 in row   ",
	      "12.      Anything   ",0
d DWORD "eciD",0
d1 DWORD ":",0
tekrar BYTE "This score is already choosed.",0
choose BYTE "Do you want to reroll(Y/N)?:",0
change BYTE "How many dice do you want to reroll? ",0
emptt BYTE "                                       ",0
which BYTE "Which dices do you want to reroll? ",0
select BYTE "Select score ",0
no_str BYTE "no selected.",0
irr BYTE "irrelevant choose. Please enter y/n.",0
total BYTE "total score:",0
reroll DWORD 0;
sum DWORD 0;
cntrl BYTE 0;
prompt BYTE "Press Enter to roll the dice...";0	


.code
main PROC
			;call clrscr
	mov edx, OFFSET welcome			;WELCOME TO YAHTZEE GAME
	call WriteString
	call crlf
	mov edx, OFFSET baslik			;ORDER COMBINATION SCORE
	call WriteString
	call crlf
	mov esi,20
	mov ebx,0
	mov ecx,240						;PRINT SCORE TABLE
L1:
	mov al,menu[ebx]
	call WriteChar
	inc ebx	
	cmp ebx,esi
	jnz x
	call crlf
	add esi, 20
	x:
	loop L1
	
	;DH X COORDINATE, DL Y COORDINATE
	mov esi,0
	mov ecx,12
	mov dh,25
	mov dl,22
L2:										;print scores
	call gotoxy	
	mov eax,score[esi]
	call WriteDec
	inc dh
	inc esi
	loop L2
	
	;first
	call play_game
	call cleaning
	call clean_reg
	
	;second
	mov dh,36
	mov dl,0
	call gotoxy
	call play_game
	call cleaning
	call clean_reg
	
	;third
	mov dh,36
	mov dl,0
	call gotoxy
	call play_game
	call cleaning
	call clean_reg
	
	;fourth
	mov dh,36
	mov dl,0
	call gotoxy
	call play_game
	call cleaning
	call clean_reg
	
	;fifth
	mov dh,36
	mov dl,0
	call gotoxy
	call play_game
	call cleaning
	call clean_reg
	
	;sixth
	mov dh,36
	mov dl,0
	call gotoxy
	call play_game
	call cleaning
	call clean_reg
	
	;seventh
	mov dh,36
	mov dl,0
	call gotoxy
	call play_game
	call cleaning
	call clean_reg
	
	;eight
	mov dh,36
	mov dl,0
	call gotoxy
	call play_game
	call cleaning
	call clean_reg
	
	;nine
	mov dh,36
	mov dl,0
	call gotoxy
	call play_game
	call cleaning
	call clean_reg
	
	;ten
	mov dh,36
	mov dl,0
	call gotoxy
	call play_game
	call cleaning
	call clean_reg
	
	;eleven
	mov dh,36
	mov dl,0
	call gotoxy
	call play_game
	call cleaning
	call clean_reg
	
	;twelve
	mov dh,36
	mov dl,0
	call gotoxy
	call play_game
	call cleaning
	call clean_reg
	
	mov esi,0
	mov sum,0
	mov ecx,12
L100:
	mov eax, score[esi]
	add sum,eax
	add esi,4
	loop L100
	
	mov dh,37
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,37
	mov dl,0
	call gotoxy
	mov edx, OFFSET total
	call WriteString
	mov eax,sum
	call WriteDec
	
	
	
exit	
main ENDP


clean_reg PROC
	mov eax,0
	mov ebx,0
	mov edx,0
	mov esi,0
	mov edi,0
	mov dice[0],eax
	mov dice[4],eax
	mov dice[8],eax
	mov dice[12],eax
	mov dice[15],eax
	mov counter,0
	mov sum,0
	mov temp[0],0
	mov temp[1],0
	mov temp[2],0
	mov temp[3],0
	mov temp[4],0
	mov temp[5],0
	mov reroll,0
ret
clean_reg ENDP

cleaning PROC
	mov dh,38
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,39
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,40
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,41
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,42
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,43
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,44
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,45
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,46
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,47
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,48
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,49
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	ret
cleaning ENDP

play_game PROC
	call cleaning
	mov dh,36
	mov dl,0
	call gotoxy
	call crlf							;PRESS ENTER TO ROLL THE DICE
	mov edx,OFFSET prompt
	call WriteString
	call ReadInt
	mov dh,37
	mov dl,31
	call gotoxy
	mov edx,OFFSET emptt
	call WriteString
	
	mov dh,38
	mov dl,0
	call gotoxy
	call Randomize						;1.roll dice
	mov ecx,5
	mov ebx,1
	mov esi,0
L3:
	mov edx,OFFSET d    		
	call WriteString
	mov eax,ebx
	call WriteDec       		
	inc ebx
	mov edx,OFFSET d1    				;"Dice1: "
	call WriteString					;"Dice2: "
	mov eax,6							;"Dice3: "
	call RandomRange					;"Dice4: "
	add eax,1							;"Dice5: "
	mov dice[esi],eax
	add esi,4	
	call WriteDec
	call crlf
	loop L3

	mov edx, OFFSET choose			;"Do you want to reroll(Y/N)?:"
	call WriteString
	mov edx,0
	mov eax,0
	call crlf
	call ReadChar	
	;y=121 n=110
	cmp al,121
	jne no_select
	mov edx,OFFSET change		;"How dices do you want to reroll?"
	call WriteString
	call ReadInt
	cmp eax,5
	jbe _aw
	call play_game
	ret
	_aw:
	mov reroll,eax
	mov ecx,reroll
	mov edx,OFFSET which		;"Which dices do you want to reroll?"
	call WriteString
	jmp L4
L4:
	call ReadInt		;take index for reroll
	mov esi,eax		;save index in esi
	mov eax,6		;genarate random 
	call RandomRange
	add eax,1
	mov ebx,eax		;save random number
	dec esi
	mov eax,count
	mul esi
	mov dice[eax],ebx
	loop L4
	
	call refresh_dice
	
	
	mov dh,43
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,44
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,45
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,46
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,47
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,48
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,49
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	
	
	mov dh,43
	mov dl,0
	call gotoxy
	mov edx, OFFSET choose
	call WriteString
	mov edx,0
	mov eax,0
	call crlf
	call ReadChar
	cmp al,121
	jne no_select   			;NO SECILDI DEMEKTIR
	mov edx,OFFSET change		;"How many dice do you want to reroll?"
	call WriteString
	call ReadInt
	mov reroll, eax
	mov ecx,reroll
	mov edx,OFFSET which		;"Which dices do you want to reroll?"
	call WriteString	
	jmp L5
	

	
	L5:
	call ReadInt			;take index for reroll
	mov edi,eax
	mov esi,eax			;save index in esi
	mov eax,6			;genarate random 
	call RandomRange
	add eax,1
	mov ebx,eax			;save random number
	dec esi
	mov eax,count
	mul esi
	mov dice[eax],ebx
	
	loop L5

	call refresh_dice	
	mov dh,43
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,44
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,45
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,46
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,47
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,48
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,49
	mov dl,0
	call gotoxy
	mov edx, OFFSET emptt
	call WriteString
	mov dh,44
	mov dl,0
	call gotoxy
	call no_string
	jmp _theend	
	
	no_select:
	cmp al,110
	jne _theend
	mov dh,44
	mov dl,0
	call gotoxy
	call no_string
	ret
	_theend:
	;inc cntrl
	mov dh,44
	mov dl,0
	call gotoxy
	;mov edx,OFFSET irr
	;call WriteString
	ret

play_game ENDP

refresh_dice PROC
	mov ebx,1
	mov dh,38
	mov dl,0
	call gotoxy
	mov edx,OFFSET d
	call WriteString
	mov eax,ebx
	call WriteDec
	mov edx,OFFSET d1
	call WriteString
	mov eax,dice[0]
	call WriteDec
	inc ebx
	
	mov dh,39
	mov dl,0
	call gotoxy
	mov edx,OFFSET d
	call WriteString
	mov eax,ebx
	call WriteDec
	mov edx,OFFSET d1
	call WriteString
	mov eax,dice[4]
	call WriteDec
	inc ebx

	mov dh,40
	mov dl,0
	call gotoxy
	mov edx,OFFSET d
	call WriteString
	mov eax,ebx
	call WriteDec
	mov edx,OFFSET d1
	call WriteString
	mov eax,dice[8]
	call WriteDec
	inc ebx

	mov dh,41
	mov dl,0
	call gotoxy
	mov edx,OFFSET d
	call WriteString
	mov eax,ebx
	call WriteDec
	mov edx,OFFSET d1
	call WriteString
	mov eax,dice[12]
	call WriteDec	
	inc ebx

	mov dh,42
	mov dl,0
	call gotoxy
	mov edx,OFFSET d
	call WriteString
	mov eax,ebx
	call WriteDec
	mov edx,OFFSET d1
	call WriteString
	mov eax,dice[16]
	call WriteDec
	ret
refresh_dice ENDP
 
no_string PROC
	mov ebx,0
	mov edi,0
	mov edx,OFFSET select
	call WriteString
	call ReadInt
	cmp eax,13
	jb _dd
	call no_string
	ret
	_dd:
	cmp target[eax-1],0
	je _goo
	mov edx,OFFSET tekrar
	call WriteString
	call crlf
	call no_string
	ret
	_goo:
	mov ebx,eax		;puan atamak istediðim score ebx de
	cmp al,1				;1.ones
	jne go_2
	mov target[0],1
	mov esi,0
	mov ecx,5
L6:
	mov edi,dice[esi]
	cmp edi,1
	jne next
	inc counter
	next:
	add esi,4
	loop L6
	
	mov al,counter
	mov score[0],eax
	mov eax,0
	mov eax,score[0]
	mov dh,25
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[0]
	call WriteDec
	
	mov eax,white +(black*16)
	call settextcolor
	jmp _end
	
	go_2:				;2.twos
	cmp al,2
	jne go_3
	mov target[1],1
	mov esi,0
	mov ecx,5
L7:
	mov edi,dice[esi]
	cmp edi,2
	jne next_2
	inc counter
	next_2:
	add esi,4
	loop L7
	
	mov bl,counter
	mov al,2
	mul bl
	mov score[4],eax
	mov dh,26
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[4]
	call WriteDec
	mov eax,white +(black*16)
	call settextcolor
	jmp _end
	
	go_3:			;3.threes
	cmp al,3
	jne go_4
	mov target[2],1
	mov esi,0
	mov ecx,5
L8:
	mov edi,dice[esi]
	cmp edi,3
	jne next_3
	inc counter
	next_3:
	add esi,4
	loop L8
	
	mov bl,counter
	mov al,3				
	mul bl
	mov score[8],eax
	mov dh,27
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[8]
	call WriteDec
	mov eax,white +(black*16)
	call settextcolor
	jmp _end
	
	go_4:			;4.fours
	cmp al,4
	jne go_5
	mov target[3],1
	mov esi,0
	mov ecx,5
L9:
	mov edi,dice[esi]
	cmp edi,4
	jne next_4
	inc counter
	next_4:
	add esi,4
	loop L9
	
	mov bl,counter
	mov al,4				
	mul bl
	mov score[12],eax
	mov dh,28
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[12]
	call WriteDec
	mov eax,white +(black*16)
	call settextcolor
	jmp _end
	
	go_5:			;5.fives
	cmp al,5
	jne go_6
	mov target[4],1
	mov esi,0
	mov ecx,5
L10:
	mov edi,dice[esi]
	cmp edi,5
	jne next_5
	inc counter
	next_5:
	add esi,4
	loop L10
	
	mov bl,counter
	mov al,5				
	mul bl
	mov score[16],eax
	mov dh,29
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[16]
	call WriteDec
	mov eax,white +(black*16)
	call settextcolor
	jmp _end
	
	go_6:				;6.sixes
	cmp al,6
	jne go_7
	mov target[5],1
	mov esi,0
	mov ecx,5
L11:
	mov edi,dice[esi]
	cmp edi,6
	jne next_6
	inc counter
	next_6:
	add esi,4
	loop L11
	
	mov bl,counter
	mov al,6				
	mul bl
	mov score[20],eax
	mov dh,30
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[20]
	call WriteDec
	mov eax,white +(black*16)
	call settextcolor
	jmp _end
	
	go_7: 					;3 of a kind
	cmp al,7
	jne go_8
	mov target[6],1
	mov edi,1
	mov ecx,6
L13:
	mov counter,0
	mov esi,0
	push ecx
	mov ecx,5
L14:
	mov eax,dice[esi]
	cmp eax,edi
	jne next_7
	inc counter
	next_7:
	add esi,4
	loop L14
	mov eax,0
	mov al,counter
	mov temp[edi-1],al
	inc edi
	pop ecx
	loop L13
	
	mov sum,0
	mov eax,0
	mov ebx,0
	mov ecx,5
L27:
	mov eax,dice[ebx]
	add sum,eax
	add ebx,4
	loop L27
	
	mov eax,0
	mov ebx,0
	mov esi,0
	mov edi,0
	mov ecx,6
L26:
	mov al,temp[edi]
	cmp al,3
	jb nxx
	mov esi,sum
	nxx:
	inc edi
	loop L26
	
	mov eax,0
	mov eax,esi
	mov score[24],eax
	mov eax,0
	mov eax,score[24]
	mov dh,31
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[24]
	call WriteDec
	mov eax,white +(black*16)
	call settextcolor
	jmp _end
	
	
	go_8: 							;4 of a kind
	cmp al,8
	jne go_yahtzee
	mov target[7],1
	mov edi,1
	mov ecx,6
L16:
	mov counter,0
	mov esi,0
	push ecx
	mov ecx,5
L17:
	mov eax,dice[esi]
	cmp eax,edi
	jne next_8
	inc counter
	next_8:
	add esi,4
	loop L17
	mov eax,0
	mov al,counter
	mov temp[edi-1],al
	inc edi
	pop ecx
	loop L16
	
	mov sum,0
	mov eax,0
	mov ebx,0
	mov ecx,5
	L25:
	mov eax,dice[ebx]
	add sum,eax
	add ebx,4
	loop L25
	
	mov eax,0
	mov ebx,0
	mov esi,0
	mov edi,0
	mov ecx,6
L18:
	mov al,temp[edi]
	cmp al,4
	jb nxxt
	mov esi,sum
	nxxt:
	inc edi
	loop L18
	
	mov eax,0
	mov eax,esi
	mov score[28],eax
	mov eax,0
	mov eax,score[28]
	mov dh,32
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[28]
	call WriteDec
	mov eax,white +(black*16)
	call settextcolor
	jmp _end
	
	
	go_yahtzee:		;YAHTZEEEEE
	cmp al,9
	jne go_10
	mov counter,0
	mov target[8],1
	mov ecx,6
	mov edi,1
L12:
	mov counter,0
	mov esi,0
	push ecx
	mov ecx,5
L28:
	mov eax,dice[esi]
	cmp eax,edi
	jne next_t
	inc counter
	next_t:
	add esi,4
	loop L28
	mov al,counter
	mov temp[edi-1],al
	inc edi
	pop ecx
	loop L12
	
	mov edi,0
	mov eax,0
	mov ebx,0
	mov ecx,6
L29:
	mov al,temp[edi]
	cmp al,5
	jb nt
	mov ebx,50
	nt:
	inc edi
	loop L29	
	
	
	
	mov eax,ebx
	mov score[32],eax
	mov eax,0
	mov eax,score[32]
	mov dh,33
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[32]
	call WriteDec
	mov eax,white +(black*16)
	call settextcolor
	jmp _end
		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	go_10: 					;4 in row
	cmp al,10
	jne go_11
	mov target[9],1
	mov edi,1
	mov ecx,6
L22:
	mov counter,0
	mov esi,0
	push ecx
	mov ecx,5
L23:
	mov eax,dice[esi]
	cmp eax,edi
	jne next_10
	inc counter
	next_10:
	add esi,4
	loop L23
	mov al,counter
	mov temp[edi-1],al
	inc edi
	pop ecx
	loop L22
	
	
	mov edi,0
	mov eax,0
	mov ebx,0
	mov ecx,6
L24:
	mov al,temp[edi]
	cmp al,4
	jb nxt
	mov ebx,30
	nxt:
	inc edi
	loop L24
	
	mov eax,ebx
	mov score[36],eax
	mov dh,34
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[36]
	call WriteDec
	
	mov eax,white +(black*16)
	call settextcolor
	jmp _end
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	
	
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	go_11:
	cmp al,11
	jne go_12
	mov target[10],1
	;6sayý için 5 zara da bak
	mov edi,1
	mov ecx,6
L20:
	mov counter,0
	mov esi,0
	push ecx
	mov ecx,5
L21:
	mov eax,dice[esi]
	cmp eax,edi
	jne next_9
	inc counter
	next_9:
	add esi,4
	loop L21
	mov eax,0
	mov al,counter
	mov temp[edi-1],al
	inc edi
	pop ecx
	loop L20
	
	mov edi,0
	mov eax,0
	mov ebx,0
	mov ecx,6
L30:
	mov al,temp[edi]
	cmp al,5
	jb nnt
	mov ebx,40
	nnt:
	inc edi
	loop L30	
	
	mov eax,ebx
	mov score[40],eax
	mov eax,0
	mov eax,score[40]
	mov dh,35
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[40]
	call WriteDec
	mov eax,white +(black*16)
	call settextcolor
	jmp _end
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	go_12:
	cmp al,12
	jne _end
	mov target[11],1
	mov sum,0
	mov ebx,0
	mov ecx,5
L19:
	mov eax,dice[ebx]
	add sum,eax
	add ebx,4
	loop L19
	
	mov eax,sum
	mov score[44],eax
	mov eax,0
	mov eax,score[44]
	mov dh,36
	mov dl,22
	call gotoxy
	mov eax,red +(black*16)
	call settextcolor
	mov eax,score[44]
	call WriteDec
	mov eax,white +(black*16)
	call settextcolor
	
	_end:
	mov dh,44
	mov dl,0
	call gotoxy
	
	ret
no_string ENDP


END main
