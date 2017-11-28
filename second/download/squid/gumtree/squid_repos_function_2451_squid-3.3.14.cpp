void
FwdState::initiateSSL()
{
    SSL *ssl;
    SSL_CTX *sslContext = NULL;
    const CachePeer *peer = serverConnection()->getPeer();
    int fd = serverConnection()->fd;

    if (peer) {
        assert(peer->use_ssl);
        sslContext = peer->sslContext;
    } else {
        sslContext = Config.ssl_client.sslContext;
    }

    assert(sslContext);

    if ((ssl = SSL_new(sslContext)) == NULL) {
        debugs(83, DBG_IMPORTANT, "fwdInitiateSSL: Error allocating handle: " << ERR_error_string(ERR_get_error(), NULL)  );
        ErrorState *anErr = new ErrorState(ERR_SOCKET_FAILURE, HTTP_INTERNAL_SERVER_ERROR, request);
        // TODO: create Ssl::ErrorDetail with OpenSSL-supplied error code
        fail(anErr);
        self = NULL;		// refcounted
        return;
    }

    SSL_set_fd(ssl, fd);

    if (peer) {
        if (peer->ssldomain)
            SSL_set_ex_data(ssl, ssl_ex_index_server, peer->ssldomain);

#if NOT_YET

        else if (peer->name)
            SSL_set_ex_data(ssl, ssl_ex_index_server, peer->name);

#endif

        else
            SSL_set_ex_data(ssl, ssl_ex_index_server, peer->host);

        if (peer->sslSession)
            SSL_set_session(ssl, peer->sslSession);

    } else {
        // While we are peeking at the certificate, we may not know the server
        // name that the client will request (after interception or CONNECT)
        // unless it was the CONNECT request with a user-typed address.
        const char *hostname = request->GetHost();
        const bool hostnameIsIp = request->GetHostIsNumeric();
        const bool isConnectRequest = request->clientConnectionManager.valid() &&
                                      !request->clientConnectionManager->port->spoof_client_ip &&
                                      !request->clientConnectionManager->port->intercepted;
        if (!request->flags.sslPeek || isConnectRequest)
            SSL_set_ex_data(ssl, ssl_ex_index_server, (void*)hostname);

        // Use SNI TLS extension only when we connect directly
        // to the origin server and we know the server host name.
        if (!hostnameIsIp)
            Ssl::setClientSNI(ssl, hostname);
    }

    // Create the ACL check list now, while we have access to more info.
    // The list is used in ssl_verify_cb() and is freed in ssl_free().
    if (acl_access *acl = Config.ssl_client.cert_error) {
        ACLFilledChecklist *check = new ACLFilledChecklist(acl, request, dash_str);
        SSL_set_ex_data(ssl, ssl_ex_index_cert_error_check, check);
    }

    // store peeked cert to check SQUID_X509_V_ERR_CERT_CHANGE
    X509 *peeked_cert;
    if (request->clientConnectionManager.valid() &&
            request->clientConnectionManager->serverBump() &&
            (peeked_cert = request->clientConnectionManager->serverBump()->serverCert.get())) {
        CRYPTO_add(&(peeked_cert->references),1,CRYPTO_LOCK_X509);
        SSL_set_ex_data(ssl, ssl_ex_index_ssl_peeked_cert, peeked_cert);
    }

    fd_table[fd].ssl = ssl;
    fd_table[fd].read_method = &ssl_read_method;
    fd_table[fd].write_method = &ssl_write_method;
    negotiateSSL(fd);
}