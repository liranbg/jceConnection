#ifndef sslsocket_H
#define sslsocket_H

#include "socket.h"

#include <malloc.h>
#include <resolv.h>
#include "openssl/ssl.h"
#include "openssl/err.h"


class sslsocket : protected Socket
{
public:
    sslsocket(std::string hostname, int port);
    ~sslsocket();
    bool connectTo(std::string host, int port);

    bool send(const std::string) const;
    bool recv() const;

    void printSSL();

private:

    void InitCTX();
    void showCerts();

    SSL_CTX *ctx;
    SSL *ssl;

    bool isConnected;

};
#endif


