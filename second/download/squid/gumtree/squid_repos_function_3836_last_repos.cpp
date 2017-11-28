bool
Ssl::InitServerContext(Security::ContextPointer &ctx, AnyP::PortCfg &port)
{
    if (!ctx)
        return false;

    if (!SSL_CTX_use_certificate(ctx.get(), port.signingCert.get())) {
        const int ssl_error = ERR_get_error();
        const auto &keys = port.secure.certs.front();
        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire TLS certificate '" << keys.certFile << "': " << Security::ErrorString(ssl_error));
        return false;
    }

    if (!SSL_CTX_use_PrivateKey(ctx.get(), port.signPkey.get())) {
        const int ssl_error = ERR_get_error();
        const auto &keys = port.secure.certs.front();
        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire TLS private key '" << keys.privateKeyFile << "': " << Security::ErrorString(ssl_error));
        return false;
    }

    Ssl::addChainToSslContext(ctx, port.certsToChain.get());

    /* Alternate code;
        debugs(83, DBG_IMPORTANT, "Using certificate in " << certfile);

        if (!SSL_CTX_use_certificate_chain_file(ctx.get(), certfile)) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL certificate '" << certfile << "': " << Security::ErrorString(ssl_error));
            return false;
        }

        debugs(83, DBG_IMPORTANT, "Using private key in " << keyfile);
        ssl_ask_password(ctx.get(), keyfile);

        if (!SSL_CTX_use_PrivateKey_file(ctx.get(), keyfile, SSL_FILETYPE_PEM)) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL private key '" << keyfile << "': " << Security::ErrorString(ssl_error));
            return false;
        }

        debugs(83, 5, "Comparing private and public SSL keys.");

        if (!SSL_CTX_check_private_key(ctx.get())) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: SSL private key '" << certfile << "' does not match public key '" <<
                   keyfile << "': " << Security::ErrorString(ssl_error));
            return false;
        }
    */

    if (!configureSslContext(ctx, port)) {
        debugs(83, DBG_CRITICAL, "ERROR: Configuring static SSL context");
        return false;
    }

    return true;
}