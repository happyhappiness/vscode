bool
ConnStateData::getSslContextDone(SSL_CTX * sslContext, bool isNew)
{
    // Try to add generated ssl context to storage.
    if (port->generateHostCertificates && isNew) {
        Ssl::LocalContextStorage & ssl_ctx_cache(Ssl::TheGlobalContextStorage.getLocalStorage(port->s));
        if (sslContext && sslHostName != "") {
            if (!ssl_ctx_cache.add(sslHostName.termedBuf(), sslContext)) {
                // If it is not in storage delete after using. Else storage deleted it.
                fd_table[fd].dynamicSslContext = sslContext;
            }
        } else {
            debugs(33, 2, HERE << "Failed to generate SSL cert for " << sslHostName);
        }
    }

    // If generated ssl context = NULL, try to use static ssl context.
    if (!sslContext) {
        if (!port->staticSslContext) {
            debugs(83, 1, "Closing SSL FD " << fd << " as lacking SSL context");
            comm_close(fd);
            return false;
        } else {
            debugs(33, 5, HERE << "Using static ssl context.");
            sslContext = port->staticSslContext.get();
        }
    }

    // fake a ConnectionDetail object; XXX: make ConnState a ConnectionDetail?
    ConnectionDetail detail;
    detail.me = me;
    detail.peer = peer;

    SSL *ssl = NULL;
    if (!(ssl = httpsCreate(fd, &detail, sslContext)))
        return false;

    // commSetTimeout() was called for this request before we switched.

    // Disable the client read handler until peer selection is complete
    commSetSelect(fd, COMM_SELECT_READ, NULL, NULL, 0);

    commSetSelect(fd, COMM_SELECT_READ, clientNegotiateSSL, this, 0);

    switchedToHttps_ = true;
    return true;
}