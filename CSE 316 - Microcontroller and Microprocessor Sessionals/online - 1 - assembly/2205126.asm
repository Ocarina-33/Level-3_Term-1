.MODEL SMALL
.STACK 100H

.DATA   

ARR DB 5 DUP(?)

.CODE

MAIN PROC
    MOV AX, @DATA
    MOV DS, AX 
    
    XOR BX, BX 
    MOV SI,0   
    MOV CX, 0
    
    INPUT_LOOP:
    MOV AH,1
    INT 21H
    CMP AL, 0DH
    JE END_LOOP
    CMP AL, 0AH
    JE END_LOOP
    
    AND AL, 0FH  
    
    MOV CX, AX
    
    MOV AX, 10
    MUL BX
    ADD AX, CX
    MOV BX, AX
    
    JMP INPUT_LOOP  
    
    END_LOOP:  
    CALL NEWLINE
    
    MOV AX, BX
    CALL SUM 
    
    MOV BX,10
    MOV CX,0 
    
    DIGIT:  
    XOR DX,DX
    DIV BX
    
    PUSH DX
    INC CX
    CMP AX, 0
    JNE DIGIT
        
    MOV AH,2
    PRINT:  
    POP DX
    INT 21H
    LOOP PRINT
    
    
    MOV AH,4CH
    INT 21H
    
    
    
    MAIN ENDP  

NEWLINE PROC    
    PUSH AX
    PUSH DX
    MOV AH,2
    MOV DL, 0DH
    INT 21H
    MOV DL, 0AH
    INT 21H
    POP DX
    POP AX
    
    RET
    
    NEWLINE ENDP 


SUM PROC    
    PUSH BP
    MOV BP, SP
    
    ;BASE CASE 
    CMP WORD PTR BP[4],0
    JG RECURSION
    
    MOV AX,0
    JMP RETURN   
    
    RECURSION:
    MOV AX, BP[4]
    MOV BX, 10
    
    XOR DX,DX
    DIV BX
    MOV AX,AX
    CALL SUM
    
    ADD AX,DX
    
 
    RETURN:
    POP BP
    RET 2
    
    
    SUM ENDP

END MAIN