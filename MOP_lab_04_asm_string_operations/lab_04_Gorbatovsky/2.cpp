#include <iostream>
#include <cstring>

int asm_strcmp(const char* s1, const char* s2) {
    int result{};

    __asm {
        push esi
        push edi

        mov esi, s1
        mov edi, s2

        compare_loop :
        mov al, [esi]
            mov ah, [edi]
            cmp al, ah
            jne diff
            test al, al
            jz equal_strings
            inc esi
            inc edi
            jmp compare_loop

            diff :
        movzx eax, al
            movzx edx, ah
            sub eax, edx
            mov result, eax
            jmp finish

            equal_strings :
        mov result, 0

            finish :
            pop edi
            pop esi
    }

    return result;
}

char* asm_strcpy(char* dest, const char* src) {
    __asm {
        push esi
        push edi

        mov edi, dest
        mov esi, src

        copy_loop :
        mov al, [esi]
            mov[edi], al
            inc esi
            inc edi
            test al, al
            jnz copy_loop

            pop edi
            pop esi
    }

    return dest;
}

const char* asm_strchr(const char* str, char ch) {
    const char* result{};

    __asm {
        push esi

        mov esi, str
        mov dl, ch

        find_loop :
        mov al, [esi]
            cmp al, dl
            je found
            test al, al
            jz not_found
            inc esi
            jmp find_loop

            found :
        mov result, esi
            jmp finish

            not_found :
        mov result, 0

            finish :
            pop esi
    }

    return result;
}

void asm_replace_char(char* str, char old_char, char new_char) {
    __asm {
        push edi
        push ebx

        mov edi, str
        mov al, old_char
        mov ah, new_char

        replace_loop :
        mov bl, [edi]
            test bl, bl
            jz finish
            cmp bl, al
            jne skip
            mov[edi], ah

            skip :
        inc edi
            jmp replace_loop

            finish :
        pop ebx
            pop edi
    }
}

int main() {
    char s1[] = "hello";
    char s2[] = "hello";
    char s3[] = "world";
    char buffer[50]{};
    char test[] = "Hello, world!";

    std::cout << "strcmp test:" << std::endl;
    std::cout << "asm_strcmp(\"hello\", \"hello\") = " << asm_strcmp(s1, s2) << std::endl;
    std::cout << "asm_strcmp(\"hello\", \"world\") = " << asm_strcmp(s1, s3) << std::endl;

    std::cout << "\nstrcpy test:" << std::endl;
    asm_strcpy(buffer, "Copy this string");
    std::cout << "Copied: " << buffer << std::endl;

    std::cout << "\nstrchr test:" << std::endl;
    const char* pos = asm_strchr(test, 'w');
    if (pos != nullptr) {
        std::cout << "Found 'w' at position " << (pos - test) << " in \"" << test << "\"" << std::endl;
    }
    else {
        std::cout << "'w' not found" << std::endl;
    }

    std::cout << "\nreplace char test:" << std::endl;
    char replace_str[] = "aabbaa";
    std::cout << "Original: " << replace_str << std::endl;
    asm_replace_char(replace_str, 'a', 'x');
    std::cout << "After replacing 'a' with 'x': " << replace_str << std::endl;

    return 0;
}