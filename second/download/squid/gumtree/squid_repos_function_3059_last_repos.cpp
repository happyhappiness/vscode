void
ConnStateData::getSslContextDone(Security::ContextPointer &ctx, bool isNew)
{
    // Try to add generated ssl context to storage.
    if (port->generateHostCertificates && isNew) {

        if (ctx && (signAlgorithm == Ssl::algSignTrusted)) {
            Ssl::chainCertificatesToSSLContext(ctx, *port);
        } else if (signAlgorithm == Ssl::algSignTrusted) {
            debugs(33, DBG_IMPORTANT, "WARNING: can not add signing certificate to SSL context chain because SSL context chain is invalid!");
        }
        //else it is self-signed or untrusted do not attrach any certificate

        Ssl::LocalContextStorage *ssl_ctx_cache = Ssl::TheGlobalContextStorage.getLocalStorage(port->s);
        assert(sslBumpCertKey.size() > 0 && sslBumpCertKey[0] != '\0');
        if (ctx) {
            if (!ssl_ctx_cache || !ssl_ctx_cache->add(sslBumpCertKey.termedBuf(), new Security::ContextPointer(ctx))) {
                // If it is not in storage delete after using. Else storage deleted it.
                fd_table[clientConnection->fd].dynamicTlsContext = ctx;
            }
        } else {
            debugs(33, 2, HERE << "Failed to generate SSL cert for " << sslConnectHostOrIp);
        }
    }

    // If generated ssl context = NULL, try to use static ssl context.
    if (!ctx) {
        if (!port->secure.staticContext) {
            debugs(83, DBG_IMPORTANT, "Closing " << clientConnection->remote << " as lacking TLS context");
            clientConnection->close();
            return;
        } else {
            debugs(33, 5, "Using static TLS context.");
            ctx = port->secure.staticContext;
        }
    }

    if (!httpsCreate(clientConnection, ctx))
        return;

    // bumped intercepted conns should already have Config.Timeout.request set
    // but forwarded connections may only have Config.Timeout.lifetime. [Re]set
    // to make sure the connection does not get stuck on non-SSL clients.
    typedef CommCbMemFunT<ConnStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall = JobCallback(33, 5, TimeoutDialer,
                                     this, ConnStateData::requestTimeout);
    commSetConnTimeout(clientConnection, Config.Timeout.request, timeoutCall);

    switchedToHttps_ = true;

    auto ssl = fd_table[clientConnection->fd].ssl.get();
    BIO *b = SSL_get_rbio(ssl);
    Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(BIO_get_data(b));
    bio->setReadBufData(inBuf);
    inBuf.clear();
    clientNegotiateSSL(clientConnection->fd, this);
}