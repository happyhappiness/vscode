void
FwdState::negotiateSSL(int fd)
{
    unsigned long ssl_lib_error = SSL_ERROR_NONE;
    SSL *ssl = fd_table[fd].ssl;
    int ret;

    if ((ret = SSL_connect(ssl)) <= 0) {
        int ssl_error = SSL_get_error(ssl, ret);
#ifdef EPROTO
        int sysErrNo = EPROTO;
#else
        int sysErrNo = EACCES;
#endif

        switch (ssl_error) {

        case SSL_ERROR_WANT_READ:
            Comm::SetSelect(fd, COMM_SELECT_READ, fwdNegotiateSSLWrapper, this, 0);
            return;

        case SSL_ERROR_WANT_WRITE:
            Comm::SetSelect(fd, COMM_SELECT_WRITE, fwdNegotiateSSLWrapper, this, 0);
            return;

        case SSL_ERROR_SSL:
        case SSL_ERROR_SYSCALL:
            ssl_lib_error = ERR_get_error();
            debugs(81, DBG_IMPORTANT, "fwdNegotiateSSL: Error negotiating SSL connection on FD " << fd <<
                   ": " << ERR_error_string(ssl_lib_error, NULL) << " (" << ssl_error <<
                   "/" << ret << "/" << errno << ")");

            // store/report errno when ssl_error is SSL_ERROR_SYSCALL, ssl_lib_error is 0, and ret is -1
            if (ssl_error == SSL_ERROR_SYSCALL && ret == -1 && ssl_lib_error == 0)
                sysErrNo = errno;

            // falling through to complete error handling

        default:
            // TODO: move into a method before merge
            Ssl::ErrorDetail *errDetails;
            Ssl::ErrorDetail *errFromFailure = (Ssl::ErrorDetail *)SSL_get_ex_data(ssl, ssl_ex_index_ssl_error_detail);
            if (errFromFailure != NULL) {
                // The errFromFailure is attached to the ssl object
                // and will be released when ssl object destroyed.
                // Copy errFromFailure to a new Ssl::ErrorDetail object.
                errDetails = new Ssl::ErrorDetail(*errFromFailure);
            } else {
                // server_cert can be NULL here
                X509 *server_cert = SSL_get_peer_certificate(ssl);
                errDetails = new Ssl::ErrorDetail(SQUID_ERR_SSL_HANDSHAKE, server_cert, NULL);
                X509_free(server_cert);
            }

            if (ssl_lib_error != SSL_ERROR_NONE)
                errDetails->setLibError(ssl_lib_error);

            if (request->clientConnectionManager.valid()) {
                // remember the server certificate from the ErrorDetail object
                if (Ssl::ServerBump *serverBump = request->clientConnectionManager->serverBump()) {
                    serverBump->serverCert.resetAndLock(errDetails->peerCert());

                    // remember validation errors, if any
                    if (Ssl::CertErrors *errs = static_cast<Ssl::CertErrors*>(SSL_get_ex_data(ssl, ssl_ex_index_ssl_errors)))
                        serverBump->sslErrors = cbdataReference(errs);
                }
            }

            // For intercepted connections, set the host name to the server
            // certificate CN. Otherwise, we just hope that CONNECT is using
            // a user-entered address (a host name or a user-entered IP).
            const bool isConnectRequest = request->clientConnectionManager.valid() &&
                                          !request->clientConnectionManager->port->flags.isIntercepted();
            if (request->flags.sslPeek && !isConnectRequest) {
                if (X509 *srvX509 = errDetails->peerCert()) {
                    if (const char *name = Ssl::CommonHostName(srvX509)) {
                        request->SetHost(name);
                        debugs(83, 3, HERE << "reset request host: " << name);
                    }
                }
            }

            ErrorState *const anErr = makeConnectingError(ERR_SECURE_CONNECT_FAIL);
            anErr->xerrno = sysErrNo;
            anErr->detail = errDetails;
            fail(anErr);

            if (serverConnection()->getPeer()) {
                peerConnectFailed(serverConnection()->getPeer());
            }

            serverConn->close();
            return;
        }
    }

    if (request->clientConnectionManager.valid()) {
        // remember the server certificate from the ErrorDetail object
        if (Ssl::ServerBump *serverBump = request->clientConnectionManager->serverBump()) {
            serverBump->serverCert.reset(SSL_get_peer_certificate(ssl));

            // remember validation errors, if any
            if (Ssl::CertErrors *errs = static_cast<Ssl::CertErrors *>(SSL_get_ex_data(ssl, ssl_ex_index_ssl_errors)))
                serverBump->sslErrors = cbdataReference(errs);
        }
    }

    if (serverConnection()->getPeer() && !SSL_session_reused(ssl)) {
        if (serverConnection()->getPeer()->sslSession)
            SSL_SESSION_free(serverConnection()->getPeer()->sslSession);

        serverConnection()->getPeer()->sslSession = SSL_get1_session(ssl);
    }

    if (Ssl::TheConfig.ssl_crt_validator) {
        Ssl::CertValidationRequest validationRequest;
        // WARNING: Currently we do not use any locking for any of the
        // members of the Ssl::CertValidationRequest class. In this code the
        // Ssl::CertValidationRequest object used only to pass data to
        // Ssl::CertValidationHelper::submit method.
        validationRequest.ssl = ssl;
        validationRequest.domainName = request->GetHost();
        if (Ssl::CertErrors *errs = static_cast<Ssl::CertErrors *>(SSL_get_ex_data(ssl, ssl_ex_index_ssl_errors)))
            // validationRequest disappears on return so no need to cbdataReference
            validationRequest.errors = errs;
        else
            validationRequest.errors = NULL;
        try {
            debugs(83, 5, "Sending SSL certificate for validation to ssl_crtvd.");
            Ssl::CertValidationHelper::GetInstance()->sslSubmit(validationRequest, sslCrtvdHandleReplyWrapper, this);
            return;
        } catch (const std::exception &e) {
            debugs(33, DBG_IMPORTANT, "ERROR: Failed to compose ssl_crtvd " <<
                   "request for " << validationRequest.domainName <<
                   " certificate: " << e.what() << "; will now block to " <<
                   "validate that certificate.");
            // fall through to do blocking in-process generation.
            ErrorState *anErr = new ErrorState(ERR_GATEWAY_FAILURE, Http::scInternalServerError, request);
            fail(anErr);
            if (serverConnection()->getPeer()) {
                peerConnectFailed(serverConnection()->getPeer());
            }
            serverConn->close();
            self = NULL;
            return;
        }
    }

    dispatch();
}