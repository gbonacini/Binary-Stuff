CPP_FLAGS=-I.. -static -std=c++17 -fno-exceptions 
NO_STD_LIB=-nostdlib -e main

all : embeddedPrint embeddedPrint2 embeddedPrintShrinked embeddedPrintShrinked2 embeddedPrintStriped embeddedPrintShrinkedStriped embeddedFileShrinked embeddedGetc embeddedUnlink compare_size

embeddedPrint : embeddedPrint.cpp
	g++ $(CPP_FLAGS) -O0 -o embeddedPrint embeddedPrint.cpp

embeddedPrintShrinked : embeddedPrintShrinked.cpp
	g++ $(NO_STD_LIB) $(CPP_FLAGS) -O0 -o embeddedPrintShrinked embeddedPrintShrinked.cpp

embeddedPrint2 : embeddedPrint.cpp
	g++ $(CPP_FLAGS) -O2 -o embeddedPrint2 embeddedPrint.cpp

embeddedPrintShrinked2 : embeddedPrintShrinked.cpp
	g++ $(NO_STD_LIB) $(CPP_FLAGS) -O2 -o embeddedPrintShrinked2 embeddedPrintShrinked.cpp

embeddedFileShrinked : embeddedFileShrinked.cpp
	g++ $(NO_STD_LIB) $(CPP_FLAGS) -O2 -o embeddedFileShrinked embeddedFileShrinked.cpp

embeddedGetc : embeddedGetc.cpp
	g++ $(NO_STD_LIB) $(CPP_FLAGS) -O2 -o embeddedGetc embeddedGetc.cpp

embeddedUnlink : embeddedUnlink.cpp
	g++ $(NO_STD_LIB) $(CPP_FLAGS) -O2 -o embeddedUnlink embeddedUnlink.cpp

compare_size :  embeddedPrint embeddedPrintStriped embeddedPrintShrinked
	@echo "\nNote thed differences in size between the executables just created:\n"
	@echo "O0, static, no strip          : $$(du -b  ./embeddedPrint)"
	@echo "O2, static, no strip          : $$(du -b  ./embeddedPrint2)"
	@echo "O0, static, striped           : $$(du -b  ./embeddedPrintStriped)"
	@echo "O0, static, nostdlib          : $$(du -b  ./embeddedPrintShrinked)"
	@echo "O2, static, nostdlib          : $$(du -b  ./embeddedPrintShrinked2)"
	@echo "O0, static, nostdlib, striped : $$(du -b  ./embeddedPrintShrinkedStriped)"

embeddedPrintStriped: embeddedPrint
	cp embeddedPrint embeddedPrintStriped
	strip embeddedPrintStriped

embeddedPrintShrinkedStriped: embeddedPrintShrinked
	cp embeddedPrintShrinked embeddedPrintShrinkedStriped
	strip embeddedPrintShrinkedStriped

clean:
	rm -f embeddedPrint embeddedPrint2 embeddedPrintStriped embeddedPrintShrinked embeddedPrintShrinked2 embeddedPrintShrinkedStriped embeddedFileShrinked embeddedGetc samplefile.txt new_samplefile.txt to_delete.txt embeddedUnlink
