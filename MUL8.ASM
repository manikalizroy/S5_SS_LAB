ASSUME CS:CODE, DS:DATA

DATA SEGMENT
    M1 DB 13,10,"Enter 2 Numbers: $"
    M2 DB 13,10,"Product : $"
DATA ENDS

PRTMSG MACRO MESSAGE
    LEA DX, MESSAGE     
    MOV AH, 09H        
    INT 21H
ENDM

GETDCM MACRO
    MOV AH, 01H       
    INT 21H
    SUB AL, 30H         
ENDM

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX          

    PRTMSG M1          
	GETDCM               
    MOV BL, AL           
    GETDCM     

    MOV AH, 00H
    MUL BL               
    AAM                  
    MOV BX, AX           

    PRTMSG M2            ; Print "Product : "
    MOV DL, BH           ; Print tens digit
    OR DL, 30H			; converts numeric digit → ASCII code
    MOV AH, 02H
    INT 21H

    MOV DL, BL           ; Print ones digit
    OR DL, 30H			; converts numeric digit → ASCII code
    INT 21H

    MOV AH, 4CH          
    INT 21H

CODE ENDS
END START
