bool
ConnStateData::handleIdleClientPinnedTlsRead()
{
    // A ready-for-reading connection means that the TLS server either closed
    // the connection, sent us some unexpected HTTP data, or started TLS
    // renegotiations. We should close the connection except for the last case.

    Must(pinning.serverConnection != NULL);
    SSL *ssl = fd_table[pinning.serverConnection->fd].ssl;
    if (!ssl)
        return false;

    char buf[1];
    const int readResult = SSL_read(ssl, buf, sizeof(buf));

    if (readResult > 0 || SSL_pending(ssl) > 0) {
        debugs(83, 2, pinning.serverConnection << " TLS application data read");
        return false;
    }

    switch(const int error = SSL_get_error(ssl, readResult)) {
    case SSL_ERROR_WANT_WRITE:
        debugs(83, DBG_IMPORTANT, pinning.serverConnection << " TLS SSL_ERROR_WANT_WRITE request for idle pinned connection");
    // fall through to restart monitoring, for now
    case SSL_ERROR_NONE:
    case SSL_ERROR_WANT_READ:
        startPinnedConnectionMonitoring();
        return true;

    default:
        debugs(83, 2, pinning.serverConnection << " TLS error: " << error);
        return false;
    }

    // not reached
    return true;
}