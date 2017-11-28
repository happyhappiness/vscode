void
Ssl::PeerConnector::initializeSsl()
{
    SSL_CTX *sslContext = NULL;
    const CachePeer *peer = serverConnection()->getPeer();
    const int fd = serverConnection()->fd;

    if (peer) {
        assert(peer->use_ssl);
        sslContext = peer->sslContext;
    } else {
        sslContext = ::Config.ssl_client.sslContext;
    }

    assert(sslContext);

    SSL *ssl = Ssl::CreateClient(sslContext, fd, "server https start");
    if (!ssl) {
        ErrorState *anErr = new ErrorState(ERR_SOCKET_FAILURE, Http::scInternalServerError, request.getRaw());
        anErr->xerrno = errno;
        debugs(83, DBG_IMPORTANT, "Error allocating SSL handle: " << ERR_error_string(ERR_get_error(), NULL));
        bail(anErr);
        return;
    }

    if (peer) {
        SBuf *host = new SBuf(peer->ssldomain ? peer->ssldomain : peer->host);
        SSL_set_ex_data(ssl, ssl_ex_index_server, host);

        if (peer->sslSession)
            SSL_set_session(ssl, peer->sslSession);
    } else if (ConnStateData *csd = request->clientConnectionManager.valid()) {
        // client connection is required in the case we need to splice
        // or terminate client and server connections
        assert(clientConn != NULL);
        SBuf *hostName = NULL;
        Ssl::ClientBio *cltBio = NULL;

        //Enable Status_request tls extension, required to bump some clients
        SSL_set_tlsext_status_type(ssl, TLSEXT_STATUSTYPE_ocsp);

        // In server-first bumping mode, clientSsl is NULL.
        if (SSL *clientSsl = fd_table[clientConn->fd].ssl) {
            BIO *b = SSL_get_rbio(clientSsl);
            cltBio = static_cast<Ssl::ClientBio *>(b->ptr);
            const Ssl::Bio::sslFeatures &features = cltBio->getFeatures();
            if (!features.serverName.isEmpty())
                hostName = new SBuf(features.serverName);
        }

        if (!hostName) {
            // While we are peeking at the certificate, we may not know the server
            // name that the client will request (after interception or CONNECT)
            // unless it was the CONNECT request with a user-typed address.
            const bool isConnectRequest = !csd->port->flags.isIntercepted();
            if (!request->flags.sslPeek || isConnectRequest)
                hostName = new SBuf(request->GetHost());
        }

        if (hostName)
            SSL_set_ex_data(ssl, ssl_ex_index_server, (void*)hostName);

        Must(!csd->serverBump() || csd->serverBump()->step <= Ssl::bumpStep2);
        if (csd->sslBumpMode == Ssl::bumpPeek || csd->sslBumpMode == Ssl::bumpStare) {
            assert(cltBio);
            const Ssl::Bio::sslFeatures &features = cltBio->getFeatures();
            if (features.sslVersion != -1)
                features.applyToSSL(ssl, csd->sslBumpMode);

            BIO *b = SSL_get_rbio(ssl);
            Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(b->ptr);
            // Inherite client features, like SSL version, SNI and other
            srvBio->setClientFeatures(features);
            srvBio->recordInput(true);
            srvBio->mode(csd->sslBumpMode);
        } else {
            // Set client SSL options
            SSL_set_options(ssl, ::Config.ssl_client.parsedOptions);

            // Use SNI TLS extension only when we connect directly
            // to the origin server and we know the server host name.
            const char *sniServer = NULL;
            const bool redirected = request->flags.redirected && ::Config.onoff.redir_rewrites_host;
            if (!hostName || redirected)
                sniServer = !request->GetHostIsNumeric() ? request->GetHost() : NULL;
            else
                sniServer = hostName->c_str();

            if (sniServer)
                Ssl::setClientSNI(ssl, sniServer);
        }

        if (Ssl::ServerBump *serverBump = csd->serverBump())
            serverBump->attachServerSSL(ssl);
    }

    // If CertValidation Helper used do not lookup checklist for errors,
    // but keep a list of errors to send it to CertValidator
    if (!Ssl::TheConfig.ssl_crt_validator) {
        // Create the ACL check list now, while we have access to more info.
        // The list is used in ssl_verify_cb() and is freed in ssl_free().
        if (acl_access *acl = ::Config.ssl_client.cert_error) {
            ACLFilledChecklist *check = new ACLFilledChecklist(acl, request.getRaw(), dash_str);
            // check->fd(fd); XXX: need client FD here
            SSL_set_ex_data(ssl, ssl_ex_index_cert_error_check, check);
        }
    }

    // store peeked cert to check SQUID_X509_V_ERR_CERT_CHANGE
    X509 *peeked_cert;
    if (request->clientConnectionManager.valid() &&
            request->clientConnectionManager->serverBump() &&
            (peeked_cert = request->clientConnectionManager->serverBump()->serverCert.get())) {
        CRYPTO_add(&(peeked_cert->references),1,CRYPTO_LOCK_X509);
        SSL_set_ex_data(ssl, ssl_ex_index_ssl_peeked_cert, peeked_cert);
    }
}