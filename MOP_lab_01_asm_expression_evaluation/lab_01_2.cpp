#include <iostream>

int main() {
    try {
        double x{}, y{}, result{}, three{ 3.0 }, denom{};
        std::cout << "Enter 2 integers:" << '\n';
        std::cin >> x >> y;
        if (x <= 0) {
            throw "Incorrect integers";
        }
        __asm {
            fld1
            fld x
            fyl2x
            fldln2
            fmulp st(1), st
            fmul x
            fstp result

            fld x
            fcos
            fld x
            fdiv three
            fsubp st(1), st
            fstp denom

            fld y
            fdiv denom
            fadd result
            fstp result
        }
        std::cout << "x*ln(x) + y/(cos(x) - x/3) = " << result << '\n';
    }
    catch (const char* err) {
        std::cerr << err << '\n';
    }
    return 0;
}