ASSUME CS:CODE, DS:DATA

DATA SEGMENT
    N1   DB 10,13,"Enter First number:$"
    M2   DB 10,13,"Enter Second number:$"
    M3   DB 10,13,"SUM:$"
    SUM  DB 03
DATA ENDS

PRTMSG MACRO MESSAGE
    LEA DX, MESSAGE
    MOV AH, 09
    INT 21H
ENDM

GETDCM MACRO
    MOV AH, 01
    INT 21H
    SUB AL, 30H        ; Convert ASCII to number
ENDM

PRTDCM MACRO
    MOV DL, [SI]
    ADD DL, 30H        ; Convert number to ASCII
    MOV AH, 02
    INT 21H
ENDM

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX

    ; --- Input first number ---
    PRTMSG N1
    GETDCM
    MOV BH, AL          ; Store first digit
    GETDCM
    MOV BL, AL          ; Store second digit

    ; --- Input second number ---
    PRTMSG M2
    GETDCM
    MOV CH, AL          ; Store first digit
    GETDCM
    MOV CL, AL          ; Store second digit

    ; --- Add ones place ---
    ADD BL, CL
    MOV AL, BL
    MOV AH, 00
    AAA
    LEA SI, SUM
    MOV [SI], AL

    ; --- Add tens place and carry ---
    ADD BH, AH
    ADD BH, CH
    MOV AL, BH
    MOV AH, 00
    AAA
    INC SI
    MOV [SI], AL
    INC SI
    MOV [SI], AH

    ; --- Display result ---
    PRTMSG M3
    PRTDCM              ; Units
    DEC SI
    PRTDCM              ; Tens
    DEC SI
    PRTDCM              ; Hundreds (if any)

    ; --- Exit program ---
    MOV AH, 4CH
    INT 21H

CODE ENDS
END START
