all : embeddedPrint

embeddedPrint : embeddedPrint.cpp
	g++ -I.. -static -std=c++17 -O2 -o embeddedPrint embeddedPrint.cpp

strip: embeddedPrint
	strip embeddedPrint

clean:
	rm -f embeddedPrint
