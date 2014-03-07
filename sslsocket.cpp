#include "sslsocket.h"




sslsocket::sslsocket(std::string hostname, int port) :  Socket(), isConnected(false)
{
    create(); //creating socket
    InitCTX(); //initializing certificate
    
    if (connectTo(hostname,port))
        isConnected = true;
    
    //prgname=LoginValidtion1&Arguments=-N302539556,-A,-N013145836517240,-A,-A

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

bool sslsocket::recieve(std::vector<std::string> &strvec) const
{
    if (!isConnected)
        return false;

    char buf[BUFFER_SIZE];
    bzero(buf, sizeof(buf));

    int status;
    while ((status = SSL_read(ssl, buf, sizeof(buf))) > 0)
    {
        std::string msg = buf;
        strvec.push_back(msg);
        bzero(buf, sizeof(buf));
    }
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
    SSL_do_handshake(ssl);
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



