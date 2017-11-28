SSL_CTX *
sslCreateServerContext(AnyP::PortCfg &port)
{
    int ssl_error;
    SSL_CTX *sslContext;
    const char *keyfile, *certfile;
    certfile = port.cert;
    keyfile = port.key;

    ssl_initialize();

    if (!keyfile)
        keyfile = certfile;

    if (!certfile)
        certfile = keyfile;

    sslContext = SSL_CTX_new(port.contextMethod);

    if (sslContext == NULL) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_CRITICAL, "ERROR: Failed to allocate SSL context: " << ERR_error_string(ssl_error, NULL));
        return NULL;
    }

    if (!SSL_CTX_use_certificate(sslContext, port.signingCert.get())) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL certificate '" << certfile << "': " << ERR_error_string(ssl_error, NULL));
        SSL_CTX_free(sslContext);
        return NULL;
    }

    if (!SSL_CTX_use_PrivateKey(sslContext, port.signPkey.get())) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL private key '" << keyfile << "': " << ERR_error_string(ssl_error, NULL));
        SSL_CTX_free(sslContext);
        return NULL;
    }

    Ssl::addChainToSslContext(sslContext, port.certsToChain.get());

    /* Alternate code;
        debugs(83, DBG_IMPORTANT, "Using certificate in " << certfile);

        if (!SSL_CTX_use_certificate_chain_file(sslContext, certfile)) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL certificate '" << certfile << "': " << ERR_error_string(ssl_error, NULL));
            SSL_CTX_free(sslContext);
            return NULL;
        }

        debugs(83, DBG_IMPORTANT, "Using private key in " << keyfile);
        ssl_ask_password(sslContext, keyfile);

        if (!SSL_CTX_use_PrivateKey_file(sslContext, keyfile, SSL_FILETYPE_PEM)) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL private key '" << keyfile << "': " << ERR_error_string(ssl_error, NULL));
            SSL_CTX_free(sslContext);
            return NULL;
        }

        debugs(83, 5, "Comparing private and public SSL keys.");

        if (!SSL_CTX_check_private_key(sslContext)) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: SSL private key '" << certfile << "' does not match public key '" <<
                   keyfile << "': " << ERR_error_string(ssl_error, NULL));
            SSL_CTX_free(sslContext);
            return NULL;
        }
    */

    if (!configureSslContext(sslContext, port)) {
        debugs(83, DBG_CRITICAL, "ERROR: Configuring static SSL context");
        SSL_CTX_free(sslContext);
        return NULL;
    }

    return sslContext;
}