MAKE = make
GCC = gcc
CFLAGS = -Wall -g
INCLUDE=./include
SRC = ./src/main.c ./src/Json.c ./src/object.c ./src/search.c ./src/SISO.c ./src/user.c
OBJ = $(SRC:.c=.o)
EXEC = Byblio-Tech.exe

all: $(EXEC)
	mkdir -p lib

$(EXEC): $(OBJ) $(INCLUDE)/*.h
	$(GCC) $(CFLAGS) -o $(OBJ) -I$(INCLUDE)
	mv src/*.o lib

src/main.o: src/main.c 
	$(GCC) $(CFLAGS) -o ./src/main.o -c ./src/main.c

src/Json.o: src/Json.c
	$(GCC) $(CFLAGS) -o ./src/Json.o -c ./src/Json.c

src/object.o: src/object.c
	$(GCC) $(CFLAGS) -o ./src/object.o -c ./src/object.c

src/search.o: src/search.c
	$(GCC) $(CFLAGS) -o ./src/search.o -c ./src/search.c

src/SISO.o: src/SISO.c
	$(GCC) $(CFLAGS) -o ./src/SISO.o -c ./src/SISO.c

src/user.o: src/user.c
	$(GCC) $(CFLAGS) -o ./src/user.o -c ./src/user.c

clean:
	rm -rf $(OBJ) $(EXEC)