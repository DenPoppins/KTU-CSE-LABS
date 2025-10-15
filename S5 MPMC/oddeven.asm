data segment
 m1 db 0ah,0dh,"Enter a number (0-9): $"    ; message asking user input
 m2 db 0ah,0dh,"The number is EVEN.$"       ; message if number is even
 m3 db 0ah,0dh,"The number is ODD.$"        ; message if number is odd
data ends

code segment
assume cs:code, ds:data

start:
    mov ax, data      ; move starting address of data segment into AX register
    mov ds, ax        ; copy AX to DS, so DS points to our data segment

    lea dx, m1        ; load effective address of message m1 into DX
    mov ah, 09h       ; DOS function 09h → display string until '$'
    int 21h           ; call DOS interrupt → prints "Enter a number (0-9):"

    mov ah, 01h       ; DOS function 01h → read a single character from keyboard
    int 21h           ; result (ASCII code of key pressed) stored in AL

    sub al, 30h       ; convert ASCII digit (e.g., '5' = 53) to numeric value (5)

    test al, 1        ; bitwise test: checks if least significant bit = 1 (odd) or 0 (even)
    jz even           ; if zero flag = 1 (i.e., bit 0 is 0) → jump to even label

    lea dx, m3        ; load address of m3 (odd message)
    mov ah, 09h       ; DOS print string function
    int 21h           ; print "The number is ODD"
    jmp stop          ; jump to stop to avoid running even section

even:
    lea dx, m2        ; load address of m2 (even message)
    mov ah, 09h       ; DOS print string function
    int 21h           ; print "The number is EVEN"

stop:
    mov ah, 4ch       ; DOS terminate program function
    int 21h           ; exit to DOS
code ends
end start
