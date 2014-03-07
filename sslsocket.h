#ifndef sslsocket_H
#define sslsocket_H

#include "socket.h"
#include <malloc.h>
#include <resolv.h>
#include <vector>
#include "openssl/ssl.h"
#include "openssl/err.h"

#define BUFFER_SIZE 8000


class sslsocket : protected Socket
{
public:
    sslsocket(std::string hostname, int port);
    ~sslsocket();
    bool connectTo(std::string host, int port);
    bool isCon(){ return isConnected; }
    bool send(const std::string) const;
    bool recieve(std::vector<std::string> &) const;

    void printSSL();

private:

    void InitCTX();
    void showCerts();

    SSL_CTX *ctx;
    SSL *ssl;

    bool isConnected;

};
#endif


