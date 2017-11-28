bool
configureSslContext(Security::ContextPointer &ctx, AnyP::PortCfg &port)
{
    int ssl_error;
    SSL_CTX_set_options(ctx.get(), port.secure.parsedOptions);

    if (port.sslContextSessionId)
        SSL_CTX_set_session_id_context(ctx.get(), (const unsigned char *)port.sslContextSessionId, strlen(port.sslContextSessionId));

    if (port.secure.parsedFlags & SSL_FLAG_NO_SESSION_REUSE) {
        SSL_CTX_set_session_cache_mode(ctx.get(), SSL_SESS_CACHE_OFF);
    }

    if (Config.SSL.unclean_shutdown) {
        debugs(83, 5, "Enabling quiet SSL shutdowns (RFC violation).");

        SSL_CTX_set_quiet_shutdown(ctx.get(), 1);
    }

    if (!port.secure.sslCipher.isEmpty()) {
        debugs(83, 5, "Using chiper suite " << port.secure.sslCipher << ".");

        if (!SSL_CTX_set_cipher_list(ctx.get(), port.secure.sslCipher.c_str())) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to set SSL cipher suite '" << port.secure.sslCipher << "': " << Security::ErrorString(ssl_error));
            return false;
        }
    }

    maybeSetupRsaCallback(ctx);

    port.secure.updateContextEecdh(ctx);
    port.secure.updateContextCa(ctx);

    if (port.clientCA.get()) {
        ERR_clear_error();
        if (STACK_OF(X509_NAME) *clientca = SSL_dup_CA_list(port.clientCA.get())) {
            SSL_CTX_set_client_CA_list(ctx.get(), clientca);
        } else {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to dupe the client CA list: " << Security::ErrorString(ssl_error));
            return false;
        }

        if (port.secure.parsedFlags & SSL_FLAG_DELAYED_AUTH) {
            debugs(83, 9, "Not requesting client certificates until acl processing requires one");
            SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_NONE, NULL);
        } else {
            debugs(83, 9, "Requiring client certificates.");
            SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, ssl_verify_cb);
        }

        port.secure.updateContextCrl(ctx);

    } else {
        debugs(83, 9, "Not requiring any client certificates");
        SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_NONE, NULL);
    }

    if (port.secure.parsedFlags & SSL_FLAG_DONT_VERIFY_DOMAIN)
        SSL_CTX_set_ex_data(ctx.get(), ssl_ctx_ex_index_dont_verify_domain, (void *) -1);

    Security::SetSessionCacheCallbacks(ctx);

    return true;
}