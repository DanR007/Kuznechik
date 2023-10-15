all: Kuznechik clean

clean:
	rm -f *.o
Kuznechik: Crypt.o
	g++ -g -o Kuznechik Crypt.o 
Crypt.0: Crypt.cpp Kuznechik.hpp Math.h Interactive.hpp
	g++ -g -c Crypt.cpp -o Crypt.o