#include "sslsocket.h"
#include <string>
#include <iostream>
#include <sstream>

template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}

sslsocket::sslsocket(std::string hostname, int port) :  Socket(), isConnected(false)
{
    create(); //creating socket

    InitCTX(); //initializing certificate
    char password[15];
    char username[15];
    printf("\nenter your username: ");
    scanf("%s", username);
    printf("enter your password: ");
    scanf("%s", password);
    if (connectTo(hostname,port))
        isConnected = true;
    std::string msg;

    //		GET METHOD
	//    msg = "GET /";
	//    msg += "yedion/fireflyweb.aspx?appname=BSHITA&prgname=LoginValidation&arguments=-N[FILLUSERNAME],-N";
	//    msg += password;
	//    msg += " HTTP/1.1\r\n";
	//    msg += "Host: " + hostname + "\r\n";
	//    msg += "Proxy-Connection: Keep-Alive\r\n";
	//    msg += "Accept: */*\r\n";
	//    msg += "Connection: close\r\n";
	//    msg += "\n";

    //		HTTP POST METHOD - MORE DATA TO SEND
    std::string parameters = "yedion/fireflyweb.aspx?appname=BSHITA&prgname=LoginValidation&arguments=-N";
    parameters += username;
    parameters += ",-N";
    parameters += password;
    puts(parameters.c_str());
    std::string sizeo = to_string(parameters.length());
    msg = "POST /yedion/fireflyweb.aspx HTTP/1.1\r\n";
    msg += "Host: " + hostname + "\r\n";
    msg += "Content-Type: application/x-www-form-urlencoded\r\n";
    msg += "Content-Length: " + sizeo + "\r\n";
    msg += "Proxy-Connection: Keep-Alive\r\n";
    msg += "Connection: Keep-Alive\r\n";
    msg += "\r\n";
    msg += parameters;

    send(msg);
    recv();

    printSSL(); //useage to see certificates
    std::string moreToDo;
    puts("write something");
    std::cin >> moreToDo;
    moreToDo += "\r\n";
    if (send(msg))
        puts("sent!");
    if (recv())
        puts("recieving...");


}
void sslsocket::printSSL()
{
    if (!isConnected)
    {
        printf("not connected\n");
        return;
    }
    printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
    showCerts();  /* get any certs */
}

bool sslsocket::recv() const
{
    if (!isConnected)
        return false;

    const int buffsize = 1024;
    char buf[buffsize];
    bzero(buf, sizeof(buf));

    int status;
    while ((status = SSL_read(ssl, buf, sizeof(buf))) > 0)
    {
        printf("%s",buf);
        bzero(buf, sizeof(buf));
    }
    printf("\n");
    if (status == SSL_RECEIVED_SHUTDOWN) //probably got what we need
        return true;

    return false;

}
bool sslsocket::send(const std::string p) const
{
    if (!isConnected)
        return false;
    int status = SSL_write(ssl, p.c_str(), p.size());			/* encrypt & send message */
    if (status == SSL_ERROR_ZERO_RETURN)
        return false;
    return true;
}
sslsocket::~sslsocket()
{
    SSL_free(ssl);
    delete this->ctx;
    delete this->ssl;
}
bool sslsocket::connectTo(std::string host, int port)
{
    if (!connect(host,port)) //connecting the socket
    {
        close();
        perror(host.c_str());
        return false;
    }
    //socket is connected, lets connecting the ssl
    this->ssl = SSL_new(this->ctx);
    SSL_set_fd(ssl, getSocket());

    if (SSL_connect(this->ssl) <= 0)
    {
        ERR_print_errors_fp(stderr);
        return false;
    }
    return true;
}

void sslsocket::showCerts()
{
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);	/* get the server's certificate */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);							/* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);							/* free the malloc'ed string */
        X509_free(cert);					/* free the malloc'ed certificate copy */
        free(cert);
    }
    else
        printf("No certificates.\n");
}

void sslsocket::InitCTX()
{
    const SSL_METHOD *method;
    SSL_library_init();
    OpenSSL_add_all_ciphers();
    OpenSSL_add_all_algorithms();		/* Load cryptos, et.al. */
    SSL_load_error_strings();			/* Bring in and register error messages */
    method = SSLv23_client_method();	/* Create new client-method instance */
    ctx = SSL_CTX_new(method);			/* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
}
//useage to convert types into string (int,doubles and etc.)



