ASSUME CS:CODE,DS:DATA
DATA SEGMENT
 M1 DB 10,13,"Enter first number;$"
 M2 DB 10,13,"Enter second number:$"
 M3 DB 10,13,"Product:$"
 PROD DB 4(00H)
DATA ENDS

PRTMSG MACRO MESSAGE
  LEA DX,MESSAGE
  MOV AH,09
  INT 21H
ENDM

GETDCM MACRO
  MOV AH,01
  INT 21H
  SUB AL,30H
ENDM

PRTDCM MACRO
  MOV DL,[SI]
  ADD DL,30H
  MOV AH,02
  INT 21H
ENDM

CODE SEGMENT
 START:
       MOV AX,DATA
       MOV DS,AX
       
       PRTMSG M1
       GETDCM
       MOV BH,AL
       GETDCM
       MOV BL,AL

       PRTMSG M2
       GETDCM
       MOV CH,AL
       GETDCM
       MOV CL,AL

       LEA SI,PROD
       MOV AH,00H
       MUL BL        ; ie CL * BL
       AAM
       MOV [SI],AL
       INC SI
       MOV [SI],AH
       MOV AH,00H

       MOV AL,BH
       MUL CL        ; ie CL * BH
       AAM

       MOV DX,AX        ; DX stores result contained in AX
       ADD DL,[SI]
       MOV AH,00H

       MOV AL,CH      
       MUL BL        ; CH * BL
       AAM
       ADD DX,AX     ;  Add partial product to running sum
       MOV AL,DL      ;  Isolate lower byte
       MOV AH,00H     
       AAM
       ADD DH,AH     ;  Propagate carry
       MOV DL,DH       ;  Shift and clear for next digit
       MOV DH,00H       ;  Shift and clear for next digit
       MOV [SI],AL
       INC SI
       MOV AH,00H       ;  Reset AH

       MOV AL,BH
       MUL CH
       AAM
       ADD DX,AX
       MOV AL,DL
       MOV AH,00H
       AAM
       MOV [SI],AL
       INC SI
       ADD DH,AH
       MOV AL,DH
       MOV [SI],AL
       
       PRTMSG M3
       PRTDCM
       DEC SI
       PRTDCM
       DEC SI
       PRTDCM
       DEC SI
       PRTDCM

       MOV AH,4CH
       INT 21H
CODE ENDS
END START
