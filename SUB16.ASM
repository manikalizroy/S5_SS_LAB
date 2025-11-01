ASSUME CS:CODE, DS:DATA

DATA SEGMENT
    N1   DB 10,13,"Enter First number:$"
    M2   DB 10,13,"Enter Second number:$"
    M3   DB 10,13,"DIFFERENCE:$"
    DIFF DB 03 DUP(?)
DATA ENDS

PRTMSG MACRO MESSAGE
    LEA DX, MESSAGE
    MOV AH, 09
    INT 21H
ENDM

GETDCM MACRO
    MOV AH, 01
    INT 21H
    SUB AL, 30H          ; Convert ASCII to number
ENDM

PRTDCM MACRO
    MOV DL, [SI]
    ADD DL, 30H          ; Convert number to ASCII
    MOV AH, 02
    INT 21H
ENDM

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX

    PRTMSG N1
    GETDCM
    MOV BH, AL           ; Store first digit
    GETDCM
    MOV BL, AL           ; Store second digit

    PRTMSG M2
    GETDCM
    MOV CH, AL           ; Store first digit
    GETDCM
    MOV CL, AL           ; Store second digit

    ; --- Subtract ones place ---
    SUB BL, CL
    MOV AL, BL
    MOV AH, 00
    AAS                  ; Adjust after subtraction
    LEA SI, DIFF
    MOV [SI], AL

    ; --- Subtract tens place with borrow ---
    SBB BH, CH
    MOV AL, BH
    MOV AH, 00
    AAS
    INC SI
    MOV [SI], AL
    INC SI
    MOV [SI], AH

    PRTMSG M3
    PRTDCM               ; Units
    DEC SI
    PRTDCM               ; Tens
    DEC SI
    PRTDCM               ; Hundreds (if any)

    MOV AH, 4CH
    INT 21H

CODE ENDS
END START
