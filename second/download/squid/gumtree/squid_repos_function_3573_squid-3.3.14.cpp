void
ConnStateData::getSslContextDone(SSL_CTX * sslContext, bool isNew)
{
    // Try to add generated ssl context to storage.
    if (port->generateHostCertificates && isNew) {

        if (signAlgorithm == Ssl::algSignTrusted) {
            // Add signing certificate to the certificates chain
            X509 *cert = port->signingCert.get();
            if (SSL_CTX_add_extra_chain_cert(sslContext, cert)) {
                // increase the certificate lock
                CRYPTO_add(&(cert->references),1,CRYPTO_LOCK_X509);
            } else {
                const int ssl_error = ERR_get_error();
                debugs(33, DBG_IMPORTANT, "WARNING: can not add signing certificate to SSL context chain: " << ERR_error_string(ssl_error, NULL));
            }
            Ssl::addChainToSslContext(sslContext, port->certsToChain.get());
        }
        //else it is self-signed or untrusted do not attrach any certificate

        Ssl::LocalContextStorage & ssl_ctx_cache(Ssl::TheGlobalContextStorage.getLocalStorage(port->s));
        assert(sslBumpCertKey.defined() && sslBumpCertKey[0] != '\0');
        if (sslContext) {
            if (!ssl_ctx_cache.add(sslBumpCertKey.termedBuf(), sslContext)) {
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

    SSL *ssl = NULL;
    if (!(ssl = httpsCreate(clientConnection, sslContext)))
        return;

    // commSetConnTimeout() was called for this request before we switched.

    // Disable the client read handler until CachePeer selection is complete
    Comm::SetSelect(clientConnection->fd, COMM_SELECT_READ, NULL, NULL, 0);
    Comm::SetSelect(clientConnection->fd, COMM_SELECT_READ, clientNegotiateSSL, this, 0);
    switchedToHttps_ = true;
}