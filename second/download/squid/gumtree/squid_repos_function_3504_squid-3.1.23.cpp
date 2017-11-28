bool
ConnStateData::getSslContextStart()
{
    char const * host = sslHostName.termedBuf();
    if (port->generateHostCertificates && host && strcmp(host, "") != 0) {
        debugs(33, 5, HERE << "Finding SSL certificate for " << host << " in cache");
        Ssl::LocalContextStorage & ssl_ctx_cache(Ssl::TheGlobalContextStorage.getLocalStorage(port->s));
        SSL_CTX * dynCtx = ssl_ctx_cache.find(host);
        if (dynCtx) {
            debugs(33, 5, HERE << "SSL certificate for " << host << " have found in cache");
            if (Ssl::verifySslCertificateDate(dynCtx)) {
                debugs(33, 5, HERE << "Cached SSL certificate for " << host << " is valid");
                return getSslContextDone(dynCtx);
            } else {
                debugs(33, 5, HERE << "Cached SSL certificate for " << host << " is out of date. Delete this certificate from cache");
                ssl_ctx_cache.remove(host);
            }
        } else {
            debugs(33, 5, HERE << "SSL certificate for " << host << " haven't found in cache");
        }

#ifdef USE_SSL_CRTD
        debugs(33, 5, HERE << "Generating SSL certificate for " << host << " using ssl_crtd.");
        Ssl::CrtdMessage request_message;
        request_message.setCode(Ssl::CrtdMessage::code_new_certificate);
        Ssl::CrtdMessage::BodyParams map;
        map.insert(std::make_pair(Ssl::CrtdMessage::param_host, host));
        std::string bufferToWrite;
        Ssl::writeCertAndPrivateKeyToMemory(port->signingCert, port->signPkey, bufferToWrite);
        request_message.composeBody(map, bufferToWrite);
        Ssl::Helper::GetInstance()->sslSubmit(request_message, sslCrtdHandleReplyWrapper, this);
        return true;
#else
        debugs(33, 5, HERE << "Generating SSL certificate for " << host);
        dynCtx = Ssl::generateSslContext(host, port->signingCert, port->signPkey);
        return getSslContextDone(dynCtx, true);
#endif //USE_SSL_CRTD
    }
    return getSslContextDone(NULL);
}