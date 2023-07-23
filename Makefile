all: main

main: libmandelbrot
	g++ src/main.cxx -o out/main.o -lSDL2 -std=c++23 -L./libs -lmandelbrot -g3

libmandelbrot: 
	g++ -c libs/mandelbrot.cxx -o out/mandelbrot.o -std=c++23 -g3
	ar cr libs/libmandelbrot.a out/mandelbrot.o

clear:
	find . -name "*.o" -type f -delete

debug: main
	gdb --annotate=3 out/main.o

run: main
	./out/main.o