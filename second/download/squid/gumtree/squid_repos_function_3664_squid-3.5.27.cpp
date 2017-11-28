void
ConnStateData::getSslContextDone(SSL_CTX * sslContext, bool isNew)
{
    // Try to add generated ssl context to storage.
    if (port->generateHostCertificates && isNew) {

        if (sslContext && (signAlgorithm == Ssl::algSignTrusted)) {
            Ssl::chainCertificatesToSSLContext(sslContext, *port);
        } else if (signAlgorithm == Ssl::algSignTrusted) {
            debugs(33, DBG_IMPORTANT, "WARNING: can not add signing certificate to SSL context chain because SSL context chain is invalid!");
        }
        //else it is self-signed or untrusted do not attrach any certificate

        Ssl::LocalContextStorage *ssl_ctx_cache = Ssl::TheGlobalContextStorage.getLocalStorage(port->s);
        assert(sslBumpCertKey.size() > 0 && sslBumpCertKey[0] != '\0');
        if (sslContext) {
            if (!ssl_ctx_cache || !ssl_ctx_cache->add(sslBumpCertKey.termedBuf(), new Ssl::SSL_CTX_Pointer(sslContext))) {
                // If it is not in storage delete after using. Else storage deleted it.
                fd_table[clientConnection->fd].dynamicSslContext = sslContext;
            }
        } else {
            debugs(33, 2, HERE << "Failed to generate SSL cert for " << sslConnectHostOrIp);
        }
    }

    // If generated ssl context = NULL, try to use static ssl context.
    if (!sslContext) {
        if (!port->staticSslContext) {
            debugs(83, DBG_IMPORTANT, "Closing SSL " << clientConnection->remote << " as lacking SSL context");
            clientConnection->close();
            return;
        } else {
            debugs(33, 5, HERE << "Using static ssl context.");
            sslContext = port->staticSslContext.get();
        }
    }

    if (!httpsCreate(clientConnection, sslContext))
        return;

    // bumped intercepted conns should already have Config.Timeout.request set
    // but forwarded connections may only have Config.Timeout.lifetime. [Re]set
    // to make sure the connection does not get stuck on non-SSL clients.
    typedef CommCbMemFunT<ConnStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall = JobCallback(33, 5, TimeoutDialer,
                                     this, ConnStateData::requestTimeout);
    commSetConnTimeout(clientConnection, Config.Timeout.request, timeoutCall);

    // Disable the client read handler until CachePeer selection is complete
    Comm::SetSelect(clientConnection->fd, COMM_SELECT_READ, NULL, NULL, 0);
    Comm::SetSelect(clientConnection->fd, COMM_SELECT_READ, clientNegotiateSSL, this, 0);
    switchedToHttps_ = true;
}