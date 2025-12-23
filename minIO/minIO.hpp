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

int printScreen(const char* txt, uint64_t len){

    int ret { -1 };
    if(len == 0 || txt == nullptr) return ret;

    asm volatile (
        "\nmov %1, %%rax"
        "\nmov %2, %%rdi"
        "\nmov %3, %%rsi"
        "\nmov %4, %%rdx"
        "\nsyscall\n\t"
        "\nmov %%eax, %0"
        : "=r" (ret)
        : "i"  (1LL), 
          "i"  (1LL),
          "r"  (txt),
          "r"  (len)
        : "%rax", "%rdi", "%rsi", "%rdx");

    return ret;
}

uint64_t strnlen(const char* txt, uint64_t maxDigits){

    if(maxDigits == 0 || txt == nullptr) return 0;

    uint64_t len { 0 };
    for( ; txt[len] != 0 && len < maxDigits; len++);
    
    return len <= maxDigits ? len : 0;
}

#else
#error Unsupported Architecture
#endif

} // End Namespace

