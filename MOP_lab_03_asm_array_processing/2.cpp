#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;
    int A[100];
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) cin >> A[i];

    int cnt = 0;

    __asm {
        push ebp
        push esi
        push edi
        push ebx

        lea ebx, A
        mov ecx, n
        cmp ecx, 3
        jl done2

        mov esi, 1
        loop2:
        mov eax, [ebx + esi * 4]
            mov edx, [ebx + (esi - 1) * 4]
            mov edi, [ebx + (esi + 1) * 4]

            cmp eax, edx
            jl check_less
            jg check_greater
            jmp next2

            check_less :
        cmp eax, edi
            jl inc_cnt
            jmp next2

            check_greater :
        cmp eax, edi
            jg inc_cnt
            jmp next2

            inc_cnt :
        add cnt, 1

            next2 :
            inc esi
            cmp esi, ecx
            jl loop2

            done2 :
        pop ebx
            pop edi
            pop esi
            pop ebp
    }

    cout << "Number of local minima/maxima: " << cnt << endl;
    return 0;
}
