#include <iostream>

int main() {
    try {
        double a, b, result;
        char op;
        std::cout << "Enter 2 real numbers:\n";
        std::cin >> a >> b;
        std::cout << "Enter operation (example : \" + - * / \")" << std::endl;
        std::cin >> op;
        if (b == 0 && op == '/') {
            throw "Incorrect number";
        }
        __asm {
            mov al, op
            cmp al, '+'
            je add_op
            cmp al, '-'
            je sub_op
            cmp al, '*'
            je mul_op
            cmp al, '/'
            je div_op
            jmp error

            add_op :
            fld b
                fld a
                faddp st(1), st(0)
                jmp save
                sub_op :
            fld b
                fld a
                fsubrp st(1), st(0)
                jmp save
                mul_op :
            fld b
                fld a
                fmulp st(1), st(0)
                jmp save
                div_op :
            fld b
                fld a
                fdivrp st(1), st(0)
                jmp save
                error :
            fldz
                fstp result
                jmp done
                save :
            fstp result
                done :
        }
        std::cout << "Result:\n" << result << std::endl;
    }
    catch (const char* err) {
        std::cerr << err << '\n';
    }
    return 0;
}
