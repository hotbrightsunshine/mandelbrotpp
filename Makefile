all: main

main: libmandelbrot
	g++ src/main.cxx -o out/main.o -lSDL2 -std=c++23 -L./libs -lmandelbrot

libmandelbrot: 
	g++ -c libs/mandelbrot.cxx -o out/mandelbrot.o
	ar cr libs/libmandelbrot.a out/mandelbrot.o

clear:
	rm -rf *.a *.o *.so 

run: main
	./out/main.o