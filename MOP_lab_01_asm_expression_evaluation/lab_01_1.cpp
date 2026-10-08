#include <iostream>
#include <cstdint>

int main() {
	try {
		int32_t a{}, b{}, c{}, x{}, Y{};
		std::cout << "Enter 4 integers:" << '\n';
		std::cin >> a >> b >> c >> x;
		if (b == 0 || a == 0) {
			throw "Incorrect integers";
		}
		__asm {
			mov eax, b
			imul eax
			imul b
			mov ecx, eax
			mov eax, 25
			mov edx, 0
			cdq
			idiv ecx

			mov ebx, a
			imul ebx, 4
			imul ebx, c

			add ebx, eax

			mov eax, x
			imul eax
			imul x
			imul a
			mov ecx, 2
			cdq
			idiv ecx

			add ebx, eax
			mov Y, ebx

			mov eax, x
			imul eax
			imul eax, 3

			mov ebx, eax

			mov eax, b
			mov ecx, 7
			imul ecx, a
			cdq
			idiv ecx

			sub ebx, eax
			sub ebx, 6

			mov eax, Y
			cdq
			idiv ebx

			mov Y, eax
		}
		std::cout << "Y = (25/b^3 + 4ac +(ax^3)/2) / (3x^2 - b/7a - 6) = " << Y << '\n';
	}
	catch (const char* err) {
		std::cerr << err << '\n';
	}
	return 0;
}