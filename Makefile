all: Kuznechik clean

clean:
	rm -f *.o
Kuznechik: Crypt.o
	g++ -g -o Kuznechik Crypt.o 
Crypt.0: Crypt.cpp Crypt.h Math.h Interactive.h
	g++ -g -c Crypt.cpp -o Crypt.o