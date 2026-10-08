; string_ops.asm
.code

asm_copy_palindrome PROC
    mov     rax, rcx
    push    rsi
    push    rdi
    mov     rsi, rdx
    mov     rdi, rcx
    mov     rcx, r8
    cld
copy_loop:
    lodsb
    stosb
    loop    copy_loop
    mov     byte ptr [rdi], 0
    pop     rdi
    pop     rsi
    ret
asm_copy_palindrome ENDP

asm_is_palindrome PROC
    xor     eax, eax
    cmp     rcx, rdx
    jae     return_true
    push    rbx
    mov     rbx, rcx
    mov     rcx, rdx
check_loop:
    mov     al, byte ptr [rbx]
    mov     dl, byte ptr [rcx]
    cmp     al, dl
    jne     not_palindrome
    inc     rbx
    dec     rcx
    cmp     rbx, rcx
    jb      check_loop
return_true:
    mov     eax, 1
not_palindrome:
    pop     rbx
    ret
asm_is_palindrome ENDP

END