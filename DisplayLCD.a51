LCD		EQU P1 
RS		BIT	P2.0
RW		BIT	P2.1
EN		BIT	P2.2
ORG		0100H
ACALL	XOA_LCD_SAU_KHI_RESET
ACALL	SANG_FULL_LED_DON
ACALL	khoi_tao_lcd
ACALL	ghi_du_lieu
;-----------------XOA_LCD_SAU_KHI_RESET---------------------
XOA_LCD_SAU_KHI_RESET:
	MOV 	A,#01
	ACALL	ghi_lenh
RET
;---------------------------------sang tat ca led don---------------
SANG_FULL_LED_DON:
	MOV A, #00101010B
	MOV P3, A
	ACALL 	DELAY01S
	MOV A, #11111111B
	MOV P3, A
	ACALL 	DELAY01S
	MOV A, #00101010B
	MOV P3, A
	ACALL 	DELAY01S
	MOV A, #11111111B
	MOV P3, A
	RET
;--------------chuong trinh con khoi tao lcd ------------------------	
khoi_tao_lcd:
	MOV		A, #1h		; xoa man hinh
	ACALL	ghi_lenh
	MOV 	A, #38h		; khoi tao LCD hai dong 5x7
	ACALL	ghi_lenh
	MOV 	A, #0CH		; hien thi man hinh, tat con tro
	ACALL	ghi_lenh
RET	
; ------------- chuong trinh con ghi lenh----------------------------
ghi_lenh:
	MOV		LCD,A
	CLR		RS			; dat RS=0 de chon thanh ghi lenh
	CLR		RW			; dat RW=0 de ghi du lieu LCD
	SETB	EN
	NOP
	NOP
	CLR		EN
	ACALL	timer
RET
;------------- chuong trinh con ghi du lieu -----------------------
ghi_du_lieu: 
		acall	set_local_1
		acall	set_local_2
; hien thi dong 1
	LAP:
		MOV		A,R0
		ACALL	ghi_lenh
		MOV		DPTR, #line1
		ACALL	out_line_1
; hien thi dong 2
		mov 	A, R1
		acall	ghi_lenh
		mov		DPTR, #line2
		acall	out_line_1
		acall	DELAY01S
		dec 	R0				; Giam vi tri cua dong 1 de dich trai
		inc 	R1				; Tang vi tri cua dong 2 de dich phai
		mov 	A,#01H
		acall 	ghi_lenh
		
		cjne	R0,#080H,hihi
		acall	set_local_1
hihi:	cjne	R1,#0D1H,hihii
		acall   set_local_2
hihii:	jmp 	LAP
ret
;----------------------khoi tao local cho line 1 and line2-------------------
	set_local_1:	
		mov 	R0,#8FH
		ret
	set_local_2:	
		mov 	R1,#0B0H
		ret
; ---------- chuong trinh con hien thi mot dong ket thuc boi so 0------------
out_line_1:
	LAP1:	
		clr		A
		movc	A,@A+DPTR	; chuyen nd o nho (ma ASCII cua ky tu can hien thi) vao A
		JZ		skip		; nhay toi nhan “skip” neu A=0 (het dong)
		acall	out_char
		inc 	DPTR
		sjmp	LAP1
	skip:
ret
;------------------- chuong trinh con hien thi mot ky tu------------
out_char:
	MOV 	LCD, A
	SETB	RS
	CLR 	EN
	SETB	EN
	NOP
	NOP
	CLR 	EN
	ACALL	timer
RET
;----------------------CTC tao do tre 1s------------------------------------------
DELAY01S:
	mov 	R3,#200
again_1s:
	acall	timer
	djnz	R3,again_1s
ret
;----------------------khoi tao timer voi do tre la 2ms -------------------------
timer:
		MOV 	R5,#2
		MOV 	TMOD,#01
	here:
		MOV 	TL0,#08H		; #LOW(-1000)
		MOV 	TH0,#0FCH		; #HIGH(-1000)
		SETB	TR0				; khoi dong timer 0
	again:
		JNB 	TF0,again
		CLR 	TR0		
		CLR 	TF0	
		DJNZ 	R5,here
RET
;-------------------------------------------------------------------------------------------
line1:	DB	"DIEM 10",0
line2:	DB	"NGUYEN THANH QUANG",0
END