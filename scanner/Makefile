CC = g++
CFLAGS = -O0 -g -std=c++14

BUILD_PATH = _build/obj/
BUILD_PATHEXE = _build/
LIB_TRANS =

OBJ_TRANS  = $(BUILD_PATH)main.o \
	$(BUILD_PATH)scanner.o \
	$(BUILD_PATH)testout.o

all : $(BUILD_PATHEXE)scanner

$(BUILD_PATHEXE)scanner : $(OBJ_TRANS)
	$(CC) -o $(BUILD_PATHEXE)scanner $(OBJ_TRANS) $(LIB_TRANS)

$(BUILD_PATH)main.o : scanner_ext.h main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o $(BUILD_PATH)main.o

$(BUILD_PATH)scanner.o : scanner_data.h scanner_local.h scanner.cpp
	$(CC) $(CFLAGS) -c scanner.cpp -o $(BUILD_PATH)scanner.o

$(BUILD_PATH)testout.o : scanner_ext.h testout.cpp
	$(CC) $(CFLAGS) -c testout.cpp -o $(BUILD_PATH)testout.o


clean :
	rm _build/obj/*.o
	rm _build/scanner