CC = g++
CFLAGS = -O0 -g -std=c++14

BUILD_PATH = _build/obj/
BUILD_PATHEXE = _build/
LIB_TRANS =

OBJ_TRANS  = $(BUILD_PATH)error.o \
	$(BUILD_PATH)main.o \
	$(BUILD_PATH)scanner.o \
	$(BUILD_PATH)testout.o \
	$(BUILD_PATH)name_table.o \
	$(BUILD_PATH)app_types.o \
	$(BUILD_PATH)parser.o

all : $(BUILD_PATHEXE)compiler

$(BUILD_PATHEXE)compiler : $(OBJ_TRANS)
	$(CC) -o $(BUILD_PATHEXE)compiler $(OBJ_TRANS) $(LIB_TRANS)

$(BUILD_PATH)error.o : errors/error.h errors/error.cpp
	$(CC) $(CFLAGS) -c errors/error.cpp -o $(BUILD_PATH)error.o

$(BUILD_PATH)main.o : scanner/scanner_ext.h main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o $(BUILD_PATH)main.o

$(BUILD_PATH)scanner.o : scanner/scanner_data.h scanner/scanner_local.h scanner/scanner.cpp
	$(CC) $(CFLAGS) -c scanner/scanner.cpp -o $(BUILD_PATH)scanner.o

$(BUILD_PATH)testout.o : scanner/scanner_ext.h scanner/testout.cpp
	$(CC) $(CFLAGS) -c scanner/testout.cpp -o $(BUILD_PATH)testout.o

$(BUILD_PATH)parser.o : scanner/scanner_ext.h parser/parser.cpp
	$(CC) $(CFLAGS) -c parser/parser.cpp -o $(BUILD_PATH)parser.o

$(BUILD_PATH)name_table.o : name_table/name_table.h name_table/name_table.cpp
	$(CC) $(CFLAGS) -c name_table/name_table.cpp -o $(BUILD_PATH)name_table.o

$(BUILD_PATH)app_types.o : name_table/app_types.h name_table/app_types.cpp
	$(CC) $(CFLAGS) -c name_table/app_types.cpp -o $(BUILD_PATH)app_types.o

clean :
	rm _build/obj/*.o
	rm _build/compiler
