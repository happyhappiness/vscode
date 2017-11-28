void
Ssl::PeerConnector::handleNegotiateError(const int ret)
{
    const int fd = serverConnection()->fd;
    unsigned long ssl_lib_error = SSL_ERROR_NONE;
    SSL *ssl = fd_table[fd].ssl;
    int ssl_error = SSL_get_error(ssl, ret);
    BIO *b = SSL_get_rbio(ssl);
    Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(b->ptr);

#ifdef EPROTO
    int sysErrNo = EPROTO;
#else
    int sysErrNo = EACCES;
#endif

    switch (ssl_error) {

    case SSL_ERROR_WANT_READ:
        setReadTimeout();
        Comm::SetSelect(fd, COMM_SELECT_READ, &NegotiateSsl, this, 0);
        return;

    case SSL_ERROR_WANT_WRITE:
        if ((srvBio->bumpMode() == Ssl::bumpPeek || srvBio->bumpMode() == Ssl::bumpStare) && srvBio->holdWrite()) {
            debugs(81, 3, "hold write on SSL connection on FD " << fd);
            checkForPeekAndSplice();
            return;
        }
        Comm::SetSelect(fd, COMM_SELECT_WRITE, &NegotiateSsl, this, 0);
        return;

    case SSL_ERROR_SSL:
    case SSL_ERROR_SYSCALL:
        ssl_lib_error = ERR_get_error();

        // In Peek mode, the ClientHello message sent to the server. If the
        // server resuming a previous (spliced) SSL session with the client,
        // then probably we are here because local SSL object does not know
        // anything about the session being resumed.
        //
        if (srvBio->bumpMode() == Ssl::bumpPeek && (resumingSession = srvBio->resumingSession())) {
            // we currently splice all resumed sessions unconditionally
            if (const bool spliceResumed = true) {
                checkForPeekAndSpliceMatched(Ssl::bumpSplice);
                return;
            } // else fall through to find a matching ssl_bump action (with limited info)
        }

        // If we are in peek-and-splice mode and still we did not write to
        // server yet, try to see if we should splice.
        // In this case the connection can be saved.
        // If the checklist decision is do not splice a new error will
        // occure in the next SSL_connect call, and we will fail again.
        // Abort on certificate validation errors to avoid splicing and
        // thus hiding them.
        // Abort if no certificate found probably because of malformed or
        // unsupported server Hello message (TODO: make configurable).
#if 1
        if (!SSL_get_ex_data(ssl, ssl_ex_index_ssl_error_detail) &&
                (srvBio->bumpMode() == Ssl::bumpPeek  || srvBio->bumpMode() == Ssl::bumpStare) && srvBio->holdWrite()) {
            Ssl::X509_Pointer serverCert(SSL_get_peer_certificate(ssl));
            if (serverCert.get()) {
                debugs(81, 3, "Error ("  << ERR_error_string(ssl_lib_error, NULL) <<  ") but, hold write on SSL connection on FD " << fd);
                checkForPeekAndSplice();
                return;
            }
        }
#endif

        // store/report errno when ssl_error is SSL_ERROR_SYSCALL, ssl_lib_error is 0, and ret is -1
        if (ssl_error == SSL_ERROR_SYSCALL && ret == -1 && ssl_lib_error == 0)
            sysErrNo = errno;

        debugs(83, DBG_IMPORTANT, "Error negotiating SSL on FD " << fd <<
               ": " << ERR_error_string(ssl_lib_error, NULL) << " (" <<
               ssl_error << "/" << ret << "/" << errno << ")");

        break; // proceed to the general error handling code

    default:
        break; // no special error handling for all other errors
    }

    ErrorState *const anErr = ErrorState::NewForwarding(ERR_SECURE_CONNECT_FAIL, request.getRaw());
    anErr->xerrno = sysErrNo;

    Ssl::ErrorDetail *errFromFailure = (Ssl::ErrorDetail *)SSL_get_ex_data(ssl, ssl_ex_index_ssl_error_detail);
    if (errFromFailure != NULL) {
        // The errFromFailure is attached to the ssl object
        // and will be released when ssl object destroyed.
        // Copy errFromFailure to a new Ssl::ErrorDetail object
        anErr->detail = new Ssl::ErrorDetail(*errFromFailure);
    } else {
        // server_cert can be NULL here
        X509 *server_cert = SSL_get_peer_certificate(ssl);
        anErr->detail = new Ssl::ErrorDetail(SQUID_ERR_SSL_HANDSHAKE, server_cert, NULL);
        X509_free(server_cert);
    }

    if (ssl_lib_error != SSL_ERROR_NONE)
        anErr->detail->setLibError(ssl_lib_error);

    if (request->clientConnectionManager.valid()) {
        // remember the server certificate from the ErrorDetail object
        if (Ssl::ServerBump *serverBump = request->clientConnectionManager->serverBump())
            serverBump->serverCert.resetAndLock(anErr->detail->peerCert());

        // For intercepted connections, set the host name to the server
        // certificate CN. Otherwise, we just hope that CONNECT is using
        // a user-entered address (a host name or a user-entered IP).
        const bool isConnectRequest = !request->clientConnectionManager->port->flags.isIntercepted();
        if (request->flags.sslPeek && !isConnectRequest) {
            if (X509 *srvX509 = anErr->detail->peerCert()) {
                if (const char *name = Ssl::CommonHostName(srvX509)) {
                    request->SetHost(name);
                    debugs(83, 3, HERE << "reset request host: " << name);
                }
            }
        }
    }

    bail(anErr);
}