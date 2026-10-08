#include <iostream>
#include <cstdint>

int main() {
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    double x{}, temp{};
    const double one = 1.0, two = 2.0, three = 3.0, four = 4.0;
    std::cout << "Enter integer:\n";
    std::cin >> x;
    __asm {
        fld x
        fldz
        fcompp
        fstsw ax
        sahf
        jg second
        fld x
        fadd four
        jmp end_label

    second:
        fld x
        fld1
        fcompp
        fstsw ax
        sahf
        jae third
        fld x
        fadd one
        jmp end_label

    third:
        fld x
        fld two
        fcompp
        fstsw ax
        sahf
        ja fourth
        fld two
        jmp end_label

    fourth:
        fld x
        fmul three
        fsub four

    end_label:
        fstp temp
    }
    std::cout << temp << '\n';
    return 0;
}