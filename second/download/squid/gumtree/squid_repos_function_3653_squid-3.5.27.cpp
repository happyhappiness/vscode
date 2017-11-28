static SSL *
httpsCreate(const Comm::ConnectionPointer &conn, SSL_CTX *sslContext)
{
    if (SSL *ssl = Ssl::CreateServer(sslContext, conn->fd, "client https start")) {
        debugs(33, 5, "will negotate SSL on " << conn);
        return ssl;
    }

    conn->close();
    return NULL;
}