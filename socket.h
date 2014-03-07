#ifndef Socket_H
#define Socket_H

#define FAIL -1
#define socketTimeOut 4
//sock headers
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#include <iostream>
#include <string.h>


const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 10000;

class Socket
{
protected:
    Socket();
    virtual ~Socket();

    // Server initialization
    bool create();
    bool bind ( const int port ); //binding port
    bool listen() const;
    bool accept ( Socket& ) const;

    // Client initialization
    bool connect ( const std::string host, const int port );

    // Data Transimission
    virtual bool send ( const std::string ) const;
    virtual bool recv ( ) const;

    void close();
    void set_non_blocking ( const bool );

    bool is_valid() const { return (m_sock != FAIL); }
    int getSocket() { if (is_valid()) return m_sock; //else
    														return FAIL; }

private:

    int m_sock;
    sockaddr_in m_addr;

};

#endif
