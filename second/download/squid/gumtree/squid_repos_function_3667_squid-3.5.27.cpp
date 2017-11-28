void ConnStateData::startPeekAndSplice()
{
    // will call httpsPeeked() with certificate and connection, eventually
    SSL_CTX *unConfiguredCTX = Ssl::createSSLContext(port->signingCert, port->signPkey, *port);
    fd_table[clientConnection->fd].dynamicSslContext = unConfiguredCTX;

    if (!httpsCreate(clientConnection, unConfiguredCTX))
        return;

    // commSetConnTimeout() was called for this request before we switched.

    // Disable the client read handler until CachePeer selection is complete
    Comm::SetSelect(clientConnection->fd, COMM_SELECT_READ, NULL, NULL, 0);
    Comm::SetSelect(clientConnection->fd, COMM_SELECT_READ, clientPeekAndSpliceSSL, this, 0);
    switchedToHttps_ = true;

    SSL *ssl = fd_table[clientConnection->fd].ssl;
    BIO *b = SSL_get_rbio(ssl);
    Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(b->ptr);
    bio->hold(true);
}