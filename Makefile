
#HOW-TO:
#	make			to compile
#	make clean		cleaning objects directory
#	make bclean		cleaning all files
#	make rebuild	clean and remake

# compiler
CC = g++

# compile arguments
CFLAGS = -Wall -g -fexceptions -std=c++11 -D_REENTRANT -pthread

# linker flags
LDFLAGS = -g -std=c++11

# libraries
LIBS = -lcrypto -lssl

#our source files
SOURCES = $(wildcard *.cpp)

# a macro to define the objects from sources
BUILD_DIR := build
OBJC=$(SOURCES:%.cpp=${BUILD_DIR}/%.o)

# executable name
EXECUTABLE=jce

.PHONY: all

all:	$(EXECUTABLE)

$(EXECUTABLE): $(OBJC)
	@echo "Building target" $@
	@$(CC) $(LDFLAGS) -o $@ $(OBJC) $(LIBS)
	@echo "Done."

# a rule for generating object files given their c files
#.cpp.o: /$(OBJCDIR)
${BUILD_DIR}/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Ceaning up *.o Files"
	@rm -rf ${BUILD_DIR}
	@echo "Done."

bclean:
	@echo "Ceaning all"
	@rm -rf $(EXECUTABLE) ${BUILD_DIR}
	@echo "Done."

rebuild: bclean all


