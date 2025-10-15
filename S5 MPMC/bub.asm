data segment
    arr db 5, 3, 1, 4, 2       ; array of 5 numbers
    len db 5                   ; number of elements
    msg db 0ah,0dh, "Sorted array: $"
data ends

code segment
assume cs:code, ds:data

start:
    mov ax, data               ; load address of data segment
    mov ds, ax                 ; initialize DS register

    mov cl, len                ; load length of array into CL
    dec cl                     ; outer loop counter = n - 1

outer:
    mov ch, cl                 ; inner loop counter
    mov si, 0                  ; SI used as array index

inner:
    mov al, arr[si]            ; load current element into AL
    mov bl, arr[si+1]          ; load next element into BL
    cmp al, bl                 ; compare AL and BL
    jbe skip                   ; if AL ≤ BL, skip swapping

    mov arr[si], bl            ; swap values if out of order
    mov arr[si+1], al

skip:
    inc si                     ; move to next element
    dec ch                     ; decrease inner loop counter
    jnz inner                  ; repeat inner loop if not finished

    dec cl                     ; decrease outer loop counter
    jnz outer                  ; repeat outer loop if not finished

    lea dx, msg                ; load address of message
    mov ah, 09h                ; DOS print string function
    int 21h                    ; display "Sorted array:"

    mov cl, len                ; reload length to print all numbers
    mov si, 0

display:
    mov dl, arr[si]            ; move element into DL
    add dl, 30h                ; convert number to ASCII
    mov ah, 02h                ; DOS function to print character
    int 21h
    mov dl, ' '                ; print space between numbers
    int 21h
    inc si
    dec cl
    jnz display

    mov ah, 4ch                ; terminate program
    int 21h

code ends
end start
