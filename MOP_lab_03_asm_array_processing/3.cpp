#include <iostream>
#include <cstdint>
#include <vector>

int main() {
	try {
		std::ios_base::sync_with_stdio(0); std::cin.tie(0);
		std::cout << "Enter the first array size:\n";
		size_t size1{}, size2{};
		std::cin >> size1;
		if (size1 > 10 || size1 < 0) {
			throw "Incorrect size";
		}
		std::vector<int32_t> arr1(size1, 0);
		std::cout << "Enter the first array elements (in non-decreasing order):\n";
		std::cin >> arr1[0];
		for (size_t i = 1; i < size1; ++i) {
			std::cin >> arr1[i];
			if (arr1[i] < arr1[i - 1]) {
				throw "Incorrect array input";
			}
		}
		std::cout << "Enter the second array size:\n";
		std::cin >> size2;
		if (size2 > 10 || size2 < 0) {
			throw "Incorrect size";
		}
		std::vector<int32_t> arr2(size2, 0);
		std::cout << "Enter the second array elements (in non-decreasing order):\n";
		std::cin >> arr2[0];
		for (size_t i = 1; i < size2; ++i) {
			std::cin >> arr2[i];
			if (arr2[i] < arr2[i - 1]) {
				throw "Incorrect array input";
			}
		}
		std::vector<int32_t> res;
		int32_t* p1 = arr1.data();
		int32_t* p2 = arr2.data();
		int i = 0, j = 0;
		int32_t temp[10];
		int k = 0;
		__asm {
			mov esi, p1
			mov edi, p2
			loop_start :
			mov ecx, i
				cmp ecx, size1
				jge loop_end
				mov edx, j
				cmp edx, size2
				jge loop_end
				mov eax, [esi + ecx * 4]
				mov ebx, [edi + edx * 4]
				cmp eax, ebx
				jl inc_i
				jg inc_j
				; equal
				mov ecx, k
				mov DWORD PTR temp[ecx * 4], eax
				inc k
				inc i
				inc j
				jmp loop_start
				inc_i :
			inc i
				jmp loop_start
				inc_j :
			inc j
				jmp loop_start
				loop_end :
		}
		res.assign(temp, temp + k);
		std::cout << "intersection of arrays:\n";
		for (size_t i = 0; i < res.size(); ++i) {
			std::cout << res[i] << ' ';
		}
		std::cout << '\n';
	}
	catch (const char* err) {
		std::cerr << err << '\n';
	}
	return 0;
}