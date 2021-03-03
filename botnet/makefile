CC=gcc
LINK=gcc
 
.PHONY : all
all : bin/main.exe
 
bin/main.exe : build/main.o
	$(LINK) build/main.o -o bin/main.exe 

build/main.o : src/main.c
	$(CC) -c src/main.c -o build/main.o

.PHONY : clean
clean :
	del /Q /S *.o
	del /Q /S *.exe
	