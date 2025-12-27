// -----------------------------------------------------------------
// Copyright (C) 2025  Gabriele Bonacini
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
// -----------------------------------------------------------------


#pragma once

namespace minIO {

#if defined(__x86_64__)

using uint64_t=unsigned long long;

uint64_t printScreen(const char* txt, uint64_t len){

    long long ret { -1 };
    if(len == 0 || txt == nullptr) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nsyscall"
        "\nmov %%rax, %0"
        : "=r" (ret)
        : "i"  (1ULL),
          "i"  (1ULL),
          "r"  (txt),
          "r"  (len)
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11");

    return ret > 0 ? ret: 0;
}

void exit(bool err=false){

    uint64_t ret { err ? 1ULL : 0ULL };
    asm volatile (
        "\nmov %0, %%rax"
        "\nmov %1, %%rdi"
        "\nsyscall"
        : // void
        : "i"  (0x3cULL),
          "r"  (ret)
        : "%rax", "%rdi", "%rcx", "%r11");
}

uint64_t strnlen(const char* txt, uint64_t maxDigits){

    if(maxDigits == 0 || txt == nullptr) return 0;

    uint64_t len { 0 };
    for( ; txt[len] != 0 && len < maxDigits; len++);

    return len <= maxDigits ? len : 0;
}

const char* digitToTxt(unsigned char digit){
    static const char lookup[11] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ' };
    return &lookup[digit < 10 ? digit : 10];
}

char digitToChar(unsigned char digit){
    return *digitToTxt(digit);
}

void printDigit(unsigned char digit){
    printScreen(digitToTxt(digit), 1);
}

void printNumber(uint64_t number){
    const unsigned int    MAX_DIGITS         { 20 };
    static unsigned char  numTxt[MAX_DIGITS];
    
    if(number != 0){
       volatile int idx{0};
       for(; idx < MAX_DIGITS; idx++) numTxt[idx] = 0;

       idx=MAX_DIGITS-1;
       for(; number > 0; number /= 10){
           unsigned char digit { static_cast<unsigned char>(number % 10) };
           numTxt[idx]         = digit;
           idx--;
       }

       idx++;
       for(; idx < MAX_DIGITS; idx++)
           printDigit(numTxt[idx]);

    } else {

       printDigit(0);

    }
}

const char* numberToString(uint64_t number){
    const unsigned int    MAX_DIGITS         { 20 };
    static char           numTxt[MAX_DIGITS + 1];
    
    volatile int idx{0};
    if(number != 0){
       for(; idx <= MAX_DIGITS; idx++) numTxt[idx] = 0;

       idx=MAX_DIGITS-1;
       for(; number > 0; number /= 10){
           unsigned char digit { static_cast<unsigned char>(number % 10) };
           numTxt[idx]         = digitToChar(digit);
           idx--;
       }

       idx++;

    } else {

       idx = MAX_DIGITS - 1;
       numTxt[idx] = '0';

    }

    return numTxt + idx;
}

#else
#error Unsupported Architecture
#endif

} // End Namespace

