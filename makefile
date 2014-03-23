
# compiler
CC=g++

# compile arguments
CFLAGS+= -Wall -g -fexceptions -std=c++11 -D_REENTRANT -pthread

# linker flags
LDFLAGS+= -g -std=c++11

# libraries
LIBS+= -lcrypto -lssl

# our source files
SOURCES=main.cpp socket.cpp sslsocket.cpp jce.cpp Page.cpp user.cpp GradePage.cpp GradePage.h Course.cpp Course.h

# a macro to define the objects from sources
OBJECTS=$(SOURCES:.c=.o)

# executable name
EXECUTABLE=jce

$(EXECUTABLE): $(OBJECTS)
	@echo "Building target" $@ "..."
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)
	@echo "Done!"
	
# a rule for generating object files given their c files
.c.o:
	@echo "Compiling" $< "..."
	$(CC) $(CFLAGS) $< -o $@
	@echo "Done!"
	
clean:
	@echo "Ceaning up *.o Files..."
	rm -rf *s *o $(EXECUTABLE)
	@echo "Done!"

.PHONY: all clean
