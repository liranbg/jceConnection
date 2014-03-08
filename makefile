CC=g++
CFLAGS = -Wall -g -fexceptions -std=c++11 -D_REENTRANT -pthread
LDFLAGS = -g -std=c++11
LIBS = -lcrypto -lssl
EXECUTE=jce
SRCS=main.cpp socket.cpp sslsocket.cpp jce.cpp Page.cpp

all: jce
jce:
	$(CC) $(LDFLAGS) -o $(EXECUTE) $(SRCS) $(LIBS)
	rm -f *.o *~ *.gch

clean:
	rm -f *.o *~ *.gch $(EXECUTE)
