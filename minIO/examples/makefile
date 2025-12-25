CPP_FLAGS=-I.. -static -std=c++17 -fno-exceptions -O0
NO_STD_LIB=-nostdlib -e main

all : embeddedPrint embeddedPrintShrinked embeddedPrintStriped embeddedPrintShrinkedStriped compare_size

embeddedPrint : embeddedPrint.cpp
	g++ $(CPP_FLAGS) -o embeddedPrint embeddedPrint.cpp

embeddedPrintShrinked : embeddedPrintShrinked.cpp
	g++ $(NO_STD_LIB) $(CPP_FLAGS) -o embeddedPrintShrinked embeddedPrintShrinked.cpp

compare_size :  embeddedPrint embeddedPrintStriped embeddedPrintShrinked
	@echo "\nNote thed differences in size between the executables just created:\n"
	@echo "static, no strip          : $$(du -b  ./embeddedPrint)"
	@echo "static, striped           : $$(du -b  ./embeddedPrintStriped)"
	@echo "static, nostdlib          : $$(du -b  ./embeddedPrintShrinked)"
	@echo "static, nostdlib, striped : $$(du -b  ./embeddedPrintShrinkedStriped)"

embeddedPrintStriped: embeddedPrint
	cp embeddedPrint embeddedPrintStriped
	strip embeddedPrintStriped

embeddedPrintShrinkedStriped: embeddedPrintShrinked
	cp embeddedPrintShrinked embeddedPrintShrinkedStriped
	strip embeddedPrintShrinkedStriped

clean:
	rm -f embeddedPrint embeddedPrintStriped embeddedPrintShrinked embeddedPrintShrinkedStriped
