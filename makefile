CC=g++
CFLAGS = -Wall -g -fexceptions -std=c++11 -D_REENTRANT -pthread
LDFLAGS = -g -std=c++11
LIBS = -lcrypto -lssl
EXECUTE=jce
SRCS=main.cpp socket.cpp sslsocket.cpp jce.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: jce

jce: $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXECUTE) $(OBJS) $(LIBS)
	rm -f *.o *~ *.gch

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $? $(LIBS)

#g++ -Wall -Iinclude -o hello_world hello_world.cpp ./out/x64.debug/obj.target/tools/gyp/libv8_{base.x64,snapshot}.a ./out/x64.debug/obj.target/third_party/icu/libicu{i18n,uc,data}.a -lrt  -lpthread

clean:
	rm -f *.o *~ *.gch $(EXECUTE)
