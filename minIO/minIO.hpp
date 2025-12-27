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
using mode_t=unsigned int;

const mode_t S_EMPTY      {00000000},  
             S_IRWXU      {00000700},  
             S_IRUSR      {00000400},  
             S_IWUSR      {00000200},  
             S_IXUSR      {00000100},  
             S_IRWXG      {00000070},  
             S_IRGRP      {00000040},  
             S_IWGRP      {00000020},  
             S_IXGRP      {00000010},  
             S_IRWXO      {00000007},  
             S_IROTH      {00000004},  
             S_IWOTH      {00000002},  
             S_IXOTH      {00000001},  
             S_ISUID      {00004000},  
             S_ISGID      {00002000},  
             S_ISVTX      {00001000},  
             O_ACCMODE    {00000003},
             O_RDONLY     {00000000},
             O_WRONLY     {00000001},
             O_RDWR       {00000002},
             O_CREAT      {00000100},   
             O_EXCL       {00000200}, 
             O_NOCTTY     {00000400}, 
             O_TRUNC      {00001000}, 
             O_APPEND     {00002000},
             O_NONBLOCK   {00004000},
             O_DSYNC      {00010000}, 
             FASYNC       {00020000}, 
             O_DIRECT     {00040000}, 
             O_LARGEFILE  {00100000},
             O_DIRECTORY  {00200000}, 
             O_NOFOLLOW   {00400000}, 
             O_NOATIME    {01000000},
             O_CLOEXEC    {02000000}; 


uint64_t write(unsigned int fd, const char* txt, uint64_t len) noexcept {

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
          "r"  (static_cast<uint64_t>(fd)),
          "r"  (txt),
          "r"  (len)
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11");

    return ret > 0 ? ret: 0;
}

uint64_t printScreen(const char* txt, uint64_t len) noexcept {
    return write(1, txt, len);
}

uint64_t read(unsigned int fd, char* txt, uint64_t len) noexcept {

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
        : "i"  (0ULL),
          "r"  (static_cast<uint64_t>(fd)),
          "r"  (txt),
          "r"  (len)
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11", "memory");

    return ret > 0 ? ret: 0;
}

char getChar(void){
   char buff {0};
   uint64_t ret { read(0, &buff, 1) };

   return ret != 0 ? buff : 0;
}

void exit(bool err=false) noexcept {

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

int open(const char *path, mode_t flags, mode_t mode=S_EMPTY)  noexcept {

    int ret { -1 };
    if(path == nullptr) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%esi"
        "\nmov %4, %%edx"
        "\nsyscall"
        "\nmov %%eax, %0"
        : "=r" (ret)
        : "i"  (0x02ULL),
          "r"  (path),
          "r"  (flags),
          "r"  (mode)
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11");

    return ret > 0 ? ret: -1;
}

int close(int fd)  noexcept {

    int ret { -1 };

    asm volatile (
        "\nmov %1, %%rax"
        "\nsyscall"
        "\nmov %%eax, %0"
        : "=r" (ret)
        : "i"  (0x03ULL)
        : "%rax", "%rcx", "%r11");

    return ret > 0 ? ret: -1;
}

uint64_t strnlen(const char* txt, uint64_t maxDigits) noexcept {

    if(maxDigits == 0 || txt == nullptr) return 0;

    uint64_t len { 0 };
    for( ; txt[len] != 0 && len < maxDigits; len++);

    return len <= maxDigits ? len : 0;
}

const char* digitToTxt(unsigned char digit) noexcept {
    static const char lookup[11] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ' };
    return &lookup[digit < 10 ? digit : 10];
}

char digitToChar(unsigned char digit) noexcept {
    return *digitToTxt(digit);
}

void printDigit(unsigned char digit) noexcept {
    printScreen(digitToTxt(digit), 1);
}

void printNumber(uint64_t number) noexcept {
    const unsigned int    MAX_DIGITS         { 20 };
    static unsigned char  numTxt[MAX_DIGITS];
    
    if(number != 0){
       int idx{0};
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

const char* numberToString(uint64_t number) noexcept {
    const unsigned int    MAX_DIGITS         { 20 };
    static char           numTxt[MAX_DIGITS + 1];
    
    int idx{0};
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

