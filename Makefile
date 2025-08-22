build:
	g++ main.cpp glad.c -lglfw -lGL

run: build
	./a.out