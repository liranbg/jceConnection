CC=g++
CFLAGS = -Wall -g -fexceptions -std=c++11 -D_REENTRANT -pthread
LDFLAGS = -g -std=c++11
LIBS = -lcrypto -lssl
EXECUTE=jce
SRCS=main.cpp socket.cpp sslsocket.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: jce

jce: $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXECUTE) $(OBJS) $(LIBS)

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $? $(LIBS)

#main.o: main.cpp main.h
#	$(CC) $(CFLAGS) -c $(SRCS) $(LIBS)
#
#socket.o: socket.cpp socket.h
#	$(CC) $(CFLAGS) -c $(SRCS) $(LIBS)
#
#sslsocket.o: sslsocket.cpp sslsocket.h
#	$(CC) $(CFLAGS) -c $(SRCS) $(LIBS)

clean:
	rm -f *.o *~ *.gch $(EXECUTE)
