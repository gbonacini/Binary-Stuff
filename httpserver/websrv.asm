;shell.asm

[SECTION .text]
global _start
_start:
          mov       rax,      41                ; socket syscall (41)
          mov       rdi,      2                 
          mov       rsi,      1                 
          xor       rdx,      rdx               
          syscall                               

          xchg      rax,      rdi               
          mov       r9,       rdi               

          mov       rax,      54                ; setsockopt syscall (54)
          mov       rsi,      1                 
          mov       rdx,      2                 
          mov       r10,      on                
          mov       r8,       1                 
          syscall                               
          
          mov       dx,       0xB022            
          shl       rdx,      16                
          xor       dl,       2                 
          push      rdx          
          mov       rsi,      rsp

          mov       rdx,      16                
          mov       rax,      49                ; bind syscall (49)
          syscall                               
          
                                                
          mov       rsi,      5                 
          mov       rax,      50                ; listen syscall (50)
          syscall                               

          jmp short ender

          starter:

                                                
          xor       rsi,      rsi               
          xor       rdx,      rdx               
          mov       rax,      43                ; accept syscall (43)
          syscall                               

          mov       rdi,      rax               

          mov       rsi,      buff
          mov       rdx,      512

          xor       rax,      rax               ; read  syscall (0)
          syscall                               

          mov       rsi,      page
          mov       rdx,      pagelen

          mov       rax,      1                 ; write  syscall (1)
          syscall                               

                                                
          mov       rax,      3                 ; close syscall (3)
          syscall                               

          mov       rdi,      r9                


          ender:
          call starter                         

[SECTION .rodata]
          page:     db        "HTTP/1.1 200 OK",10,10,"<html><header></header><body>Hello world</body></html>"
          pagelen:  equ $ -   page
          on:       db        1

[section .bss]
          buff resb 512

