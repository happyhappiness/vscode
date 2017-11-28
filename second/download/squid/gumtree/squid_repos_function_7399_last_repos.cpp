void
Security::PeerConnector::noteNegotiationError(const int ret, const int ssl_error, const int ssl_lib_error)
{
#if defined(EPROTO)
    int sysErrNo = EPROTO;
#else
    int sysErrNo = EACCES;
#endif

#if USE_OPENSSL
    // store/report errno when ssl_error is SSL_ERROR_SYSCALL, ssl_lib_error is 0, and ret is -1
    if (ssl_error == SSL_ERROR_SYSCALL && ret == -1 && ssl_lib_error == 0)
        sysErrNo = errno;
#endif
    int xerr = errno;

    const int fd = serverConnection()->fd;
    debugs(83, DBG_IMPORTANT, "ERROR: negotiating TLS on FD " << fd <<
           ": " << Security::ErrorString(ssl_lib_error) << " (" <<
           ssl_error << "/" << ret << "/" << xerr << ")");

    ErrorState *anErr = NULL;
    if (request != NULL)
        anErr = ErrorState::NewForwarding(ERR_SECURE_CONNECT_FAIL, request.getRaw());
    else
        anErr = new ErrorState(ERR_SECURE_CONNECT_FAIL, Http::scServiceUnavailable, NULL);
    anErr->xerrno = sysErrNo;

#if USE_OPENSSL
    Security::SessionPointer session(fd_table[fd].ssl);
    Ssl::ErrorDetail *errFromFailure = static_cast<Ssl::ErrorDetail *>(SSL_get_ex_data(session.get(), ssl_ex_index_ssl_error_detail));
    if (errFromFailure != NULL) {
        // The errFromFailure is attached to the ssl object
        // and will be released when ssl object destroyed.
        // Copy errFromFailure to a new Ssl::ErrorDetail object
        anErr->detail = new Ssl::ErrorDetail(*errFromFailure);
    } else {
        // server_cert can be NULL here
        X509 *server_cert = SSL_get_peer_certificate(session.get());
        anErr->detail = new Ssl::ErrorDetail(SQUID_ERR_SSL_HANDSHAKE, server_cert, NULL);
        X509_free(server_cert);
    }

    if (ssl_lib_error != SSL_ERROR_NONE)
        anErr->detail->setLibError(ssl_lib_error);
#endif

    noteNegotiationDone(anErr);
    bail(anErr);
}