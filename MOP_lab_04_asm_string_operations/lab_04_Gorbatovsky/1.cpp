#include <iostream>
#include <string.h>
#include <limits>
#include <cctype>

extern "C" char* asm_copy_palindrome(char* dest, const char* src, int32_t len);
extern "C" int32_t asm_is_palindrome(const char* start, const char* end);

void solve();
void check_separator(char sep);
void palindromes(const char* str, char** ans, int32_t& ansSize, char sep);
void sort_string(char** ans, int32_t ansSize);
void free_memory(char** ans, int32_t ansSize);

int main() {
    try {
        solve();
    }
    catch (const char* err) {
        std::cerr << err << std::endl;
    }
    return 0;
}

void solve() {
    std::cout << "Enter one character - separator (Examples: !#$%&'()*+,-./:;<=>?@[]^_`{|}~ ):\n";
    char sep;
    sep = std::cin.get();
    std::cin.ignore();
    check_separator(sep);
    std::cout << "Enter a string:\n";
    char str[301];
    std::cin.getline(str, 301);
    char* ans[151];
    int32_t ansSize{};
    palindromes(str, ans, ansSize, sep);
    sort_string(ans, ansSize);
    for (size_t i = 0; i < ansSize - 1; ++i) {
        std::cout << ans[i] << ' ';
    }
    std::cout << ans[ansSize - 1];
    std::cout << '\n';
    free_memory(ans, ansSize);
}

void check_separator(char sep) {
    char separators[] = " !#$%&'()*+,-./:;<=>?@[]^_`{|}~";
    int len = strlen(separators);
    for (size_t i = 0; i < len; ++i) {
        if (sep == separators[i]) return;
    }
    throw "Error. Separator not found.";
}


void palindromes(const char* str, char* ans[], int32_t& ansSize, char sep) {
    const char* p = str;
    while (*p != '\0') {
        while (*p != '\0' && *p == sep) p++;
        if (*p == '\0') break;
        const char* word_start = p;
        while (*p != '\0' && *p != sep) p++;
        const char* word_end = p - 1;

        if (asm_is_palindrome(word_start, word_end)) {
            int32_t word_len = word_end - word_start + 1;
            ans[ansSize] = new char[word_len + 1];
            asm_copy_palindrome(ans[ansSize], word_start, word_len);
            ansSize++;
        }
    }
}

bool is_palindrome(const char* start, const char* end) {
    while (start < end) {
        if (*start != *end) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}


void sort_string(char** ans, int ansSize) {
    for (size_t i = 0; i < ansSize - 1; ++i) {
        for (size_t j = i + 1; j < ansSize; ++j) {
            int32_t len1 = strlen(ans[i]);
            int32_t len2 = strlen(ans[j]);
            if (len1 > len2) {
                std::swap(ans[i], ans[j]);
            }
        }
    }
}

void free_memory(char** ans, int32_t ansSize) {
    for (size_t i = 0; i < ansSize; ++i) {
        delete[] ans[i];
    }
}
