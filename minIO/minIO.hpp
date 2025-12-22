#pragma once

namespace minIO {

#if defined(__x86_64__)

using uint64_t=unsigned long long int;

int printScreen(const char* txt, uint64_t len){

    int ret = { -1 };

    asm volatile ("\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nsyscall\n\t"
        : "=r" (ret)
        : "i"  (1LL), 
          "i"  (1LL),
          "r"  (txt),
          "r"  (len)
        : "%rax", "%rdi", "%rsi", "%rdx");

    return ret;
}

uint64_t strnlen(const char* txt, uint64_t maxDigits){
    uint64_t len { 0 };
    for( ; txt[len] != 0; len++);
    
    return len <= maxDigits ? len : 0;
}

#else
# error Unsupported Architecture
#endif

} // End Namespace
