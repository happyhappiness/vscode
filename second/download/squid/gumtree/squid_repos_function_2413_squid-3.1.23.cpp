void
FwdState::initiateSSL()
{
    FwdServer *fs = servers;
    int fd = server_fd;
    SSL *ssl;
    SSL_CTX *sslContext = NULL;
    peer *peer = fs->_peer;

    if (peer) {
        assert(peer->use_ssl);
        sslContext = peer->sslContext;
    } else {
        sslContext = Config.ssl_client.sslContext;
    }

    assert(sslContext);

    if ((ssl = SSL_new(sslContext)) == NULL) {
        debugs(83, 1, "fwdInitiateSSL: Error allocating handle: " << ERR_error_string(ERR_get_error(), NULL)  );
        ErrorState *anErr = errorCon(ERR_SOCKET_FAILURE, HTTP_INTERNAL_SERVER_ERROR, request);
        anErr->xerrno = errno;
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
        SSL_set_ex_data(ssl, ssl_ex_index_server, (void*)request->GetHost());
    }

    // Create the ACL check list now, while we have access to more info.
    // The list is used in ssl_verify_cb() and is freed in ssl_free().
    if (acl_access *acl = Config.ssl_client.cert_error) {
        ACLFilledChecklist *check = new ACLFilledChecklist(acl, request, dash_str);
        check->fd(fd);
        SSL_set_ex_data(ssl, ssl_ex_index_cert_error_check, check);
    }

    fd_table[fd].ssl = ssl;
    fd_table[fd].read_method = &ssl_read_method;
    fd_table[fd].write_method = &ssl_write_method;
    negotiateSSL(fd);
}