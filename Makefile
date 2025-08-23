LIBS= -lglfw -lGL -ldl

# gather all files in src folder that end in .cpp
SOURCE_FILES=$(wildcard src/*.cpp)

# make a list of object files by getting all source files and replacing the .cpp with the .o extension
OBJ_FILES=$(patsubst src/%.cpp, obj/%.o, ${SOURCE_FILES})

# in case any of the obj files change compile
program: ${OBJ_FILES} | obj/glad.o
	g++ -o program.out $^ obj/glad.o ${LIBS}

run: program 
	./program.out

# in case any of the cpp files make the matching .o file 
obj/%.o: src/%.cpp | obj
	g++ -c $< -o $@

obj/glad.o: src/glad.c | obj 
	gcc -c $< -o $@

# if we depend on this make the folder. -p is to avoid errors if folder already exists
obj:
	mkdir -p obj

clean:
	rm -rf obj program.out