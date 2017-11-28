void
ConnStateData::httpsPeeked(Comm::ConnectionPointer serverConnection)
{
    Must(sslServerBump != NULL);

    if (Comm::IsConnOpen(serverConnection)) {
        SSL *ssl = fd_table[serverConnection->fd].ssl;
        assert(ssl);
        Ssl::X509_Pointer serverCert(SSL_get_peer_certificate(ssl));
        assert(serverCert.get() != NULL);
        sslCommonName = Ssl::CommonHostName(serverCert.get());
        debugs(33, 5, HERE << "HTTPS server CN: " << sslCommonName <<
               " bumped: " << *serverConnection);

        pinConnection(serverConnection, NULL, NULL, false);

        debugs(33, 5, HERE << "bumped HTTPS server: " << sslConnectHostOrIp);
    } else {
        debugs(33, 5, HERE << "Error while bumping: " << sslConnectHostOrIp);
        Ip::Address intendedDest;
        intendedDest = sslConnectHostOrIp.termedBuf();
        const bool isConnectRequest = !port->flags.isIntercepted();

        // Squid serves its own error page and closes, so we want
        // a CN that causes no additional browser errors. Possible
        // only when bumping CONNECT with a user-typed address.
        if (intendedDest.isAnyAddr() || isConnectRequest)
            sslCommonName = sslConnectHostOrIp;
        else if (sslServerBump->serverCert.get())
            sslCommonName = Ssl::CommonHostName(sslServerBump->serverCert.get());

        //  copy error detail from bump-server-first request to CONNECT request
        if (currentobject != NULL && currentobject->http != NULL && currentobject->http->request)
            currentobject->http->request->detailError(sslServerBump->request->errType, sslServerBump->request->errDetail);
    }

    getSslContextStart();
}