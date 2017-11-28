void
ConnStateData::getSslContextStart()
{
    assert(areAllContextsForThisConnection());
    freeAllContexts();
    /* careful: freeAllContexts() above frees request, host, etc. */

    if (port->generateHostCertificates) {
        Ssl::CertificateProperties certProperties;
        buildSslCertGenerationParams(certProperties);
        sslBumpCertKey = certProperties.dbKey().c_str();
        assert(sslBumpCertKey.defined() && sslBumpCertKey[0] != '\0');

        debugs(33, 5, HERE << "Finding SSL certificate for " << sslBumpCertKey << " in cache");
        Ssl::LocalContextStorage *ssl_ctx_cache = Ssl::TheGlobalContextStorage.getLocalStorage(port->s);
        SSL_CTX * dynCtx = NULL;
        Ssl::SSL_CTX_Pointer *cachedCtx = ssl_ctx_cache ? ssl_ctx_cache->get(sslBumpCertKey.termedBuf()) : NULL;
        if (cachedCtx && (dynCtx = cachedCtx->get())) {
            debugs(33, 5, HERE << "SSL certificate for " << sslBumpCertKey << " have found in cache");
            if (Ssl::verifySslCertificate(dynCtx, certProperties)) {
                debugs(33, 5, HERE << "Cached SSL certificate for " << sslBumpCertKey << " is valid");
                getSslContextDone(dynCtx);
                return;
            } else {
                debugs(33, 5, HERE << "Cached SSL certificate for " << sslBumpCertKey << " is out of date. Delete this certificate from cache");
                if (ssl_ctx_cache)
                    ssl_ctx_cache->del(sslBumpCertKey.termedBuf());
            }
        } else {
            debugs(33, 5, HERE << "SSL certificate for " << sslBumpCertKey << " haven't found in cache");
        }

#if USE_SSL_CRTD
        try {
            debugs(33, 5, HERE << "Generating SSL certificate for " << certProperties.commonName << " using ssl_crtd.");
            Ssl::CrtdMessage request_message(Ssl::CrtdMessage::REQUEST);
            request_message.setCode(Ssl::CrtdMessage::code_new_certificate);
            request_message.composeRequest(certProperties);
            debugs(33, 5, HERE << "SSL crtd request: " << request_message.compose().c_str());
            Ssl::Helper::GetInstance()->sslSubmit(request_message, sslCrtdHandleReplyWrapper, this);
            return;
        } catch (const std::exception &e) {
            debugs(33, DBG_IMPORTANT, "ERROR: Failed to compose ssl_crtd " <<
                   "request for " << certProperties.commonName <<
                   " certificate: " << e.what() << "; will now block to " <<
                   "generate that certificate.");
            // fall through to do blocking in-process generation.
        }
#endif // USE_SSL_CRTD

        debugs(33, 5, HERE << "Generating SSL certificate for " << certProperties.commonName);
        dynCtx = Ssl::generateSslContext(certProperties, *port);
        getSslContextDone(dynCtx, true);
        return;
    }
    getSslContextDone(NULL);
}