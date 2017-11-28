void
Ssl::PeerConnector::negotiateSsl()
{
    if (!Comm::IsConnOpen(serverConnection()) || fd_table[serverConnection()->fd].closing())
        return;

    const int fd = serverConnection()->fd;
    SSL *ssl = fd_table[fd].ssl;
    const int result = SSL_connect(ssl);
    if (result <= 0) {
        handleNegotiateError(result);
        return; // we might be gone by now
    }

    if (serverConnection()->getPeer() && !SSL_session_reused(ssl)) {
        if (serverConnection()->getPeer()->sslSession)
            SSL_SESSION_free(serverConnection()->getPeer()->sslSession);

        serverConnection()->getPeer()->sslSession = SSL_get1_session(ssl);
    }

    if (!sslFinalized())
        return;

    callBack();
}