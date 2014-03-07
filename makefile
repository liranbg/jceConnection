CC=g++
CFLAGS = -Wall -g -fexceptions -std=c++11 -D_REENTRANT -pthread
LDFLAGS = -g -std=c++11
LIBS = -lcrypto -lssl
EXECUTE=jce
SRCS=main.cpp socket.cpp sslsocket.cpp jce.cpp

#g++ -g -std=c++11 -o jce main.cpp jce.cpp socket.cpp sslsocket.cpp -lcrypto -lssl


all: jce
jce:
	$(CC) $(LDFLAGS) -o $(EXECUTE) $(SRCS) $(LIBS)
	rm -f *.o *~ *.gch


#g++ -Wall -Iinclude -o hello_world hello_world.cpp ./out/x64.debug/obj.target/tools/gyp/libv8_{base.x64,snapshot}.a ./out/x64.debug/obj.target/third_party/icu/libicu{i18n,uc,data}.a -lrt  -lpthread

clean:
	rm -f *.o *~ *.gch $(EXECUTE)
