#include <iostream>
using namespace std;

void swapFirstMaxLastMin(int arr[], int n) {
    __asm {
        mov esi, arr
        mov ecx, n
        test ecx, ecx
        jz done
        mov eax, [esi]
        mov ebx, 0
        mov edx, 0
        dec ecx
        jz find_min
        find_max_loop :
        inc edx
            cmp eax, [esi + edx * 4]
            jge not_new_max
            mov eax, [esi + edx * 4]
            mov ebx, edx
            not_new_max :
        loop find_max_loop
            find_min :
        mov ecx, n
            mov eax, [esi]
            mov edx, 0
            mov edi, 0
            dec ecx
            jz swap_elements
            find_min_loop :
        inc edx
            cmp eax, [esi + edx * 4]
            jle not_new_min
            mov eax, [esi + edx * 4]
            mov edi, edx
            jmp cont_min
            not_new_min :
        cmp eax, [esi + edx * 4]
            jne cont_min
            mov edi, edx
            cont_min :
        loop find_min_loop
            swap_elements :
        cmp ebx, edi
            je done
            mov eax, [esi + ebx * 4]
            mov ecx, [esi + edi * 4]
            mov[esi + ebx * 4], ecx
            mov[esi + edi * 4], eax
            done :
    }
}

int main() {
    const int MAX_N = 100;
    int A[MAX_N];
    int n;
    cout << "Vvedite razmer massiva (n <= 100): ";
    cin >> n;
    if (n < 1 || n > MAX_N) {
        cout << "Nekorrektnyj razmer.\n";
        return 1;
    }
    cout << "Vvedite " << n << " tselyh chisel:\n";
    for (int i = 0; i < n; ++i)
        cin >> A[i];
    swapFirstMaxLastMin(A, n);
    cout << "Rezultat:\n";
    for (int i = 0; i < n; ++i)
        cout << A[i] << " ";
    cout << endl;
    return 0;
}