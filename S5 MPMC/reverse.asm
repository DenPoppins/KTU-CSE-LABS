data segment
    str db "HELLO$", 0          ; string to reverse (ends with $)
    msg db 0ah,0dh, "Reversed string: $"
data ends

code segment
assume cs:code, ds:data

start:
    mov ax, data                ; load address of data segment
    mov ds, ax                  ; initialize DS register

    lea si, str                 ; SI points to start of string
    lea di, str                 ; DI used to find end of string

find_end:
    mov al, [di]                ; read character from DI
    cmp al, '$'                 ; check for end of string
    je reverse                  ; jump when '$' is found
    inc di                      ; move to next character
    jmp find_end                ; repeat until '$'

reverse:
    dec di                      ; move DI to last character (before '$')

    lea dx, msg                 ; load address of message
    mov ah, 09h                 ; DOS print string function
    int 21h                     ; display "Reversed string:"

print_loop:
    cmp di, si                  ; compare end pointer and start pointer
    jb done                     ; if DI < SI, all characters printed
    mov dl, [di]                ; get current character
    mov ah, 02h                 ; DOS function to print single character
    int 21h                     ; print the character
    dec di                      ; move backwards through the string
    jmp print_loop              ; repeat until done

done:
    mov ah, 4ch                 ; terminate program
    int 21h

code ends
end start
