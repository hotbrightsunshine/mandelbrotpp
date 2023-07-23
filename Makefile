all: main

main: libmandelbrot
	g++ src/main.cxx -o out/main.o -lSDL2 -std=c++23 -L./libs -lmandelbrot

libmandelbrot: 
	g++ -c libs/mandelbrot.cxx -o out/mandelbrot.o -std=c++23
	ar cr libs/libmandelbrot.a out/mandelbrot.o

clear:
	find . -name "*.o" -type f -delete

run: main
	./out/main.o