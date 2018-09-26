all: shell2.hex


shell2: shell2.asm
	@nasm -f elf64 shell2.asm
	@ld -o shell2 shell2.o

shell2.hex : shell2
	@objdump -d shell2 | grep '^[ ]' | cut -f2 | awk '{for(i=1; i<=NF; ++i) printf "\\\\x"$$i }' > shell2.hex

clean:
	rm -f shell2.hex shell2.o shell2 test.cpp test

test.cpp: shell2.hex
	@printf "#include<iostream>\n unsigned char code[] = \"PUTITHERE\";\n int main(){\n std::cerr << \"Shellcode Length: \" << sizeof(code) << std::endl;\n ((void(*)())code)();\n return 0;\n }" | sed -s "s/PUTITHERE/`cat shell2.hex`/" > test.cpp

test: test.cpp
	@g++ -z execstack -otest test.cpp

dist: shell2.asm makefile
	tar czvf shellcode2.tar.gz shell2.asm makefile
